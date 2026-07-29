# Application target

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Gui Svg LinguistTools)

qt_standard_project_setup()


# -----------------------------------------------------------------------------
# Application files
# -----------------------------------------------------------------------------
set(APP_SOURCES
    App/main.cpp
    App/MainWindow.cpp
    App/DialogAbout.cpp
)
set(APP_HEADERS
    App/MainWindow.h
    App/DialogAbout.h
)
set(APP_FORMS
    App/MainWindow.ui
    App/DialogAbout.ui
)

# -----------------------------------------------------------------------------
# Core files
# -----------------------------------------------------------------------------
set(CORE_SOURCES    
    Core/Document/RollScriptDocument.cpp
    Core/Document/RollScriptDocumentSettings.cpp

    Core/Translation/TranslationManager.cpp

    Core/Plugins/PluginManager.cpp
    Core/Plugins/PrinterPluginRegistry.cpp
)
set(CORE_HEADERS
    Core/Document/RollScriptDocument.h
    Core/Document/RollScriptDocumentSettings.h

    Core/Translation/TranslationManager.h

    Core/Plugins/PluginManager.h
    Core/Plugins/PrinterPluginRegistry.h
)

# -----------------------------------------------------------------------------
# GUI files
# -----------------------------------------------------------------------------
set(GUI_SOURCES
    Gui/Widgets/SettingsWidget.cpp
)
set(GUI_HEADERS
    Gui/Widgets/SettingsWidget.h
)
set(GUI_FORMS
    Gui/Widgets/SettingsWidget.ui
)

# -----------------------------------------------------------------------------
# Common directory
# -----------------------------------------------------------------------------
set(COMMON_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/../Common
)

# -----------------------------------------------------------------------------
# Common GUI files
# -----------------------------------------------------------------------------
set(COMMON_GUI_SOURCES
    ${COMMON_DIR}/Gui/Widgets/DoublePairWidget.cpp
    ${COMMON_DIR}/Gui/Widgets/MarginsWidget.cpp
)
set(COMMON_GUI_HEADERS
    ${COMMON_DIR}/Gui/Widgets/DoublePairWidget.h
    ${COMMON_DIR}/Gui/Widgets/MarginsWidget.h
)
set(COMMON_GUI_FORMS
    ${COMMON_DIR}/Gui/Widgets/DoublePairWidget.ui
    ${COMMON_DIR}/Gui/Widgets/MarginsWidget.ui
)

# -----------------------------------------------------------------------------
# Common Core files
# -----------------------------------------------------------------------------
set(COMMON_CORE_SOURCES
    ${COMMON_DIR}/Core/Devices/PrinterInstance.cpp
)
set(COMMON_CORE_HEADERS
    ${COMMON_DIR}/Core/Devices/UsbDeviceInfo.h
    ${COMMON_DIR}/Core/Devices/PrinterInstance.h
    ${COMMON_DIR}/Core/Plugins/IPlugin.h
    ${COMMON_DIR}/Core/Plugins/IPrinterPlugin.h
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

    ${COMMON_CORE_SOURCES}
    ${COMMON_CORE_HEADERS}

    ${COMMON_GUI_SOURCES}
    ${COMMON_GUI_HEADERS}
    ${COMMON_GUI_FORMS}

    Resources/RollScript.qrc
    ${COMMON_DIR}/Resources/Common.qrc
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
#    FILES
#        Resources/Icons/ActionExit.svg
#        Resources/Icons/ActionFileNew.svg
)

# -----------------------------------------------------------------------------
# Includes and Libraries
# -----------------------------------------------------------------------------
target_include_directories(RollScript
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}
)
target_link_libraries(RollScript
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Gui
        Qt6::Svg
)

# -----------------------------------------------------------------------------
# Variables e.g. version
# -----------------------------------------------------------------------------
target_compile_definitions(RollScript
    PRIVATE
        ROLLSCRIPT_VERSION="${PROJECT_VERSION}"
)

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
