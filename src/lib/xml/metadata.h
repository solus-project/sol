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

typedef struct SolMetadata SolMetadata;

/**
 * Construct a new SolMetadata instance
 */
SolMetadata *sol_metadata_new(void);

/**
 * Unref a given SolMetadata instance
 */
SolMetadata *sol_metadata_unref(SolMetadata *meta);

/**
 * Load the SolMetadata from the given path
 */
bool sol_metadata_load(SolMetadata *meta, const char *filename);

/**
 * Get the package name
 */
const char *sol_metadata_get_package_name(SolMetadata *meta);

/**
 * Get the package component
 */
const char *sol_metadata_get_component(SolMetadata *meta);

DEF_AUTOFREE(SolMetadata, sol_metadata_unref)
