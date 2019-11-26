#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/application.h>

class Counter : public Gtk::Window {
public:
  Counter() : button_{"Click Me!"}, counter_{0} {
    set_title("Counter");

    button_.set_margin_top(20);
    button_.set_margin_right(20);
    button_.set_margin_bottom(20);
    button_.set_margin_left(20);

    button_.signal_clicked().connect([&] {
      counter_ += 1;
      button_.set_label(Glib::ustring::compose("Click Count [ %1 ] ", counter_));
    });

    button_.show();
    add(button_);
  }
  ~Counter() override {};

protected:
  Gtk::Button button_;
  int counter_;
};

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  Counter counter;
  return app->run(counter);
}
