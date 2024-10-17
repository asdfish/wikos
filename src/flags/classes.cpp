#include <flags/classes.hpp>

#include <ftxui/component/component_options.hpp>

CheckboxFlag::CheckboxFlag(const std::string& header, const std::string& name, const std::vector<std::string>& items) {
  this->header = header;
  this->name = name;
  this->items = items;

  selections.reserve(items.size());
  for(unsigned int i = 0; i < items.size(); i ++)
    selections.push_back(new bool);
}
CheckboxFlag::~CheckboxFlag() {
  for(unsigned int i = 0; i < selections.size(); i ++)
    delete selections.at(i);
}

void CheckboxFlag::add_to_json(Json::Value& root) {
  Json::Value array;
  for(unsigned int i = 0; i < selections.size(); i ++)
    array[i] = *selections[i];

  root[name] = array;
}

void CheckboxFlag::add_to_tab(ftxui::Component tab) {
  ftxui::Component container = ftxui::Container::Vertical({});
  for(unsigned int i = 0; i < items.size(); i ++)
    container->Add(ftxui::Checkbox(&items[i], selections[i]));

  tab->Add(container);
}

bool CheckboxFlag::check_json(Json::Value& root) {
  if(!root[name].isArray())
    return false;

  for(unsigned int i = 0; i < root[name].size(); i ++)
    if(!root[name][i].isBool())
      return false;

  return true;
}

void CheckboxFlag::set_default() {
  for(unsigned int i = 0; i < items.size(); i ++)
    *selections[i] = false;
}

void CheckboxFlag::set_from_json(Json::Value& root) {
  if(!check_json(root)) {
    set_default();
    return;
  }

  for(unsigned int i = 0; i < items.size(); i ++)
    *selections[i] = root[name][i].asBool();
}

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

RadioboxFlag::RadioboxFlag(const std::string& header, const std::string& name, const std::vector<std::string>& items) {
  this->header = header;
  this->name = name;
  this->items = items;
}

void RadioboxFlag::add_to_json(Json::Value& root) {
  root[name] = selection;
}

void RadioboxFlag::add_to_tab(ftxui::Component tab) {
  ftxui::Component container = ftxui::Container::Vertical({});
  container->Add(ftxui::Radiobox(&items, &selection));

  tab->Add(container);
}

bool RadioboxFlag::check_json(Json::Value& root) {
  if(!root[name].isConvertibleTo(Json::ValueType::uintValue))
    return false;

  if(root[name].asUInt() >= items.size())
    return false;

  return true;
}

void RadioboxFlag::set_default() {
  selection = 0;
}

void RadioboxFlag::set_from_json(Json::Value& root) {
  if(!check_json(root)) {
    set_default();
    return;
  }

  selection = root[name].asInt();
}
