#include <utils/files.hpp>
#include <utils/vectors.hpp>

#include <filesystem>

#define DIRECTORY_FUNCTION(SELECTOR) {                                                                               \
  std::vector<std::string> output_buffer;                                                                            \
  for(const std::filesystem::directory_entry& directory_entry : std::filesystem::directory_iterator(directory_path)) \
    if(SELECTOR)                                                                                                     \
      output_buffer.push_back(directory_entry.path().string());                                                      \
                                                                                                                     \
  return output_buffer;                                                                                              \
}

std::vector<std::string> directory_files(const std::string& directory_path)
  DIRECTORY_FUNCTION(directory_entry.is_regular_file())
std::vector<std::string> directory_directories(const std::string& directory_path)
  DIRECTORY_FUNCTION(directory_entry.is_directory())

std::vector<std::string> get_source_files(void) {
  std::vector<std::string> source_files;

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

  return source_files;
}
