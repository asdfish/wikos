#include <flags/checkbox_array_flag.hpp>

std::string CheckboxArrayFlag::as_string() {
  std::string output = header + "=\'";
  for(unsigned int i = 0; i < items.size(); i ++) {
    output += items[i];
    if(i != items.size() - 1)
      output += ",";
  }
  output += "\'";

  return output;
}
