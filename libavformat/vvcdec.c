/*
 * RAW H.266 / VVC video demuxer
 * Copyright (c) 2020 Nuo Mi <nuomi2021@gmail.com>
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

#include "libavcodec/vvc.h"

#include "avformat.h"
#include "rawdec.h"

static int vvc_probe(const AVProbeData *p)
{
    uint32_t code = -1;
    int sps = 0, pps = 0, irap = 0;
    int i;

    for (i = 0; i < p->buf_size - 1; i++) {
        code = (code << 8) + p->buf[i];
        if ((code & 0xffffff00) == 0x100) {
            uint8_t nal2 = p->buf[i + 1];
            int type = (nal2 & 0xF8) >> 3;

            if (code & 0x80) // forbidden_zero_bit
                return 0;

            if ((nal2 & 0x7) == 0) // nuh_temporal_id_plus1
                return 0;

            switch (type) {
            case VVC_SPS_NUT:       sps++;  break;
            case VVC_PPS_NUT:       pps++;  break;
            case VVC_IDR_N_LP:
            case VVC_IDR_W_RADL:
            case VVC_CRA_NUT:
            case VVC_GDR_NUT:       irap++; break;
            }
        }
    }

    if (sps && pps && irap)
        return AVPROBE_SCORE_EXTENSION + 1; // 1 more than .mpg
    return 0;
}

FF_DEF_RAWVIDEO_DEMUXER(vvc, "raw H.266/VVC video", vvc_probe, "h266,266,vvc", AV_CODEC_ID_VVC)
