#!/bin/bash

function Main() {
  local COMMAND="${1}"; shift;
  case "${COMMAND}" in
    watch)
      mkdir -p build
      inotifywait -mr -e close_write src/theme/gtk/theme/Adwaita | \
        xargs -I x sh -c 'echo ":: INOTIFY - x"; sassc src/theme/gtk/theme/Adwaita/gtk-contained.scss build/dev.css'
    ;;
    install)
      mkdir -p dist/CustomAdwaita/gtk-3.0
      mkdir -p $HOME/.local/share/themes
      ln -sf $PWD/dist/CustomAdwaita $HOME/.local/share/themes
      sassc src/theme/gtk/theme/Adwaita/gtk-contained.scss dist/CustomAdwaita/gtk-3.0/gtk.css
      gsettings reset org.gnome.desktop.interface gtk-theme
      gsettings set org.gnome.desktop.interface gtk-theme 'CustomAdwaita'
    ;;
  esac
}

Main "${@}"
