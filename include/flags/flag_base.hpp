#ifndef FLAG_BASE_HPP
#define FLAG_BASE_HPP

#include <memory>
#include <string>
#include <vector>

#include <ftxui/component/component.hpp>
#include <json/json.h>

class FlagBase {
  public:
    std::string header;
    std::string name;
    std::vector<std::string> items;

    virtual void add_to_json(Json::Value&) = 0;
    virtual void add_to_tab(ftxui::Component tab) = 0;
    virtual bool check_json(Json::Value&) = 0;
    virtual void set_default() = 0;
    virtual void set_from_json(Json::Value&) = 0;

    virtual ~FlagBase() {}
};

#endif
