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
  bikos_jsonc <<     "{\n"
                     "\t\"files\": [\n";
  for(unsigned int i = 0; i < source_files.size(); i ++) {
    bikos_jsonc <<   "\t\t\"" << source_files[i] << "\"";
    if (i != source_files.size() - 1) [[unlikely]]
      bikos_jsonc << ",";
    bikos_jsonc <<   '\n';
  }
  bikos_jsonc <<     "\t],\n"
                     "\t\"checks\": [\n";
  for(unsigned int i = 0; i < check_names.size(); i ++) {
    bikos_jsonc <<   "\t\tfalse";
    if(i != check_names.size() - 1)
      bikos_jsonc << ",";
    bikos_jsonc <<   '\n';
  }
  bikos_jsonc <<     "\t],\n"
                     "\t\"numeric_abstract_domain\": 0,\n"
                     "\t\"entry_points\": [],\n"
                     "\t\"jobs\": 1,\n"
                     "\t\"optimization\": 1,\n"
                     "\t\"intra_procedural\": false,\n"
                     "\t\"widening_strategy\": 0,\n"
                     "\t\"narrowing_strategy\": 3,\n"
                     "\t\"widening_delays\": [],\n"
                     "\t\"partitioning\": 0,\n"
                     "\t\"miscellaneous\": [\n";
  for(unsigned int i = 0; i < miscellaneous.size(); i ++) {
    bikos_jsonc <<   "\t\tfalse";
    if(i != miscellaneous.size() - 1)
      bikos_jsonc << ",";
    bikos_jsonc <<   "\n";
  }
  bikos_jsonc <<     "\t]\n"
                     "}\n";
  bikos_jsonc.close();
  return 0;
}
