#ifndef CHECKBOX_FLAG_HPP
#define CHECKBOX_FLAG_HPP

#include <flags/flag_base.hpp>

class CheckboxFlag : public FlagBase {
  public:
    std::vector<bool*> selections;

    CheckboxFlag(const std::string& header, const std::string& name, const std::vector<std::string>& items);
    ~CheckboxFlag() override;

    void add_to_json(Json::Value&) override;
    void add_to_tab(ftxui::Component tab) override;
    bool check_json(Json::Value&) override;
    void set_default() override;
    void set_from_json(Json::Value&) override;
};

#endif
