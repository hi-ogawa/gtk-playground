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

    gnome)
      local SUB_COMMAND="${1}"; shift;
      case "${SUB_COMMAND}" in
        setup)
          gsettings set org.gnome.shell enabled-extensions "['user-theme@gnome-shell-extensions.gcampax.github.com']"
        ;;
        watch)
          mkdir -p build
          inotifywait -mr -e close_write src/theme/gnome-shell/data/theme | \
            xargs -I x sh -c 'echo ":: INOTIFY - x"; sassc src/theme/gnome-shell/data/theme/gnome-shell.scss build/dev-gnome-shell.css'
        ;;
        install)
          mkdir -p dist/CustomAdwaita/gnome-shell
          mkdir -p $HOME/.local/share/themes
          ln -sf $PWD/dist/CustomAdwaita $HOME/.local/share/themes
          sassc src/theme/gnome-shell/data/theme/gnome-shell.scss dist/CustomAdwaita/gnome-shell/gnome-shell.css
          gsettings reset org.gnome.shell.extensions.user-theme name
          gsettings set org.gnome.shell.extensions.user-theme name 'CustomAdwaita'
        ;;
      esac
    ;;
  esac
}

Main "${@}"
