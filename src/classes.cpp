#include <classes.hpp>

#include <ftxui/component/component_options.hpp>

CheckboxFlag::CheckboxFlag(const std::string& name, const std::vector<std::string>& items) {
  this->name = name;
  this->items = items;
  
  selections.reserve(items.size());
  for(unsigned int i = 0; i < items.size(); i ++)
    selections.push_back(new bool(false));
}
CheckboxFlag::~CheckboxFlag() {
  for(unsigned int i = 0; i < selections.size(); i ++)
    delete selections.at(i);
}

void CheckboxFlag::add_to_tab(ftxui::Component tab) {
  ftxui::Component container = ftxui::Container::Vertical({});
  for(unsigned int i = 0; i < items.size(); i ++)
    container->Add(ftxui::Checkbox(&items[i], selections[i]));

  tab->Add(container);
}

bool CheckboxFlag::check_syntax(Json::Value& json_root) {
  if(!json_root[name].isArray())
    return false;

  for(unsigned int i = 0; i < json_root[name].size(); i ++)
    if(!json_root[name][i].isBool())
      return false;

  return true;
}

void CheckboxFlag::into_json(Json::Value& json_root) {
  Json::Value array;
  for(unsigned int i = 0; i < selections.size(); i ++)
    array[i] = *selections[i];

  json_root[name] = array;
}

RadioboxFlag::RadioboxFlag(const std::string& name, const std::vector<std::string>& items) {
  this->name = name;
  this->items = items;
}

void RadioboxFlag::add_to_tab(ftxui::Component tab) {
  ftxui::Component container = ftxui::Container::Vertical({});
  container->Add(ftxui::Radiobox(&items, &selection));

  tab->Add(container);
}

bool RadioboxFlag::check_syntax(Json::Value& json_root) {
  if(!json_root[name].isConvertibleTo(Json::ValueType::uintValue))
    return false;

  if(json_root[name] >= items.size())
    return false;

  return true;
}

void RadioboxFlag::into_json(Json::Value& json_root) {
  json_root[name] = selection;
}
