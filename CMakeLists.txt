cmake_minimum_required(VERSION 3.19)
project(RollScript LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

# -----------------------------------------------------------------------------
# Application sources
# -----------------------------------------------------------------------------
set(APP_SOURCES
    App/main.cpp
    App/MainWindow.cpp
)
set(APP_HEADERS
    App/MainWindow.h
)
set(APP_FORMS
    App/MainWindow.ui
)

# -----------------------------------------------------------------------------
# Core sources
# -----------------------------------------------------------------------------
set(CORE_SOURCES
)
set(CORE_HEADERS
)

# -----------------------------------------------------------------------------
# GUI sources
# -----------------------------------------------------------------------------
set(GUI_SOURCES
)
set(GUI_HEADERS
)
set(GUI_FORMS
)

# -----------------------------------------------------------------------------
# Translations
# -----------------------------------------------------------------------------
set(TRANSLATIONS
    Translations/RollScript_de_DE.ts
)

# -----------------------------------------------------------------------------
# Application
# -----------------------------------------------------------------------------
qt_add_executable(RollScript
    WIN32
    MACOSX_BUNDLE

    ${APP_SOURCES}
    ${APP_HEADES}
    ${APP_FORMS}

    ${CORE_SOURCES}
    ${CORE_HEADERS}

    ${GUI_SOURCES}
    ${GUI_HEADERS}
    ${GUI_FORMS}
)

# -----------------------------------------------------------------------------
# Translations
# -----------------------------------------------------------------------------
qt_add_translations(
    TARGETS RollScript
    TS_FILES ${TRANSLATIONS}
)

# -----------------------------------------------------------------------------
# Libraries
# -----------------------------------------------------------------------------
target_link_libraries(RollScript
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

# -----------------------------------------------------------------------------
# Plugins
# -----------------------------------------------------------------------------
#add_subdirectory(Plugins/Printers/DymoLabelPoint350)
#add_subdirectory(Plugins/Features/LabelBlockText)

# -----------------------------------------------------------------------------
# Installation
# -----------------------------------------------------------------------------
install(TARGETS RollScript
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# -----------------------------------------------------------------------------
# Deployment
# -----------------------------------------------------------------------------
qt_generate_deploy_app_script(
    TARGET RollScript
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})
