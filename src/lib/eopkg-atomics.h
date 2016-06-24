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

#pragma once

#include <assert.h>
#include <stdatomic.h>
#include <stdlib.h>

#include "util.h"

/**
 * Valid unref function for an eopkg atomic
 */
typedef void (*eopkg_atomic_free)(void *);

typedef struct eopkg_atomic_t {
        atomic_int ref_count;
        eopkg_atomic_free dtor;
} eopkg_atomic_t;

__eopkg_inline__ static inline void *eopkg_atomic_ref(void *v)
{
        eopkg_atomic_t *t = v;
        if (!t) {
                return NULL;
        }
        int ref_count = atomic_fetch_add(&(t->ref_count), 1);
        assert(ref_count >= 0);
        return t;
}

__eopkg_inline__ static inline void *eopkg_atomic_init(eopkg_atomic_t *atom, eopkg_atomic_free dtor)
{
        assert(atom->dtor == NULL);
        assert(atomic_load(&(atom->ref_count)) < 1);
        atom->dtor = dtor;
        return eopkg_atomic_ref(atom);
}

__eopkg_inline__ static inline void *eopkg_atomic_unref(void *v)
{
        eopkg_atomic_t *t = v;
        if (!t) {
                return NULL;
        }
        int ref_count = atomic_fetch_sub(&(t->ref_count), 1);
        assert(ref_count > 0);
        if (ref_count == 1) {
                if (t->dtor) {
                        t->dtor(t);
                } else {
                        free(t);
                }
                return NULL;
        }
        return t;
}
