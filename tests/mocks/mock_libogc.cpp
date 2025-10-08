#include "mock_libogc.h"

// Mock video mode objects
// These are simplified versions - just enough to satisfy linker requirements

GXRModeObj TVNtsc480IntDf = {
    0,      // viTVMode
    640,    // fbWidth
    480,    // efbHeight
    480,    // xfbHeight
    0,      // viXOrigin
    0,      // viYOrigin
    640,    // viWidth
    480,    // viHeight
    0,      // xfbMode
    0,      // field_rendering
    0,      // aa
    {{0}},  // sample_pattern
    {0}     // vfilter
};

GXRModeObj TVNtsc480Prog = {
    0,
    640,
    480,
    480,
    0,
    0,
    640,
    480,
    0,
    0,
    0,
    {{0}},
    {0}
};

GXRModeObj TVNtsc480ProgSoft = {
    0,
    640,
    480,
    480,
    0,
    0,
    640,
    480,
    0,
    0,
    0,
    {{0}},
    {0}
};

GXRModeObj TVNtsc480ProgAa = {
    0,
    640,
    480,
    480,
    0,
    0,
    640,
    480,
    0,
    0,
    1,      // aa enabled
    {{0}},
    {0}
};

GXRModeObj TVPal528IntDf = {
    0,
    640,
    528,
    528,
    0,
    0,
    640,
    528,
    0,
    0,
    0,
    {{0}},
    {0}
};

GXRModeObj TVPal528ProgSoft = {
    0,
    640,
    528,
    528,
    0,
    0,
    640,
    528,
    0,
    0,
    0,
    {{0}},
    {0}
};

GXRModeObj TVPal524IntAa = {
    0,
    640,
    524,
    524,
    0,
    0,
    640,
    524,
    0,
    0,
    1,      // aa enabled
    {{0}},
    {0}
};

GXRModeObj TVEurgb60Hz480IntDf = {
    0,
    640,
    480,
    480,
    0,
    0,
    640,
    480,
    0,
    0,
    0,
    {{0}},
    {0}
};

GXRModeObj TVMpal480IntDf = {
    0,
    640,
    480,
    480,
    0,
    0,
    640,
    480,
    0,
    0,
    0,
    {{0}},
    {0}
};
