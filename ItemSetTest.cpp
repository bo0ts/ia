#include "ItemSet.hh"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/assign.hpp>
#include <iostream>

using namespace std;
using namespace boost::assign;

struct Fixture {
  ItemSet test1,test2, test3;
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

BOOST_AUTO_TEST_CASE(matches) {
  BOOST_CHECK(!test1.matches(test2, test2.end()));
  test2.insert("baz");
  BOOST_CHECK(test1.matches(test2, test2.end()));
  test2.erase("baz");

  BOOST_CHECK(!test2.matches(test3, test3.end()));

  BOOST_CHECK(!test2.matches(test3, test3.find(std::string("foo"))));
}

BOOST_AUTO_TEST_CASE(contains) {
  BOOST_CHECK(test1.contains(test2));
  BOOST_CHECK(!test2.contains(test1));
  BOOST_CHECK(!test2.contains(test3));
}

BOOST_AUTO_TEST_CASE(subset) {
  ItemSet sub = test1.subset(test1.find("bar"));
  BOOST_CHECK(test3.matches(sub, sub.end()));
}

BOOST_AUTO_TEST_CASE(compare) {
  ItemSet a, b, c, d, e;
  vector<string> aV; aV += "a", "b", "c", "d";
  vector<string> bV; bV += "a", "b", "c", "d", "e";
  a = ItemSet(aV);
  b = ItemSet(bV);
  BOOST_CHECK(a < b);
  vector<string> cV; cV += "a", "b", "c";
  c = ItemSet(cV);
  vector<string> dV; dV += "a", "b", "d";
  d = ItemSet(dV);
  vector<string> eV; eV += "b", "c";
  e = ItemSet(eV);
  BOOST_CHECK(c < d);
  BOOST_CHECK(c < e);
}

BOOST_AUTO_TEST_SUITE_END();
