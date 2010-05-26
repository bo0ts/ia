//prj
#include "ItemSetContainer.hh"
#include "str_pool.hh"

//std
#include <iostream>
#include <string>
#include <algorithm>

#include <vector>

//boost
#include <boost/program_options.hpp>
#include <boost/assign.hpp>

using namespace boost::assign;

namespace po = boost::program_options;

int main(int argc, char *argv[]) {

  const char* logo = 
    "+------------------------------------------------------------------------+\n"
    "|  +------------------------------------------------------------------+  |\n"
    "|  |                 _            ___                                 |  |\n"
    "|  |        __ _ ___| | ___ __   ( _ )    _ __  _ __ ___  _ __        |  |\n"
    "|  |       / _` / __| |/ / '__|  / _ \\/\\ | '_ \\| '_ ` _ \\| '__|       |  |\n"
    "|  |      | (_| \\__ \\   <| |    | (_>  < | |_) | | | | | | |          |  |\n"
    "|  |       \\__,_|___/_|\\_\\_|     \\___/\\/ | .__/|_| |_| |_|_|          |  |\n"
    "|  |                                     |_|                          |  |\n"
    "|  |                          _            _   _                      |  |\n"
    "|  |      _ __  _ __ ___   __| |_   _  ___| |_(_) ___  _ __  ___      |  |\n"
    "|  |     | '_ \\| '__/ _ \\ / _` | | | |/ __| __| |/ _ \\| '_ \\/ __|     |  |\n"
    "|  |     | |_) | | | (_) | (_| | |_| | (__| |_| | (_) | | | \\__ \\     |  |\n"
    "|  |     | .__/|_|  \\___/ \\__,_|\\__,_|\\___|\\__|_|\\___/|_| |_|___/     |  |\n"
    "|  |     |_|                                                          |  |\n"
    "|  |                                                                  |  |\n"
    "|  +------------------------------------------------------------------+  |\n"
    "+------------------------------------------------------------------------+\n";

  std::cout << logo << std::endl;

  for(auto i = 0; i < 5; ++i)
    std::cout << "ATTN: tags.txt works good with minsup 0.01" << std::endl;

  std::cout << std::endl;

  // Declare the supported options.
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "help message")
    ("file", po::value<std::string>(), "input file")
    ("minsup", po::value<double>(), "minsup")
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

  double minsup;
  if (vm.count("minsup")) {
    std::cout << "Minsup: "
	 << vm["minsup"].as<double>() << ".\n";
    minsup = vm["minsup"].as<double>();
  } else {
    std::cout << "No minsup. Assuming 0.5";
    minsup = 0.5;
  }
  
  str_pool pool;

  ItemSetContainer transactions(vm["file"].as<std::string>(), pool);

  std::vector<ItemSetContainer> runs;
  runs.push_back(transactions.init_pass(minsup));

  while(!runs.back().empty()) {
     runs.push_back(runs.back().generate_candidates(transactions, minsup));
     std::cout << "Result of generation: " << std::endl 
	       << runs.back() << std::endl << std::endl;
  }
}
