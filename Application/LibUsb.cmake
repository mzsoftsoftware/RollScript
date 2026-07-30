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

FetchContent_MakeAvailable(libusb)

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
