/*
 * File:        HexMapTests.cc
 * Description: Unit tests for HexMap class
 *
 * Authors:     Wojciech Sarwiński
 * 
 * Date:        02.12.2024
 */

#define BOOST_TEST_MODULE UnitTests
#include <boost/test/included/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <algorithm>

#include "HexMap.hpp"

typedef boost::mpl::list<int, bool> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(HexMap_Constructor, T, test_types)
{
    HexMap<T> my_map(7, 7);
}

BOOST_AUTO_TEST_CASE(HexMap_At)
{
    HexMap<int> my_map(2, 2);
    my_map.at(Hex(0,0)) = 0;
    my_map.at(Hex(1,0)) = 1;
    my_map.at(Hex(0,1)) = 2;
    my_map.at(Hex(1, 1)) = 3;
    
    BOOST_CHECK_EQUAL(my_map.at(Hex(0, 0)), 0);
    BOOST_CHECK_EQUAL(my_map.at(Hex(1, 0)), 1);
    BOOST_CHECK_EQUAL(my_map.at(Hex(0, 1)), 2);
    BOOST_CHECK_EQUAL(my_map.at(Hex(1, 1)), 3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(HexMap_inBounds, T, test_types)
{
    HexMap<T> my_map(2, 2);
    
    BOOST_CHECK(my_map.inBounds(Hex(0, 0)));
    BOOST_CHECK(my_map.inBounds(Hex(1, 0)));
    BOOST_CHECK(my_map.inBounds(Hex(0, 1)));
    BOOST_CHECK(my_map.inBounds(Hex(1, 1)));

    BOOST_CHECK(!my_map.inBounds(Hex(0,-1)));
    BOOST_CHECK(!my_map.inBounds(Hex(1,-1)));
    BOOST_CHECK(!my_map.inBounds(Hex(2,-1)));

    BOOST_CHECK(!my_map.inBounds(Hex(2, 0)));
    BOOST_CHECK(!my_map.inBounds(Hex(-1, 0)));

    BOOST_CHECK(!my_map.inBounds(Hex(2, 1)));
    BOOST_CHECK(!my_map.inBounds(Hex(-1, 1)));

    BOOST_CHECK(!my_map.inBounds(Hex(1, 2)));
    BOOST_CHECK(!my_map.inBounds(Hex(0, 2)));
    BOOST_CHECK(!my_map.inBounds(Hex(-1, 2)));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(HexMap_getNeighbors_zero_zero, T, test_types)
{
    HexMap<T> my_map(7, 7);

    std::vector<Hex> neighbors = my_map.getNeighbors(Hex(0, 0));
    
}