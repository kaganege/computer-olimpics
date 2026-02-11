add_library(container_of INTERFACE)

target_sources(container_of
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS
            include/
        FILES
            include/container_of.h
)
