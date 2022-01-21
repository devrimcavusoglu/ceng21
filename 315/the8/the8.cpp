#include "the8.h"

//DO NOT ADD OTHER LIBRARIES


// 5th Fermat Prime
long long MOD_VALUE = std::pow(2, std::pow(2, 5)) + 1;

long long hash(const std::string &str) {
    long long h = 0;
    for (unsigned int i = 0; i < str.length(); i++) {
        h += 17 * str[i];
    }

    h %= MOD_VALUE;
    if (h < 0)   /* in case of overflow */
        h += MOD_VALUE;

    return h;
}

template <class T>
bool vector_contains(const std::vector<T> &vec, T val) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == val)
            return true;
    }
    return false;
}


class RollingHash {
    public:
        RollingHash(const std::string &str, int pattern_length);
        void update();
        long long get_current_hash();
        std::string get_current_span();
    private:
        std::string text;
        std::string current_span;
        int window_size;
        long long hash_value;
        int start;
        int end;
};

RollingHash::RollingHash(const std::string &str, int pattern_length) {
    this->text = str;
    this->start = 0;
    this->window_size = pattern_length;
    this->end = pattern_length;
    this->current_span = str.substr(this->start, this->window_size);
    this->hash_value = hash(this->current_span);
}

void RollingHash::update() {
    if (this->end >= this->text.length())
        return;
    std::string old_char = this->text.substr(this->start, 1);
    std::string new_char = this->text.substr(this->end, 1);
    long long old_hash = hash(old_char);
    long long new_hash = hash(new_char);

    this->hash_value += new_hash - old_hash;
    if (this->hash_value < 0)   /* in case of overflow */
        this->hash_value += MOD_VALUE;
    this->start++;
    this->end++;
    this->current_span = this->text.substr(this->start, this->window_size);
}

long long RollingHash::get_current_hash() {
    return this->hash_value;
}

std::string RollingHash::get_current_span() {
    return this->current_span;
}


std::vector<int> the8(const std::string& text, const std::vector<std::string>& patterns){
    std::vector<int> shifts; //DO NOT CHANGE THIS

    std::string sub;
    int n = text.length();
    int m = patterns[0].length();
    std::vector<long long> hp;


    for (int i = 0; i < patterns.size(); i++) {
        long long h = hash(patterns[i]);
        hp.push_back(h);        
    }

    RollingHash hsub = RollingHash(text, m);
    int i = 0;
    while (i <= n-m) {
        if (vector_contains(hp, hsub.get_current_hash()) && vector_contains(patterns, hsub.get_current_span()))
            shifts.push_back(i);
        hsub.update();
        i++;
    }

    return shifts; //DO NOT CHANGE THIS
}
