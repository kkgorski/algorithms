#include <iostream>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

template<typename TYPE, std::size_t SIZE>
class linkedList
{
};

TEST_CASE( "Linked list is constructed") {
    REQUIRE( true );
}

