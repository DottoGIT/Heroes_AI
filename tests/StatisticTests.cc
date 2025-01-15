/*
 * File:        StatisticTests.cc
 * Description: Unit tests for Statistic class
 *
 * Authors:     Wojciech Sarwiński
 * 
 * Date:        27.12.2024
 */

#define BOOST_TEST_MODULE StatisticTests
#include <boost/test/included/unit_test.hpp>
#include <algorithm>

#include "Statistic.h"

BOOST_AUTO_TEST_CASE(Statistic_Constructor)
{
    Statistic strength(1);
    BOOST_CHECK_EQUAL(1, strength.get());
}

BOOST_AUTO_TEST_CASE(Statistic_Increase)
{
    Statistic strength(1);
    strength.increase(1);
    BOOST_CHECK_EQUAL(2, strength.get());
}