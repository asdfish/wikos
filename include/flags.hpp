#ifndef FLAGS_HPP
#define FLAGS_HPP

#include <string>
#include <vector>

#include <json/json.h>

class Flag {
  public:
    std::string name;
    std::vector<std::string> items;

    /*virtual void add_to_container(void) = 0;*/
    virtual bool check_syntax(Json::Value&) = 0;
    virtual void into_json(Json::Value&) = 0;
};

class CheckboxFlag : public Flag {
  public:
    std::vector<bool> selections;

    CheckboxFlag(const std::string& name, const std::vector<std::string>& items);

    bool check_syntax(Json::Value&);
    void into_json(Json::Value&);
};

class DropdownFlag : public Flag {
  public:
    unsigned int selection = 0;

    DropdownFlag(const std::string& name, const std::vector<std::string>& items);

    bool check_syntax(Json::Value&);
    void into_json(Json::Value&);
};

#endif
