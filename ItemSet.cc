#include "ItemSet.hh"

#include "ItemSetContainer.hh"

void ItemSet::determine_count(const ItemSetContainer& in) {
  count_ = 0;
  std::for_each(in.begin(), in.end(), [this](const ItemSet& is) {
      if(is.contains(*this))
	count_ += 1;
    });
}

