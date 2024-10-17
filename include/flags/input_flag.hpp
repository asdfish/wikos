#ifndef INPUT_FLAG_HPP
#define INPUT_FLAG_HPP

#include <flags/flag_base.hpp>

class InputFlag : public FlagBase {
  public:
    std::string contents = "";

    InputFlag(const std::string&, const std::string&);
    void add_to_json(Json::Value&);
    void add_to_tab(ftxui::Component);
    std::string as_string(void);
    bool check_json(Json::Value&);
    void set_default(void);
    void set_from_json(Json::Value&);
};

#endif
