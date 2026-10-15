project(RollScriptBlockImageFeaturePlugin
    VERSION 0.1.0
)

# -----------------------------------------------------------------------------
# Sources
# -----------------------------------------------------------------------------
set(SOURCES
    RollScriptBlockImageFeaturePlugin.cpp

    RollScriptBlockImageDocument.cpp

    RollScriptBlockImageWidget.cpp

    RollScriptBlockImageRenderer.cpp
)

set(HEADERS
    RollScriptBlockImageFeaturePlugin.h
    RollScriptBlockImageFeaturePluginInfo.h

    RollScriptBlockImageDocument.h

    RollScriptBlockImageWidget.h

    RollScriptBlockImageRenderer.h
)

set(FORMS
    RollScriptBlockImageWidget.ui
)

set(CORE_HEADERS
    ${CMAKE_SOURCE_DIR}/Core/Plugins/IPlugin.h
    ${CMAKE_SOURCE_DIR}/Core/Plugins/IFeaturePlugin.h
    ${CMAKE_SOURCE_DIR}/Core/Blocks/IFeatureBlock.h
    ${CMAKE_SOURCE_DIR}/Core/Blocks/IFeatureBlockInfo.h
)

set(COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/Common/Info/PluginInfo.cpp
    ${CMAKE_SOURCE_DIR}/Common/Info/FeaturePluginInfo.cpp
    ${CMAKE_SOURCE_DIR}/Common/Info/FeatureBlockInfo.cpp
)

set(COMMON_HEADERS
    ${CMAKE_SOURCE_DIR}/Common/Info/PluginInfo.h
    ${CMAKE_SOURCE_DIR}/Common/Info/FeaturePluginInfo.h
    ${CMAKE_SOURCE_DIR}/Common/Info/FeatureBlockInfo.h
)

# -----------------------------------------------------------------------------
# Translations
# -----------------------------------------------------------------------------
set(TRANSLATIONS
    Translations/RollScriptBlockImageFeaturePlugin_de_DE.ts
    Translations/RollScriptBlockImageFeaturePlugin_en_US.ts
)

# -----------------------------------------------------------------------------
# Ressources
# -----------------------------------------------------------------------------
set(RESSOURCES
    Resources/RollScriptBlockImageFeaturePlugin.qrc
)

# -----------------------------------------------------------------------------
# Plugin
# -----------------------------------------------------------------------------
qt_add_plugin(RollScriptBlockImageFeaturePlugin
	CLASS_NAME RollScriptBlockImageFeaturePlugin

    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${CORE_HEADERS}
    ${COMMON_SOURCES}
    ${COMMON_HEADERS}
    ${RESSOURCES}
)

target_sources(RollScriptBlockImageFeaturePlugin
  PRIVATE

)
target_compile_definitions(RollScriptBlockImageFeaturePlugin
    PRIVATE
        ROLLSCRIPT_PLUGIN_VERSION="${PROJECT_VERSION}"
)

# -----------------------------------------------------------------------------
# Translations
# -----------------------------------------------------------------------------
qt_add_translations(
	TARGETS RollScriptBlockImageFeaturePlugin
    TS_FILES ${TRANSLATIONS}
)

# -----------------------------------------------------------------------------
# Include directories
# -----------------------------------------------------------------------------
target_include_directories(RollScriptBlockImageFeaturePlugin
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}
)

# -----------------------------------------------------------------------------
# Libraries
# -----------------------------------------------------------------------------
target_link_libraries(RollScriptBlockImageFeaturePlugin
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

# -----------------------------------------------------------------------------
# Metadata
# -----------------------------------------------------------------------------
set_target_properties(RollScriptBlockImageFeaturePlugin PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/plugins/features"
)
