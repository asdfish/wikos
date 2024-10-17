#ifndef FILES_HPP
#define FILES_HPP

#include <string>
#include <vector>

extern std::vector<std::string> directory_files(const std::string& directory_path);
extern std::vector<std::string> directory_directories(const std::string& directory_path);
extern std::vector<std::string> get_source_files(void);

#endif
