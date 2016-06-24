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

#include <libxml/parser.h>

/**
 * Init libxml on library initialisation
 */
__attribute__((constructor)) static void eopkg_xml_init(void)
{
        LIBXML_TEST_VERSION
}

/**
 * Cleanup libxml on library deconstruction
 */
__attribute__((destructor)) static void eopkg_xml_deinit(void)
{
        xmlCleanupParser();
}
