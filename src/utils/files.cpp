#include <utils/files.hpp>

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
