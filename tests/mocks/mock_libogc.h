#ifndef MOCK_LIBOGC_H
#define MOCK_LIBOGC_H

#include <cstdint>
#include <cstdlib>

// Basic types from libogc
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef volatile uint8_t vu8;
typedef volatile uint16_t vu16;
typedef volatile uint32_t vu32;
typedef volatile uint64_t vu64;

typedef volatile int8_t vs8;
typedef volatile int16_t vs16;
typedef volatile int32_t vs32;
typedef volatile int64_t vs64;

typedef float f32;
typedef double f64;

typedef volatile float vf32;
typedef volatile double vf64;

// Boolean type
typedef int BOOL;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

// Video mode object structure (simplified)
typedef struct _GXRModeObj {
    u32 viTVMode;
    u16 fbWidth;
    u16 efbHeight;
    u16 xfbHeight;
    u16 viXOrigin;
    u16 viYOrigin;
    u16 viWidth;
    u16 viHeight;
    u32 xfbMode;
    u8 field_rendering;
    u8 aa;
    u8 sample_pattern[12][2];
    u8 vfilter[7];
} GXRModeObj;

// PAD types (controller)
#define PAD_BUTTON_LEFT     0x0001
#define PAD_BUTTON_RIGHT    0x0002
#define PAD_BUTTON_DOWN     0x0004
#define PAD_BUTTON_UP       0x0008
#define PAD_TRIGGER_Z       0x0010
#define PAD_TRIGGER_R       0x0020
#define PAD_TRIGGER_L       0x0040
#define PAD_BUTTON_A        0x0100
#define PAD_BUTTON_B        0x0200
#define PAD_BUTTON_X        0x0400
#define PAD_BUTTON_Y        0x0800
#define PAD_BUTTON_START    0x1000

// WPAD types (Wiimote)
#define WPAD_BUTTON_2       0x0001
#define WPAD_BUTTON_1       0x0002
#define WPAD_BUTTON_B       0x0004
#define WPAD_BUTTON_A       0x0008
#define WPAD_BUTTON_MINUS   0x0010
#define WPAD_BUTTON_HOME    0x0080
#define WPAD_BUTTON_LEFT    0x0100
#define WPAD_BUTTON_RIGHT   0x0200
#define WPAD_BUTTON_DOWN    0x0400
#define WPAD_BUTTON_UP      0x0800
#define WPAD_BUTTON_PLUS    0x1000

// Mock video functions
static inline void VIDEO_Init() {}
static inline void VIDEO_Flush() {}
static inline void VIDEO_SetNextFramebuffer(void* fb) { (void)fb; }
static inline void VIDEO_SetBlack(int black) { (void)black; }
static inline void VIDEO_WaitVSync() {}
static inline void* VIDEO_GetPreferredMode(void* mode) { return mode; }

// Mock PAD functions
static inline void PAD_Init() {}
static inline u16 PAD_ButtonsHeld(int chan) { (void)chan; return 0; }
static inline u16 PAD_ButtonsDown(int chan) { (void)chan; return 0; }
static inline s8 PAD_StickX(int chan) { (void)chan; return 0; }
static inline s8 PAD_StickY(int chan) { (void)chan; return 0; }

// Mock WPAD functions
static inline void WPAD_Init() {}
static inline u32 WPAD_ButtonsHeld(int chan) { (void)chan; return 0; }
static inline u32 WPAD_ButtonsDown(int chan) { (void)chan; return 0; }

// Mock memory functions
static inline void* MEM2_alloc(u32 size) { return malloc(size); }
static inline void MEM2_free(void* ptr) { free(ptr); }
static inline void* SYS_AllocateFramebuffer(GXRModeObj* rmode) { (void)rmode; return malloc(1024*1024); }

// Mock system functions
static inline void SYS_SetResetCallback(void (*cb)(void)) { (void)cb; }
static inline void SYS_SetPowerCallback(void (*cb)(void)) { (void)cb; }

// Mock GX (graphics) functions
static inline void GX_Init(void* fifo, u32 size) { (void)fifo; (void)size; }
static inline void GX_SetViewport(f32 x, f32 y, f32 w, f32 h, f32 n, f32 f) {
    (void)x; (void)y; (void)w; (void)h; (void)n; (void)f;
}

// Mock audio functions
static inline void AUDIO_Init(void* unused) { (void)unused; }
static inline void AUDIO_SetDSPSampleRate(u8 rate) { (void)rate; }
static inline void AUDIO_RegisterDMACallback(void (*cb)(void)) { (void)cb; }

// Mock DVD functions
static inline void DVD_Init() {}
static inline s32 DVD_Mount() { return 1; }
static inline s32 DVD_Unmount() { return 1; }

// Mock FAT functions  
static inline int fatMountSimple(const char* name, void* interface) { 
    (void)name; (void)interface; 
    return 1; 
}
static inline void fatUnmount(const char* name) { (void)name; }

// Mock USB functions
static inline s32 USB_Initialize() { return 0; }
static inline void USB_Deinitialize() {}

// Mock network functions
static inline s32 net_init() { return 0; }
static inline s32 net_deinit() { return 0; }

// Video mode declarations (defined in mock_libogc.cpp)
extern GXRModeObj TVNtsc480IntDf;
extern GXRModeObj TVNtsc480Prog;
extern GXRModeObj TVNtsc480ProgSoft;
extern GXRModeObj TVNtsc480ProgAa;
extern GXRModeObj TVPal528IntDf;
extern GXRModeObj TVPal528ProgSoft;
extern GXRModeObj TVPal524IntAa;
extern GXRModeObj TVEurgb60Hz480IntDf;
extern GXRModeObj TVMpal480IntDf;

#endif // MOCK_LIBOGC_H
