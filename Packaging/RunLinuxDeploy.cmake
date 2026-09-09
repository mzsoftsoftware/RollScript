execute_process(
    COMMAND "${QMAKE}" -query QT_INSTALL_LIBS
    OUTPUT_VARIABLE QT_INSTALL_LIBS
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE QMAKE_RESULT
)

if(NOT QMAKE_RESULT EQUAL 0)
    message(FATAL_ERROR
        "Failed to query QT_INSTALL_LIBS from QMAKE"
    )
endif()

message(STATUS
    "RunLinuxDeploy: QT_INSTALL_LIBS='${QT_INSTALL_LIBS}'"
)

set(ENV{EXTRA_PLATFORM_PLUGINS} "libqwayland.so")
set(ENV{QMAKE} "${QMAKE}")
set(ENV{NO_STRIP} "1")
set(ENV{LD_LIBRARY_PATH}
    "${QT_INSTALL_LIBS}:$ENV{LD_LIBRARY_PATH}"
)

execute_process(
    COMMAND
        ${CMAKE_COMMAND}
        -E env
        QMAKE=${QMAKE}
        ${LINUXDEPLOY}
        --verbosity=0
        --appdir ${APPDIR}
        --plugin qt
	--output appimage
    WORKING_DIRECTORY "${APPDIR}/.."
    RESULT_VARIABLE RESULT
)

if(NOT RESULT EQUAL 0)
    message(FATAL_ERROR
        "linuxdeploy failed with exit code ${RESULT}"
    )
endif()
