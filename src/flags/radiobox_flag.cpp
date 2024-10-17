#include <flags/radiobox_flag.hpp>

#include <ftxui/component/component_options.hpp>

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
  if(!root[name].isConvertibleTo(Json::ValueType::uintValue) || root[name].asUInt() >= items.size())
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
