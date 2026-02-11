add_library(linked_list)

target_sources(linked_list
    PRIVATE
        linked_list.c
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            include/
        FILES
            include/linked_list_node.h
            include/linked_list.h
)

target_link_libraries(linked_list PRIVATE ensure_not_null)
