/*
 * Copyright (c) 2000, 2001 Fabrice Bellard
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

#ifndef AVFORMAT_ASF_H
#define AVFORMAT_ASF_H

#include <stdint.h>
#include "avformat.h"
#include "metadata.h"
#include "riff.h"

typedef enum ASFDataType {
    ASF_UNICODE    = 0,
    ASF_BYTE_ARRAY = 1,
    ASF_BOOL       = 2,
    ASF_DWORD      = 3,
    ASF_QWORD      = 4,
    ASF_WORD       = 5,
    ASF_GUID       = 6,
}ASFDataType;

typedef struct ASFMainHeader {
    ff_asf_guid guid;                  ///< generated by client computer
    uint64_t file_size;         /**< in bytes
                                 *   invalid if broadcasting */
    uint64_t create_time;       /**< time of creation, in 100-nanosecond units since 1.1.1601
                                 *   invalid if broadcasting */
    uint64_t play_time;         /**< play time, in 100-nanosecond units
                                 * invalid if broadcasting */
    uint64_t send_time;         /**< time to send file, in 100-nanosecond units
                                 *   invalid if broadcasting (could be ignored) */
    uint32_t preroll;           /**< timestamp of the first packet, in milliseconds
                                 *   if nonzero - subtract from time */
    uint32_t ignore;            ///< preroll is 64 bits - but let's just ignore it
    uint32_t flags;             /**< 0x01 - broadcast
                                 *   0x02 - seekable
                                 *   rest is reserved should be 0 */
    uint32_t min_pktsize;       /**< size of a data packet
                                 *   invalid if broadcasting */
    uint32_t max_pktsize;       /**< shall be the same as for min_pktsize
                                 *   invalid if broadcasting */
    uint32_t max_bitrate;       /**< bandwidth of stream in bps
                                 *   should be the sum of bitrates of the
                                 *   individual media streams */
} ASFMainHeader;


typedef struct ASFIndex {
    uint32_t packet_number;
    uint16_t packet_count;
    uint64_t send_time;
    uint64_t offset;
} ASFIndex;

extern const ff_asf_guid ff_asf_header;
extern const ff_asf_guid ff_asf_file_header;
extern const ff_asf_guid ff_asf_stream_header;
extern const ff_asf_guid ff_asf_ext_stream_header;
extern const ff_asf_guid ff_asf_audio_stream;
extern const ff_asf_guid ff_asf_audio_conceal_spread;
extern const ff_asf_guid ff_asf_video_stream;
extern const ff_asf_guid ff_asf_jfif_media;
extern const ff_asf_guid ff_asf_video_conceal_none;
extern const ff_asf_guid ff_asf_command_stream;
extern const ff_asf_guid ff_asf_comment_header;
extern const ff_asf_guid ff_asf_codec_comment_header;
extern const ff_asf_guid ff_asf_codec_comment1_header;
extern const ff_asf_guid ff_asf_data_header;
extern const ff_asf_guid ff_asf_head1_guid;
extern const ff_asf_guid ff_asf_head2_guid;
extern const ff_asf_guid ff_asf_extended_content_header;
extern const ff_asf_guid ff_asf_simple_index_header;
extern const ff_asf_guid ff_asf_ext_stream_embed_stream_header;
extern const ff_asf_guid ff_asf_ext_stream_audio_stream;
extern const ff_asf_guid ff_asf_metadata_header;
extern const ff_asf_guid ff_asf_metadata_library_header;
extern const ff_asf_guid ff_asf_marker_header;
extern const ff_asf_guid ff_asf_reserved_4;
extern const ff_asf_guid ff_asf_my_guid;
extern const ff_asf_guid ff_asf_language_guid;
extern const ff_asf_guid ff_asf_content_encryption;
extern const ff_asf_guid ff_asf_ext_content_encryption;
extern const ff_asf_guid ff_asf_digital_signature;
extern const ff_asf_guid ff_asf_extended_stream_properties_object;
extern const ff_asf_guid ff_asf_group_mutual_exclusion_object;
extern const ff_asf_guid ff_asf_mutex_language;

extern const AVMetadataConv ff_asf_metadata_conv[];

/**
 * Handles both attached pictures as well as id3 tags.
 *
 * @return Returns < 0 on error, 1 if the type of the byte array
 *         is unsupported by this function and 0 otherwise.
 */
int ff_asf_handle_byte_array(AVFormatContext *s, const char *name,
                             int val_len);


#define ASF_PACKET_FLAG_ERROR_CORRECTION_PRESENT 0x80 //1000 0000


//   ASF data packet structure
//   =========================
//
//
//  -----------------------------------
// | Error Correction Data             |  Optional
//  -----------------------------------
// | Payload Parsing Information (PPI) |
//  -----------------------------------
// | Payload Data                      |
//  -----------------------------------
// | Padding Data                      |
//  -----------------------------------


// PPI_FLAG - Payload parsing information flags
#define ASF_PPI_FLAG_MULTIPLE_PAYLOADS_PRESENT 1

#define ASF_PPI_FLAG_SEQUENCE_FIELD_IS_BYTE  0x02 //0000 0010
#define ASF_PPI_FLAG_SEQUENCE_FIELD_IS_WORD  0x04 //0000 0100
#define ASF_PPI_FLAG_SEQUENCE_FIELD_IS_DWORD 0x06 //0000 0110
#define ASF_PPI_MASK_SEQUENCE_FIELD_SIZE     0x06 //0000 0110

#define ASF_PPI_FLAG_PADDING_LENGTH_FIELD_IS_BYTE  0x08 //0000 1000
#define ASF_PPI_FLAG_PADDING_LENGTH_FIELD_IS_WORD  0x10 //0001 0000
#define ASF_PPI_FLAG_PADDING_LENGTH_FIELD_IS_DWORD 0x18 //0001 1000
#define ASF_PPI_MASK_PADDING_LENGTH_FIELD_SIZE     0x18 //0001 1000

#define ASF_PPI_FLAG_PACKET_LENGTH_FIELD_IS_BYTE  0x20 //0010 0000
#define ASF_PPI_FLAG_PACKET_LENGTH_FIELD_IS_WORD  0x40 //0100 0000
#define ASF_PPI_FLAG_PACKET_LENGTH_FIELD_IS_DWORD 0x60 //0110 0000
#define ASF_PPI_MASK_PACKET_LENGTH_FIELD_SIZE     0x60 //0110 0000

// PL_FLAG - Payload flags
#define ASF_PL_FLAG_REPLICATED_DATA_LENGTH_FIELD_IS_BYTE   0x01 //0000 0001
#define ASF_PL_FLAG_REPLICATED_DATA_LENGTH_FIELD_IS_WORD   0x02 //0000 0010
#define ASF_PL_FLAG_REPLICATED_DATA_LENGTH_FIELD_IS_DWORD  0x03 //0000 0011
#define ASF_PL_MASK_REPLICATED_DATA_LENGTH_FIELD_SIZE      0x03 //0000 0011

#define ASF_PL_FLAG_OFFSET_INTO_MEDIA_OBJECT_LENGTH_FIELD_IS_BYTE  0x04 //0000 0100
#define ASF_PL_FLAG_OFFSET_INTO_MEDIA_OBJECT_LENGTH_FIELD_IS_WORD  0x08 //0000 1000
#define ASF_PL_FLAG_OFFSET_INTO_MEDIA_OBJECT_LENGTH_FIELD_IS_DWORD 0x0c //0000 1100
#define ASF_PL_MASK_OFFSET_INTO_MEDIA_OBJECT_LENGTH_FIELD_SIZE     0x0c //0000 1100

#define ASF_PL_FLAG_MEDIA_OBJECT_NUMBER_LENGTH_FIELD_IS_BYTE  0x10 //0001 0000
#define ASF_PL_FLAG_MEDIA_OBJECT_NUMBER_LENGTH_FIELD_IS_WORD  0x20 //0010 0000
#define ASF_PL_FLAG_MEDIA_OBJECT_NUMBER_LENGTH_FIELD_IS_DWORD 0x30 //0011 0000
#define ASF_PL_MASK_MEDIA_OBJECT_NUMBER_LENGTH_FIELD_SIZE     0x30 //0011 0000

#define ASF_PL_FLAG_STREAM_NUMBER_LENGTH_FIELD_IS_BYTE  0x40 //0100 0000
#define ASF_PL_MASK_STREAM_NUMBER_LENGTH_FIELD_SIZE     0xc0 //1100 0000

#define ASF_PL_FLAG_PAYLOAD_LENGTH_FIELD_IS_BYTE  0x40 //0100 0000
#define ASF_PL_FLAG_PAYLOAD_LENGTH_FIELD_IS_WORD  0x80 //1000 0000
#define ASF_PL_MASK_PAYLOAD_LENGTH_FIELD_SIZE     0xc0 //1100 0000

#define ASF_PL_FLAG_KEY_FRAME 0x80 //1000 0000

#endif /* AVFORMAT_ASF_H */
