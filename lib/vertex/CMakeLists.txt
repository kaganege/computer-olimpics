add_library(vertex)

target_sources(vertex
    PRIVATE
        vertex.c
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            include/
        FILES
            include/vertex.h
)
