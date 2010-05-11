#include "ItemSetContainer.hh"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>

using namespace std;

namespace {
  class CopyAndCount {
    typedef map<ItemSet, unsigned int> ItemCounter;
    ItemCounter& toFill;
  public:
    CopyAndCount(ItemCounter& toFill) : toFill(toFill) {}
    void operator() (const ItemSet& in) {
      for(ItemSet::const_iterator it = in.begin(); it != in.end(); ++it) {
	//sure...
	ItemSet tmp;
	tmp.insert(*it);
	pair<ItemCounter::iterator, bool> ret = toFill.insert(make_pair(tmp, 1u));
	if(ret.second == false) {
	  ++(ret.first->second);
	}
      }
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
    
    copy(istream_iterator<string>(iss),
	 istream_iterator<string>(),
	 back_inserter<vector<string> >(tokens)); 
    //emacs indentation borks, when there is no SPC between
    //closing angle bracket, jesus...
    itemSets.push_back(ItemSet(tokens));    
  }
}

map<ItemSet, unsigned int> ItemSetContainer::init_pass() const {
  map<ItemSet, unsigned int> tmp;
  for_each(begin(), end(), CopyAndCount(tmp));

  //rvo will save us
  return tmp;
}
