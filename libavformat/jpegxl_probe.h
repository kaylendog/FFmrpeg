/*
 * Jpeg XL header verification
 * Copyright (c) 2022 Leo Izen <leo.izen@gmail.com>
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

#ifndef AVFORMAT_JPEGXL_PROBE_H
#define AVFORMAT_JPEGXL_PROBE_H

#include <stdint.h>

#define FF_JPEGXL_CODESTREAM_SIGNATURE_LE 0x0aff
#define FF_JPEGXL_CONTAINER_SIGNATURE_LE 0x204c584a0c000000

/**
 * @brief verify that a codestream header is valid
 * @return Negative upon error, 0 upon verifying that the codestream is not animated,
 *         and 1 upon verifying that it is animated
 */
int ff_jpegxl_verify_codestream_header(const uint8_t *buf, int buflen, int validate_level);

#endif /* AVFORMAT_JPEGXL_PROBE_H */
