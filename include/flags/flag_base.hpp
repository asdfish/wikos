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

    virtual void add_to_json(Json::Value&) = 0;
    virtual void add_to_tab(ftxui::Component) = 0;
    virtual std::string as_string(void) = 0;
    virtual bool check_json(Json::Value&) = 0;
    virtual void set_default(void) = 0;
    virtual void set_from_json(Json::Value&) = 0;

    virtual ~FlagBase(void) {}
};

#endif
