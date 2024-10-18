#include <flags/checkbox_array_flag.hpp>

std::string CheckboxArrayFlag::as_string(void) {
  std::vector<std::string> selected;
  for(unsigned int i = 0; i < items.size(); i ++)
    if(*selections[i])
      selected.push_back(items[i]);

  if(selected.size() == 0)
    return "";

  std::string output = header + "\'";
  for(unsigned int i = 0; i < selected.size(); i ++) {
    output += selected[i];
    if(i != selected.size() - 1)
      output += ",";
  }
  output += "\'";

  return output;
}
