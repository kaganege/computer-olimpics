add_library(rusty_types)

target_sources(rusty_types
    PRIVATE
        option.c
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            include/
        FILES
            include/rusty_types.h
            include/option.h
)
