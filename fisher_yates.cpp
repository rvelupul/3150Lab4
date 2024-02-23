#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <climits>
#include <vector>

#include "fisher_yates.h"

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void fisher_yates(std::vector<int> &array) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, array.size() - 1);

    for (int i = array.size() - 1; i > 0; --i) {
        int j = distr(eng) % (i + 1);
        swap(array[i], array[j]);
    }
}

bool non_neg_prefix_sum(const std::vector<int> &ary) {
    bool negative_found = true;
    int sum = 0;
    for (int i = 0; i < ary.size(); i++) {
        sum += ary[i];
        if (sum < 0) {
            negative_found = false; 
            break;
        }
    }
    return negative_found; 
}

bool non_pos_prefix_sum(const std::vector<int> &ary) {
    bool positive_found = true;
    int sum = 0;
    for (int i = 0; i < ary.size(); i++) {
        sum += ary[i];
        if (sum > 0) {
            positive_found = false;
            break;
        }
    }
    return positive_found;
}

void print_vector(const std::vector<int> &vec) {
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

std::vector<int> generate_balanced_sequence(std::vector<int>& sequence) {

    do {
        fisher_yates(sequence);
    } while (sequence[0] != 1);

    int min_index = 0;
    int sum = 0, min_sum = INT_MAX;
    for (int i = 0; i < sequence.size(); ++i) {
        sum += sequence[i];
        if (sum < min_sum) {
            min_sum = sum;
            min_index = i;
        }
    }

    std::vector<int> p1(sequence.begin(), sequence.begin() + min_index + 1);
    std::vector<int> p2(sequence.begin() + min_index + 1, sequence.end());

    if (p1.back() == -1) {
        p1.pop_back();
    }

    std::vector<int> new_sequence;
    new_sequence.insert(new_sequence.end(), p2.begin(), p2.end());
    new_sequence.insert(new_sequence.end(), p1.begin(), p1.end());

    return new_sequence;
}
