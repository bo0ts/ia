#ifndef ITEMSET_HH__
#define ITEMSET_HH__

//STD
#include <set>
#include <vector>
#include <string>
#include <iostream>

//ItemSet
//changes to spec: no passing of ints, just iterators, "resorts" after every insertion,
//no back(), could be a typedef as well
class ItemSet {
public:
  //from vector, convenience
  ItemSet(const std::vector<std::string>& in) : items(in.begin(), in.end()) {}
  ItemSet(const std::set<std::string>& in) : items(in) {}
  ItemSet() { }

  //typedefs
  typedef std::set<std::string> Items;
  typedef Items::iterator iterator;
  typedef Items::const_iterator const_iterator;


  //iterators, no reverse
  iterator begin() { return items.begin(); }
  const_iterator begin() const { return items.begin(); }
  iterator end() { return items.end(); }
  const_iterator end() const { return items.end(); }


  //capacity
  bool empty() const { return items.empty(); }
  Items::size_type size() const { return items.size(); }
  
  //modifiers
  std::pair<iterator, bool> insert(const std::string& in) { return items.insert(in); }
  void clear() { items.clear(); }
  void erase(iterator position) { items.erase(position); }
  void erase(const std::string& x) { items.erase(x); }

  //access
  iterator find(const std::string& x) const { return items.find(x); }

  //compares the range [ other.begin, pos ) to [ this.begin, ... ) and
  //returns true if they are equal
  //Pre: pos is a iterator to an element of other 
  //Post: none
  bool matches(const ItemSet& other, iterator pos) const;

  //checks if this includes other
  //Pre: true if it is Post: none
  bool contains(const ItemSet& other) const; 
  
  //Pre: pos is in range [ begin(), end() )
  //Post: return value is the subset of this without the value pointed to by pos
  ItemSet subset(iterator pos) const;

  friend std::ostream& operator<<(std::ostream& os, const ItemSet& rhs) {
    for(ItemSet::iterator it = rhs.begin(); it != rhs.end(); ++it)
      os << (*it) << " ";
    return os;
  }

  bool operator< (const ItemSet& rhs) const;
private:
  Items items;
};

#endif //header guard


