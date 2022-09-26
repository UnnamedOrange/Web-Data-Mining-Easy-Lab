#pragma once

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

    enum token_t
    {
        t_eof = 0, // Lex will return 0 at EOF.
        t_unused,  // Any value greater than t_unused should be handled.
        t_page_begin,
        t_page_end,
        t_title,
        t_link,
    };

#ifdef __cplusplus
}
#endif
