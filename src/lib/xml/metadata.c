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

#include <libxml/SAX2.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <stdbool.h>
#include <string.h>

#include "sol-atomics.h"
#include "metadata.h"

struct SolMetadata {
        sol_atomic_t eatom;
        char *package_name;
        char *component;
};

typedef enum {
        MDATA_MIN = 1 << 0,
        MDATA_ROOT = 1 << 1,
        MDATA_PACKAGE = 1 << 2,
        MDATA_HISTORY = 1 << 3,
        MDATA_SOURCE = 1 << 4,
        MDATA_NAME = 1 << 5,
        MDATA_COMPONENT = 1 << 6,
} SolMetadataParseFlags;

/**
 * Instance tracking during initial load
 */
typedef struct SolMetadataParseContext {
        SolMetadataParseFlags flags;
        SolMetadata *metadata;
} SolMetadataParseContext;

__sol_inline__ static inline bool sol_sax_in_root(SolMetadataParseContext *self)
{
        return (self->flags & MDATA_ROOT) != 0;
}

__sol_inline__ static inline bool sol_sax_flip_state(SolMetadataParseContext *self,
                                                         const xmlChar *name, const char *key,
                                                         SolMetadataParseFlags flag)
{
        if (!xmlStrEqual(name, BAD_CAST key)) {
                return false;
        }
        self->flags ^= flag;
        return true;
}

/**
 * Handle state flips between close and opens
 */
static void sol_sax_flip_states(SolMetadataParseContext *self, const xmlChar *name)
{
        /* Handle root */
        if (sol_sax_flip_state(self, name, "PISI", MDATA_ROOT)) {
                return;
        }
        if (sol_sax_flip_state(self, name, "SOL", MDATA_ROOT)) {
                return;
        }
        /* Only parse within the root */
        if (!sol_sax_in_root(self)) {
                return;
        }
        if (sol_sax_flip_state(self, name, "Package", MDATA_PACKAGE)) {
                return;
        }
        if (sol_sax_flip_state(self, name, "History", MDATA_HISTORY)) {
                return;
        }
        if (sol_sax_flip_state(self, name, "Source", MDATA_SOURCE)) {
                return;
        }
        if (sol_sax_flip_state(self, name, "Name", MDATA_NAME)) {
                return;
        }
        if (!sol_sax_flip_state(self, name, "PartOf", MDATA_COMPONENT)) {
                return;
        }
}

/**
 * Handle opening of a new element
 */
static void sol_sax_start_element(void *udata, const xmlChar *name, const xmlChar **attrs)
{
        sol_sax_flip_states(udata, name);
}

/**
 * Handle closing of an element
 */
static void sol_sax_end_element(void *udata, const xmlChar *name)
{
        sol_sax_flip_states(udata, name);
}

/**
 * Handle character input
 */
static void sol_sax_characters(void *udata, const xmlChar *ch, int len)
{
        SolMetadataParseContext *self = udata;
        /* Handle package name */
        if (self->flags == (MDATA_ROOT | MDATA_PACKAGE | MDATA_NAME)) {
                self->metadata->package_name = strndup((char *)ch, len);
                return;
        }
        if (self->flags & MDATA_COMPONENT) {
                self->metadata->component = strndup((char *)ch, len);
                return;
        }
}

/**
 * Allow state resets
 */
static void sol_metadata_clean(SolMetadata *self)
{
        free(self->package_name);
        self->package_name = NULL;
        free(self->component);
        self->component = NULL;
}

static void sol_metadata_free(SolMetadata *self)
{
        sol_metadata_clean(self);
        free(self);
}

SolMetadata *sol_metadata_new(void)
{
        SolMetadata *ret = NULL;

        ret = calloc(1, sizeof(struct SolMetadata));
        if (!ret) {
                return NULL;
        }
        return sol_atomic_init((sol_atomic_t *)ret, (sol_atomic_free)sol_metadata_free);
}

SolMetadata *sol_metadata_unref(SolMetadata *meta)
{
        return sol_atomic_unref(meta);
}

bool sol_metadata_load(SolMetadata *meta, const char *filename)
{
        assert(meta != NULL);
        xmlParserCtxtPtr ctx = NULL;
        xmlDocPtr p = NULL;
        xmlSAXHandler *old = NULL;
        xmlSAXHandler handler = {.startElement = sol_sax_start_element,
                                 .endElement = sol_sax_end_element,
                                 .characters = sol_sax_characters };
        SolMetadataParseContext instance = {.metadata = meta };
        ctx = xmlCreateFileParserCtxt(filename);
        if (!ctx) {
                fprintf(stderr, "sol: Error creating XML context\n");
                return false;
        }
        old = ctx->sax;
        ctx->sax = &handler;
        ctx->userData = &instance;

        xmlParseDocument(ctx);
        p = ctx->myDoc;
        bool good = ctx->wellFormed;
        ctx->sax = old;
        xmlFreeParserCtxt(ctx);
        if (p) {
                xmlFreeDoc(p);
        }

        if (!good) {
                fprintf(stderr, "sol: Badly formed XML file, aborting\n");
                sol_metadata_clean(meta);
        }
        return good;
}

const char *sol_metadata_get_package_name(SolMetadata *meta)
{
        assert(meta != NULL);
        return (const char *)meta->package_name;
}

const char *sol_metadata_get_component(SolMetadata *meta)
{
        assert(meta != NULL);
        return (const char *)meta->component;
}
