#include <iostream>

#include <gdkmm/screen.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/stylecontext.h>
#include <gtkmm/cssprovider.h>

struct StyleExample : Gtk::Window {
  Gtk::Button button_;
  // Glib::RefPtr<Gtk::StyleContext> style_context_;
  Glib::RefPtr<Gtk::CssProvider> css_provider_;
  std::string css_path_;

  StyleExample(char* css_path)
    : button_{"My Button"},
      // style_context_{Gtk::StyleContext::create()},
      // style_context_{get_style_context()},
      css_provider_{Gtk::CssProvider::create()},
      css_path_{css_path} {
    // Setup css style
    loadCss();

    // Setup widigets
    property_title() = "My Window";
    button_.signal_clicked().connect([] {
      std::cout << "My Button Clicked!\n";
    });
    button_.signal_clicked().connect([this] {
      this->loadCss();
    });
    button_.show();
    add(button_);
  }

  void loadCss() {
    css_provider_->load_from_path(css_path_);
    Gtk::StyleContext::add_provider_for_screen(
        Gdk::Screen::get_default(), css_provider_, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    // style_context_->add_provider(css_provider_, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  }
};

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: <program-name> <css file>\n";
    return 1;
  }
  auto app = Gtk::Application::create();
  StyleExample style_example{argv[1]};
  return app->run(style_example);
}
