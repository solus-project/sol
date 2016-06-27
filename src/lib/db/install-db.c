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

#include <stdlib.h>

#include "eopkg-atomics.h"
#include "install-db.h"

/**
 * Actual EopkgInstallDB implementation
 */
struct EopkgInstallDB {
        eopkg_atomic_t eatom;
};

static inline void eopkg_install_db_free(EopkgInstallDB *self)
{
        free(self);
}

EopkgInstallDB *eopkg_install_db_new(void)
{
        EopkgInstallDB *r = NULL;

        r = calloc(1, sizeof(struct EopkgInstallDB));
        if (!r) {
                return NULL;
        }
        return eopkg_atomic_init((eopkg_atomic_t *)r, (eopkg_atomic_free)eopkg_install_db_free);
}

EopkgInstallDB *eopkg_install_db_unref(EopkgInstallDB *db)
{
        assert(db != NULL);
        return eopkg_atomic_unref(db);
}
