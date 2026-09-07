project(RollScriptCore
    VERSION 0.1.0
)

# -----------------------------------------------------------------------------
# External dependencies
# -----------------------------------------------------------------------------
include(LibUsb.cmake)

# -----------------------------------------------------------------------------
# Sources
# -----------------------------------------------------------------------------
set(SOURCES
    Errors/RollScriptError.cpp
    Errors/RollScriptErrorOwner.cpp


    Blocks/RollScriptBlockDocumentBase.cpp
    Blocks/RollScriptBlockWidgetBase.cpp
    Blocks/RollScriptBlockRendererBase.cpp

    Printers/PrinterInstance.cpp
    Printers/PrinterMedia.cpp
    Printers/PrinterDeviceInfo.cpp

    USB/PrinterInstanceUSB.cpp
    USB/USBDeviceInfo.cpp
    USB/USBManager.cpp

    Rendering/RenderContext.cpp
    Rendering/RenderGeometry.cpp
)

# -----------------------------------------------------------------------------
# Headers
# -----------------------------------------------------------------------------
set(HEADERS
    Errors/RollScriptError.h
    Errors/RollScriptErrorOwner.h
    Errors/RollScriptErrorMacros.h

    Blocks/IFeatureBlock.h
    Blocks/IFeatureBlockInfo.h

    Blocks/RollScriptBlockDocumentBase.h
    Blocks/RollScriptBlockWidgetBase.h
    Blocks/RollScriptBlockRendererBase.h

    Plugins/IPlugin.h
    Plugins/IPluginInfo.h
    Plugins/IPrinterPlugin.h
    Plugins/IPrinterPluginInfo.h
    Plugins/IFeaturePlugin.h
    Plugins/IFeaturePluginInfo.h

    Printers/PrinterInstance.h
    Printers/PrinterMedia.h
    Printers/PrinterMediaConstraints.h
    Printers/PrinterDeviceInfo.h

    USB/PrinterInstanceUSB.h
    USB/USBDeviceInfo.h
    USB/USBManager.h

    Rendering/RenderContext.h
    Rendering/RenderGeometry.h
)

# -----------------------------------------------------------------------------
# Translations
# -----------------------------------------------------------------------------
#set(TRANSLATIONS
#    Translations/RollScriptCore_de_DE.ts
#    Translations/RollScriptCore_en_US.ts
#)

# -----------------------------------------------------------------------------
# Ressources
# -----------------------------------------------------------------------------
#set(RESSOURCES
#)

# -----------------------------------------------------------------------------
# Library
# -----------------------------------------------------------------------------

add_library(RollScriptCore SHARED
    ${SOURCES}
    ${HEADERS}    
)

# -----------------------------------------------------------------------------
# Translations
# -----------------------------------------------------------------------------
#qt_add_translations(
#    TARGETS RollScriptCore
#    TS_FILES ${TRANSLATIONS}
#)

# -----------------------------------------------------------------------------
# Resources
# -----------------------------------------------------------------------------
#qt_add_resources(
#    TARGETS RollScriptCore
#    ${RESSOURCES}
#)

# -----------------------------------------------------------------------------
# Include directories
# -----------------------------------------------------------------------------

target_include_directories(RollScriptCore
    PUBLIC
    ${CMAKE_SOURCE_DIR}
)


# -----------------------------------------------------------------------------
# Libraries
# -----------------------------------------------------------------------------

target_link_libraries(RollScriptCore
    PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets

    RollScript::LibUsb
)
