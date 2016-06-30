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

#include "util.h"

typedef struct SolInstallDB SolInstallDB;

SolInstallDB *sol_install_db_new(void);

SolInstallDB *sol_install_db_unref(SolInstallDB *db);

/**
 * UNSTABLE API: This will disappear into SolContext
 */
void sol_install_db_load(SolInstallDB *db);

DEF_AUTOFREE(SolInstallDB, sol_install_db_unref)
