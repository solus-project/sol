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

#include <check.h>
#include <stdlib.h>

#include "db/install-db.h"
#include "xml/metadata.h"

START_TEST(eopkg_metadata_new_test)
{
        autofree(EopkgMetadata) *meta = NULL;

        meta = eopkg_metadata_new();
        fail_if(!meta, "Failed to create EopkgMetadata");
}
END_TEST

START_TEST(eopkg_metadata_load_test)
{
        autofree(EopkgMetadata) *meta = NULL;
        const char *fname = TOP_DIR "/tests/data/metadata.xml";

        meta = eopkg_metadata_new();

        fail_if(!eopkg_metadata_load(meta, fname), "Failed to load well-formed meta");

        fail_if(!streq(eopkg_metadata_get_package_name(meta), "bash"),
                "Package name does not match expectation");
        fail_if(!streq(eopkg_metadata_get_component(meta), "system.base"),
                "Package PartOf does not match expectation");
}
END_TEST

START_TEST(eopkg_installdb_load)
{
        autofree(EopkgInstallDB) *db = NULL;

        db = eopkg_install_db_new();
        fail_if(!db, "Failed to load install-db");
        eopkg_install_db_load(db);
}
END_TEST

static Suite *core_suite(void)
{
        Suite *s = NULL;
        TCase *tc = NULL;

        s = suite_create("eopkg_metadata");
        tc = tcase_create("eopkg_metadata_functions");
        tcase_add_test(tc, eopkg_metadata_new_test);
        tcase_add_test(tc, eopkg_metadata_load_test);
        tcase_add_test(tc, eopkg_installdb_load);
        suite_add_tcase(s, tc);

        return s;
}

int main(void)
{
        Suite *s;
        SRunner *sr;
        int fail;

        s = core_suite();
        sr = srunner_create(s);
        srunner_run_all(sr, CK_VERBOSE);
        fail = srunner_ntests_failed(sr);
        srunner_free(sr);

        if (fail > 0) {
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}
