cmake_minimum_required(VERSION 3.19)

project(DymoLabelPoint350PrinterPlugin)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui)

qt_standard_project_setup()

# -----------------------------------------------------------------------------
# Sources
# -----------------------------------------------------------------------------

set(SOURCES
    DymoLabelPoint350PrinterPlugin.cpp
)

set(HEADERS
    DymoLabelPoint350PrinterPlugin.h
)

# -----------------------------------------------------------------------------
# Common directory
# -----------------------------------------------------------------------------
set(COMMON_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Common
)

# -----------------------------------------------------------------------------
# Common Core files
# -----------------------------------------------------------------------------
set(COMMON_CORE_SOURCES
)
set(COMMON_CORE_HEADERS
    ${COMMON_DIR}/Core/Plugins/IPlugin.h
    ${COMMON_DIR}/Core/Plugins/IPrinterPlugin.h
)

# -----------------------------------------------------------------------------
# Plugin
# -----------------------------------------------------------------------------

qt_add_plugin(DymoLabelPoint350PrinterPlugin
    CLASS_NAME DymoLabelPoint350PrinterPlugin

    ${SOURCES}
    ${HEADERS}

    ${COMMON_CORE_SOURCES}
    ${COMMON_CORE_HEADERS}
)

# -----------------------------------------------------------------------------
# Include directories
# -----------------------------------------------------------------------------

target_include_directories(DymoLabelPoint350PrinterPlugin
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}
)

# -----------------------------------------------------------------------------
# Libraries
# -----------------------------------------------------------------------------

target_link_libraries(DymoLabelPoint350PrinterPlugin
    PRIVATE
        Qt6::Core
        Qt6::Gui
)

# -----------------------------------------------------------------------------
# Metadata
# -----------------------------------------------------------------------------

set_target_properties(DymoLabelPoint350PrinterPlugin PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY
        "${CMAKE_BINARY_DIR}/plugins/printers"
)

