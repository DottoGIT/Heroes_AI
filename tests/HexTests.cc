/*
 * File:        HexTests.cc
 * Description: Unit tests for Hex struct
 *
 * Authors:     Wojciech Sarwiński
 * 
 * Date:        02.12.2024
 */

#define BOOST_TEST_MODULE UnitTests
#include <boost/test/included/unit_test.hpp>
#include <algorithm>
#include "Hex.h"

BOOST_AUTO_TEST_CASE(Hex_Constructor)
{
    Hex my_hex(1, 2);
    BOOST_CHECK_EQUAL(1, my_hex.q);
    BOOST_CHECK_EQUAL(2, my_hex.r);
}

BOOST_AUTO_TEST_CASE(Hex_Default_Constructor)
{
    Hex my_hex;
}

BOOST_AUTO_TEST_CASE(Hex_Add)
{
    Hex hex1(1, 2), hex2(3, 4);
    Hex hex3 = hex1 + hex2;
    BOOST_CHECK_EQUAL(hex3.q, 4);
    BOOST_CHECK_EQUAL(hex3.r, 6);
}

BOOST_AUTO_TEST_CASE(Hex_Equal_True)
{
    Hex hex1(1, 2), hex2(1, 2);
    BOOST_CHECK(hex1 == hex2);
}

BOOST_AUTO_TEST_CASE(Hex_Equal_False)
{
    Hex hex1(1, 2), hex2(3, 4);
    BOOST_CHECK(!(hex1 == hex2));
}

BOOST_AUTO_TEST_CASE(Hex_Neighbors)
{
    std::array<Hex, 6> expected_neighbors = {
        Hex(2, 1), Hex(1, 2), Hex(0, 2), Hex(0, 1), Hex(1, 0), Hex(2, 0)
    };
    Hex my_hex(1, 1);
    std::array<Hex, 6> neighbors = my_hex.neighbors();
    BOOST_CHECK(std::equal(neighbors.begin(), neighbors.end(), expected_neighbors.begin()));
}