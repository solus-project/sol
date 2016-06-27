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

#include "util.h"

typedef struct EopkgInstallDB EopkgInstallDB;

EopkgInstallDB *eopkg_install_db_new(void);

EopkgInstallDB *eopkg_install_db_unref(EopkgInstallDB *db);

/**
 * UNSTABLE API: This will disappear into EopkgContext
 */
void eopkg_install_db_load(EopkgInstallDB *db);

DEF_AUTOFREE(EopkgInstallDB, eopkg_install_db_unref)
