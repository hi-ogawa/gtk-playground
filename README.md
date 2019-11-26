Pick up a few nice files from upstream.
cf. https://stackoverflow.com/questions/7106012/download-a-single-folder-or-directory-from-a-github-repo

```
mkdir -p thirdparty/gtk/demos/widget-factory
mkdir -p thirdparty/gtk/gtk
mkdir -p thirdparty/gnome-shell/data

svn export \
  https://github.com/GNOME/gtk/branches/gtk-3-24/demos/widget-factory/widget-factory.ui \
  thirdparty/gtk/demos/widget-factory/widget-factory.ui

svn export \
  https://github.com/GNOME/gtk/branches/gtk-3-24/gtk/theme \
  thirdparty/gtk/gtk/theme

svn export \
  https://github.com/GNOME/gnome-shell/branches/gnome-3-34/data/theme \
  thirdparty/gnome-shell/data/theme
```

TODO

- Setup scss-based style development
  - [*] scss compiler live reload
  - [*] gtk theme development
    - use glade + widget factory ui file
  - [ ] gnome theme development
    - auto reload?

```
# Example

# - setup inotifywait from one shell
inotifywait -mr -e close_write theme/Adwaita | \
  xargs -I x sh -c 'echo ":: INOTIFY - x"; sassc theme/Adwaita/gtk-contained.scss out.css'

# - then open glade file and preview it
glade widget-factory.ui
```

- style to change
  - decrease border radius entirely
  - use Roboto font entirely
  - background whiter and font whiter
  - everything lighter
    - background
    - font color
    - shadow
    - button outline
  - button
    - no gradient
  - menubar
    - decrease font-weight
    - decrease padding
    - decrease height
    - tweak font (font size, font-weight)

```
// base color
$base_color: darken(white,  1%);
$text_color: darken(white, 70%);
$bg_color: darken(white,  1%);
$fg_color: darken(white, 60%);
```

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

- gtk theme
  -
- gnome theme
  -
- widget factory
  -
- sass
  - https://sass-lang.com/
  - https://github.com/sass/libsass/blob/master/src/ast_values.cpp
  - https://github.com/sass/libsass/blob/master/src/fn_colors.cpp
