#include <iostream>
#include <cstdlib>

#include "fisher_yates.h"

using namespace std;

int main() {
    int n = 5; 

    std::vector<int> sequence(2 * n + 1);
      for (int i = 0; i < n; i++) {
        sequence[i] = 1;
    }

    for (int i = n; i < 2 * n + 1; i++) {
        sequence[i] = -1;
    }

    auto balanced_sequence = generate_balanced_sequence(sequence);

    std::cout << "Generated balanced sequence: ";
    print_vector(balanced_sequence);

    bool is_non_neg = non_neg_prefix_sum(balanced_sequence);
    bool is_non_pos = non_pos_prefix_sum(balanced_sequence);

    std::cout << "Is non-neg prefix sum valid: " << is_non_neg << std::endl;
    std::cout << "Is non-pos prefix sum valid: " << is_non_pos << std::endl;

    return 0;
}
