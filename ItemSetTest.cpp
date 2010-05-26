#include "ItemSet.hh"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/assign.hpp>
#include <iostream>

#include "str_pool.hh"

using namespace std;
using namespace boost::assign;

struct Fixture {
  str_pool pool;
  ItemSet test1,test2, test3;
  Fixture() {
    vector<str_proxy> one, two, three;
    one += str_proxy("foo", pool), str_proxy("bar", pool), str_proxy("baz", pool);
    two += str_proxy("foo", pool), str_proxy("bar", pool);
    three += str_proxy("foo", pool), str_proxy("baz", pool);

    test1 = ItemSet(one);
    test2 = ItemSet(two);
    test3 = ItemSet(three);
    pool.seal();

    test1.sort(); test2.sort(); test3.sort();
  }
};

BOOST_FIXTURE_TEST_SUITE(s, Fixture)

BOOST_AUTO_TEST_CASE(matches) {
  BOOST_CHECK(!test1.matches(test2, test2.end()));
  test2.push_back(str_proxy("baz", pool));
  pool.seal();
  test2.sort();

  BOOST_CHECK(test1.matches(test2, test2.end()));
  test2.erase(test2.find(str_proxy("baz", pool)));
  pool.seal();
  test2.sort();

  BOOST_CHECK(!test2.matches(test3, test3.end()));
}

BOOST_AUTO_TEST_CASE(contains) {
  BOOST_CHECK(test1.contains(test2));
  BOOST_CHECK(!test2.contains(test1));
  BOOST_CHECK(!test2.contains(test3));
}

BOOST_AUTO_TEST_CASE(compare) {
  ItemSet a, b, c, d, e;
  vector<str_proxy> aV; aV += str_proxy("a", pool), str_proxy("b", pool), 
		       str_proxy("c", pool), str_proxy("d", pool);

  vector<str_proxy> bV; bV += str_proxy("a", pool), str_proxy("b", pool), 
		       str_proxy("c", pool), str_proxy("d", pool), str_proxy("e", pool);

  vector<str_proxy> cV; cV += str_proxy("a", pool), str_proxy("b", pool), str_proxy("c", pool);

  vector<str_proxy> dV; dV += str_proxy("a", pool), str_proxy("b", pool), str_proxy("d", pool);

  vector<str_proxy> eV; eV += str_proxy("b", pool), str_proxy("c", pool);
  
  pool.seal();

  a = ItemSet(aV);
  b = ItemSet(bV);
  BOOST_CHECK(a < b);

  c = ItemSet(cV);

  d = ItemSet(dV);

  e = ItemSet(eV);
  BOOST_CHECK(c < d);
  BOOST_CHECK(c < e);
}

BOOST_AUTO_TEST_SUITE_END()
