#include <flags/input_flag.hpp>

InputFlag::InputFlag(const std::string& header, const std::string& name) {
  this->header = header;
  this->name = name;
}

void InputFlag::add_to_json(Json::Value& root) {
  root[name] = contents;
}

void InputFlag::add_to_tab(ftxui::Component tab) {
  tab->Add(ftxui::Input(&contents));
}

std::string InputFlag::as_string(void) {
  return contents;
}

bool InputFlag::check_json(Json::Value& root) {
  if(!root[name].isString())
    return false;
  return true;
}

void InputFlag::set_default(void) {
  contents = "";
}

void InputFlag::set_from_json(Json::Value& root) {
  if(!check_json(root)) {
    set_default();
    return;
  }

  contents = root[name].asString();
}
