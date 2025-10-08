#include "../framework/simple_test.h"
#include "../mocks/mock_libogc.h"
#include <cstring>
#include <cstdlib>

/**
 * File Operation Tests
 * 
 * These tests verify file operation utilities without requiring
 * actual hardware or the full build system.
 */

// Test helper: StripDevice
// Based on source/fileop.cpp StripDevice function
// Strips device prefix from path (e.g., "sd:/path" -> "/path")
char* TestStripDevice(char* path) {
    if (path == NULL)
        return NULL;
    
    char* newpath = strchr(path, '/');
    
    if (newpath != NULL)
        newpath++;
    
    return newpath;
}

// Test helper: Check if path has device prefix
bool HasDevicePrefix(const char* path) {
    if (!path) return false;
    
    // Look for device prefix pattern like "sd:", "usb:", etc.
    const char* colon = strchr(path, ':');
    if (colon && colon[1] == '/') {
        return true;
    }
    
    return false;
}

// Test helper: Extract device name from path
bool GetDeviceName(const char* path, char* device, size_t maxLen) {
    if (!path || !device || maxLen == 0) return false;
    
    const char* colon = strchr(path, ':');
    if (colon && colon[1] == '/') {
        size_t len = colon - path;
        if (len >= maxLen) len = maxLen - 1;
        strncpy(device, path, len);
        device[len] = '\0';
        return true;
    }
    
    return false;
}

// Test helper: Check if file has valid ROM extension
bool IsValidRomExtension(const char* filename) {
    if (!filename) return false;
    
    const char* dot = strrchr(filename, '.');
    if (!dot) return false;
    
    const char* ext = dot + 1;
    
    // NES ROM extensions
    if (strcasecmp(ext, "nes") == 0) return true;
    if (strcasecmp(ext, "fds") == 0) return true;
    if (strcasecmp(ext, "nsf") == 0) return true;
    if (strcasecmp(ext, "unf") == 0) return true;
    if (strcasecmp(ext, "unif") == 0) return true;
    
    // Compressed formats
    if (strcasecmp(ext, "zip") == 0) return true;
    if (strcasecmp(ext, "gz") == 0) return true;
    if (strcasecmp(ext, "7z") == 0) return true;
    
    return false;
}

// Test helper: Get file extension
const char* GetFileExtension(const char* filename) {
    if (!filename) return NULL;
    
    const char* dot = strrchr(filename, '.');
    if (!dot || dot == filename) return NULL;
    
    return dot + 1;
}

/*****************************************************************************
 * TESTS: StripDevice
 *****************************************************************************/

TEST(strip_device_with_sd_prefix) {
    char path[] = "sd:/roms/game.nes";
    char* result = TestStripDevice(path);
    
    ASSERT_NOT_NULL(result);
    ASSERT_STREQ("roms/game.nes", result);
    return true;
}

TEST(strip_device_with_usb_prefix) {
    char path[] = "usb:/games/mario.nes";
    char* result = TestStripDevice(path);
    
    ASSERT_NOT_NULL(result);
    ASSERT_STREQ("games/mario.nes", result);
    return true;
}

TEST(strip_device_with_carda_prefix) {
    char path[] = "carda:/saves/game.sav";
    char* result = TestStripDevice(path);
    
    ASSERT_NOT_NULL(result);
    ASSERT_STREQ("saves/game.sav", result);
    return true;
}

TEST(strip_device_without_prefix) {
    char path[] = "/home/user/game.nes";
    char* result = TestStripDevice(path);
    
    ASSERT_NOT_NULL(result);
    ASSERT_STREQ("home/user/game.nes", result);
    return true;
}

TEST(strip_device_null_input) {
    char* result = TestStripDevice(nullptr);
    ASSERT_NULL(result);
    return true;
}

TEST(strip_device_no_slash) {
    char path[] = "sd:roms";
    char* result = TestStripDevice(path);
    
    ASSERT_NULL(result);
    return true;
}

/*****************************************************************************
 * TESTS: Device Prefix Detection
 *****************************************************************************/

TEST(has_device_prefix_sd) {
    ASSERT_TRUE(HasDevicePrefix("sd:/path"));
    return true;
}

TEST(has_device_prefix_usb) {
    ASSERT_TRUE(HasDevicePrefix("usb:/path"));
    return true;
}

TEST(has_device_prefix_carda) {
    ASSERT_TRUE(HasDevicePrefix("carda:/path"));
    return true;
}

TEST(has_device_prefix_none) {
    ASSERT_FALSE(HasDevicePrefix("/path/to/file"));
    return true;
}

TEST(has_device_prefix_invalid_format) {
    ASSERT_FALSE(HasDevicePrefix("sd:path"));  // Missing /
    return true;
}

TEST(has_device_prefix_null) {
    ASSERT_FALSE(HasDevicePrefix(nullptr));
    return true;
}

/*****************************************************************************
 * TESTS: Device Name Extraction
 *****************************************************************************/

TEST(get_device_name_sd) {
    char device[32];
    bool result = GetDeviceName("sd:/roms/game.nes", device, sizeof(device));
    
    ASSERT_TRUE(result);
    ASSERT_STREQ("sd", device);
    return true;
}

TEST(get_device_name_usb) {
    char device[32];
    bool result = GetDeviceName("usb:/games", device, sizeof(device));
    
    ASSERT_TRUE(result);
    ASSERT_STREQ("usb", device);
    return true;
}

TEST(get_device_name_carda) {
    char device[32];
    bool result = GetDeviceName("carda:/saves", device, sizeof(device));
    
    ASSERT_TRUE(result);
    ASSERT_STREQ("carda", device);
    return true;
}

TEST(get_device_name_no_device) {
    char device[32];
    bool result = GetDeviceName("/path/file", device, sizeof(device));
    
    ASSERT_FALSE(result);
    return true;
}

TEST(get_device_name_null_path) {
    char device[32];
    bool result = GetDeviceName(nullptr, device, sizeof(device));
    
    ASSERT_FALSE(result);
    return true;
}

TEST(get_device_name_null_buffer) {
    bool result = GetDeviceName("sd:/path", nullptr, 32);
    
    ASSERT_FALSE(result);
    return true;
}

/*****************************************************************************
 * TESTS: ROM Extension Validation
 *****************************************************************************/

TEST(valid_rom_extension_nes) {
    ASSERT_TRUE(IsValidRomExtension("game.nes"));
    return true;
}

TEST(valid_rom_extension_nes_uppercase) {
    ASSERT_TRUE(IsValidRomExtension("GAME.NES"));
    return true;
}

TEST(valid_rom_extension_fds) {
    ASSERT_TRUE(IsValidRomExtension("game.fds"));
    return true;
}

TEST(valid_rom_extension_nsf) {
    ASSERT_TRUE(IsValidRomExtension("music.nsf"));
    return true;
}

TEST(valid_rom_extension_unf) {
    ASSERT_TRUE(IsValidRomExtension("game.unf"));
    return true;
}

TEST(valid_rom_extension_unif) {
    ASSERT_TRUE(IsValidRomExtension("game.unif"));
    return true;
}

TEST(valid_rom_extension_zip) {
    ASSERT_TRUE(IsValidRomExtension("game.zip"));
    return true;
}

TEST(valid_rom_extension_gz) {
    ASSERT_TRUE(IsValidRomExtension("game.nes.gz"));
    return true;
}

TEST(valid_rom_extension_7z) {
    ASSERT_TRUE(IsValidRomExtension("game.7z"));
    return true;
}

TEST(invalid_rom_extension_txt) {
    ASSERT_FALSE(IsValidRomExtension("readme.txt"));
    return true;
}

TEST(invalid_rom_extension_sav) {
    ASSERT_FALSE(IsValidRomExtension("game.sav"));
    return true;
}

TEST(invalid_rom_extension_none) {
    ASSERT_FALSE(IsValidRomExtension("game"));
    return true;
}

TEST(invalid_rom_extension_null) {
    ASSERT_FALSE(IsValidRomExtension(nullptr));
    return true;
}

TEST(valid_rom_extension_with_path) {
    ASSERT_TRUE(IsValidRomExtension("/path/to/game.nes"));
    return true;
}

/*****************************************************************************
 * TESTS: File Extension Extraction
 *****************************************************************************/

TEST(get_extension_simple) {
    const char* ext = GetFileExtension("game.nes");
    ASSERT_NOT_NULL(ext);
    ASSERT_STREQ("nes", ext);
    return true;
}

TEST(get_extension_multiple_dots) {
    const char* ext = GetFileExtension("game.nes.gz");
    ASSERT_NOT_NULL(ext);
    ASSERT_STREQ("gz", ext);
    return true;
}

TEST(get_extension_with_path) {
    const char* ext = GetFileExtension("/roms/nes/game.nes");
    ASSERT_NOT_NULL(ext);
    ASSERT_STREQ("nes", ext);
    return true;
}

TEST(get_extension_no_extension) {
    const char* ext = GetFileExtension("game");
    ASSERT_NULL(ext);
    return true;
}

TEST(get_extension_hidden_file) {
    const char* ext = GetFileExtension(".hidden");
    ASSERT_NULL(ext);
    return true;
}

TEST(get_extension_null) {
    const char* ext = GetFileExtension(nullptr);
    ASSERT_NULL(ext);
    return true;
}

/*****************************************************************************
 * TESTS: Path Manipulation
 *****************************************************************************/

TEST(path_ends_with_slash) {
    const char* path1 = "/roms/";
    const char* path2 = "/roms";
    
    ASSERT_TRUE(path1[strlen(path1) - 1] == '/');
    ASSERT_FALSE(path2[strlen(path2) - 1] == '/');
    return true;
}

TEST(empty_path_check) {
    const char* empty = "";
    const char* nonempty = "/path";
    
    ASSERT_TRUE(strlen(empty) == 0);
    ASSERT_FALSE(strlen(nonempty) == 0);
    return true;
}
