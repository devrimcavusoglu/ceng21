#include "the8.h"
#include <filesystem>
#include <fstream>
#include <chrono>

namespace fs = std::filesystem;

template <class T>
void print_vec(const std::vector<T> &vec, int size = 0) {
	if (size == 0 or size > vec.size())
		size = vec.size();

	for (int i = 0; i < size; i++) {
		std::cout << vec[i] << " ";
		if ((i+1) % 20 == 0)
			std::cout << std::endl;
	}
	if (size < vec.size())
		std::cout << "..." << std::endl;
	else
		std::cout << std::endl;
}

void print_test_begin(std::string test_name) {
    std::cout << "#### TEST " << test_name << " BEGIN ####\n";
}

void print_test_end() {
    std::cout << "############### TEST END ###############\n";
}

template <
    class result_t   = std::chrono::milliseconds,
    class clock_t    = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start) {
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

std::string readText(fs::path path)
{
    // Open the stream to 'lock' the file.
    std::ifstream f(path, std::ios::in | std::ios::binary);

    // Obtain the size of the file.
    const auto sz = fs::file_size(path);

    // Create a buffer.
    std::string result(sz, '\0');

    // Read the whole file into the buffer.
    f.read(result.data(), sz);

    return result;
}


std::vector<std::string> readPatterns(fs::path path) {
	std::vector<std::string> patterns;

	std::ifstream file(path);
	if (file.is_open()) {
	    std::string line;
	    while (std::getline(file, line)) {
	    	patterns.push_back(line.c_str());
	    }
	    file.close();
	}
	return patterns;
}


std::vector<int> readOutput(fs::path path) {
	std::vector<int> shifts;

	std::ifstream file(path);
	if (file.is_open()) {
	    std::string line;
	    while (std::getline(file, line)) {
	    	int val = std::stoi(line.c_str());
	    	shifts.push_back(val);
	    }
	    file.close();
	}
	return shifts;
}


template <class T>
bool is_equal(std::vector<T> &v1, std::vector<T> &v2) {
	int i = 0;
	int n = v1.size();
	int m  = v2.size();
	if (n != m)
		return false;

	while (i < n) {
		if (v1[i] != v2[i])
			return false;
		i++;
	}

	return true;
}


void test_case_1() {
    print_test_begin("case 1");
	std::string text = "abcde";
	std::vector<std::string> patterns = {"ab", "ed"};
	std::vector<int> output = the8(text, patterns);
	std::cout << ">>> Actual Output shifts (first 10 elem.)\n";
	print_vec(output);
	std::cout << ">>> Desired Output shifts (first 10 elem.)\n";
	std::cout << "0\n";
	print_test_end();
}

void test_case_2() {
    print_test_begin("case 2");
	std::string text = "abcdefgijbcde";
	std::vector<std::string> patterns = {"bcde", "defg", "qwer", "uutz"};
	std::vector<int> output = the8(text, patterns);
	std::cout << ">>> Actual Output shifts (first 10 elem.)\n";
	print_vec(output);
	std::cout << ">>> Desired Output shifts (first 10 elem.)\n";
	std::cout << "1 3 9\n";
	print_test_end();
}


void test_small_input() {
	print_test_begin("Small input");
	std::string text = readText("sample-io/text_small");
	std::vector<std::string> patterns = readPatterns("sample-io/patterns_small");
	std::cout << "Text size = " << text.length() << std::endl;
	std::cout << "Pattern size = " << patterns.size() << std::endl;
	std::cout << "Pattern string length = " << patterns[0].length() << std::endl;
	
	auto start = std::chrono::steady_clock::now();
	std::vector<int> output = the8(text, patterns);
	std::cout << "Elapsed(ms)=" << since(start).count() << std::endl;
	std::cout << "Match count = " << output.size() << std::endl;

	std::vector<int> desired_out = readOutput("sample-io/output_small");

	std::cout << ">>> Actual Output shifts (first 10 elem.)\n";
	print_vec(output, 10);	
	std::cout << ">>> Desired Output shifts (first 10 elem.)\n";
	print_vec(desired_out, 10);

	std::string passed = is_equal(output, desired_out) ? "YES" : "NO";
	std::cout << "Actual == Output ? " << passed << std::endl;
	print_test_end();
}


void test_big_input() {
	print_test_begin("Big input");
	std::string text = readText("sample-io/text_big");
	std::vector<std::string> patterns = readPatterns("sample-io/patterns_big");
	std::cout << "Text size = " << text.length() << std::endl;
	std::cout << "Pattern size = " << patterns.size() << std::endl;
	std::cout << "Pattern string length = " << patterns[0].length() << std::endl;

	auto start = std::chrono::steady_clock::now();
	std::vector<int> output = the8(text, patterns);
	std::cout << "Elapsed(ms)=" << since(start).count() << std::endl;
	std::vector<int> desired_out = readOutput("sample-io/output_big");
	std::cout << "Match count = " << output.size() << std::endl;

	std::cout << ">>> Actual Output shifts (first 10 elem.)\n";
	print_vec(output, 10);	
	std::cout << ">>> Desired Output shifts (first 10 elem.)\n";
	print_vec(desired_out, 10);

	std::string passed = is_equal(output, desired_out) ? "YES" : "NO";
	std::cout << "Actual == Output ? " << passed << std::endl;
	print_test_end();
}


int main() {
	test_case_1();
	test_case_2();
	test_small_input();
	test_big_input();

	return 0;
}