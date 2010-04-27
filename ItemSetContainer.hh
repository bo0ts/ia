#ifndef ITEMSETCONTAINER_HH__
#define ITEMSETCONTAINER_HH__

#include "ItemSet.hh"

//STD
#include <vector>
#include <string>

//somewhat satisfies Backward Insertion Container and Sequence concepts
//complete no-op code, could be a typedef
class ItemSetContainer {
public:
  //construct all itemsets from inFile
  ItemSetContainer(const std::string& inFile);
  //typedefs
  typedef std::vector<ItemSet> ItemSets;
  typedef ItemSets::iterator iterator;
  typedef ItemSets::const_iterator const_iterator;
  typedef ItemSets::reverse_iterator reverse_iterator;
  typedef ItemSets::const_reverse_iterator const_reverse_iterator;

  //iterators
  const_iterator begin() const { return itemSets.begin(); }
  iterator begin() { return itemSets.begin(); }
  const_iterator end() const { return itemSets.end(); }
  iterator end() { return itemSets.end(); }
  reverse_iterator rbegin() { return itemSets.rbegin(); }
  const_reverse_iterator rbegin() const { return itemSets.rbegin(); }
  reverse_iterator rend() { return itemSets.rend(); }
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
private:
  ItemSets itemSets;
};

#endif //header guard
