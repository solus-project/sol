/*
 * This file is part of sol.
 *
 * Copyright © 2016 Ikey Doherty <ikey@solus-project.com>
 *
 * sol is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define __sol_unused__ __attribute__((unused))
#define __sol_inline__ __attribute__((always_inline))

/**
 * Taken from libnica and about fourteen of my previous projects..
 */

#define DEF_AUTOFREE(N, C)                                                                         \
        static inline void _autofree_func_##N(void *p)                                             \
        {                                                                                          \
                if (p && *(N **)p) {                                                               \
                        C(*(N **)p);                                                               \
                        (*(void **)p) = NULL;                                                      \
                }                                                                                  \
        }

#define autofree(N) __attribute__((cleanup(_autofree_func_##N))) N

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
/**
 * Determine if a file actually exists or not
 */
__sol_inline__ static inline bool sol_file_exists(const char *p)
{
        __sol_unused__ struct stat st = { 0 };
        return stat(p, &st) == 0;
}

/**
 * String equality, from libnica
 */
__sol_inline__ static inline bool streq(const char *a, const char *b)
{
        if (a == b) {
                return true;
        }
        if (!a || !b) {
                return false;
        }
        return strcmp(a, b) == 0;
}

DEF_AUTOFREE(char, free)
