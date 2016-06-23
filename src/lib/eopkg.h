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

/**
 * Handle to the underlying library instance
 */
typedef struct EopkgContext EopkgContext;

/**
 * Open a handle and initialise the library
 */
EopkgContext *eopkg_open(void);

/**
 * Close the library handle
 */
void eopkg_close(EopkgContext *eopkg);
