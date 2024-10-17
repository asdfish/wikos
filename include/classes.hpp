#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <memory>
#include <string>
#include <vector>

#include <ftxui/component/component.hpp>
#include <json/json.h>

class Flag {
  public:
    std::string header;
    std::string name;
    std::vector<std::string> items;

    virtual void add_to_json(Json::Value&) = 0;
    virtual void add_to_tab(ftxui::Component tab) = 0;
    virtual bool check_json(Json::Value&) = 0;
    virtual void set_default() = 0;
    /*virtual void set_from_json(Json::Value&) = 0;*/

    virtual ~Flag() {}
};

class CheckboxFlag : public Flag {
  public:
    std::vector<bool*> selections;

    CheckboxFlag(const std::string& header, const std::string& name, const std::vector<std::string>& items);
    ~CheckboxFlag() override;

    void add_to_json(Json::Value&) override;
    void add_to_tab(ftxui::Component tab) override;
    bool check_json(Json::Value&) override;
    void set_default() override;
};

class RadioboxFlag : public Flag {
  public:
    int selection = 0;

    RadioboxFlag(const std::string& header, const std::string& name, const std::vector<std::string>& items);
    ~RadioboxFlag() override;

    void add_to_json(Json::Value&) override;
    void add_to_tab(ftxui::Component tab) override;
    bool check_json(Json::Value&) override;
    void set_default() override;
};

#endif
