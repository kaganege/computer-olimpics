#include <stdio.h>
#include <assert.h>

#include "rusty_types.h"

OPTION_IMPL(custom, char)

int main()
{
    struct option_custom op = OPTION_NONE(custom);
    assert(op.is_some == false);

    char d = OPTION_UNWRAP_OR(op, 'a');
    assert(d == 'a');

    op = OPTION_SOME(custom, 'a');
    assert(op.is_some == true);

    char value = OPTION_EXPECT(op, "It's a DDOS attack!");
    assert(value == 'a');

    printf("Success\n");

    return 0;
}
