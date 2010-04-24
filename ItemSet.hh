#ifndef ITEMSET_HH__
#define ITEMSET_HH__

//STD
#include <vector>
#include <string>

//An ItemSet that isn't really a set. Not degenerating it into a multiset
//is the responsibility of the user.
class ItemSet {
public:
  
  ItemSet(const std::vector<std::string>& in) : itemV(in) {}
  ItemSet() { }

  typedef std::vector<std::string> ItemVec;
  typedef ItemVec::iterator iterator;
  typedef ItemVec::const_iterator const_iterator;

  iterator begin() { return itemV.begin(); }
  const_iterator begin() const { return itemV.begin(); }
  iterator end() { return itemV.end(); }
  const_iterator end() const { return itemV.end(); }


  //Pre: None
  //Post: in is the last member of this itemset (e.g. back())
  //Sets shouldn't have push_back
  void push_back(const std::string& in);

  //Pre: None
  //Post: the items in this ItemSet are lexically sorted (by std::less<std::string>)
  void sort();

  const std::string& back() const { return itemV.back(); }

  std::string& back() { return itemV.back(); }

  //Pre: i <= other.itemV.size()
  //Post: none
  bool matches(const ItemSet& other, unsigned int i) const;

  //Pre: this and the argument are sorted
  //Post: none
  bool contains(const ItemSet& other) const; 
  
  //Pre: i < itemV.size()
  //Post: return value is subset without i-th value of this
  ItemSet subset(unsigned int i) const;
private:
  ItemVec itemV;
};

#endif //header guard


