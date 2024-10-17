#include <flags/source_files_flag.hpp>
#include <utils/files.hpp>

SourceFilesFlag::SourceFilesFlag(const std::string& name) {
  this->name = name;
}
SourceFilesFlag::~SourceFilesFlag(void) {
  if(file_selections.size() == 0)
    return;

  for(unsigned int i = 0; i < file_selections.size(); i ++)
    delete file_selections[i];
}

void SourceFilesFlag::add_to_json(Json::Value& root) {
  Json::Value array;

  for(unsigned int i = 0; i < file_paths.size(); i ++) {
    Json::Value object;
    object["path"] = Json::Value(file_paths[i]);
    object["selected"] = Json::Value(*file_selections[i]);

    array[i] = object;
  }

  root[name] = array;
}

void SourceFilesFlag::add_to_tab(ftxui::Component tab) {
  ftxui::Component container = ftxui::Container::Vertical({});
  for(unsigned int i = 0; i < file_paths.size(); i ++)
    container->Add(ftxui::Checkbox(file_paths[i], file_selections[i]));

  tab->Add(container);
}

std::string SourceFilesFlag::as_string(void) {
  std::vector<std::string> selected_files;
  for(unsigned int i = 0; i < file_selections.size(); i ++)
    if(*file_selections[i])
      selected_files.push_back(file_paths[i]);

  std::string output;
  for(unsigned int i = 0; i < selected_files.size(); i ++) {
    output += selected_files[i];
    if(i != selected_files.size() - 1)
      output += " ";
  }

  return output;
}

bool SourceFilesFlag::check_json(Json::Value& root) {
  if(!root[name].isArray())
    return false;
  
  for(unsigned int i = 0; i < root[name].size(); i ++) {
    if(!root[name][i].isObject())
      return false;

    if(!root[name][i]["path"].isString() || !root[name][i]["selected"].isBool())
      return false;
  }

  return true;
}

void SourceFilesFlag::set_default(void) {
  file_paths = get_source_files();
  for(unsigned int i = 0; i < file_paths.size(); i ++)
    file_selections.push_back(new bool(false));
}

void SourceFilesFlag::set_from_json(Json::Value& root) {
  if(!check_json(root)) {
    set_default();
    return;
  }

  for(unsigned int i = 0; i < root[name].size(); i ++) {
    file_paths.push_back(root[name]["path"].asString());
    file_selections.push_back(new bool(root[name]["selected"].asBool()));
  }
}
