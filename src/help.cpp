#include <help.hpp>

#include <iostream>

int help(bool print_title) {
  if(print_title) {
    std::cout << "bikos - tui ikos wrapper\n"
                 "\n";
  }
  std::cout << "Syntax: bikos [command]\n"
               "\n"
               "Commands:\n"
               "\tconfig - Configures ikos with tui.\n"
               "\thelp   - Prints this message.\n"
               "\tinit   - Initiates bikos in current directory.\n"
               "\trun    - Runs ikos with configuration.\n";

  return 0;
}
