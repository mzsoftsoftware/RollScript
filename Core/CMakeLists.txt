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

    Licensing/LicenseInfo.cpp
    Licensing/CoreLicenseProvider.cpp

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

    Licensing/ILicenseProvider.h
    Licensing/LicenseInfo.h
    Licensing/CoreLicenseProvider.h

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

add_dependencies(
    RollScriptCore
    RollScriptLibUsbLicenseMetadata
)

target_compile_definitions(RollScriptCore
    PUBLIC
        LIBUSB_VERSION="${LIBUSB_VERSION}"
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
set(LIBUSB_LICENSE_RESOURCE
    "${CMAKE_CURRENT_BINARY_DIR}/Resources/Licenses/libusb-license.txt"
)
set(LIBUSB_LICENSE_METADATA_RESOURCE
    "${CMAKE_CURRENT_BINARY_DIR}/Resources/Licenses/libusb-license.json"
)

set_source_files_properties(
    "${LIBUSB_LICENSE_RESOURCE}"
    PROPERTIES
        QT_RESOURCE_ALIAS "libusb-license.txt"
)
set_source_files_properties(
    "${LIBUSB_LICENSE_METADATA_RESOURCE}"
    PROPERTIES
        QT_RESOURCE_ALIAS "libusb-license.json"
)
set_property(
    TARGET RollScriptCore
    PROPERTY QT_EXCLUDE_SOURCES_FROM_TRANSLATION
        "${LIBUSB_LICENSE_RESOURCE}"
        "${LIBUSB_LICENSE_METADATA_RESOURCE}"
)

qt_add_resources(
    RollScriptCore
    "RollScriptCoreResources"
    PREFIX "/Licenses"
    FILES
        "${LIBUSB_LICENSE_RESOURCE}"
        "${LIBUSB_LICENSE_METADATA_RESOURCE}"
)

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
