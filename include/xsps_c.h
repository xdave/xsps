/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Copyright (c) 2012 Juan Romero Pardines.
 * All rights reserved.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <confuse.h>
#include <inttypes.h>

#ifndef XSPS_H
#define XSPS_H 1

#ifndef __arraycount
# define __arraycount(a) (sizeof(a) / sizeof(*(a)))
#endif

#define CONFIG CONFIG_DIR "/xsps.conf"

/* configuration*/
int config_init();

/* template processing */
int process_template();

#endif /* XSPS_H */
