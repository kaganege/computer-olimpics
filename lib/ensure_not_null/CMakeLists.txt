add_library(ensure_not_null INTERFACE)

target_sources(ensure_not_null
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS
            include/
        FILES
            include/ensure_not_null.h
)
