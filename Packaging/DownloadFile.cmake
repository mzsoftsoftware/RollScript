if(NOT DEFINED URL)
    message(FATAL_ERROR "URL is not defined")
endif()

if(NOT DEFINED OUTPUT)
    message(FATAL_ERROR "OUTPUT is not defined")
endif()

message(STATUS "Downloading ${URL}")

file(DOWNLOAD
    "${URL}"
    "${OUTPUT}"
    SHOW_PROGRESS
    TLS_VERIFY ON
    STATUS DOWNLOAD_STATUS
)

list(GET DOWNLOAD_STATUS 0 DOWNLOAD_ERROR)

if(NOT DOWNLOAD_ERROR EQUAL 0)

    list(GET DOWNLOAD_STATUS 1 DOWNLOAD_MESSAGE)

    file(REMOVE "${OUTPUT}")

    message(FATAL_ERROR
        "Download failed: ${DOWNLOAD_MESSAGE}"
    )

endif()

file(
    CHMOD "${OUTPUT}"
    PERMISSIONS
        OWNER_READ
        OWNER_WRITE
        OWNER_EXECUTE
        GROUP_READ
        GROUP_EXECUTE
        WORLD_READ
        WORLD_EXECUTE
)
