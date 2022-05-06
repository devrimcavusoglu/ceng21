#include "parser.hpp"


// Init Grid
std::vector<std::vector<int>> G;

// Init Lock
std::vector<std::unique_ptr<std::binary_semaphore>> S;
std::binary_semaphore lock_turn{1};


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
    /*std::vector<std::vector<int>> *grid;
    std::vector<std::unique_ptr<std::binary_semaphore>> *sem;*/
} thargs_t;


void *start(void* arguments) {
	thargs_t *args = (thargs_t*)arguments;
	Private *pvt = args->pvt;
    pvt->start_collecting(G, S, lock_turn);
    return NULL;
}


int main() {
	// initialize notifier
	hw2_init_notifier();

	Parser parser;
	parser.parse();

	std::cout << "=============OUT===========\n";
	std::cout << "Grid size: " << parser.grid_size[0] << " x " << parser.grid_size[1] << std::endl;
	print_2darr(parser.grid);
	std::cout << "Privates: " << parser.privates.size() << std::endl;
	print_arr(parser.privates);
	std::cout << "=============OUT===========\n";

	// Init lock
	//std::vector<std::unique_ptr<std::binary_semaphore>> sem(parser.grid_size[0] * parser.grid_size[1]);

	for (int i = 0; i < parser.grid_size[0]; i++) {
		for (int j = 0; j < parser.grid_size[1]; j++) {
			S.emplace_back(std::make_unique<std::binary_semaphore>(1));
		}
	}
	G = parser.grid;

	// Multi-threading
	// https://stackoverflow.com/a/15717075
	pthread_t threads[parser.n_private];
	thargs_t args[parser.n_private];
	int rc;

	for(int i = 0; i < parser.n_private; i++ ) {
		args[i].pvt = &parser.privates[i];
		rc = pthread_create(&threads[i], NULL, &start, &args[i]);
		if (rc) {
		 std::cerr << "Error:unable to create thread," << rc << std::endl;
		 exit(-1);
		}
	}

	for (int i = 0; i < parser.n_private; i++) {
		pthread_join(threads[i], NULL);
	}

	std::cout << "=================\n";
	print_2darr(G);
	std::cout << "=================\n";
	return 0;
}
