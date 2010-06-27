/* babl - dynamically extendable universal pixel conversion library.
 * Copyright (C) 2005-2008, Øyvind Kolås.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef _BABL_H
#define _BABL_H

#ifdef __cplusplus
extern "C" {
#endif

#define BABL_INSIDE_BABL_H
#include <babl/babl-macros.h>
#include <babl/babl-types.h>
#include <babl/babl-version.h>
#undef BABL_INSIDE_BABL_H


/**
 * Initializes the babl library.
 */
void         babl_init      (void);

/**
 * Deinitializes the babl library and frees any resources used when
 * matched with the number of calls to babl_init().
 */
void         babl_exit      (void);

/**
 * Returns the babl object representing the data type given by @name
 * such as for example "u8", "u16" or "float".
 */
Babl *       babl_type      (const char *name);

/**
 * Returns the babl object representing the @horizontal and @vertical
 * sampling such as for example 2, 2 for the chroma components in
 * YCbCr.
 */
Babl *       babl_sampling  (int horizontal,
                             int vertical);

/**
 * Returns the babl object representing the color component given by
 * @name such as for example "R", "cyan" or "CIE L".
 */
Babl *       babl_component (const char *name);

/**
 * Returns the babl object representing the color model given by @name
 * such as for example "RGB", "CMYK" or "CIE Lab".
 */
Babl *       babl_model     (const char *name);

/**
 * Returns the babl object representing the color format given by
 * @name such as for example "RGB u8", "CMYK float" or "CIE Lab u16".
 */
Babl *       babl_format    (const char *name);

/*  Create a babl fish capable of converting from source_format to
 *  destination_format, source and destination can be either strings
 *  with the names of the formats or Babl-format objects.
 */
Babl *       babl_fish      (const void *source_format,
                             const void *destination_format);

/** Process n pixels from source to destination using babl_fish,
 *  returns number of pixels converted.
 */
long         babl_process   (Babl *babl_fish,
                             void *source,
                             void *destination,
                             long  n);


/**
 * Returns a string decsribing a Babl object.
 */
const char * babl_get_name                     (const Babl *babl);

/**
 * Returns whether the @format has an alpha channel.
 */
int          babl_format_has_alpha             (const Babl *format);

/**
 * Returns the bytes per pixel for a babl color format.
 */
int          babl_format_get_bytes_per_pixel   (const Babl *format);

/**
 * Returns the number of components for the given @format.
 */
int          babl_format_get_n_components      (const Babl *format);

/**
 * Returns the type in the given @format for the given
 * @component_index.
 */
Babl *       babl_format_get_type              (const Babl *format,
                                                int         component_index);


/**
 * Defines a new data type in babl. A data type that babl can have in
 * its buffers requires conversions to and from "double" to be
 * registered before passing sanity.
 *
 *     babl_type_new       (const char *name,
 *                          "bits",     int bits,
 *                          ["min_val", double min_val,]
 *                          ["max_val", double max_val,]
 *                          NULL);
 */
Babl * babl_type_new       (void *first_arg,
                            ...) BABL_ARG_NULL_TERMINATED;

/**
 * Defines a new color component with babl.
 *
 *     babl_component_new  (const char *name,
 *                          NULL);
 */
Babl * babl_component_new  (void *first_arg,
                            ...) BABL_ARG_NULL_TERMINATED;

/**
 * Defines a new color model in babl. If no name is provided a name is
 * generated by concatenating the name of all the involved components.
 *
 *     babl_model_new      (["name", const char *name,]
 *                          BablComponent *component1,
 *                          [BablComponent *componentN, ...]
 *                          NULL);
 */
Babl * babl_model_new      (void *first_arg,
                            ...) BABL_ARG_NULL_TERMINATED;

/**
 * Defines a new pixel format in babl. Provided BablType and|or
 * BablSampling is valid for the following components as well. If no
 * name is provided a (long) descriptive name is used.
 *
 *     babl_format_new     (["name", const char *name,]
 *                          BablModel          *model,
 *                          [BablType           *type,]
 *                          [BablSampling,      *sampling,]
 *                          BablComponent      *component1,
 *                          [[BablType           *type,]
 *                           [BablSampling       *sampling,]
 *                           BablComponent      *componentN,
 *                           ...]
 *                          ["planar",]
 *                          NULL);
 */
Babl * babl_format_new     (void *first_arg,
                            ...) BABL_ARG_NULL_TERMINATED;

/*
 * Defines a new pixel format in babl. With the specified data storage
 * type and the given number of components. At the moment behavior of 
 * conversions are only well defined to other babl_format_n derived formats
 * with the same number of components.
 */
Babl *
babl_format_n (Babl *type,
               int   components);

/**
 * Defines a new conversion between either two formats, two models or
 * two types in babl.
 *
 *     babl_conversion_new (<BablFormat *source, BablFormat *destination|
 *                          BablModel  *source, BablModel  *destination|
 *                          BablType   *source, BablType   *destination>,
 *                          <"linear"|"planar">, <BablFuncLinear | BablFuncPlanar> conv_func,
 *                          NULL);
 */
Babl * babl_conversion_new (void *first_arg,
                            ...) BABL_ARG_NULL_TERMINATED;


/*
 * Backwards compatibility stuff
 *
 * NOTE: will most likely be removed in the first stable release!
 */
#ifndef BABL_DISABLE_DEPRECATED
#define babl_destroy babl_exit
#endif


#ifdef __cplusplus
}
#endif

#endif
