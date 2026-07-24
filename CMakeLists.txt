cmake_minimum_required(VERSION 3.19)
project(RollScript LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Gui Svg LinguistTools)

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
    Core/Translation/TranslationManager.cpp
    Core/Plugins/PluginManager.cpp
)
set(CORE_HEADERS
    Core/Translation/TranslationManager.h
    Core/Plugins/IPlugin.h
    Core/Plugins/PluginManager.h
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
    Translations/RollScript_en_US.ts
)

# -----------------------------------------------------------------------------
# Application
# -----------------------------------------------------------------------------
qt_add_executable(RollScript
    WIN32
    MACOSX_BUNDLE

    ${APP_SOURCES}
    ${APP_HEADERS}
    ${APP_FORMS}

    ${CORE_SOURCES}
    ${CORE_HEADERS}

    ${GUI_SOURCES}
    ${GUI_HEADERS}
    ${GUI_FORMS}

    Resources/RollScript.qrc
)

# -----------------------------------------------------------------------------
# Translations
# -----------------------------------------------------------------------------
qt_add_translations(
    TARGETS RollScript
    TS_FILES ${TRANSLATIONS}
)

# -----------------------------------------------------------------------------
# Resources
# -----------------------------------------------------------------------------
qt_add_resources(
    TARGETS RollScript
    FILES
        Resources/Icons/ActionExit.svg
        Resources/Icons/ActionFileNew.svg
)

# -----------------------------------------------------------------------------
# Includes and Libraries
# -----------------------------------------------------------------------------
target_include_directories(RollScript
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(RollScript
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Gui
        Qt6::Svg
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
