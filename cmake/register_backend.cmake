
macro(register_backend NAME)
    string(TOUPPER ${NAME} NAME_UPPER)
    list(APPEND REGISTERED_BACKENDS "${NAME_UPPER}")
endmacro()


macro(use_backend NAME)
    if ("${NAME}" IN_LIST REGISTERED_BACKENDS)
        string(TOUPPER ${NAME} NAME_UPPER)
        set(BACKEND_FILE ${CMAKE_CURRENT_SOURCE_DIR}/backends/${NAME_UPPER}.cmake)

        if (NOT EXISTS ${BACKEND_FILE})
            message(FATAL_ERROR "${BACKEND_FILE} not found!")
        endif ()

        message("Using the '${NAME_UPPER}' backend")
        include(${BACKEND_FILE})
    else ()
        message(FATAL_ERROR "Unsupported BACKEND: ${NAME}")
    endif ()

endmacro()