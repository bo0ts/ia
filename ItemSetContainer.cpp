#include "ItemSetContainer.hh"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <iostream>
#include <boost/utility.hpp>

using namespace std;

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

ItemSetContainer ItemSetContainer::init_pass(double minsup) const {
  ItemSetContainer tmp;

  typedef map<std::string, unsigned int> StringCounter;
  StringCounter counter;

  for_each(begin(), end(), [&counter](const ItemSet& in) {
      for_each(in.begin(), in.end(), [&counter](const std::string& in2) {
	  pair<StringCounter::iterator, bool> ret = counter.insert(make_pair(in2, 1u));
	  if(ret.second == false) { ++(ret.first->second); }});
    });

  std::transform(counter.begin(), counter.end(), 
		 back_inserter(tmp), 
		 [](const pair<std::string, unsigned int>& in) { 
		   ItemSet tmp(in.second); tmp.push_back(in.first); return tmp; });

  auto it = std::remove_if(tmp.begin(), tmp.end(), [&minsup, this](const ItemSet& in) {
      return in.support(this->size()) < minsup; });

  tmp.erase(it, tmp.end());

  return tmp;
}

ItemSetContainer ItemSetContainer::generate_candidates(const ItemSetContainer& trans, double minsup) const {
  ItemSetContainer tmp;
  auto end = boost::prior(this->end());

  for(auto it = begin(); it != end; ++it) {
    auto it2 = boost::next(it);
    while(it2 != this->end() && it->matches(*it2, boost::prior(it2->end()))) {
      //Maybe assert
      ItemSet c(*it);
      c.push_back(*boost::prior(it2->end()));
      
      //all k-1 subsets of c
      bool notFound = false;
      for(auto x = c.begin(); x != c.end(); ++x) {
	auto sub = c.subset(x);
	if(!std::binary_search(this->begin(), this->end(), sub)) {
	  notFound = true;
	  break;
	}
      }

      if(!notFound) {
	c.determine_count(trans);
	//do we need to check for duplicity?
	if(c.support(trans.size()) >= minsup)
	   tmp.push_back(c);
      }
      ++it2;
    }
  }
  return tmp;
}
