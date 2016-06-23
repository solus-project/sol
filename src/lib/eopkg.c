/*
 * This file is part of eopkg.
 *
 * Copyright © 2016 Ikey Doherty <ikey@solus-project.com>
 *
 * eopkg is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#include <stdatomic.h>
#include <stdlib.h>

#include "eopkg-atomics.h"
#include "eopkg.h"
#include "util.h"

struct EopkgContext {
        eopkg_atomic_t eatom; /**<Integrate with atomic refcounts */
};

void eopkg_context_free(EopkgContext *self)
{
        free(self);
}

EopkgContext *eopkg_open(void)
{
        EopkgContext *c = NULL;

        c = calloc(1, sizeof(struct EopkgContext));
        if (!c) {
                return NULL;
        }
        return eopkg_atomic_init((eopkg_atomic_t *)c, (eopkg_atomic_free)eopkg_context_free);
}

/**
 * Close the library handle
 */
void eopkg_close(EopkgContext *eopkg)
{
        eopkg_atomic_unref(eopkg);
}
