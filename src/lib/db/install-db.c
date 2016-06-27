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

#define _GNU_SOURCE

#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "eopkg-atomics.h"
#include "install-db.h"
#include "xml/metadata.h"

#define INSTALL_DB_DISK "/var/lib/eopkg/package"

DEF_AUTOFREE(DIR, closedir)

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

void eopkg_install_db_load(EopkgInstallDB *db)
{
        autofree(DIR) *d = NULL;
        assert(db != NULL);
        struct dirent *ent = NULL;

        d = opendir(INSTALL_DB_DISK);
        if (!d) {
                return;
        }

        /* ALL DEMO CODE! */
        static int load_count = 0;
        while ((ent = readdir(d)) != NULL) {
                autofree(char) *meta_path = NULL;
                autofree(EopkgMetadata) *meta = NULL;

                if (!asprintf(&meta_path,
                              "%s/%s/%s",
                              INSTALL_DB_DISK,
                              ent->d_name,
                              "metadata.xml")) {
                        abort();
                }

                if (access(meta_path, F_OK) != 0) {
                        continue;
                }
                meta = eopkg_metadata_new();
                if (!eopkg_metadata_load(meta, meta_path)) {
                        fprintf(stderr, "Failed to load: %s\n", meta_path);
                        continue;
                }
                ++load_count;
                fprintf(stderr,
                        "Loaded %s (%s)\n",
                        eopkg_metadata_get_package_name(meta),
                        eopkg_metadata_get_component(meta));
        }
        fprintf(stderr, "Loaded %d entries\n", load_count);
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
