#include "ItemSetContainer.hh"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <iostream>

using namespace std;

namespace {
  struct Counter {
    //this just isn't getting any smaller
    typedef map<ItemSet, unsigned int> ItemCounter;
    ItemCounter counter;

    void operator() (const ItemSet& in) {
      for(ItemSet::const_iterator it = in.begin(); it != in.end(); ++it) {
	ItemSet tmp;
	tmp.push_back(*it);
	pair<ItemCounter::iterator, bool> ret = counter.insert(make_pair(tmp, 1u));
	//raise if known
	if(ret.second == false) { ++(ret.first->second); }
      }
    }
  };

  struct PairToItemSet {
    ItemSet operator() (const pair<ItemSet, unsigned int>& in) {
      ItemSet tmp(in.first);
      tmp.support() = in.second;
      return tmp;
    }
  };

}; //file static

ItemSetContainer::ItemSetContainer(const string& inFile) {
  ifstream is(inFile.data());
  //getline from <string> _not_ iostream member
  while(is.good()) {
    string tokenLine;
    getline(is, tokenLine);
    vector<string> tokens;

    istringstream iss(tokenLine);

    itemSets.push_back(ItemSet(0));
    copy(istream_iterator<string>(iss),
	 istream_iterator<string>(),
	 back_inserter<ItemSet>(itemSets.back())); 
    //emacs indentation borks, when there is no SPC between
    //closing angle bracket, jesus...
    itemSets.back().sort();
  }
}

ItemSetContainer ItemSetContainer::init_pass() const {
  Counter counter = for_each(begin(), end(), Counter());
  ItemSetContainer tmp;
  std::transform(counter.counter.begin(), counter.counter.end(), back_inserter(tmp), PairToItemSet());

  return tmp;
}
