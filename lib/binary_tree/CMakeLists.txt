add_library(binary_tree)

target_sources(binary_tree
    PRIVATE
        binary_tree.c
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            include
        FILES
            include/binary_tree.h
)
