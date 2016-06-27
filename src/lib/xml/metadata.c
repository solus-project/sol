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

#define _GNU_SOURCE

#include <libxml/SAX2.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <stdbool.h>
#include <string.h>

#include "eopkg-atomics.h"
#include "metadata.h"

struct EopkgMetadata {
        eopkg_atomic_t eatom;
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
} EopkgMetadataParseFlags;

/**
 * Instance tracking during initial load
 */
typedef struct EopkgMetadataParseContext {
        EopkgMetadataParseFlags flags;
        EopkgMetadata *metadata;
} EopkgMetadataParseContext;

__eopkg_inline__ static inline bool eopkg_sax_in_root(EopkgMetadataParseContext *self)
{
        return (self->flags & MDATA_ROOT) != 0;
}

__eopkg_inline__ static inline bool eopkg_sax_flip_state(EopkgMetadataParseContext *self,
                                                         const xmlChar *name, const char *key,
                                                         EopkgMetadataParseFlags flag)
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
static void eopkg_sax_flip_states(EopkgMetadataParseContext *self, const xmlChar *name)
{
        /* Handle root */
        if (eopkg_sax_flip_state(self, name, "PISI", MDATA_ROOT)) {
                return;
        }
        if (eopkg_sax_flip_state(self, name, "EOPKG", MDATA_ROOT)) {
                return;
        }
        /* Only parse within the root */
        if (!eopkg_sax_in_root(self)) {
                return;
        }
        if (eopkg_sax_flip_state(self, name, "Package", MDATA_PACKAGE)) {
                return;
        }
        if (eopkg_sax_flip_state(self, name, "History", MDATA_HISTORY)) {
                return;
        }
        if (eopkg_sax_flip_state(self, name, "Source", MDATA_SOURCE)) {
                return;
        }
        if (eopkg_sax_flip_state(self, name, "Name", MDATA_NAME)) {
                return;
        }
        if (!eopkg_sax_flip_state(self, name, "PartOf", MDATA_COMPONENT)) {
                return;
        }
}

/**
 * Handle opening of a new element
 */
static void eopkg_sax_start_element(void *udata, const xmlChar *name, const xmlChar **attrs)
{
        eopkg_sax_flip_states(udata, name);
}

/**
 * Handle closing of an element
 */
static void eopkg_sax_end_element(void *udata, const xmlChar *name)
{
        eopkg_sax_flip_states(udata, name);
}

/**
 * Handle character input
 */
static void eopkg_sax_characters(void *udata, const xmlChar *ch, int len)
{
        EopkgMetadataParseContext *self = udata;
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
static void eopkg_metadata_clean(EopkgMetadata *self)
{
        free(self->package_name);
        self->package_name = NULL;
        free(self->component);
        self->component = NULL;
}

static void eopkg_metadata_free(EopkgMetadata *self)
{
        eopkg_metadata_clean(self);
        free(self);
}

EopkgMetadata *eopkg_metadata_new(void)
{
        EopkgMetadata *ret = NULL;

        ret = calloc(1, sizeof(struct EopkgMetadata));
        if (!ret) {
                return NULL;
        }
        return eopkg_atomic_init((eopkg_atomic_t *)ret, (eopkg_atomic_free)eopkg_metadata_free);
}

EopkgMetadata *eopkg_metadata_unref(EopkgMetadata *meta)
{
        return eopkg_atomic_unref(meta);
}

bool eopkg_metadata_load(EopkgMetadata *meta, const char *filename)
{
        assert(meta != NULL);
        xmlParserCtxtPtr ctx = NULL;
        xmlDocPtr p = NULL;
        xmlSAXHandler *old = NULL;
        xmlSAXHandler handler = {.startElement = eopkg_sax_start_element,
                                 .endElement = eopkg_sax_end_element,
                                 .characters = eopkg_sax_characters };
        EopkgMetadataParseContext instance = {.metadata = meta };
        ctx = xmlCreateFileParserCtxt(filename);
        if (!ctx) {
                fprintf(stderr, "eopkg: Error creating XML context\n");
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
                fprintf(stderr, "eopkg: Badly formed XML file, aborting\n");
                eopkg_metadata_clean(meta);
        }
        return good;
}

const char *eopkg_metadata_get_package_name(EopkgMetadata *meta)
{
        assert(meta != NULL);
        return (const char *)meta->package_name;
}

const char *eopkg_metadata_get_component(EopkgMetadata *meta)
{
        assert(meta != NULL);
        return (const char *)meta->component;
}
