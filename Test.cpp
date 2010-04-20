#include "ItemSet.hh"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/assign.hpp>
#include <iostream>

using namespace std;
using namespace boost::assign;

struct Fixture {
  ItemSet test1;
  ItemSet test2;
  ItemSet test3;
  Fixture() {
    vector<string> one;
    vector<string> two;
    vector<string> three;
    one += "foo", "bar", "baz";
    two += "foo", "bar";
    three += "foo", "baz";
    test1 = ItemSet(one);
    test2 = ItemSet(two);
    test3 = ItemSet(three);
  }
};



BOOST_FIXTURE_TEST_SUITE(s, Fixture);
BOOST_AUTO_TEST_CASE(add_and_back) {
  ItemSet itemset;
  std::string test = "foo";
  std::string test2 = "bar";
  itemset.push_back(test);
  BOOST_CHECK_EQUAL(test, itemset.back());
  itemset.push_back(test2);
  BOOST_CHECK_EQUAL(test2, itemset.back());
}

BOOST_AUTO_TEST_CASE(matches) {
  BOOST_CHECK(test1.matches(test2, 2));
  BOOST_CHECK(!test2.matches(test3, 2));
  BOOST_CHECK(test2.matches(test3, 1));
}

BOOST_AUTO_TEST_CASE(contains) {
  BOOST_CHECK(test1.contains(test2));
  BOOST_CHECK(!test2.contains(test1));
  BOOST_CHECK(!test2.contains(test3));
}

BOOST_AUTO_TEST_CASE(subset) {
  ItemSet sub = test1.subset(1);
  BOOST_CHECK(test3.matches(sub, 2));
}

BOOST_AUTO_TEST_SUITE_END();
