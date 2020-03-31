#include "../lib/catch2.hpp"

#include "../src/binary_search_tree.hpp"

TEST_CASE ( "Conversion to sorted vector", "binary_search_tree" ) {
    std::vector<int> my_list{ 101, 202, 100, 203, 444, 593, 208, 534, 352, 242, 252 };
    binary_search_tree<int> tree;

    for (std::size_t i = 0; i < my_list.size(); i++) {
        tree.insert(my_list[i]);
    }

    std::vector<int> sorted{ tree.to_vector() };

    REQUIRE( sorted.size() == my_list.size() );

    int last = 0;

    for (std::size_t i = 0; i < sorted.size(); i++) {
        REQUIRE(last <= sorted[i]);
        last = sorted[i];
    }
}

TEST_CASE( "Element removal", "binary_search_tree") {
    std::vector<int> my_list{ 101, 202, 100, 203, 444, 593, 208, 534, 352, 242, 252 };

    for (std::size_t i = 0; i < my_list.size(); i++) {
        binary_search_tree<int> tree;

        for (std::size_t j = 0; j < my_list.size(); j++) {
            tree.insert(my_list[j]);
        }

        REQUIRE( tree.search(my_list[i]) != nullptr );

        tree.remove(my_list[i]);

        REQUIRE( tree.search(my_list[i]) == nullptr );

        std::vector<int> chopped{ tree.to_vector() };

        REQUIRE( chopped.size() + 1 == my_list.size() );
    }
}
