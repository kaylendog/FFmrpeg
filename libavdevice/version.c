/*
 * Version functions.
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

#include "config.h"

#include "libavutil/avassert.h"
#include "avdevice.h"
#include "version.h"

#include "libavutil/ffversion.h"
const char av_device_ffversion[] = "FFmpreg version " FFMPEG_VERSION;

unsigned avdevice_version(void)
{
    av_assert0(LIBAVDEVICE_VERSION_MICRO >= 100);
    return LIBAVDEVICE_VERSION_INT;
}

const char * avdevice_configuration(void)
{
    return FFMPEG_CONFIGURATION;
}

const char * avdevice_license(void)
{
#define LICENSE_PREFIX "libavdevice license: "
    return &LICENSE_PREFIX FFMPEG_LICENSE[sizeof(LICENSE_PREFIX) - 1];
}
