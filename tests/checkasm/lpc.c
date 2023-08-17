/*
 * This file is part of FFmpreg.
 *
 * FFmpreg is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * FFmpreg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with FFmpreg; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "libavutil/mem_internal.h"

#include "libavcodec/lpc.h"

#include "checkasm.h"

#define randomize_int32(buf, len)                                         \
    do {                                                                  \
        for (int i = 0; i < len; i++) {                                   \
            int32_t f = ((int)(UINT32_MAX >> 17)) - ((int)(rnd() >> 16)); \
            buf[i] = f;                                                   \
        }                                                                 \
    } while (0)

#define EPS 0.005

static void test_window(int len)
{
    LOCAL_ALIGNED(16, int32_t, src, [5000]);
    LOCAL_ALIGNED(16, double, dst0, [5000]);
    LOCAL_ALIGNED(16, double, dst1, [5000]);

    declare_func(void, const int32_t *in, ptrdiff_t len, double *out);

    randomize_int32(src, len);

    call_ref(src, len, dst0);
    call_new(src, len, dst1);

    for (int i = 0; i < len; i++) {
        if (!double_near_abs_eps(dst0[i], dst1[i], EPS)) {
            fprintf(stderr, "%d: %- .12f - %- .12f = % .12g\n",
                    i, dst0[i], dst1[i], dst0[i] - dst1[i]);
            fail();
            break;
        }
    }

    bench_new(src, len, dst1);
}

void checkasm_check_lpc(void)
{
    LPCContext ctx;
    int len = rnd() % 5000;
    ff_lpc_init(&ctx, 32, 16, FF_LPC_TYPE_DEFAULT);

    if (check_func(ctx.lpc_apply_welch_window, "apply_welch_window_even")) {
        test_window(len & ~1);
    }
    report("apply_welch_window_even");

    if (check_func(ctx.lpc_apply_welch_window, "apply_welch_window_odd")) {
        test_window(len | 1);
    }
    report("apply_welch_window_odd");

    ff_lpc_end(&ctx);
}
