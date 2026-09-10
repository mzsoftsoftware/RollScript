cmake_minimum_required(VERSION 3.24)

project(RollScript
    VERSION 0.1.1
    LANGUAGES C CXX
)

include(GNUInstallDirs)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_compile_definitions(
    QT_NO_CAST_FROM_ASCII
    QT_NO_CAST_TO_ASCII
)

# -----------------------------------------------------------------------------
# Qt
# -----------------------------------------------------------------------------
set(QT_ENABLE_VERBOSE_DEPLOYMENT ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Gui Svg LinguistTools)
qt_standard_project_setup()

# -----------------------------------------------------------------------------
# Core Library
# -----------------------------------------------------------------------------
add_subdirectory(Core)

# -----------------------------------------------------------------------------
# Application
# -----------------------------------------------------------------------------
add_subdirectory(Application)

# -----------------------------------------------------------------------------
# Plugins
# -----------------------------------------------------------------------------
# --- Printers ----------------------------------------------------------------
add_subdirectory(Plugins/Printers/DymoLabelPoint350)

# --- Features ----------------------------------------------------------------
add_subdirectory(Plugins/Features/RollScriptBlockText)

# -----------------------------------------------------------------------------
# Installation RPATH
# -----------------------------------------------------------------------------
set_target_properties(RollScript PROPERTIES
    INSTALL_RPATH "$ORIGIN/../lib"
)
set_target_properties(RollScriptCore PROPERTIES
    INSTALL_RPATH "$ORIGIN"
)
set_target_properties(DymoLabelPoint350PrinterPlugin PROPERTIES
    INSTALL_RPATH "$ORIGIN/../../lib"
)
set_target_properties(RollScriptBlockTextFeaturePlugin PROPERTIES
    INSTALL_RPATH "$ORIGIN/../../lib"
)

# -----------------------------------------------------------------------------
# Installation
# -----------------------------------------------------------------------------
install(TARGETS RollScript
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(TARGETS RollScriptCore
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(TARGETS DymoLabelPoint350PrinterPlugin
    LIBRARY DESTINATION plugins/printers
)

install(TARGETS RollScriptBlockTextFeaturePlugin
    LIBRARY DESTINATION plugins/features
)

install(FILES
    ${CMAKE_SOURCE_DIR}/Packaging/de.mzsoft.RollScript.desktop
    DESTINATION share/applications
)
install(FILES
    ${CMAKE_SOURCE_DIR}/Packaging/de.mzsoft.RollScript.appdata.xml
    DESTINATION share/metainfo
)

install(FILES
    ${CMAKE_SOURCE_DIR}/Application/Resources/RollScript.svg
    DESTINATION share/icons/hicolor/scalable/apps
)

# -----------------------------------------------------------------------------
# Deployment
# -----------------------------------------------------------------------------
set(LINUXDEPLOY_EXECUTABLE
    ${CMAKE_BINARY_DIR}/linuxdeploy-x86_64.AppImage
)

set(LINUXDEPLOY_QT_PLUGIN
    ${CMAKE_BINARY_DIR}/linuxdeploy-plugin-qt-x86_64.AppImage
)

add_custom_command(
    OUTPUT ${LINUXDEPLOY_EXECUTABLE}
    COMMAND ${CMAKE_COMMAND}
            -DURL=https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
            -DOUTPUT=${LINUXDEPLOY_EXECUTABLE}
            -P ${CMAKE_SOURCE_DIR}/Packaging/DownloadFile.cmake
    COMMENT "Downloading linuxdeploy..."
    VERBATIM
)

add_custom_command(
    OUTPUT ${LINUXDEPLOY_QT_PLUGIN}
    COMMAND ${CMAKE_COMMAND}
            -DURL=https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/continuous/linuxdeploy-plugin-qt-x86_64.AppImage
            -DOUTPUT=${LINUXDEPLOY_QT_PLUGIN}
            -P ${CMAKE_SOURCE_DIR}/Packaging/DownloadFile.cmake
    COMMENT "Downloading linuxdeploy-plugin-qt..."
    VERBATIM
)

# -----------------------------------------------------------------------------
# AppDir
# -----------------------------------------------------------------------------
set(PACKAGING_FILES
    ${CMAKE_SOURCE_DIR}/Packaging/DownloadFile.cmake
    ${CMAKE_SOURCE_DIR}/Packaging/RunLinuxDeploy.cmake
    ${CMAKE_SOURCE_DIR}/Packaging/de.mzsoft.RollScript.desktop
    ${CMAKE_SOURCE_DIR}/Packaging/de.mzsoft.RollScript.appdata.xml
)

add_custom_target(AppDir

    COMMAND ${CMAKE_COMMAND} -E rm -rf
            ${CMAKE_BINARY_DIR}/AppDir

    COMMAND ${CMAKE_COMMAND}
            -E env
            DESTDIR=${CMAKE_BINARY_DIR}/AppDir
            ${CMAKE_COMMAND}
            --install ${CMAKE_BINARY_DIR}
            --prefix /usr
            --config $<CONFIG>

    DEPENDS
        RollScript
        RollScriptCore
        DymoLabelPoint350PrinterPlugin
        RollScriptBlockTextFeaturePlugin

    COMMENT "Creating RollScript AppDir"
    SOURCES ${PACKAGING_FILES}
)
set_target_properties(AppDir PROPERTIES
    FOLDER "Packaging"
)

# -----------------------------------------------------------------------------
# AppImage
# -----------------------------------------------------------------------------
find_program(QMAKE_EXECUTABLE
    NAMES qmake6 qmake
    HINTS
        "${CMAKE_PREFIX_PATH}/bin"
    REQUIRED
)

add_custom_target(AppImage
    COMMAND ${CMAKE_COMMAND}
            -DLINUXDEPLOY=${LINUXDEPLOY_EXECUTABLE}
            -DQMAKE=${QMAKE_EXECUTABLE}
            -DAPPDIR=${CMAKE_BINARY_DIR}/AppDir
            -P ${CMAKE_SOURCE_DIR}/Packaging/RunLinuxDeploy.cmake
    DEPENDS
        AppDir
        ${LINUXDEPLOY_EXECUTABLE}
        ${LINUXDEPLOY_QT_PLUGIN}
    COMMENT "Creating RollScript AppImage"
)
set_target_properties(AppImage PROPERTIES
    FOLDER "Packaging"
)