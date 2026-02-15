#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <vcruntime.h>

#define OPTION_IMPL(name, type) \
    struct option_##name { \
        struct option; \
        type data; \
    };

#define OPTION_NONE(impl) ((struct option_##impl){false})
#define OPTION_SOME(impl, data) ((struct option_##impl){true, data})

#define OPTION_OP(_option, op, ...) \
    (*(typeof(_option.data) *)option_##op((struct option*)&_option, ##__VA_ARGS__))
#define OPTION_UNWRAP(option) OPTION_OP(option, unwrap)
#define OPTION_UNWRAP_OR(option, default_value) \
        OPTION_OP(option, unwrap_or, &(typeof(option.data)){default_value});
#define OPTION_UNWRAP_OR_ELSE(option, default_fn) OPTION_OP(option, unwrap_or_else, default_fn)
#define OPTION_EXPECT(option, message) OPTION_OP(option, expect, _CRT_WIDE(message))

struct option {
    bool is_some;
};

void* option_unwrap(struct option* option);
void* option_unwrap_or(struct option* option, void* default_value);
void* option_unwrap_or_else(struct option* option, void* (*default_fn)(void));
void* option_expect(struct option* option, const wchar_t* message);
