#include "ItemSetContainer.hh"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;
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
