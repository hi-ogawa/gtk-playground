import os
import gi; gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, Gdk

class Handler:
    def onDestroy(self, *args):
        Gtk.main_quit()

    def onButtonPressed(self, button):
        print("Hello World!")

builder = Gtk.Builder()
builder.add_from_file(f"{os.path.dirname(__file__)}/example.glade")
builder.connect_signals(Handler())

css_provider = Gtk.CssProvider()
css_provider.load_from_path(f"{os.path.dirname(__file__)}/example.css")
Gtk.StyleContext.add_provider_for_screen(
    Gdk.Screen.get_default(), css_provider, Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION)

window = builder.get_object("root")
window.show_all()
Gtk.main()
