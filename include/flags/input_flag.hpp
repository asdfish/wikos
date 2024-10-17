#ifndef INPUT_FLAG_HPP
#define INPUT_FLAG_HPP

#include <flags/flag_base.hpp>

class InputFlag : public FlagBase {
  public:
    int selection = 0;

    InputFlag(const std::string& header, const std::string& name, const std::vector<std::string>& items);

    void add_to_json(Json::Value&) override;
    void add_to_tab(ftxui::Component tab) override;
    bool check_json(Json::Value&) override;
    void set_default() override;
    void set_from_json(Json::Value&) override;
};

#endif
