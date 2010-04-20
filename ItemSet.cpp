#include "ItemSet.hh"

#include <algorithm>
#include <iterator>
#include <cassert>

using namespace std;

void ItemSet::push_back(const std::string& in) { 
  itemV.push_back(in);
}

void ItemSet::sort() {
  std::sort(itemV.begin(), itemV.end());
}

bool ItemSet::matches(const ItemSet& other, unsigned int i) const {
  assert(i <= other.itemV.size());
  ItemVec::const_iterator it = other.itemV.begin();
  advance(it, i);
  return equal(other.itemV.begin(), it, this->itemV.begin());
}

bool ItemSet::contains(const ItemSet& other) const {
  return includes(itemV.begin(), itemV.end(), other.itemV.begin(), other.itemV.end());
}

ItemSet ItemSet::subset(unsigned int i) const {
  assert(i < itemV.size());
  //passing ints for container access ain't beautiful...
  ItemSet tmp;
  for(unsigned int c = 0; c < itemV.size(); ++c) {
    if(c != i) {
      tmp.push_back(itemV[c]);
    }
  }
  return tmp;
}
