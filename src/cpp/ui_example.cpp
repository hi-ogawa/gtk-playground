#include <iostream>

#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>

// For convinience
template<typename T>
T* get_widget(const Glib::RefPtr<Gtk::Builder>& builder, const Glib::ustring& id) {
  T* ptr;
  builder->get_widget<T>(id, ptr);
  return ptr;
}

struct GladeExample : Gtk::Window {
  Glib::RefPtr<Gtk::Builder> builder_;

  // For convinience
  template<typename T>
  T& query(const Glib::ustring& id) {
    return *get_widget<T>(builder_, id);
  }

  GladeExample(char* glade_path)
    : builder_{Gtk::Builder::create()} {
    // load ui file
    builder_->add_from_file(glade_path);

    // load main widget
    add(query<Gtk::Widget>("main"));
    show_all();

    // setup callback
    query<Gtk::Button>("ui-load").signal_clicked().connect([this] {
      this->loadSubUI();
    });
  }

  void loadSubUI() {
    auto& sub_main = query<Gtk::Box>("sub-main");
    for (auto child : sub_main.get_children()) {
      delete child;
    }

    auto sub_builder = Gtk::Builder::create();
    try {
      sub_builder->add_from_file(query<Gtk::Entry>("ui-file").get_text());
    } catch (Glib::Error e) {
      query<Gtk::Label>("ui-message").set_label(e.what());
      return;
    }

    auto id = query<Gtk::Entry>("object-id").get_text();
    auto subUI = get_widget<Gtk::Widget>(sub_builder, id);
    if (!subUI) {
      query<Gtk::Label>("ui-message").set_label("Object ID (" + id + ") doesn't exist in ui file.");
      return;
    }
    query<Gtk::Label>("ui-message").set_label("");
    sub_main.add(*subUI);
    show_all();
  }
};

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: <program-name> <main ui file>\n";
    return 1;
  }
  auto app = Gtk::Application::create();
  GladeExample glade_example{argv[1]};
  return app->run(glade_example);
}
