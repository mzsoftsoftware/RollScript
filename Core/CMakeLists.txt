cmake_minimum_required(VERSION 3.19)

project(RollScriptCore)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core
    Gui
)

qt_standard_project_setup()


# -----------------------------------------------------------------------------
# Sources
# -----------------------------------------------------------------------------

set(SOURCES
    Printers/PrinterInstance.cpp

    USB/PrinterInstanceUSB.cpp
    USB/USBDeviceInfo.h
)


# -----------------------------------------------------------------------------
# Headers
# -----------------------------------------------------------------------------

set(HEADERS
    Plugins/IPlugin.h
    Plugins/IPrinterPlugin.h

    Printers/PrinterInstance.h

    USB/PrinterInstanceUSB.h
    USB/USBDeviceInfo.h
)


# -----------------------------------------------------------------------------
# Library
# -----------------------------------------------------------------------------

add_library(RollScriptCore SHARED
    ${SOURCES}
    ${HEADERS}
)


# -----------------------------------------------------------------------------
# Include directories
# -----------------------------------------------------------------------------

target_include_directories(RollScriptCore
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


# -----------------------------------------------------------------------------
# Libraries
# -----------------------------------------------------------------------------

target_link_libraries(RollScriptCore
    PUBLIC
    Qt6::Core
    Qt6::Gui
)