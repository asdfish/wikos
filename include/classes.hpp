#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <string>
#include <vector>

#include <ftxui/component/component.hpp>
#include <json/json.h>

class Flag {
  public:
    std::string name;
    std::vector<std::string> items;

    virtual void add_to_tab(ftxui::Component tab) = 0;
    virtual bool check_syntax(Json::Value&) = 0;
    virtual void into_json(Json::Value&) = 0;

    virtual ~Flag() {}
};

class CheckboxFlag : public Flag {
  public:
    std::vector<bool*> selections;

    CheckboxFlag(const std::string& name, const std::vector<std::string>& items);
    ~CheckboxFlag() override;

    void add_to_tab(ftxui::Component tab) override;
    bool check_syntax(Json::Value&) override;
    void into_json(Json::Value&) override;
};

class DropdownFlag : public Flag {
  public:
    unsigned int selection = 0;

    DropdownFlag(const std::string& name, const std::vector<std::string>& items);

    bool check_syntax(Json::Value&) override;
    void into_json(Json::Value&) override;
};

#endif
