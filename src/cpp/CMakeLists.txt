find_package(PkgConfig)
pkg_search_module(GTKMM REQUIRED gtkmm-3.0)

add_compile_options(${GTKMM_CFLAGS})
add_link_options(${GTKMM_LDFLAGS})

add_executable(counter counter.cpp)
add_executable(style_example style_example.cpp)
add_executable(ui_example ui_example.cpp)
