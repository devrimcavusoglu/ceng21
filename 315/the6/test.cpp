#include "the6.h"


template <class T>
void print_vector(std::vector<T> vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

int test_case_1() {
	std::cout << "######## Test case 1 BEGIN ########\n";
	int N = 5;
	std::vector<std::pair<int, int>> pairs;
	std::pair<int, int> p0 = {0,2};
	std::pair<int, int> p1 = {0,1};
	std::pair<int, int> p2 = {1,3};
	std::pair<int, int> p3 = {1,2};
	std::pair<int, int> p4 = {2,3};
	pairs.push_back(p0);
	pairs.push_back(p1);
	pairs.push_back(p2);
	pairs.push_back(p3);
	pairs.push_back(p4);

	std::pair<bool, std::vector<int>> res;
	res = RaceResult(N, pairs);

	std::cout << "Result: " << res.first << std::endl;
	print_vector(res.second);
	std::cout << "######## Test case 1 END ########\n";
}


int test_case_2() {
	/*
	* Input: N=5 
	* updates=[{0, 2}, {0, 1}, {1, 3}, {1, 2}, {2, 3}, {3, 0}]
	*/
	std::cout << "######## Test case 2 BEGIN ########\n";
	int N = 5;
	std::vector<std::pair<int, int>> pairs;
	std::pair<int, int> p0 = {0,2};
	std::pair<int, int> p1 = {0,1};
	std::pair<int, int> p2 = {1,3};
	std::pair<int, int> p3 = {1,2};
	std::pair<int, int> p4 = {2,3};
	std::pair<int, int> p5 = {3,0};
	pairs.push_back(p0);
	pairs.push_back(p1);
	pairs.push_back(p2);
	pairs.push_back(p3);
	pairs.push_back(p4);
	pairs.push_back(p5);

	std::pair<bool, std::vector<int>> res;
	res = RaceResult(N, pairs);

	std::cout << "Result: " << res.first << std::endl;
	print_vector(res.second);
	std::cout << "######## Test case 2 END ########\n";
}


int test_case_3() {
	/*
	* Input: N=10
	* updates=[{0, 5}, {1, 0}, {1, 7}, {2, 4}, {2, 0}, {3, 4}, {3, 5}, {3, 7}, {3, 6}, {4, 7}, {4, 1}, {6, 2}, {6, 5}, {6, 9}, {7, 9}, {7, 5}, {8, 3}]
	*/
	std::cout << "######## Test case 3 BEGIN ########\n";
	int N = 10;
	std::vector<std::pair<int, int>> pairs;
	std::pair<int, int> p0 = {0,5};
	std::pair<int, int> p1 = {1,0};
	std::pair<int, int> p2 = {1,7};
	std::pair<int, int> p3 = {2,4};
	std::pair<int, int> p4 = {3,4};
	std::pair<int, int> p5 = {3,5};
	std::pair<int, int> p6 = {3,7};
	std::pair<int, int> p7 = {3,6};
	std::pair<int, int> p8 = {4,7};
	std::pair<int, int> p9 = {4,1};
	std::pair<int, int> p10 = {6,2};
	std::pair<int, int> p11 = {6,5};
	std::pair<int, int> p12 = {6,9};
	std::pair<int, int> p13 = {7,9};
	std::pair<int, int> p14 = {7,5};
	std::pair<int, int> p15 = {8,3};

	pairs.push_back(p0);
	pairs.push_back(p1);
	pairs.push_back(p2);
	pairs.push_back(p3);
	pairs.push_back(p4);
	pairs.push_back(p5);
	pairs.push_back(p6);
	pairs.push_back(p7);
	pairs.push_back(p8);
	pairs.push_back(p9);
	pairs.push_back(p10);
	pairs.push_back(p11);
	pairs.push_back(p12);
	pairs.push_back(p13);
	pairs.push_back(p14);
	pairs.push_back(p15);

	std::pair<bool, std::vector<int>> res;
	res = RaceResult(N, pairs);

	std::cout << "Result: " << res.first << std::endl;
	print_vector(res.second);
	std::cout << "######## Test case 3 END ########\n";
}


int test_case_4() {
	/*
	* Input: N=10
	* updates=[{0, 5}, {1, 0}, {1, 7}, {2, 4}, {2, 0}, {3, 4}, {3, 5}, {3, 7}, {3, 6}, {4, 7}, {4, 1}, {6, 2}, {6, 5}, {6, 9}, {7, 9}, {7, 5}, {7, 3}, {8, 3}]
	*/
	std::cout << "######## Test case 4 BEGIN ########\n";
	int N = 10;
	std::vector<std::pair<int, int>> pairs;
	std::pair<int, int> p0 = {0,5};
	std::pair<int, int> p1 = {1,0};
	std::pair<int, int> p2 = {1,7};
	std::pair<int, int> p3 = {2,4};
	std::pair<int, int> p35 = {2,0};
	std::pair<int, int> p4 = {3,4};
	std::pair<int, int> p5 = {3,5};
	std::pair<int, int> p6 = {3,7};
	std::pair<int, int> p7 = {3,6};
	std::pair<int, int> p8 = {4,7};
	std::pair<int, int> p9 = {4,1};
	std::pair<int, int> p10 = {6,2};
	std::pair<int, int> p11 = {6,5};
	std::pair<int, int> p12 = {6,9};
	std::pair<int, int> p13 = {7,9};
	std::pair<int, int> p14 = {7,5};
	std::pair<int, int> p145 = {7,3};
	std::pair<int, int> p15 = {8,3};

	pairs.push_back(p0);
	pairs.push_back(p1);
	pairs.push_back(p2);
	pairs.push_back(p3);
	pairs.push_back(p35);
	pairs.push_back(p4);
	pairs.push_back(p5);
	pairs.push_back(p6);
	pairs.push_back(p7);
	pairs.push_back(p8);
	pairs.push_back(p9);
	pairs.push_back(p10);
	pairs.push_back(p11);
	pairs.push_back(p12);
	pairs.push_back(p13);
	pairs.push_back(p14);
	pairs.push_back(p145);
	pairs.push_back(p15);

	std::pair<bool, std::vector<int>> res;
	res = RaceResult(N, pairs);

	std::cout << "Result: " << res.first << std::endl;
	print_vector(res.second);
	std::cout << "######## Test case 4 END ########\n";
}


int main() {
	test_case_1();
	test_case_2();
	test_case_3();
	test_case_4();
}
