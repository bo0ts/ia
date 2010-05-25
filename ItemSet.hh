#ifndef ITEMSET_HH__
#define ITEMSET_HH__

//STD
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

//ItemSet
//changes to spec: no passing of ints, just iterators, "resorts" after every insertion,
//no back(), could be a typedef as well
class ItemSet {
public:
  //from vector, convenience
  explicit ItemSet(const std::vector<std::string>& in, unsigned int support = 0) : 
    support_(support), items(in) {}
  explicit ItemSet(unsigned int support) : support_(support) {}
  ItemSet() : support_(0) { }

  //typedefs
  typedef std::vector<std::string> Items;
  typedef Items::iterator iterator;
  typedef Items::const_iterator const_iterator;
  typedef Items::const_reference const_reference;
  typedef Items::reference reference;
  typedef Items::size_type size_type;

  //iterators, no reverse
  const_iterator begin() const { return items.begin(); }
  const_iterator end() const { return items.end(); }
  iterator begin() { return items.begin(); }
  iterator end() { return items.end(); }


  //capacity
  bool empty() const { return items.empty(); }
  size_type size() const { return items.size(); }
  
  //modifiers
  //std::pair<iterator, bool> insert(const std::string& in) { return items.insert(in); }
  void push_back(const std::string& x) { items.push_back(x); }
  void clear() { items.clear(); }
  void reserve(size_type n) { items.reserve(n); }
  void sort() { std::sort(begin(), end()); }
  void erase(iterator it) { items.erase(it); }
  //linear find
  const_iterator find(const std::string& in) const { return std::find(begin(), end(), in); }
  iterator find(const std::string& in) { return std::find(begin(), end(), in); }

  //access, no non-const
  const_reference front() const { return items.front(); }
  const_reference back() const { return items.back(); }

  //compares the range [ other.begin, pos ) to [ this.begin, ... ) and
  //returns true if they are equal
  //Pre: pos is a iterator to an element of other 
  //Post: none
  bool matches(const ItemSet& other, const_iterator pos) const {
    return std::equal(other.items.begin(), pos, this->items.begin());
  }

  //checks if this includes other
  //Pre: true if it is Post: none
  bool contains(const ItemSet& other) const {
    return std::includes(items.begin(), items.end(), other.items.begin(), other.items.end());
  }
  
  //Pre: pos is in range [ begin(), end() )
  //Post: return value is the subset of this without the value pointed to by pos
  ItemSet subset(const_iterator pos) const {
    ItemSet tmp;
    tmp.reserve(size() - 1);
    for(const_iterator it = begin(); it != end(); ++it) {
      if(pos != it)
	tmp.push_back(*it);
    }
    return tmp;
  }

  bool operator< (const ItemSet& rhs) const {
    return std::lexicographical_compare(items.begin(), items.end(), rhs.items.begin(), rhs.items.end());
  }
  
  unsigned int& support() { return support_; }
  const unsigned int& support() const { return support_; }

  friend std::ostream& operator<<(std::ostream& os, const ItemSet& rhs) {
    for(ItemSet::const_iterator it = rhs.begin(); it != rhs.end(); ++it)
      os << (*it) << " ";
    os << "Support: " << rhs.support();
    return os;
  }

private:
  unsigned int support_;
  Items items;
};

#endif //header guard


