#ifndef _FISHER_YATES_H_
#define _FISHER_YATES_H_

#include <vector>

void swap(int &a, int &b);
void fisher_yates(std::vector<int> &array);
bool non_neg_prefix_sum(const std::vector<int> &ary);
bool non_pos_prefix_sum(const std::vector<int> &ary);
void print_vector(const std::vector<int> &vec);

std::vector<int> generate_balanced_sequence(std::vector<int>& sequence);

#endif
