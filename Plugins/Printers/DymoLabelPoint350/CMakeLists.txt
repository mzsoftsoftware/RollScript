project(DymoLabelPoint350PrinterPlugin
    VERSION 0.1.0
)

# -----------------------------------------------------------------------------
# Sources
# -----------------------------------------------------------------------------

set(SOURCES
    DLP350PrinterPlugin.cpp
    DLP350PrinterMedia.cpp
    DLP350PrinterWorker.cpp
    DLP350PrinterJob.cpp
    DLP350PrinterJobAlive.cpp
    DLP350PrinterJobPrint.cpp
)

set(HEADERS
    DLP350PrinterPlugin.h
    DLP350PrinterPluginInfo.h
    DLP350PrinterMedia.h
    DLP350PrinterWorker.h
    DLP350PrinterJob.h
    DLP350PrinterJobAlive.h
    DLP350PrinterJobPrint.h
)

set(CORE_HEADERS
    ${CMAKE_SOURCE_DIR}/Core/Plugins/IPlugin.h
    ${CMAKE_SOURCE_DIR}/Core/Plugins/IPrinterPlugin.h
)

set(COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/Common/Info/PluginInfo.cpp
    ${CMAKE_SOURCE_DIR}/Common/Info/PrinterPluginInfo.cpp
)

set(COMMON_HEADERS
    ${CMAKE_SOURCE_DIR}/Common/Info/PluginInfo.h
    ${CMAKE_SOURCE_DIR}/Common/Info/PrinterPluginInfo.h
)

# -----------------------------------------------------------------------------
# Translations
# -----------------------------------------------------------------------------
set(TRANSLATIONS
    Translations/DymoLabelPoint350PrinterPlugin_de_DE.ts
    Translations/DymoLabelPoint350PrinterPlugin_en_US.ts
)

# -----------------------------------------------------------------------------
# Ressources
# -----------------------------------------------------------------------------
set(RESSOURCES
    Resources/DymoLabelPoint350PrinterPlugin.qrc
)

# -----------------------------------------------------------------------------
# Plugin
# -----------------------------------------------------------------------------

qt_add_plugin(DymoLabelPoint350PrinterPlugin
    CLASS_NAME DymoLabelPoint350PrinterPlugin

    ${SOURCES}
    ${HEADERS}
    ${CORE_HEADERS}
    ${COMMON_SOURCES}
    ${COMMON_HEADERS}
    ${RESSOURCES}
)

# -----------------------------------------------------------------------------
# Translations
# -----------------------------------------------------------------------------
qt_add_translations(
    TARGETS DymoLabelPoint350PrinterPlugin
    TS_FILES ${TRANSLATIONS}
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
