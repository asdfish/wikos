#include <commands/init.hpp>
#include <utils/flag_definitions.hpp>
#include <utils/files.hpp>
#include <utils/vectors.hpp>

#include <json/json.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <system_error>

int init(void) {
  std::vector<std::string> source_files = get_source_files();

  if(std::filesystem::exists(".wikos.jsonc")) {
    std::cout << "wikos.jsonc already exists. Overide? (y): ";
    std::string confirmation;
    std::cin >> confirmation;

    std::error_code error;
    error.clear();

    if(std::filesystem::is_regular_file(".wikos.jsonc"))
      std::filesystem::remove(".wikos.jsonc", error);
    else
      std::filesystem::remove_all(".wikos.jsonc", error);

    if(error.value() != 0) {
      std::cout << "Failed to remove .wikos.jsonc\n";
      return -1;
    }
  }

  std::ofstream wikos_jsonc(".wikos.jsonc");
  if(!wikos_jsonc.good()) {
    std::cout << "Failed to open .wikos.jsonc for writing\n";
    return -1;
  }

  flags_define_default();

  Json::Value root;
  for(unsigned int i = 0; i < flags.size(); i ++)
    flags[i]->add_to_json(root);

  Json::Value files;
  for(unsigned int i = 0; i < source_files.size(); i ++)
    files[i] = source_files[i];
  root["files"] = files;


  Json::FastWriter writer;
  wikos_jsonc << writer.write(root);

  wikos_jsonc.close();
  return 0;
}
