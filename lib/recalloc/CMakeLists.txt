add_library(recalloc INTERFACE)

target_sources(recalloc
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS
            include/
        FILES
            include/recalloc.h
)
