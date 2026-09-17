project(RollScriptBlockQRCodeFeaturePlugin
    VERSION 0.1.0
)

# -----------------------------------------------------------------------------
# Sources
# -----------------------------------------------------------------------------
set(SOURCES
	RollScriptBlockQRCodeFeaturePlugin.cpp
)

set(HEADERS
	RollScriptBlockQRCodeFeaturePlugin.h
	RollScriptBlockQRCodeFeaturePluginInfo.h
)

set(FORMS
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
	Translations/RollScriptBlockQRCodeFeaturePlugin_de_DE.ts
	Translations/RollScriptBlockQRCodeFeaturePlugin_en_US.ts
)

# -----------------------------------------------------------------------------
# Ressources
# -----------------------------------------------------------------------------
set(RESSOURCES
	Resources/RollScriptBlockQRCodeFeaturePlugin.qrc
)

# -----------------------------------------------------------------------------
# Plugin
# -----------------------------------------------------------------------------
qt_add_plugin(RollScriptBlockQRCodeFeaturePlugin
	CLASS_NAME RollScriptBlockQRCodeFeaturePlugin

    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${CORE_HEADERS}
    ${COMMON_SOURCES}
    ${COMMON_HEADERS}
    ${RESSOURCES}
)
target_compile_definitions(RollScriptBlockQRCodeFeaturePlugin
    PRIVATE
        ROLLSCRIPT_PLUGIN_VERSION="${PROJECT_VERSION}"
)

# -----------------------------------------------------------------------------
# Translations
# -----------------------------------------------------------------------------
qt_add_translations(
	TARGETS RollScriptBlockQRCodeFeaturePlugin
    TS_FILES ${TRANSLATIONS}
)

# -----------------------------------------------------------------------------
# Include directories
# -----------------------------------------------------------------------------
target_include_directories(RollScriptBlockQRCodeFeaturePlugin
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}
)

# -----------------------------------------------------------------------------
# Libraries
# -----------------------------------------------------------------------------
target_link_libraries(RollScriptBlockQRCodeFeaturePlugin
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

# -----------------------------------------------------------------------------
# Metadata
# -----------------------------------------------------------------------------
set_target_properties(RollScriptBlockQRCodeFeaturePlugin PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/plugins/features"
)
