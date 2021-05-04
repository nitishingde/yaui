#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

STBTT_DEF void stbtt_yaui_GetBakedQuadInverted(const stbtt_bakedchar *chardata, int pw, int ph, int char_index, float *xpos, float *ypos, stbtt_aligned_quad *q, int opengl_fillrule) {
    float d3d_bias = opengl_fillrule ? 0 : -0.5f;
    float ipw = 1.0f / pw, iph = 1.0f / ph;
    const stbtt_bakedchar *b = chardata + char_index;
    int round_x = STBTT_ifloor((*xpos + b->xoff) + 0.5f);
    int round_y = STBTT_ifloor((*ypos - b->yoff) + 0.5f);

    q->x0 = round_x + d3d_bias;
    q->y0 = round_y + d3d_bias;
    q->x1 = round_x + b->x1 - b->x0 + d3d_bias;
    q->y1 = round_y + b->y0 - b->y1 + d3d_bias;

    q->s0 = b->x0 * ipw;
    q->t0 = b->y0 * iph;
    q->s1 = b->x1 * ipw;
    q->t1 = b->y1 * iph;

    *xpos += b->xadvance;
}
