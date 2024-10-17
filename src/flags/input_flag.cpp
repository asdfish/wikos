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
  ftxui::Component inputs = ftxui::Container::Vertical({});
  for(unsigned int i = 0; i < items.size(); i ++)
    inputs->Add(ftxui::Input(&items[i]));

  ftxui::Component buttons = ftxui::Container::Vertical({
    ftxui::Button({
      .label = "Add Input",
      .on_click = [&] {
        items.push_back(std::string(""));
        inputs->Add(ftxui::Input(&items.back()));
      }
    })
  });

  ftxui::Component container = ftxui::Container::Horizontal({
    inputs,
    buttons,
  });

  tab->Add(container);
}

bool InputFlag::check_json(Json::Value& root) {
  if(!root[name].isArray())
    return false;

  for(unsigned int i = 0; i < root[name].size(); i ++)
    if(!root[name][i].isString())
      return false;

  return true;
};

void InputFlag::set_default() {
  for(unsigned int i = 0; i < items.size(); i ++)
    items[i] = "";
};

void InputFlag::set_from_json(Json::Value& root) {
  if(!check_json(root)) {
    set_default();
    return;
  }

  items.clear();
  items.reserve(root[name].size());
  for(unsigned int i = 0; i < root[name].size(); i ++)
    items.push_back(root[name][i].asString());
}
