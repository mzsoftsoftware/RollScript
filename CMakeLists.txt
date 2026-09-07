cmake_minimum_required(VERSION 3.24)

project(RollScript
    VERSION 0.1.0
    LANGUAGES C CXX
)

include(GNUInstallDirs)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_compile_definitions(
    QT_NO_CAST_FROM_ASCII
    QT_NO_CAST_TO_ASCII
)

# -----------------------------------------------------------------------------
# Qt
# -----------------------------------------------------------------------------
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Gui Svg LinguistTools)

qt_standard_project_setup()

# -----------------------------------------------------------------------------
# Core Library
# -----------------------------------------------------------------------------

add_subdirectory(Core)


# -----------------------------------------------------------------------------
# Application
# -----------------------------------------------------------------------------

add_subdirectory(Application)


# -----------------------------------------------------------------------------
# Plugins
# -----------------------------------------------------------------------------
# --- Printers ----------------------------------------------------------------
add_subdirectory(Plugins/Printers/DymoLabelPoint350)

# --- Features ----------------------------------------------------------------
add_subdirectory(Plugins/Features/RollScriptBlockText)
