#include "../lib/catch2.hpp"

#include "../src/linked_list.hpp"

#include <stdexcept>

TEST_CASE ( "Insert find delete", "linked_list" ) {
    linked_list<int> list;

    REQUIRE( list.size() == 0 );

    REQUIRE( list.find(5) == nullptr );

    auto node5{ list.insert(5) };
    auto node6{ list.insert(6) };
    auto node7{ list.insert(7) };

    REQUIRE( list.size() == 3 );

    REQUIRE( list.find(5) == node5 );
    REQUIRE( list.find(6) == node6 );
    REQUIRE( list.find(7) == node7 );

    list.remove(5);
    list.remove(6);
    list.remove(7);

    REQUIRE( list.size() == 0 );
    REQUIRE( list.find(5) == nullptr );
    REQUIRE( list.find(6) == nullptr );

    REQUIRE_THROWS_AS( list.remove(2), std::runtime_error );
}
