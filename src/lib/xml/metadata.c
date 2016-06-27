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

#include <libxml/SAX2.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>

#include "eopkg-atomics.h"
#include "metadata.h"

struct EopkgMetadata {
        eopkg_atomic_t eatom;
};

/**
 * Handle opening of a new element
 */
static void eopkg_sax_start_element(void *udata, const xmlChar *name, const xmlChar **attrs)
{
}

/**
 * Handle closing of an element
 */
static void eopkg_sax_end_element(void *udata, const xmlChar *name)
{
}

/**
 * Handle character input
 */
static void eopkg_sax_characters(void *udata, const xmlChar *ch, int len)
{
}

static void eopkg_metadata_free(EopkgMetadata *self)
{
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
        ctx = xmlCreateFileParserCtxt(filename);
        if (!ctx) {
                fprintf(stderr, "eopkg: Error creating XML context\n");
                return false;
        }
        old = ctx->sax;
        ctx->sax = &handler;
        /* ctx->userData = &instance; */
        ctx->userData = NULL;

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
        }
        return good;
}
