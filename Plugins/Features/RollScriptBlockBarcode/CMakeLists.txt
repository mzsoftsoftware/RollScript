project(RollScriptBlockBarcodeFeaturePlugin
    VERSION 0.1.0
)

# ============================================================
# ZXing-C++
# ============================================================
set(ZXING_READERS OFF CACHE BOOL "" FORCE)
set(ZXING_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ZXING_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ZXING_EXAMPLES_QT OFF CACHE BOOL "" FORCE)
set(ZXING_USE_OPENCV OFF CACHE BOOL "" FORCE)
set(ZXING_C_API OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    zxing
    GIT_REPOSITORY https://github.com/zxing-cpp/zxing-cpp.git
    GIT_TAG v3.0.2   # oder latest stable tag prüfen
)
FetchContent_MakeAvailable(zxing)

# Nur die betreffende Warnung im ZXing-Target
# nicht als Fehler behandeln.
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(ZXing PRIVATE
        $<$<COMPILE_LANGUAGE:C>:-Wno-error=discarded-qualifiers>
    )
endif()
target_link_libraries(ZXing
    PUBLIC
        Qt6::Core
        Qt6::Gui
)

# -----------------------------------------------------------------------------
# Sources
# -----------------------------------------------------------------------------
set(SOURCES
    RollScriptBlockBarcodeFeaturePlugin.cpp

    RollScriptBlockBarcodeDocument.cpp

    RollScriptBlockBarcodeWidget.cpp

    RollScriptBlockBarcodeRenderer.cpp
)

set(HEADERS
    RollScriptBlockBarcodeFeaturePlugin.h
    RollScriptBlockBarcodeFeaturePluginInfo.h

    RollScriptBlockBarcodeDocument.h

    RollScriptBlockBarcodeWidget.h

    RollScriptBlockBarcodeRenderer.h
)

set(FORMS
    RollScriptBlockBarcodeWidget.ui
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
    Translations/RollScriptBlockBarcodeFeaturePlugin_de_DE.ts
    Translations/RollScriptBlockBarcodeFeaturePlugin_en_US.ts
)

# -----------------------------------------------------------------------------
# Ressources
# -----------------------------------------------------------------------------
set(RESSOURCES
    Resources/RollScriptBlockBarcodeFeaturePlugin.qrc
)

# -----------------------------------------------------------------------------
# Plugin
# -----------------------------------------------------------------------------
qt_add_plugin(RollScriptBlockBarcodeFeaturePlugin
        CLASS_NAME RollScriptBlockBarcodeFeaturePlugin

    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${CORE_HEADERS}
    ${COMMON_SOURCES}
    ${COMMON_HEADERS}
    ${RESSOURCES}
)
target_compile_definitions(RollScriptBlockBarcodeFeaturePlugin
    PRIVATE
        ROLLSCRIPT_PLUGIN_VERSION="${PROJECT_VERSION}"
)

# -----------------------------------------------------------------------------
# Translations
# -----------------------------------------------------------------------------
qt_add_translations(
    TARGETS RollScriptBlockBarcodeFeaturePlugin
    TS_FILES ${TRANSLATIONS}
)

# -----------------------------------------------------------------------------
# Include directories
# -----------------------------------------------------------------------------
target_include_directories(RollScriptBlockBarcodeFeaturePlugin
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}
)

# -----------------------------------------------------------------------------
# Libraries
# -----------------------------------------------------------------------------
target_link_libraries(RollScriptBlockBarcodeFeaturePlugin
    PRIVATE
    ZXing::ZXing
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

# -----------------------------------------------------------------------------
# Metadata
# -----------------------------------------------------------------------------
set_target_properties(RollScriptBlockBarcodeFeaturePlugin PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/plugins/features"
)
