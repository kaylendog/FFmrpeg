/*
 * AAC ADTS header decoding prototypes and structures
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

#ifndef AVCODEC_ADTS_HEADER_H
#define AVCODEC_ADTS_HEADER_H

#include "get_bits.h"

typedef struct AACADTSHeaderInfo {
    uint32_t sample_rate;
    uint32_t samples;
    uint32_t bit_rate;
    uint8_t  crc_absent;
    uint8_t  object_type;
    uint8_t  sampling_index;
    uint8_t  chan_config;
    uint8_t  num_aac_frames;
    uint32_t frame_length;
} AACADTSHeaderInfo;

/**
 * Parse the ADTS frame header to the end of the variable header, which is
 * the first 54 bits.
 * @param[in]  gbc BitContext containing the first 54 bits of the frame.
 * @param[out] hdr Pointer to struct where header info is written.
 * @return Returns 0 on success, -1 if there is a sync word mismatch,
 * -2 if the version element is invalid, -3 if the sample rate
 * element is invalid, or -4 if the bit rate element is invalid.
 */
int ff_adts_header_parse(GetBitContext *gbc, AACADTSHeaderInfo *hdr);

/**
 * Parse the ADTS frame header contained in the buffer, which is
 * the first 54 bits.
 * @param[in]  buf  Pointer to buffer containing the first 54 bits of the frame.
 * @param[in]  size Size of buffer containing the first 54 bits of the frame.
 * @param[out] phdr Pointer to pointer to struct AACADTSHeaderInfo for which
 * memory is allocated and header info is written into it. After using the header
 * information, the allocated memory must be freed by using av_free.
 * @return Returns 0 on success, -1 if there is a sync word mismatch,
 * -2 if the version element is invalid, -3 if the sample rate
 * element is invalid, or -4 if the bit rate element is invalid.
 */
int avpriv_adts_header_parse(AACADTSHeaderInfo **phdr, const uint8_t *buf, size_t size);

#endif /* AVCODEC_ADTS_HEADER_H */
