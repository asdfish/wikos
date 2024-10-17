#include <flags/checkbox_separated_flag.hpp>

std::string CheckboxSeparatedFlag::as_string() {
  std::vector<std::string> selected;
  for(unsigned int i = 0; i < items.size(); i ++)
    if(*selections[i])
      selected.push_back(items[i]);

  std::string output;
  for(unsigned int i = 0; i < selected.size(); i ++) {
    output += header + selected[i];
    if(i != selected.size() - 1)
      output += " ";
  }

  return output;
}
