/*
 * Common AAC and AC-3 parser prototypes
 * Copyright (c) 2003 Fabrice Bellard
 * Copyright (c) 2003 Michael Niedermayer
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

#ifndef AVCODEC_AAC_AC3_PARSER_H
#define AVCODEC_AAC_AC3_PARSER_H

#include <stdint.h>
#include "libavutil/crc.h"
#include "avcodec.h"
#include "parser.h"

typedef enum {
    AAC_AC3_PARSE_ERROR_SYNC        = -0x1030c0a,
    AAC_AC3_PARSE_ERROR_BSID        = -0x2030c0a,
    AAC_AC3_PARSE_ERROR_SAMPLE_RATE = -0x3030c0a,
    AAC_AC3_PARSE_ERROR_FRAME_SIZE  = -0x4030c0a,
    AAC_AC3_PARSE_ERROR_FRAME_TYPE  = -0x5030c0a,
    AAC_AC3_PARSE_ERROR_CRC         = -0x6030c0a,
    AAC_AC3_PARSE_ERROR_CHANNEL_CFG = -0x7030c0a,
} AACAC3ParseError;

typedef struct AACAC3ParseContext {
    ParseContext pc;
    int header_size;
    int (*sync)(uint64_t state, int *need_next_header, int *new_frame_start);

    const AVCRC *crc_ctx;
    int remaining_size;
    uint64_t state;

    int need_next_header;
    int frame_number;
} AACAC3ParseContext;

int ff_aac_ac3_parse(AVCodecParserContext *s1,
                     AVCodecContext *avctx,
                     const uint8_t **poutbuf, int *poutbuf_size,
                     const uint8_t *buf, int buf_size);

#endif /* AVCODEC_AAC_AC3_PARSER_H */
