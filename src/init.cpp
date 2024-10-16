#include <flags.hpp>
#include <files.hpp>
#include <init.hpp>
#include <utils.hpp>

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

  if(std::filesystem::exists("./.bikos.jsonc")) {
    std::cout << "./bikos.jsonc already exists. Overide? (y): ";
    std::string confirmation;
    std::cin >> confirmation;

    std::error_code error;
    error.clear();

    if(std::filesystem::is_regular_file("./.bikos.jsonc"))
      std::filesystem::remove("./.bikos.jsonc", error);
    else
      std::filesystem::remove_all("./.bikos.jsonc", error);

    if(error.value() != 0) {
      std::cout << "Failed to remove ./.bikos.jsonc\n";
      return -1;
    }
  }

  std::ofstream bikos_jsonc("./.bikos.jsonc");
  if(!bikos_jsonc.good()) {
    std::cout << "Failed to open ./.bikos.jsonc for writing\n";
    return -1;
  }
  bikos_jsonc.close();
  return 0;
}
