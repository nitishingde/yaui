#ifndef YAUI_STB_H
#define YAUI_STB_H


#include "../stb/stb_image.h"
#include "../stb/stb_truetype.h"


// @yaui
// Call GetBakedQuad with char_index = 'character - first_char', and it
// creates the quad you need to draw and advances the current position.
//
// The coordinate system used assumes y increases upwards.
//
// Characters will extend both above and below the current position;
// see discussion of "BASELINE" above.
//
// It's inefficient; you might want to c&p it and optimize it.
STBTT_DEF void stbtt_yaui_GetBakedQuadInverted(const stbtt_bakedchar *chardata, int pw, int ph,  // same data as above
                                               int char_index,             // character to display
                                               float *xpos, float *ypos,   // pointers to current position in screen pixel space
                                               stbtt_aligned_quad *q,      // output: quad to draw
                                               int opengl_fillrule);       // true if opengl fill rule; false if DX9 or earlier


#endif //YAUI_STB_H
