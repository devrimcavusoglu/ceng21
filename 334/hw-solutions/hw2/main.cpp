#include <atomic>
#include <chrono>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>

#include "parser.hpp"


// Init ProperPrivates
std::vector<ProperPrivate> P;
std::vector<SneakySmoker> SS;

// Init Grid
std::vector<std::vector<int>> G;

// Init Lock
std::vector<std::unique_ptr<std::binary_semaphore>> S;

// Commands signals part-2
std::atomic<bool> should_continue{true};
std::atomic<bool> wait_for_all{true};


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


template <class T>
struct thread_args_t {
    T *pvt;
};



// Returns elapsed time until now from ts_start
int time_elapsed(int64_t ts_start) {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - ts_start;
}


// Starts sending commands (main thread)
void fire_commands(pthread_t *thr_proper_privates, pthread_t *thr_sneaky_smokers, std::vector<Command> &commands, int64_t ts_start) {
	for (int i = 0; i < commands.size(); i++) {
		while (time_elapsed(ts_start) <= commands[i].notify_time);
		switch (commands[i].action) {
			case hw2_actions::ORDER_BREAK:
				if (should_continue.load()) {
					wait_for_all.store(true);
					should_continue.store(false);
					for (int t = 0; t < P.size(); t++)
						pthread_kill(thr_proper_privates[t], SIGUSR1);
					hw2_notify(commands[i].action, 0, 0, 0);
					wait_for_all.store(false);
				}
				break;

			case hw2_actions::ORDER_STOP:
				hw2_notify(commands[i].action, 0, 0, 0);
				for (int t = 0; t < P.size(); t++) {
					P[t].unlock_area(S);
					P[t].stopped = true;
					pthread_cancel(thr_proper_privates[t]);
					hw2_notify(hw2_actions::PROPER_PRIVATE_STOPPED, P[t].id, 0, 0);
				}
				for (int t = 0; t < SS.size(); t++) {
					SS[t].unlock_area(S);
					pthread_cancel(thr_sneaky_smokers[t]);
					hw2_notify(hw2_actions::SNEAKY_SMOKER_STOPPED, SS[t].id, 0, 0);
				}
				break;
			default:
				if (!should_continue.load()) {
					should_continue.store(true);
					hw2_notify(commands[i].action, 0, 0, 0);
					should_continue.notify_all();
				}
				break;
		}
	}
}


void *start_smoking(void* arguments) {
	thread_args_t<SneakySmoker> *args = (thread_args_t<SneakySmoker>*)arguments;
	SneakySmoker *smoker = args->pvt;
	// Notify ready
	hw2_notify(hw2_actions::SNEAKY_SMOKER_CREATED, smoker->id, 0, 0);
	smoker->start_working(G, S);
    return NULL;
}



void *start_collecting(void* arguments) {
	thread_args_t<ProperPrivate> *args = (thread_args_t<ProperPrivate>*)arguments;
	ProperPrivate *properpvt = args->pvt;
	// Notify ready
	hw2_notify(hw2_actions::PROPER_PRIVATE_CREATED, properpvt->id, 0, 0);
	properpvt->start_working(G, S);
    return NULL;
}


static void signalHandler(int signum) {
	wait_for_all.wait(true);
	// printf("I'm in signal handler (%lu)\n", pthread_self());
	ProperPrivate *p = private_by_tid<ProperPrivate>(P, pthread_self());
	if (!p) { // error or smoker
		// printf("I'm NULL by handler (%lu)\n", pthread_self());
		return;
	}
	// printf("I'm continuing (%lu)\n", pthread_self());
	if (signum == SIGUSR1) {
		usleep(10);
		if (p->is_working() or p->is_waiting()) {
			p->unlock_area(S);
			hw2_notify(hw2_actions::PROPER_PRIVATE_TOOK_BREAK, p->id, 0, 0);
		}
		should_continue.wait(false);
		if (!p->is_working()) {
			hw2_notify(hw2_actions::PROPER_PRIVATE_CONTINUED, p->id, 0, 0);
		}
	}
}


int main() {
	Parser parser;
	parser.parse();

	std::cout << "=============OUT===========\n";
	std::cout << "Grid size: " << parser.grid_size[0] << " x " << parser.grid_size[1] << std::endl;
	print_2darr(parser.grid);
	std::cout << "ProperPrivates: " << parser.privates.size() << std::endl;
	print_arr(parser.privates);
	std::cout << "SneakySmokers: " << parser.sneaky_smokers.size() << std::endl;
	print_arr(parser.sneaky_smokers);
	std::cout << "Commands: " << parser.commands.size() << std::endl;
	for (int i = 0; i < parser.commands.size(); i++) {
		std::string cmd_str;
		if (parser.commands[i].action == hw2_actions::ORDER_STOP)
			cmd_str = "STOP";
		else if (parser.commands[i].action == hw2_actions::ORDER_BREAK)
			cmd_str = "BREAK";
		else
			cmd_str = "CONTINUE";
		std::cout << "Command '" << cmd_str << "' at msec " << parser.commands[i].notify_time << std::endl;
	}
	std::cout << "=============OUT===========\n";

	for (int i = 0; i < parser.grid_size[0]; i++) {
		for (int j = 0; j < parser.grid_size[1]; j++) {
			S.emplace_back(std::make_unique<std::binary_semaphore>(1));
		}
	}
	G = parser.grid;
	P = parser.privates;
	SS = parser.sneaky_smokers;


	// see https://stackoverflow.com/a/62857783
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sa.sa_handler = signalHandler;
	sigaction(SIGUSR1, &sa, NULL);

	// initialize notifier & get start_time
	hw2_init_notifier();
	int64_t ts_start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	// Multi-threading
	// https://stackoverflow.com/a/15717075
	pthread_t thr_proper_privates[P.size()];
	pthread_t thr_sneaky_smokers[P.size()];
	thread_args_t<ProperPrivate> pp_args[P.size()];
	thread_args_t<SneakySmoker> ss_args[SS.size()];
	int rc;

	for(int i = 0; i < P.size(); i++ ) {
		pp_args[i].pvt = &P[i];
		rc = pthread_create(&thr_proper_privates[i], NULL, &start_collecting, &pp_args[i]);
		if (rc) {
		 std::cout << "Error:unable to create thread," << rc << std::endl;
		 exit(-1);
		}
	}

	for(int i = 0; i < SS.size(); i++ ) {
		ss_args[i].pvt = &SS[i];
		rc = pthread_create(&thr_sneaky_smokers[i], NULL, &start_smoking, &ss_args[i]);
		if (rc) {
		 std::cerr << "Error:unable to create thread," << rc << std::endl;
		 exit(-1);
		}
	}

	fire_commands(thr_proper_privates, thr_sneaky_smokers, parser.commands, ts_start);

	for (int i = 0; i < P.size(); i++) {
		pthread_join(thr_proper_privates[i], NULL);
	}
	for (int i = 0; i < SS.size(); i++) {
		pthread_join(thr_sneaky_smokers[i], NULL);
	}

	std::cout << "=================\n";
	print_2darr(G);
	std::cout << "=================\n";
	return 0;
}
