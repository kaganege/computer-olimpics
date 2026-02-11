add_library(graph)

target_sources(graph
    PRIVATE
        graph.c
        weighed_graph.c

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            include
        FILES
            include/graph.h
            include/weighed_graph.h
)

target_link_libraries(graph
    PUBLIC
        linked_list
    PRIVATE
        ensure_not_null
        recalloc
)

target_include_directories(graph PRIVATE ../../include)
