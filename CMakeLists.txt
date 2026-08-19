cmake_minimum_required(VERSION 3.24)

project(RollScript
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

add_compile_definitions(
    QT_NO_CAST_FROM_ASCII
    QT_NO_CAST_TO_ASCII
)

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