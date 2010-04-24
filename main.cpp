#include "ItemSetContainer.hh"
#include <iostream>

int main(void) {
  ItemSetContainer a("test.txt");
  for(ItemSetContainer::ItemSets::iterator it = a.begin();
      it != a.end(); ++it) {
    it->sort();
    for(ItemSet::const_iterator it2 = it->begin();
	it2 != it->end(); ++it2)
      std::cout << *it2 << " ";
    std::cout << std::endl;
  }
}
