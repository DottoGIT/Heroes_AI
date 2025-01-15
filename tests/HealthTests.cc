/*
 * File:        HealthTests.cc
 * Description: Unit tests for Health class
 *
 * Authors:     Wojciech Sarwiński
 * 
 * Date:        27.12.2024
 */

#define BOOST_TEST_MODULE HealthTests
#include <boost/test/included/unit_test.hpp>
#include <algorithm>

#include "Health.h"

BOOST_AUTO_TEST_CASE(Health_Constructor)
{
    Health health(10);
    BOOST_CHECK_EQUAL(10, health.get());
}

BOOST_AUTO_TEST_CASE(Health_Damage)
{
    Health health(10);
    BOOST_CHECK_EQUAL(10, health.get());
    health.damage(3);
    BOOST_CHECK_EQUAL(7, health.get());
}

BOOST_AUTO_TEST_CASE(Health_Lethal_Damage)
{
    Health health(10);
    health.damage(15);
    BOOST_CHECK_EQUAL(0, health.get());
}

BOOST_AUTO_TEST_CASE(Health_Lethal_Damage_Exact)
{
    Health health(10);
    health.damage(10);
    BOOST_CHECK_EQUAL(0, health.get());
}

BOOST_AUTO_TEST_CASE(Health_isAlive_True)
{
    Health health(10);
    BOOST_CHECK(health.isAlive());
}

BOOST_AUTO_TEST_CASE(Health_isAlive_False)
{
    Health health(0);
    BOOST_CHECK(!health.isAlive());
}
