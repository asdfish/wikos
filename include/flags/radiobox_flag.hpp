#ifndef RADIOBOX_FLAG_HPP
#define RADIOBOX_FLAG_HPP

#include <flags/flag_base.hpp>

class RadioboxFlag : public FlagBase {
  public:
    std::vector<std::string> items;
    int selection = 0;

    RadioboxFlag(const std::string&, const std::string&, const std::vector<std::string>&);

    void add_to_json(Json::Value&) override;
    void add_to_tab(ftxui::Component) override;
    std::string as_string() override;
    bool check_json(Json::Value&) override;
    void set_default() override;
    void set_from_json(Json::Value&) override;
};

#endif
