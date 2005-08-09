/* babl - dynamically extendable universal pixel conversion library.
 * Copyright (C) 2005, Øyvind Kolås.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef _BABL_INTERNAL_H
#define _BABL_INTERNAL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "babl-ids.h"
#include "babl-util.h"
#include "babl-memory.h"
#include "babl-classes.h"

#define babl_log(fmt, args...) do {      \
  fprintf (stdout, "babl: ");            \
  fprintf (stdout, fmt, args);           \
  fprintf (stdout, "\n");                \
} while (0)


extern int babl_hmpf_on_name_lookups;

#define BABL_DEFINE_EACH(type_name)                           \
void                                                          \
type_name##_each (BablEachFunction  each_fun,                 \
                     void          *user_data)                \
{                                                             \
  db_each (each_fun, user_data);                              \
}                                                             \

#define BABL_DEFINE_LOOKUP_BY_ID(TypeName, type_name)         \
TypeName *                                                    \
type_name##_id (int id)                                       \
{                                                             \
  return (TypeName*) db_exist (id, NULL);                     \
}

#define BABL_DEFINE_LOOKUP_BY_NAME(TypeName, type_name)       \
TypeName *                                                    \
type_name (const char *name)                                  \
{                                                             \
  if (babl_hmpf_on_name_lookups)                              \
    {                                                         \
      babl_log ("%s(\"%s\"): hmpf!", __FUNCTION__, name);     \
    }                                                         \
  return (TypeName*) db_exist (0, name);                      \
}

#define BABL_DEFINE_INIT(type_name)                           \
void                                                          \
type_name##_init (void)                                       \
{                                                             \
  db_init ();                                                 \
}

#define BABL_DEFINE_DESTROY(type_name)                        \
void                                                          \
type_name##_destroy (void)                                    \
{                                                             \
  db_each (each_##type_name##_destroy, NULL);                 \
  db_destroy ();                                              \
}

#define BABL_CLASS_TEMPLATE(TypeName, type_name, type_string) \
BABL_DEFINE_INIT           (type_name)                        \
BABL_DEFINE_DESTROY        (type_name)                        \
BABL_DEFINE_LOOKUP_BY_NAME (TypeName, type_name)              \
BABL_DEFINE_EACH           (type_name)                        \
BABL_DEFINE_LOOKUP_BY_ID   (TypeName, type_name)               


#endif
