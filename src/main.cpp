/*#include <config.hpp>*/
/*#include <help.hpp>*/
/*#include <init.hpp>*/
/*#include <run.hpp>*/

/*int main(int argc, const char* argv[]) {*/
/*  if(argc == 1) {*/
/*    help(true);*/
/*    return -1;*/
/*  }*/
/**/
/*  std::string command = argv[1];*/
/**/
/*  int result = 0;*/
/**/
/*  if(command == "config")*/
/*    result = config();*/
/*  else if(command == "help")*/
/*    result = help(true);*/
/*  else if(command == "init")*/
/*    result = init();*/
/*  else if(command == "run")*/
/*    result = run();*/
/*  else {*/
/*    std::cerr << "Command " << command << " not recognized.\n";*/
/*    result = help(false);*/
/*  }*/
/**/
/*  return result;*/
/*}*/

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <flags.hpp>

#include <string>
#include <vector>

int main() {
  ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

  flags_init();

  std::vector<std::string> menu_names;
  menu_names.reserve(flags.size());

  for(unsigned int i = 0; i < flags.size(); i ++)
    menu_names.push_back(flags[i]->name);

  int selected_menu = 0;
  ftxui::Component menu = ftxui::Menu(&menu_names, &selected_menu);

  ftxui::Component container = ftxui::Container::Horizontal({
    menu
  });

  ftxui::Component renderer = ftxui::Renderer(container, [&] {
    return ftxui::vbox({
      menu->Render(),
    });
  });

  screen.Loop(renderer);

  return 0;
}
