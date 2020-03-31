#include "../lib/catch2.hpp"

#include "../src/hash_table.hpp"

#include <stdexcept>

TEST_CASE ( "Insert search delete", "hash_table" ) {
    hash_function_t<std::string> hash_functions[2] {
        [] (std::string key) -> int {
            int result = key.size();

            for (std::size_t i = 0; i < key.length(); i++) {
                result += key[i];
            }

            return result;
        }, 
        [] (std::string key) -> int {
            (void) key; // Remove unused variable warning
            return 0;
        }
    };

    for (std::size_t i = 0; i < std::size(hash_functions); i++) {
        hash_table<std::string, std::string> table{ hash_functions[i], 100 };

        table.insert("hello", "world");
        table.insert("foo", "bar");
        table.insert("chicken", "little");

        REQUIRE( table.get("hello") == "world" );
        REQUIRE( table.get("foo") == "bar" );
        REQUIRE( table.get("chicken") == "little" );

        REQUIRE( table.size() == 3 );

        table.remove("hello");
        REQUIRE( table.size() == 2 );
        REQUIRE_THROWS_AS( table.get("hello"), std::runtime_error );

        table.remove("foo");
        REQUIRE( table.size() == 1 );
        REQUIRE_THROWS_AS( table.get("foo"), std::runtime_error );

        table.remove("chicken");
        REQUIRE( table.size() == 0 );
        REQUIRE_THROWS_AS( table.get("chicken"), std::runtime_error );
    }
}
