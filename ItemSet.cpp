#include "ItemSet.hh"

#include "ItemSetContainer.hh"

void ItemSet::determine_count(const ItemSetContainer& in) {
  count_ = 0;

  for(auto it = in.begin(); it != in.end(); ++it) {
    if(it->contains(*this))
      count_ += 1;
  }

  // std::for_each(in.begin(), in.end(), [this](const ItemSet& is) {
  //     if(is.contains(*this))
  // 	count_ += 1;
  //   });
}

