cmake_minimum_required(VERSION 3.10.0)
project(computer_olympics LANGUAGES C)
set_property(GLOBAL PROPERTY C_STANDARD 23)
add_compile_options(/std:clatest)

add_subdirectory(lib)

add_executable(main)
target_sources(main PRIVATE main.c)

add_executable(binary_tree_test)
target_sources(binary_tree_test PRIVATE binary_tree_main.c)
target_link_libraries(binary_tree_test PRIVATE binary_tree)

add_executable(linked_list_test)
target_sources(linked_list_test PRIVATE linked_list_main.c)
target_link_libraries(linked_list_test PRIVATE linked_list)

add_executable(vertex_test)
target_sources(vertex_test PRIVATE vertex_main.c)
target_link_libraries(vertex_test PRIVATE vertex)

add_executable(graph_test)
target_sources(graph_test PRIVATE graph_main.c)
target_link_libraries(graph_test PRIVATE graph)

add_executable(custom_linked_list)
target_sources(custom_linked_list PRIVATE custom_linked_list.c)
target_link_libraries(custom_linked_list PRIVATE linked_list)

add_executable(rusty_types_test)
target_sources(rusty_types_test PRIVATE rusty_types_main.c)
target_link_libraries(rusty_types_test PRIVATE rusty_types)
