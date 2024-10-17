#ifndef CHECKBOX_BASE_HPP
#define CHECKBOX_BASE_HPP

#include <flags/flag_base.hpp>

class CheckboxBase : public FlagBase {
  public:
    std::vector<std::string> items;
    std::vector<bool*> selections;

    CheckboxBase(const std::string& header, const std::string& name, const std::vector<std::string>& items);
    ~CheckboxBase() override;

    void add_to_json(Json::Value&) override;
    void add_to_tab(ftxui::Component tab) override;
    bool check_json(Json::Value&) override;
    void set_default() override;
    void set_from_json(Json::Value&) override;
};

#endif
