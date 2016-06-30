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

#pragma once

#include "util.h"

/**
 * Handle to the underlying library instance
 */
typedef struct SolContext SolContext;

/**
 * Open a handle and initialise the library
 */
SolContext *sol_open(void);

/**
 * Close the library handle
 */
void sol_close(SolContext *sol);

DEF_AUTOFREE(SolContext, sol_close)
