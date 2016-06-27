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

#include "util.h"

typedef struct EopkgMetadata EopkgMetadata;

/**
 * Construct a new EopkgMetadata instance
 */
EopkgMetadata *eopkg_metadata_new(void);

/**
 * Unref a given EopkgMetadata instance
 */
EopkgMetadata *eopkg_metadata_unref(EopkgMetadata *meta);

/**
 * Load the EopkgMetadata from the given path
 */
bool eopkg_metadata_load(EopkgMetadata *meta, const char *filename);

/**
 * Get the package name
 */
const char *eopkg_metadata_get_package_name(EopkgMetadata *meta);

/**
 * Get the package component
 */
const char *eopkg_metadata_get_component(EopkgMetadata *meta);

DEF_AUTOFREE(EopkgMetadata, eopkg_metadata_unref)
