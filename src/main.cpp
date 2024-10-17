#include <commands/config.hpp>
#include <commands/help.hpp>
#include <commands/init.hpp>
#include <commands/run.hpp>

#include <iostream>

int main(int argc, const char* argv[]) {
  if(argc == 1) {
    help(true);
    return -1;
  }

  std::string command = argv[1];

  int result = 0;

  if(command == "config")
    result = config();
  else if(command == "help")
    result = help(true);
  else if(command == "init")
    result = init();
  else if(command == "run")
    result = run();
  else {
    std::cerr << "Command " << command << " not recognized.\n";
    result = help(false);
  }

  return result;
}
