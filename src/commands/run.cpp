#include <commands/run.hpp>
#include <utils/flag_definitions.hpp>

#include <json/json.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

int run(void) {
  if(!std::filesystem::is_regular_file(".wikos.jsonc")) {
    std::cerr << ".wikos.jsonc does not exist. Consider running \"wikos init\"\n";
    return -1;
  }

  std::ifstream wikos_jsonc(".wikos.jsonc");
  if(!wikos_jsonc.good()) {
    std::cerr << "Failed to read from .wikos.jsonc\n";
    return -1;
  }

  std::stringstream wikos_jsonc_stringstream;
  wikos_jsonc_stringstream << wikos_jsonc.rdbuf();
  std::string wikos_jsonc_string = wikos_jsonc_stringstream.str();

  wikos_jsonc.close();

  Json::Value root;
  Json::Reader reader;
  reader.parse(wikos_jsonc_string, root);

  flags_define();
  for(unsigned int i = 0; i < flags.size(); i ++)
    flags[i]->set_from_json(root);

  std::stringstream command;
  for(unsigned int i = 0; i < flags.size(); i ++)
    command << flags[i]->as_string() << ' ';

  std::cout << command.str();
  return 0;
}
