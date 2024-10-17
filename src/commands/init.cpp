#include <flag_definitions.hpp>
#include <files.hpp>
#include <init.hpp>
#include <utils.hpp>

#include <json/json.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <system_error>

#include <iostream>

int init(void) {
  std::vector<std::string> source_files;

  {
    std::vector<std::string> directories;
    directories.push_back("."); // bootstrap

    while(!directories.empty()) {
      if(directories.size() == 0)
        break;

      std::string current_directory = vector_pop(&directories);

      std::vector<std::string> new_directories = directory_directories(current_directory);
      vector_append(&directories, &new_directories);

      std::vector<std::string> new_files = directory_files(current_directory);
      for(const std::string& new_file : new_files)
        if(new_file.ends_with(".c") || new_file.ends_with(".cpp"))
          source_files.push_back(new_file);
    }
  }

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
