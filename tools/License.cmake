# -----------------------------------------------------------------------------
# License helper
# -----------------------------------------------------------------------------

function(rollscript_add_license)

    set(options)

    set(oneValueArgs
        TARGET
        ID
        LICENSE_FILE
        RESOURCE_NAME
    )

    set(multiValueArgs)

    cmake_parse_arguments(
        LICENSE
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )

    if(NOT LICENSE_TARGET)
        message(FATAL_ERROR
            "rollscript_add_license: TARGET is required"
        )
    endif()

    if(NOT LICENSE_ID)
        message(FATAL_ERROR
            "rollscript_add_license: ID is required"
        )
    endif()

    if(NOT LICENSE_LICENSE_FILE)
        message(FATAL_ERROR
            "rollscript_add_license: LICENSE_FILE is required"
        )
    endif()

    if(NOT LICENSE_RESOURCE_NAME)
        message(FATAL_ERROR
            "rollscript_add_license: RESOURCE_NAME is required"
        )
    endif()

    # -------------------------------------------------------------------------
    # Paths
    # -------------------------------------------------------------------------

    set(LICENSE_RESOURCE_DIR
        "${CMAKE_CURRENT_BINARY_DIR}/Resources/Licenses"
    )

    set(LICENSE_RESOURCE
        "${LICENSE_RESOURCE_DIR}/${LICENSE_RESOURCE_NAME}"
    )

    get_filename_component(
        LICENSE_RESOURCE_BASE
        "${LICENSE_RESOURCE_NAME}"
        NAME_WE
    )

    set(LICENSE_METADATA_RESOURCE
        "${LICENSE_RESOURCE_DIR}/${LICENSE_RESOURCE_BASE}.json"
    )

    # -------------------------------------------------------------------------
    # License text
    # -------------------------------------------------------------------------

    file(MAKE_DIRECTORY
        "${LICENSE_RESOURCE_DIR}"
    )

    configure_file(
        "${LICENSE_LICENSE_FILE}"
        "${LICENSE_RESOURCE}"
        COPYONLY
    )

    # -------------------------------------------------------------------------
    # License metadata
    # -------------------------------------------------------------------------

    set(LICENSE_METADATA_SCRIPT
        "${CMAKE_SOURCE_DIR}/tools/update-license-metadata.sh"
    )

    if(NOT EXISTS "${LICENSE_METADATA_SCRIPT}")
        message(FATAL_ERROR
            "License metadata script not found: "
            "${LICENSE_METADATA_SCRIPT}"
        )
    endif()

    add_custom_command(
        OUTPUT
            "${LICENSE_METADATA_RESOURCE}"

        COMMAND
            "${LICENSE_METADATA_SCRIPT}"
            "${LICENSE_ID}"
            "${LICENSE_METADATA_RESOURCE}"

        DEPENDS
            "${LICENSE_METADATA_SCRIPT}"

        COMMENT
            "Updating license metadata for ${LICENSE_ID}"

        VERBATIM
    )

    add_custom_target(
        "${LICENSE_RESOURCE_BASE}LicenseMetadata"
        DEPENDS
            "${LICENSE_METADATA_RESOURCE}"
    )

    # -------------------------------------------------------------------------
    # Qt resources
    # -------------------------------------------------------------------------

    set_source_files_properties(
        "${LICENSE_RESOURCE}"
        PROPERTIES
            QT_RESOURCE_ALIAS "${LICENSE_RESOURCE_NAME}"
    )

    set_source_files_properties(
        "${LICENSE_METADATA_RESOURCE}"
        PROPERTIES
            QT_RESOURCE_ALIAS "${LICENSE_RESOURCE_BASE}.json"
    )

    qt_add_resources(
        "${LICENSE_TARGET}"
        "${LICENSE_RESOURCE_BASE}LicenseResources"
        PREFIX "/Licenses"
        FILES
            "${LICENSE_RESOURCE}"
            "${LICENSE_METADATA_RESOURCE}"
    )

    # -------------------------------------------------------------------------
    # Dependencies
    # -------------------------------------------------------------------------

    add_dependencies(
        "${LICENSE_TARGET}"
        "${LICENSE_RESOURCE_BASE}LicenseMetadata"
    )

    # -------------------------------------------------------------------------
    # Translation
    # -------------------------------------------------------------------------

    set_property(
        TARGET "${LICENSE_TARGET}"
        APPEND
        PROPERTY QT_EXCLUDE_SOURCES_FROM_TRANSLATION
            "${LICENSE_RESOURCE}"
            "${LICENSE_METADATA_RESOURCE}"
    )

endfunction()

