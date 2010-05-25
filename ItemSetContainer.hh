#ifndef ITEMSETCONTAINER_HH__
#define ITEMSETCONTAINER_HH__

//STD
#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "ItemSet.hh"

//somewhat satisfies Backward Insertion Container and Sequence concepts
//complete no-op code, could be a typedef
class ItemSetContainer {
public:
  //construct all itemsets from inFile
  ItemSetContainer() { }
  ItemSetContainer(const std::string& inFile);

  //typedefs
  typedef std::vector<ItemSet> ItemSets;
  typedef ItemSets::iterator iterator;
  typedef ItemSets::const_iterator const_iterator;
  typedef ItemSets::reverse_iterator reverse_iterator;
  typedef ItemSets::const_reverse_iterator const_reverse_iterator;
  typedef const ItemSet& const_reference;
  typedef ItemSet value_type;

  //iterators
  const_iterator begin() const { return itemSets.begin(); }
  const_iterator end() const { return itemSets.end(); }
  const_iterator cbegin() const { return itemSets.cbegin(); }
  const_iterator cend() const { return itemSets.cend(); }

  iterator begin() { return itemSets.begin(); }
  iterator end() { return itemSets.end(); }

  reverse_iterator rbegin() { return itemSets.rbegin(); }
  reverse_iterator rend() { return itemSets.rend(); }
  const_reverse_iterator rbegin() const { return itemSets.rbegin(); }
  const_reverse_iterator rend() const { return itemSets.rend(); }

  //access, no at(size_type)
  ItemSet& operator[](ItemSets::size_type i) { return itemSets[i]; }
  const ItemSet& operator[](ItemSets::size_type i) const { return itemSets[i]; }
  const ItemSet& front() const { return itemSets.front(); }
  ItemSet& front() { return itemSets.front(); }
  const ItemSet& back() const { return itemSets.back(); }
  ItemSet& back() { return itemSets.back(); }
  
  //capacity, no std::vector specific functions
  ItemSets::size_type size() const { return itemSets.size(); }
  bool empty() const { return itemSets.empty(); }
  
  //modifiers
  void push_back(const ItemSet& x) { itemSets.push_back(x); }
  void pop_back() { itemSets.pop_back(); }
  ItemSets::iterator insert(ItemSets::iterator position, const ItemSet& x) { return itemSets.insert(position, x); }
  void insert(ItemSets::iterator position, ItemSets::size_type n, const ItemSet& x) { 
    itemSets.insert(position, n, x); }
  void clear() { itemSets.clear(); }
  ItemSets::iterator erase(ItemSets::iterator position ) { return itemSets.erase(position); }
  ItemSets::iterator erase(ItemSets::iterator first, ItemSets::iterator last) { return itemSets.erase(first, last); }

  //a map of 1-itemsets to their occurences in *this* ItemSetContainer
  //this doesn't make a lot of sense to me...
  ItemSetContainer init_pass(double minsup) const;

  //we prune and filter in one step
  ItemSetContainer generate_candidates(const ItemSetContainer& trans, double minsup) const;

  friend std::ostream& operator<<(std::ostream& os, const ItemSetContainer& rhs) {
    std::for_each(rhs.begin(), rhs.end(), [&os](const ItemSet& in) { os << in << std::endl; });
    return os;
  }

private:
  ItemSets itemSets;
};

#endif //header guard
