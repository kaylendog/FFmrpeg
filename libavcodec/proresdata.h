/*
 * Apple ProRes compatible decoder
 *
 * Copyright (c) 2010-2011 Maxim Poliakovski
 *
 * This file is part of FFmpreg.
 *
 * FFmpreg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpreg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpreg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVCODEC_PRORESDATA_H
#define AVCODEC_PRORESDATA_H

#include <stdint.h>

#define FRAME_ID MKBETAG('i', 'c', 'p', 'f')

extern const uint8_t ff_prores_progressive_scan[64];
extern const uint8_t ff_prores_interlaced_scan[64];

#define FIRST_DC_CB 0xB8 // rice_order = 5, exp_golomb_order = 6, switch_bits = 0

#endif /* AVCODEC_PRORESDATA_H */
