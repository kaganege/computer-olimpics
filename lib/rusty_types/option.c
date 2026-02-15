#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "option.h"

#ifdef NDEBUG
#define assert_message(expression, message) ((void)0)
#else
#define assert_message(expression, message) ((void)(                           \
            (!!(expression)) ||                                                \
            (_wassert(message, _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0)) \
        )
#endif

static inline void* _unwrap(struct option* option)
{
    return option + sizeof(struct option);
}

void* option_unwrap(struct option* option)
{
    assert_message(option != NULL, L"Called `option_unwrap()` on a `NULL` value");
    assert_message(option->is_some, L"Called `option_unwrap()` on a `None` value");

    return _unwrap(option);
}

void* option_unwrap_or(struct option* option, void* default_value)
{
    assert_message(option != NULL, L"Called `option_unwrap_or()` on a `NULL` value");

    if (option->is_some)
        return _unwrap(option);

    return default_value;
}

void* option_unwrap_or_else(struct option* option, void* (*default_fn)(void))
{
    assert_message(option != NULL, L"Called `option_unwrap_or_else()` on a `NULL` value");

    if (option->is_some)
        return _unwrap(option);

    return default_fn();
}

void* option_expect(struct option* option, const wchar_t* message)
{
    assert_message(option != NULL, L"Called `option_expect()` on a `NULL` value");
    assert_message(option->is_some, message);

    return _unwrap(option);
}
