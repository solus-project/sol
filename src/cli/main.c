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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "eopkg.h"
#include "util.h"

typedef int (*CommandCallback)(int, char **);

typedef struct SubCommand {
        const char *name;
        CommandCallback cb;
} SubCommand;

static int print_version(__eopkg_unused__ int argc, __eopkg_unused__ char **argv)
{
        fputs("eopkg - version " PACKAGE_VERSION "\n\n", stdout);
        fputs("Copyright © 2016 Ikey Doherty\n\n", stdout);

        fputs(
            "eopkg is free software; you can redistribute it and/or modify\n"
            "it under the terms of the GNU Lesser General Public License as\n"
            "published by the Free Software Foundation; either version 2.1\n"
            " of the License, or (at your option) any later version.\n",
            stdout);

        return EXIT_SUCCESS;
}

static const struct SubCommand commands[] = { { "version", &print_version }, { 0 } };

static const SubCommand *lookup_command(const char *key)
{
        const SubCommand *command = NULL;

        for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
                command = &(commands[i]);
                if (!command->name) {
                        continue;
                }
                if (strcmp(key, command->name) != 0) {
                        continue;
                }
                return command;
        }
        return NULL;
}

int main(int argc, char **argv)
{
        autofree(EopkgContext) *c = NULL;
        const char *command_key = NULL;
        const SubCommand *command = NULL;

        if (argc > 1) {
                command_key = argv[1];
        }

        if (!command_key) {
                fprintf(stderr, "Usage: %s [command]\n", argv[0]);
                return EXIT_FAILURE;
        }

        c = eopkg_open();

        command = lookup_command(command_key);
        if (!command) {
                fprintf(stderr, "Unknown command: %s\n", command_key);
                return EXIT_FAILURE;
        }

        if (!command->cb) {
                fprintf(stderr, "Unimplemented: %s\n", command_key);
                return EXIT_FAILURE;
        }
        return command->cb(argc, argv);
}
