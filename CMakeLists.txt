cmake_minimum_required(VERSION 3.19)
project(finance LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Widgets Sql)
find_package(SQLite3)

qt_standard_project_setup()

qt_add_executable(finance
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries(finance
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
        SQLite3
)

include(GNUInstallDirs)

install(TARGETS finance
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET finance
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
