# -----------------------------------------------------------------------------
# libusb-cmake
# -----------------------------------------------------------------------------

include(FetchContent)

set(LIBUSB_VERSION "1.0.30")

FetchContent_Declare(
    libusb
    GIT_REPOSITORY https://github.com/libusb/libusb-cmake.git
    GIT_TAG v${LIBUSB_VERSION}
)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

FetchContent_MakeAvailable(libusb)

# -----------------------------------------------------------------------------
# libusb license file
# -----------------------------------------------------------------------------

FetchContent_GetProperties(libusb)

set(LIBUSB_LICENSE_SOURCE
    "${libusb_SOURCE_DIR}/libusb/COPYING"
)

set(LIBUSB_LICENSE_FILE
    "${CMAKE_CURRENT_BINARY_DIR}/Resources/Licenses/libusb-license.txt"
)

file(MAKE_DIRECTORY
    "${CMAKE_CURRENT_BINARY_DIR}/Resources/Licenses"
)

configure_file(
    "${LIBUSB_LICENSE_SOURCE}"
    "${LIBUSB_LICENSE_FILE}"
    COPYONLY
)

# -----------------------------------------------------------------------------
# libusb license metadata
# -----------------------------------------------------------------------------

set(LIBUSB_LICENSE_METADATA
    "${CMAKE_CURRENT_BINARY_DIR}/Resources/Licenses/libusb-license.json"
)

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
        "${LIBUSB_LICENSE_METADATA}"

    COMMAND
        "${LICENSE_METADATA_SCRIPT}"
        "libusb/libusb-cmake"
        "${LIBUSB_LICENSE_METADATA}"

    DEPENDS
        "${LICENSE_METADATA_SCRIPT}"

    COMMENT
        "Updating libusb license metadata"

    VERBATIM
)

add_custom_target(
    RollScriptLibUsbLicenseMetadata
    DEPENDS
        "${LIBUSB_LICENSE_METADATA}"
)

# -----------------------------------------------------------------------------
# Export eigenes RollScript Target
# -----------------------------------------------------------------------------

if(TARGET usb-1.0)
    add_library(
        RollScript::LibUsb
        ALIAS
        usb-1.0
    )
else()
    message(FATAL_ERROR
        "Could not find libusb target usb-1.0"
    )
endif()
