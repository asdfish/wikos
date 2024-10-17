#include <flags/checkbox_base.hpp>

#include <ftxui/component/component_options.hpp>

CheckboxBase::CheckboxBase(const std::string& header, const std::string& name, const std::vector<std::string>& items) {
  this->header = header;
  this->name = name;
  this->items = items;

  selections.clear();
  selections.reserve(items.size());
  for(unsigned int i = 0; i < items.size(); i ++)
    selections.push_back(new bool);
}
CheckboxBase::~CheckboxBase(void) {
  for(unsigned int i = 0; i < selections.size(); i ++)
    delete selections.at(i);
}

void CheckboxBase::add_to_json(Json::Value& root) {
  Json::Value array;
  for(unsigned int i = 0; i < selections.size(); i ++)
    array[i] = *selections[i];

  root[name] = array;
}

void CheckboxBase::add_to_tab(ftxui::Component tab) {
  ftxui::Component container = ftxui::Container::Vertical({});
  for(unsigned int i = 0; i < items.size(); i ++)
    container->Add(ftxui::Checkbox(&items[i], selections[i]));

  tab->Add(container);
}

bool CheckboxBase::check_json(Json::Value& root) {
  if(!root[name].isArray())
    return false;

  for(unsigned int i = 0; i < root[name].size(); i ++)
    if(!root[name][i].isBool())
      return false;

  return true;
}

void CheckboxBase::set_default(void) {
  for(unsigned int i = 0; i < items.size(); i ++)
    *selections[i] = false;
}

void CheckboxBase::set_from_json(Json::Value& root) {
  if(!check_json(root)) {
    set_default();
    return;
  }

  for(unsigned int i = 0; i < items.size(); i ++)
    *selections[i] = root[name][i].asBool();
}
