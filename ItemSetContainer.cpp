#include "ItemSetContainer.hh"

#include "str_pool.hh"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <iostream>

#include <boost/utility.hpp>



//boost::thread workaround
#undef BOOST_HAS_RVALUE_REFS
#define BOOST_NO_RVALUE_REFERENCES 

#include <boost/thread.hpp>

#define BOOST_HAS_RVALUE_REFS
#undef BOOST_NO_RVALUE_REFERENCES 

using namespace std;

ItemSetContainer::ItemSetContainer(const string& inFile, str_pool& pool) {
  ifstream is(inFile.data());

  //getline from <string> _not_ iostream member
  while(is.good()) {
    string tokenLine;
    getline(is, tokenLine);
    istringstream iss(tokenLine);

    itemSets.push_back(ItemSet(0));

    std::transform(istream_iterator<string>(iss),
		   istream_iterator<string>(),
		   back_inserter<ItemSet>(itemSets.back()),
		   [&pool](const std::string& x) { return str_proxy(x, pool); });
  }
  //remove the newline
  if(itemSets.back().size() == 0)
    itemSets.pop_back();
  
  pool.seal();
  std::for_each(itemSets.begin(), itemSets.end(), [](ItemSet& x) { x.sort(); });
  std::sort(begin(), end());
}

ItemSetContainer ItemSetContainer::init_pass(double minsup) const {
  ItemSetContainer tmp;

  typedef map<str_proxy, unsigned int> StringCounter;
  StringCounter counter;

  for_each(begin(), end(), [&counter](const ItemSet& in) {
      for_each(in.begin(), in.end(), [&counter](const str_proxy& in2) {
	  pair<StringCounter::iterator, bool> ret = counter.insert(make_pair(in2, 1u));
	  if(ret.second == false) { ++(ret.first->second); }});
    });

  //pedantic borks on deduction of this lambda's return type :(
  std::transform(counter.begin(), counter.end(), 
		 back_inserter(tmp), 
		 [](const pair<str_proxy, unsigned int>& in) -> ItemSet { 
		   ItemSet tmp(in.second); tmp.push_back(in.first); return tmp; });

  //prune
  auto it = std::remove_if(tmp.begin(), tmp.end(), [&minsup, this](const ItemSet& in) {
      return in.support(this->size()) < minsup; });

  tmp.erase(it, tmp.end());

  return tmp;
}

namespace {
  struct worker {
    void operator()(std::vector<ItemSet>::const_iterator begin, 
		    std::vector<ItemSet>::const_iterator end, std::vector<ItemSet>& output, 
		    const ItemSetContainer& trans, const ItemSetContainer& start, double minsup) {
      for(auto it = begin; it != end; ++it) {
	auto it2 = boost::next(it);
	while(it2 != start.end() && it->matches(*it2, boost::prior(it2->end()))) {
	  //Maybe assert
	  ItemSet c(*it);
	  c.push_back(*boost::prior(it2->end()));
      
	  //all k-1 subsets of c
	  bool notFound = false;
	  for(auto x = c.begin(); x != c.end(); ++x) {
	    auto sub = c.subset(x);
	    if(!std::binary_search(start.begin(), start.end(), sub)) {
	      notFound = true;
	      break;
	    }
	  }

	  if(!notFound) {
	    c.determine_count(trans.begin(), trans.end());
	    //do we need to check for duplicity?
	    if(c.support(trans.size()) >= minsup)
	      output.push_back(c);
	  }
	  ++it2;
	}
      }
    }
  }; //file static namespace
}

ItemSetContainer ItemSetContainer::generate_candidates(const ItemSetContainer& trans, double minsup) const {
  // ItemSetContainer tmp;
  auto end = boost::prior(this->end());

  std::vector<ItemSet> output;
  worker worker;

  //the number of threads we launch
  unsigned int thread_num = boost::thread::hardware_concurrency();

  //one output for each thread
  std::vector< std::vector<ItemSet> > outputs(thread_num);

  //all items we need to process
  ItemSets::size_type size = itemSets.size() - 1;

  unsigned int chunk_size = size / thread_num;
  std::cout << "thread_num: " << thread_num << " size: " << size 
	    << " chunk size: " << chunk_size << std::endl;

  boost::thread_group threads;

  //the last needs to go till the end
  auto out_end = boost::prior(outputs.end());
  auto start1 = itemSets.begin();
  auto start2 = itemSets.begin();
  for(auto it = outputs.begin(); it != outputs.end(); ++it) {
    if(it == out_end) {
      start2 = end;
      boost::thread* worker_thread = new boost::thread(worker, start1, start2, boost::ref(*it), 
						       boost::ref(trans), boost::ref(*this), minsup);
      threads.add_thread(worker_thread);
  } else {
      std::advance(start2, chunk_size);
      boost::thread* worker_thread = new boost::thread(worker, start1, start2, boost::ref(*it), 
						       boost::ref(trans), boost::ref(*this), minsup);
      threads.add_thread(worker_thread);
      start1 = start2;
    }
  }
  threads.join_all();

  //threads are done, merge the results
  ItemSetContainer tmp;  
  std::for_each(outputs.begin(), outputs.end(), [&tmp](const std::vector<ItemSet>& x)
		{ std::for_each(x.begin(), x.end(), [&tmp](const ItemSet& x) { tmp.push_back(x); }); });
  return tmp;


  
  // for(auto it = begin(); it != end; ++it) {
  //   auto it2 = boost::next(it);
  //   while(it2 != this->end() && it->matches(*it2, boost::prior(it2->end()))) {
  //     //Maybe assert
  //     ItemSet c(*it);
  //     c.push_back(*boost::prior(it2->end()));
      
  //     //all k-1 subsets of c
  //     bool notFound = false;
  //     for(auto x = c.begin(); x != c.end(); ++x) {
  // 	auto sub = c.subset(x);
  // 	if(!std::binary_search(this->begin(), this->end(), sub)) {
  // 	  notFound = true;
  // 	  break;
  // 	}
  //     }

  //     if(!notFound) {
  // 	c.determine_count(trans.begin(), trans.end());
  // 	//do we need to check for duplicity?
  // 	if(c.support(trans.size()) >= minsup)
  // 	   tmp.push_back(c);
  //     }
  //     ++it2;
  //   }
  // }

  return tmp;
}
