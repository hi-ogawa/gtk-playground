Pick up a few nice files from upstream.
cf. https://stackoverflow.com/questions/7106012/download-a-single-folder-or-directory-from-a-github-repo

```
mkdir -p thirdparty/gtk/demos
mkdir -p thirdparty/gtk/gtk
mkdir -p thirdparty/gnome-shell/data

svn export \
  https://github.com/GNOME/gtk/branches/gtk-3-24/demos/widget-factory \
  thirdparty/gtk/demos/widget-factory

svn export \
  https://github.com/GNOME/gtk/branches/gtk-3-24/gtk/theme \
  thirdparty/gtk/gtk/theme

svn export \
  https://github.com/GNOME/gnome-shell/branches/gnome-3-34/data/theme \
  thirdparty/gnome-shell/data/theme
```


GTK style development

```
# Setup auto compilation (from one console)
bash scripts.sh watch


# Preview style from Glade (it supports auto-reloading css file + helpful css error message)
# NOTE: "interface-css-provider-path ../../build/dev.css" in widget-factory.ui file makes Glade to load style.
glade src/ui/widget-factory.ui


# Apply system wide (I experienced gnome-shell crashed when running this. So use this with care...)
bash scripts.sh install

# Install gnome-shell theme
bash scripts.sh gnome install
```


Main changes

- Everywhere lighter
  - [*] text
  - [*] background
  - [*] border
  - [*] shadow
  - [*] lighter blue
  - [ ] tweak border color (currently some border disappers)
- [*] Decrease border radius entirely
- Menubar
  - [*] decrease padding
  - [*] upper border radius
  - [*] lighter background color
  - [*] decrease titlebar font-weight
  - [ ] better sizing
- Window
  - [*] lighter shadow
- Button
  - [*] no gradient
  - [ ] better toggle button enbled-state
- Popup
  - [*] shadow
- Gnome
  - [*] Decrease border radius
    - [ ] Cannot change topbar popup's border radius?
  - [*] Change font
  - [ ] change gdm greater font


Misc

```
# Change font globally (assuming Roboto is installed)
gsettings set org.gnome.desktop.interface font-name 'Roboto 11'
```

TODO

- Refactor widget-factory.ui

- html <-> ui file
  - "include-able" ui file
  - use slim
  - migrate widget factory to this format

- gsettings-based tweak
  - `gsettings list-recursively org.gnome.desktop.interface`
  - `gsettings list-recursively org.gnome.desktop.wm.preferences`

```
gsettings set org.gnome.desktop.wm.preferences titlebar-uses-system-font false
gsettings set org.gnome.desktop.interface font-name 'Roboto 11'
```


References

- Gnome theme
  - https://gitlab.gnome.org/GNOME/gnome-shell-extensions/tree/master/extensions/user-theme
  - org.gnome.shell.extensions.user-theme name
- SASS
  - https://sass-lang.com/
  - https://github.com/sass/libsass/blob/master/src/ast_values.cpp
  - https://github.com/sass/libsass/blob/master/src/fn_colors.cpp
