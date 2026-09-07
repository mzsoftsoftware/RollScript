# Application target
set(ROLLSCRIPT_APPLICATION_VERSION 0.1.0)

# -----------------------------------------------------------------------------
# Application files
# -----------------------------------------------------------------------------
set(APP_SOURCES
    App/main.cpp

    App/ApplicationContext.cpp
    App/SingleInstanceLock.cpp

    App/MainWindow.cpp

    App/DialogAbout.cpp
)
set(APP_HEADERS
    App/ApplicationContext.h
    App/SingleInstanceLock.h

    App/MainWindow.h

    App/DialogAbout.h
)
set(APP_FORMS
    App/MainWindow.ui

    App/DialogAbout.ui
)

# -----------------------------------------------------------------------------
# Logic files
# -----------------------------------------------------------------------------
set(LOGIC_SOURCES
    Document/RollScriptDocument.cpp
    Document/RollScriptDocumentSettings.cpp
    Document/RollScriptDocumentBlocks.cpp

    Printers/PrinterManager.cpp

    Translation/TranslationManager.cpp

    Plugins/PluginManager.cpp
    Plugins/FeaturePluginRegistry.cpp
    Plugins/PrinterPluginRegistry.cpp

    Features/FeatureBlockManager.cpp
    Features/FeatureBlockRegistry.cpp

    Rendering/RollScriptRenderer.cpp
    Rendering/RenderDeviceInfo.cpp
    Rendering/RenderLayout.cpp
)
set(LOGIC_HEADERS
    Document/RollScriptDocument.h
    Document/RollScriptDocumentSettings.h
    Document/RollScriptDocumentBlocks.h

    Printers/PrinterManager.h

    Translation/TranslationManager.h

    Plugins/PluginManager.h
    Plugins/FeaturePluginRegistry.h
    Plugins/PrinterPluginRegistry.h

    Features/FeatureBlockManager.h
    Features/FeatureBlockRegistry.h

    Rendering/RollScriptRenderer.h
    Rendering/RenderDeviceInfo.h
    Rendering/RenderLayout.h
)

# -----------------------------------------------------------------------------
# GUI files
# -----------------------------------------------------------------------------
set(GUI_SOURCES
    Gui/Models/PrintersItemModel.cpp
    Gui/Models/PrinterMediasItemModel.cpp
    Gui/Models/FeatureBlocksItemModel.cpp

    Gui/Helper/FeatureBlocksItemDelegate.cpp

    Gui/Widgets/SettingsWidget.cpp
    Gui/Widgets/FeatureBlocksWidget.cpp
    Gui/Widgets/FeatureBlockWidgetEmpty.cpp
    Gui/Widgets/PreviewWidget.cpp
)
set(GUI_HEADERS
    Gui/Models/PrintersItemModel.h
    Gui/Models/PrinterMediasItemModel.h
    Gui/Models/FeatureBlocksItemModel.h

    Gui/Helper/FeatureBlocksItemDelegate.h

    Gui/Widgets/SettingsWidget.h
    Gui/Widgets/FeatureBlocksWidget.h
    Gui/Widgets/FeatureBlockWidgetEmpty.h
    Gui/Widgets/PreviewWidget.h
)
set(GUI_FORMS
    Gui/Widgets/SettingsWidget.ui
    Gui/Widgets/FeatureBlocksWidget.ui
    Gui/Widgets/FeatureBlockWidgetEmpty.ui
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
# Translations
# -----------------------------------------------------------------------------
set(TRANSLATIONS
    Translations/RollScript_de_DE.ts
    Translations/RollScript_en_US.ts
)

# -----------------------------------------------------------------------------
# Ressources
# -----------------------------------------------------------------------------
set(RESSOURCES
    Resources/RollScript.qrc
    ${COMMON_DIR}/Resources/Common.qrc
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

    ${LOGIC_SOURCES}
    ${LOGIC_HEADERS}

    ${GUI_SOURCES}
    ${GUI_HEADERS}
    ${GUI_FORMS}

    ${COMMON_GUI_SOURCES}
    ${COMMON_GUI_HEADERS}
    ${COMMON_GUI_FORMS}

    ${RESSOURCES}
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
#qt_add_resources(
#    TARGETS RollScript
#    ${RESSOURCES}
#)

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

        RollScriptCore
)

# -----------------------------------------------------------------------------
# Variables e.g. version
# -----------------------------------------------------------------------------
target_compile_definitions(RollScript
    PRIVATE
        ROLLSCRIPT_VERSION="${PROJECT_VERSION}"
)

