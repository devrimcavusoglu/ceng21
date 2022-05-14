#include <chrono>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>

#include "parser.hpp"


// Init Privates
std::vector<Private> P;

// Init Grid
std::vector<std::vector<int>> G;

// Init Lock
std::vector<std::unique_ptr<std::binary_semaphore>> S;

// Commands signals part-2
std::atomic<bool> should_continue{true};


template <class T>
void print_2darr(std::vector<std::vector<T> > &arr) {
	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < arr[0].size(); j++)
			std::cout << arr[i][j] << " ";
		std::cout << std::endl;
	}
}


template <class T>
void print_arr(std::vector<T> &arr) {
	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << std::endl;
	}
}


typedef struct thread_args {
    Private *pvt;
} thread_args_t;



// Returns elapsed time until now from ts_start
int time_elapsed(int64_t ts_start) {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - ts_start;
}


// Starts sending commands (main thread)
void fire_commands(pthread_t *threads, std::vector<Command> &commands, int64_t ts_start) {
	std::time_t t;

	for (int i = 0; i < commands.size(); i++) {
		while (time_elapsed(ts_start) <= commands[i].notify_time);
		hw2_notify(commands[i].action, 0, 0, 0);
		if (commands[i].action == hw2_actions::ORDER_BREAK) {
			if (should_continue.load()) {
				should_continue.store(false);
				for (int t = 0; t < P.size(); t++)
					pthread_kill(threads[t], SIGUSR1);
			}
		}
		else if (commands[i].action == hw2_actions::ORDER_STOP) {
			for (int t = 0; t < P.size(); t++) {
				P[t].unlock_area(S);
				hw2_notify(hw2_actions::PROPER_PRIVATE_STOPPED, P[t].id, 0, 0);
				should_continue.store(true);
				should_continue.notify_all();
				pthread_cancel(threads[t]);
			}
		}
		else {
			if (!should_continue.load()) {
				should_continue.store(true);
				should_continue.notify_all();
			}
		}
	}
}


void *start(void* arguments) {
	thread_args_t *args = (thread_args_t*)arguments;
	Private *pvt = args->pvt;
	// Notify ready
	hw2_notify(hw2_actions::PROPER_PRIVATE_CREATED, pvt->id, 0, 0);
	pvt->start_collecting(G, S);
    return NULL;
}


static void signalHandler(int signum) {
	std::cout << "Thread id: " << pthread_self() << std::endl;
	Private *p = private_by_tid(P, pthread_self());
	if (!p) // main thread
		return;
	std::cout << "Private tid: " << p->tid << std::endl;
	if (signum == SIGUSR1) {
		if (p->working())
			hw2_notify(hw2_actions::PROPER_PRIVATE_TOOK_BREAK, p->id, 0, 0);
		p->unlock_area(S);
		should_continue.wait(false);
		if (!p->working())
			hw2_notify(hw2_actions::PROPER_PRIVATE_CONTINUED, p->id, 0, 0);
	}
}


int main() {
	Parser parser;
	parser.parse();

	std::cout << "=============OUT===========\n";
	std::cout << "Grid size: " << parser.grid_size[0] << " x " << parser.grid_size[1] << std::endl;
	print_2darr(parser.grid);
	std::cout << "Privates: " << parser.privates.size() << std::endl;
	print_arr(parser.privates);
	std::cout << "Commands: " << parser.commands.size() << std::endl;
	for (int i = 0; i < parser.commands.size(); i++) {
		std::cout << "Command #" << parser.commands[i].action << " at msec " << parser.commands[i].notify_time << std::endl;
	}
	std::cout << "=============OUT===========\n";

	for (int i = 0; i < parser.grid_size[0]; i++) {
		for (int j = 0; j < parser.grid_size[1]; j++) {
			S.emplace_back(std::make_unique<std::binary_semaphore>(1));
		}
	}
	G = parser.grid;
	P = parser.privates;


	// see https://stackoverflow.com/a/62857783
	struct sigaction sa;
	// sigset_t set;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sa.sa_handler = signalHandler;
	sigaction(SIGUSR1, &sa, NULL);

	// initialize notifier & get start_time
	hw2_init_notifier();
	int64_t ts_start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	// Multi-threading
	// https://stackoverflow.com/a/15717075
	pthread_t threads[P.size()];
	thread_args_t args[P.size()];
	int rc;

	for(int i = 0; i < P.size(); i++ ) {
		args[i].pvt = &P[i];
		rc = pthread_create(&threads[i], NULL, &start, &args[i]);
		if (rc) {
		 std::cerr << "Error:unable to create thread," << rc << std::endl;
		 exit(-1);
		}
	}

	fire_commands(threads, parser.commands, ts_start);

	for (int i = 0; i < P.size(); i++) {
		pthread_join(threads[i], NULL);
	}


	std::cout << "=================\n";
	print_2darr(G);
	std::cout << "=================\n";
	return 0;
}
