#include "ItemSet.hh"

#include <algorithm>
#include <iterator>
#include <cassert>

using namespace std;

bool ItemSet::matches(const ItemSet& other, iterator pos) const {
  return equal(other.items.begin(), pos, this->items.begin());
}

bool ItemSet::contains(const ItemSet& other) const {
  return includes(items.begin(), items.end(), other.items.begin(), other.items.end());
}

ItemSet ItemSet::subset(iterator pos) const {
  ItemSet tmp(*this);
  tmp.erase(*pos);
  return tmp;
}
