#include <chrono>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>

#include "parser.hpp"


// Init Grid
std::vector<std::vector<int>> G;

// Init Lock
std::vector<std::unique_ptr<std::binary_semaphore>> S;

// Commands signals part-2
std::atomic<hw2_actions> take_action{hw2_actions::ORDER_CONTINUE};


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


typedef struct thread_arguments {
    Private *pvt;
} thargs_t;



// Returns elapsed time until now from ts_start
int time_elapsed(int64_t ts_start) {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - ts_start;
}


// Starts sending commands (main thread)
void fire_commands(pthread_t *threads, int n_threads, std::vector<Command> &commands, int64_t ts_start) {
	std::time_t t;

	for (int i = 0; i < commands.size(); i++) {
		while (time_elapsed(ts_start) <= commands[i].notify_time);
		if (commands[i].action == hw2_actions::ORDER_BREAK) {
			for (int t = 0; t < n_threads; t++)
				pthread_kill(threads[i], SIGABRT);
		}
		else if (commands[i].action == hw2_actions::ORDER_STOP) {
			for (int t = 0; t < n_threads; t++)
				pthread_kill(threads[i], SIGABRT);
		}
		hw2_notify(commands[i].action, 0, 0, 0);
	}
}

static void signalHandler(int signum) {
	if (signum == SIGABRT)
		std::cout << "Caught BREAK signal (" << signum << ")\n";
}


void *start(void* arguments) {
	sigset_t m;
    sigemptyset(&m);
    sigaddset(&m, SIGABRT);
    int signo;

	thargs_t *args = (thargs_t*)arguments;
	Private *pvt = args->pvt;
	// Notify ready
	hw2_notify(hw2_actions::PROPER_PRIVATE_CREATED, pvt->id, 0, 0);
	pvt->start_collecting(G, S, take_action);
    return NULL;
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

	// Lock for continue/stop
	//std::atomic<int> counter = parser.n_privates;

	for (int i = 0; i < parser.grid_size[0]; i++) {
		for (int j = 0; j < parser.grid_size[1]; j++) {
			S.emplace_back(std::make_unique<std::binary_semaphore>(1));
		}
	}
	G = parser.grid;

	struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = signalHandler;
    sigaction(SIGABRT, &sa, NULL);

    sigset_t n;
    sigemptyset(&n);
    sigaddset(&n, SIGABRT);

	// initialize notifier & get start_time
	hw2_init_notifier();
	int64_t ts_start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	// Multi-threading
	// https://stackoverflow.com/a/15717075
	pthread_t threads[parser.n_privates];
	thargs_t args[parser.n_privates];
	int rc;

	for(int i = 0; i < parser.n_privates; i++ ) {
		args[i].pvt = &parser.privates[i];
		rc = pthread_create(&threads[i], NULL, &start, &args[i]);
		if (rc) {
		 std::cerr << "Error:unable to create thread," << rc << std::endl;
		 exit(-1);
		}
	}

	fire_commands(threads, parser.n_privates, parser.commands, ts_start);

	for (int i = 0; i < parser.n_privates; i++) {
		pthread_join(threads[i], NULL);
	}

	std::cout << "=================\n";
	print_2darr(G);
	std::cout << "=================\n";
	return 0;
}
