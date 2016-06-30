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

#include <stdatomic.h>
#include <stdlib.h>

#include "sol-atomics.h"
#include "sol.h"
#include "util.h"

struct SolContext {
        sol_atomic_t eatom; /**<Integrate with atomic refcounts */
};

void sol_context_free(SolContext *self)
{
        free(self);
}

SolContext *sol_open(void)
{
        SolContext *c = NULL;

        c = calloc(1, sizeof(struct SolContext));
        if (!c) {
                return NULL;
        }
        return sol_atomic_init((sol_atomic_t *)c, (sol_atomic_free)sol_context_free);
}

/**
 * Close the library handle
 */
void sol_close(SolContext *sol)
{
        sol_atomic_unref(sol);
}
