#include <flags/input_flag.hpp>

#include <ftxui/component/component_options.hpp>

InputFlag::InputFlag(const std::string& header, const std::string& name, const std::vector<std::string>& items) {
  this->header = header;
  this->name = name;
  this->items = items;
}

void InputFlag::add_to_json(Json::Value& root) {
  Json::Value array;
  for(unsigned int i = 0, j = 0; i < items.size(); i ++)
    if(items[i].length() != 0) {
      array[j] = items[i];
      j ++;
    }

  root[name] = array;
}

void InputFlag::add_to_tab(ftxui::Component tab) {
  ftxui::Component container = ftxui::Container::Horizontal({});

  ftxui::Component inputs = ftxui::Container::Vertical({});
}

bool InputFlag::check_json(Json::Value&) {
  return false;
};

void InputFlag::set_default() {
};

void InputFlag::set_from_json(Json::Value&) {
};
