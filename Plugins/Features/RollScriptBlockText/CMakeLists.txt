project(RollScriptBlockTextFeaturePlugin)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui LinguistTools)

qt_standard_project_setup()

# -----------------------------------------------------------------------------
# Sources
# -----------------------------------------------------------------------------

set(SOURCES
    RollScriptBlockTextFeaturePlugin.cpp
    RollScriptBlockText.cpp
)

set(HEADERS
    RollScriptBlockTextFeaturePlugin.h
    RollScriptBlockText.h
)

set(CORE_HEADERS
    ${CMAKE_SOURCE_DIR}/Core/Plugins/IPlugin.h
    ${CMAKE_SOURCE_DIR}/Core/Plugins/IFeaturePlugin.h
    ${CMAKE_SOURCE_DIR}/Core/Blocks/IFeatureBlock.h
)

set(COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/Common/Info/PluginInfo.cpp
    ${CMAKE_SOURCE_DIR}/Common/Info/FeaturePluginInfo.cpp
)

set(COMMON_HEADERS
    ${CMAKE_SOURCE_DIR}/Common/Info/PluginInfo.h
    ${CMAKE_SOURCE_DIR}/Common/Info/FeaturePluginInfo.h
)

# -----------------------------------------------------------------------------
# Translations
# -----------------------------------------------------------------------------
set(TRANSLATIONS
    Translations/RollScriptBlockTextFeaturePlugin_de_DE.ts
    Translations/RollScriptBlockTextFeaturePlugin_en_US.ts
)

# -----------------------------------------------------------------------------
# Plugin
# -----------------------------------------------------------------------------

qt_add_plugin(RollScriptBlockTextFeaturePlugin
        CLASS_NAME RollScriptBlockTextFeaturePlugin

    ${SOURCES}
    ${HEADERS}
    ${CORE_HEADERS}
    ${COMMON_SOURCES}
    ${COMMON_HEADERS}

    Resources/RollScriptBlockTextFeaturePlugin.qrc
)

# -----------------------------------------------------------------------------
# Translations
# -----------------------------------------------------------------------------
qt_add_translations(
    TARGETS RollScriptBlockTextFeaturePlugin
    TS_FILES ${TRANSLATIONS}
)

# -----------------------------------------------------------------------------
# Resources
# -----------------------------------------------------------------------------
qt_add_resources(RollScriptBlockTextFeaturePlugin
    Resources/RollScriptBlockTextFeaturePlugin.qrc
)

# -----------------------------------------------------------------------------
# Include directories
# -----------------------------------------------------------------------------

target_include_directories(RollScriptBlockTextFeaturePlugin
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}
)

# -----------------------------------------------------------------------------
# Libraries
# -----------------------------------------------------------------------------

target_link_libraries(RollScriptBlockTextFeaturePlugin
    PRIVATE
        Qt6::Core
        Qt6::Gui
)

# -----------------------------------------------------------------------------
# Metadata
# -----------------------------------------------------------------------------

set_target_properties(RollScriptBlockTextFeaturePlugin PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/plugins/features"
)
