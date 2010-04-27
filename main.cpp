//prj
#include "ItemSetContainer.hh"

//std
#include <iostream>
#include <string>

//boost
#include <boost/program_options.hpp>

namespace po = boost::program_options;

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
  for(ItemSetContainer::ItemSets::iterator it = a.begin();
      it != a.end(); ++it) {
    for(ItemSet::const_iterator it2 = it->begin();
	it2 != it->end(); ++it2)
      std::cout << *it2 << " ";
    std::cout << std::endl;
  }
}
