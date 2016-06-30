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

#define _GNU_SOURCE

#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sol-atomics.h"
#include "install-db.h"
#include "xml/metadata.h"

#define INSTALL_DB_DISK "/var/lib/sol/package"

DEF_AUTOFREE(DIR, closedir)

/**
 * Actual SolInstallDB implementation
 */
struct SolInstallDB {
        sol_atomic_t eatom;
};

static inline void sol_install_db_free(SolInstallDB *self)
{
        free(self);
}

void sol_install_db_load(SolInstallDB *db)
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
                autofree(SolMetadata) *meta = NULL;

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
                meta = sol_metadata_new();
                if (!sol_metadata_load(meta, meta_path)) {
                        fprintf(stderr, "Failed to load: %s\n", meta_path);
                        continue;
                }
                ++load_count;
                fprintf(stderr,
                        "Loaded %s (%s)\n",
                        sol_metadata_get_package_name(meta),
                        sol_metadata_get_component(meta));
        }
        fprintf(stderr, "Loaded %d entries\n", load_count);
}

SolInstallDB *sol_install_db_new(void)
{
        SolInstallDB *r = NULL;

        r = calloc(1, sizeof(struct SolInstallDB));
        if (!r) {
                return NULL;
        }
        return sol_atomic_init((sol_atomic_t *)r, (sol_atomic_free)sol_install_db_free);
}

SolInstallDB *sol_install_db_unref(SolInstallDB *db)
{
        assert(db != NULL);
        return sol_atomic_unref(db);
}
