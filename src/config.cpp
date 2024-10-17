#include <config.hpp>
#include <flags.hpp>

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <json/json.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int config(void) {
  flags_init();

  if(!std::filesystem::is_regular_file(".wikos.jsonc")) {
    std::cerr << ".wikos.jsonc not found. Consider running \"wikos init\" first.\n";
    return -1;
  }

  std::ifstream wikos_jsonc(".wikos.jsonc");
  if(!wikos_jsonc.good()) {
    std::cerr << ".wikos.jsonc cannot be read\n";
    return -1;
  }
  
  std::stringstream wikos_jsonc_stringstream;
  wikos_jsonc_stringstream << wikos_jsonc.rdbuf();
  std::string wikos_jsonc_string = wikos_jsonc_stringstream.str();

  wikos_jsonc.close();

  Json::Value root;
  Json::Reader reader;
  reader.parse(wikos_jsonc_string, root);

  std::vector<std::string> menu_names;
  menu_names.reserve(flags.size());
  for(unsigned int i = 0; i < flags.size(); i ++)
    menu_names.push_back(flags[i]->name);

  ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

  int selected_menu = 0;
  ftxui::Component menu = ftxui::Menu(&menu_names, &selected_menu);

  ftxui::Component tabs = ftxui::Container::Tab({}, &selected_menu);
  for(unsigned int i = 0; i < flags.size(); i ++)
    flags[i]->add_to_tab(tabs);

  int exit_state = 0;
  ftxui::Component buttons = ftxui::Container::Vertical({
    ftxui::Button({
      .label = "Save",
      .on_click = [&] {
        exit_state = 1;
        screen.Exit();
      }
    }),
    ftxui::Button({
      .label = "Exit",
      .on_click = [&] {
        screen.Exit();
      }
    })
  });

  ftxui::Component container = ftxui::Container::Horizontal({
    menu,
    tabs,
    buttons,
  });

  ftxui::Component renderer = ftxui::Renderer(container, [&] {
    return ftxui::hbox({
      menu->Render(),
      ftxui::separator(),
      tabs->Render(),
      ftxui::separator(),
      buttons->Render(),
    }) | ftxui::border;
  });

  screen.Loop(renderer);

  return 0;
}
