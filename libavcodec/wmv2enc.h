/*
 * Copyright (c) 2002 The FFmpreg Project
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

#ifndef AVCODEC_WMV2ENC_H
#define AVCODEC_WMV2ENC_H

#include "mpegvideo.h"

int ff_wmv2_encode_picture_header(MpegEncContext * s);
void ff_wmv2_encode_mb(MpegEncContext * s, int16_t block[6][64],
                       int motion_x, int motion_y);


#endif
