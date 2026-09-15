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
# Library
# -----------------------------------------------------------------------------
add_library(RollScriptCore SHARED
    ${SOURCES}
    ${HEADERS}
)

target_compile_definitions(RollScriptCore
    PUBLIC
        LIBUSB_VERSION="${LIBUSB_VERSION}"
)

# -----------------------------------------------------------------------------
# License
# -----------------------------------------------------------------------------
rollscript_add_license(
    TARGET RollScriptCore
    ID "libusb/libusb-cmake"
    LICENSE_FILE "${libusb_SOURCE_DIR}/libusb/COPYING"
    RESOURCE_NAME "libusb-license.txt"
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
