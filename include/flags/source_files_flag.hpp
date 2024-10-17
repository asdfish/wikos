#ifndef SOURCE_FILES_FLAG_HPP
#define SOURCE_FILES_FLAG_HPP

#include <flags/flag_base.hpp>

class SourceFilesFlag : public FlagBase {
  public:
    std::vector<std::string> file_paths;
    std::vector<bool*> file_selections;

    SourceFilesFlag(const std::string&);
    ~SourceFilesFlag(void) override;

    void add_to_json(Json::Value&) override;
    void add_to_tab(ftxui::Component) override;
    std::string as_string(void) override;
    bool check_json(Json::Value&) override;
    void set_default(void) override;
    void set_from_json(Json::Value&) override;
};

#endif
