#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "fisher_yates.h"

TEST_CASE("Testing the fisher_yates shuffle function") {
    std::vector<int> original = {1, 2, 3, 4, 5};
    std::vector<int> copy = original;

    SUBCASE("Shuffle does not change array size") {
        fisher_yates(copy);
        CHECK_EQ(copy.size(), original.size());
    }

    SUBCASE("Shuffle maintains the same elements") {
        fisher_yates(copy);
        std::sort(copy.begin(), copy.end());
        CHECK_EQ(copy, original);
    }

    SUBCASE("Repeated shuffles result in different orders") {
        std::vector<int> firstShuffle = original;
        fisher_yates(firstShuffle);

        std::vector<int> secondShuffle = original;
        fisher_yates(secondShuffle);

        CHECK_FALSE(std::equal(firstShuffle.begin(), firstShuffle.end(), secondShuffle.begin()));
    }

    SUBCASE("Non-negativity of prefix sums is maintained for shuffled non-negative input") {
        std::vector<int> nonNegative = {0, 1, 2, 3, 4, 5};
        fisher_yates(nonNegative);
        REQUIRE(non_neg_prefix_sum(nonNegative));
    }

    SUBCASE("Non-positivity of prefix sums is not guaranteed for shuffled input") {
        std::vector<int> mixedSigns = {-2, -1, 0, 1, 2};
        fisher_yates(mixedSigns);
        WARN(!non_pos_prefix_sum(mixedSigns)); 
    }
}


TEST_CASE("Testing the generate_balanced_sequence function") {
    std::vector<int> originalSequence = {1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1}; 

    SUBCASE("Non-negative prefix sum validation") {
        auto balancedSequence = generate_balanced_sequence(originalSequence);
        bool isNonNeg = non_neg_prefix_sum(balancedSequence);
        REQUIRE(isNonNeg); 
    }

    SUBCASE("Non-positive prefix sum validation should fail") {
        auto balancedSequence = generate_balanced_sequence(originalSequence);
        bool isNonPos = non_pos_prefix_sum(balancedSequence);
        CHECK_FALSE(isNonPos); 
    }
}

TEST_CASE("First element is always 1 after generating a balanced sequence") {
    std::vector<int> originalSequence = {1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1}; 
    for (int i = 0; i < 10; ++i) { 
        auto balancedSequence = generate_balanced_sequence(originalSequence);
        CHECK_EQ(balancedSequence[0], 1); 
    }
}

TEST_CASE("Balanced sequence should not exhibit a simple alternating pattern") {
    std::vector<int> originalSequence(12); 
    std::fill_n(originalSequence.begin(), 6, 1); 
    std::fill_n(originalSequence.begin() + 6, 6, -1); 

    auto balancedSequence = generate_balanced_sequence(originalSequence);

    int alternatingPatternCount = 0;
   
    for (size_t i = 0; i < balancedSequence.size() - 1; ++i) {
        if (balancedSequence[i] == -balancedSequence[i + 1]) {
            alternatingPatternCount++;
        }
    }

    REQUIRE(alternatingPatternCount < balancedSequence.size() - 1);
}


