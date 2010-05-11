//prj
#include "ItemSetContainer.hh"

//std
#include <iostream>
#include <string>
#include <algorithm>

//boost
#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace {
  struct SetSize {
    bool operator() (const ItemSet a, const ItemSet b) {
      return a.size() < b.size();
    }
  };
};

int main(int argc, char *argv[]) {


  // Declare the supported options.
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "help message")
    ("file", po::value<std::string>(), "input file")
    ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);    

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }

  if (vm.count("file")) {
    std::cout << "Input file: "
	 << vm["file"].as<std::string>() << ".\n";
  } else {
    std::cout << "No input file. \n";
    return EXIT_FAILURE;
  }

  ItemSetContainer a(vm["file"].as<std::string>());

  //find the largest itemset, lambdas....
  ItemSetContainer::iterator largest = std::max_element(a.begin(), a.end(), SetSize());
  std::cout << "Largest set:" << std::endl;
  std::cout << *largest << std::endl;

  //show all sets that are contained within the largest set, works but too much output :(
  /*
  for(ItemSetContainer::const_iterator it = a.begin(); it != a.end(); ++it) {
    if(largest->contains(*it)) {
      for(ItemSet::const_iterator it2 = it->begin();  it2 != it->end(); ++it2)
	std::cout << *it2 << " ";
      std::cout << std::endl;
    }
  }
  */
  
  std::cout << "Remove the middle:" << std::endl;
  ItemSet::iterator it = largest->begin();
  std::advance(it, largest->size() / 2);
  ItemSet subset = largest->subset(it);
  std::cout << subset << std::endl;
  
  std::cout << "Match on the first " << (largest->size() / 2) <<  " items:" << std::endl;
  if(subset.matches(*largest, it))
    std::cout << "True.";
  else
    std::cout << "You can't read this.";
  std::cout << std::endl << std::endl;

  

  //copy a portition to make init_pass more readable
  ItemSetContainer portition;
  std::copy(a.begin(), a.begin() + 5, std::back_inserter(portition));
  //a reduced portition, show it
  std::cout << "The first 5 ItemSetContainers contain: " << std::endl;
  for(ItemSetContainer::const_iterator it = portition.begin();
      it != portition.end(); ++it)
    std::cout << *it;

  std::cout << std::endl << std::endl;

  //showing off init_pass
  //init pass uses operator< for ItemSets, it works
  std::cout << "init_pass on those 5 yields: " << std::endl;
  std::map<ItemSet, unsigned int> init_pass = portition.init_pass();
  for(std::map<ItemSet, unsigned int>::const_iterator it = init_pass.begin();
      it != init_pass.end(); ++it)
    std::cout << it->first << " times: " << it->second << std::endl;
}
