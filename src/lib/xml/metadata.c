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

#include "metadata.h"
#include "eopkg-atomics.h"

struct EopkgMetadata {
        eopkg_atomic_t eatom;
};

static void eopkg_metadata_free(EopkgMetadata *self)
{
        free(self);
}

EopkgMetadata *eopkg_metadata_new(void)
{
        EopkgMetadata *ret = NULL;

        ret = calloc(1, sizeof(struct EopkgMetadata));
        if (!ret) {
                return NULL;
        }
        return eopkg_atomic_init((eopkg_atomic_t *)ret, (eopkg_atomic_free)eopkg_metadata_free);
}

EopkgMetadata *eopkg_metadata_unref(EopkgMetadata *meta)
{
        return eopkg_atomic_unref(meta);
}

bool eopkg_metadata_load(EopkgMetadata *meta, __eopkg_unused__ const char *filename)
{
        assert(meta != NULL);
        return false;
}
