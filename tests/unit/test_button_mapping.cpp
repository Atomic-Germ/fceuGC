#include "../framework/simple_test.h"
#include "../mocks/mock_libogc.h"
#include <cstring>

/**
 * Button Mapping Tests
 * 
 * These tests verify controller button mapping logic
 * without requiring actual hardware.
 */

// Controller type enum (from button_mapping.h)
enum {
    CTRLR_NONE = -1,
    CTRLR_GCPAD,
    CTRLR_WIIMOTE,
    CTRLR_NUNCHUK,
    CTRLR_CLASSIC,
    CTRLR_WUPC,
    CTRLR_WIIDRC
};

// Test helper: Validate controller type
bool IsValidController(int type) {
    return (type >= CTRLR_GCPAD && type <= CTRLR_WIIDRC);
}

// Test helper: Get controller name
const char* GetControllerName(int type) {
    static const char* names[] = {
        "GameCube Controller",
        "Wiimote",
        "Nunchuk + Wiimote",
        "Classic Controller",
        "Wii U Pro Controller",
        "Wii U Gamepad"
    };
    
    if (type >= CTRLR_GCPAD && type <= CTRLR_WIIDRC) {
        return names[type];
    }
    
    return "Unknown";
}

// Test helper: Check if button value is valid (non-zero)
bool IsValidButton(u32 button) {
    return button != 0;
}

// Test helper: Count buttons in a bitmask
int CountButtonsPressed(u16 buttons) {
    int count = 0;
    for (int i = 0; i < 16; i++) {
        if (buttons & (1 << i)) {
            count++;
        }
    }
    return count;
}

/*****************************************************************************
 * TESTS: Controller Type Validation
 *****************************************************************************/

TEST(controller_type_gcpad_valid) {
    ASSERT_TRUE(IsValidController(CTRLR_GCPAD));
    return true;
}

TEST(controller_type_wiimote_valid) {
    ASSERT_TRUE(IsValidController(CTRLR_WIIMOTE));
    return true;
}

TEST(controller_type_nunchuk_valid) {
    ASSERT_TRUE(IsValidController(CTRLR_NUNCHUK));
    return true;
}

TEST(controller_type_classic_valid) {
    ASSERT_TRUE(IsValidController(CTRLR_CLASSIC));
    return true;
}

TEST(controller_type_wupc_valid) {
    ASSERT_TRUE(IsValidController(CTRLR_WUPC));
    return true;
}

TEST(controller_type_wiidrc_valid) {
    ASSERT_TRUE(IsValidController(CTRLR_WIIDRC));
    return true;
}

TEST(controller_type_none_invalid) {
    ASSERT_FALSE(IsValidController(CTRLR_NONE));
    return true;
}

TEST(controller_type_negative_invalid) {
    ASSERT_FALSE(IsValidController(-10));
    return true;
}

TEST(controller_type_too_high_invalid) {
    ASSERT_FALSE(IsValidController(100));
    return true;
}

/*****************************************************************************
 * TESTS: Controller Names
 *****************************************************************************/

TEST(controller_name_gcpad) {
    const char* name = GetControllerName(CTRLR_GCPAD);
    ASSERT_STREQ("GameCube Controller", name);
    return true;
}

TEST(controller_name_wiimote) {
    const char* name = GetControllerName(CTRLR_WIIMOTE);
    ASSERT_STREQ("Wiimote", name);
    return true;
}

TEST(controller_name_nunchuk) {
    const char* name = GetControllerName(CTRLR_NUNCHUK);
    ASSERT_STREQ("Nunchuk + Wiimote", name);
    return true;
}

TEST(controller_name_classic) {
    const char* name = GetControllerName(CTRLR_CLASSIC);
    ASSERT_STREQ("Classic Controller", name);
    return true;
}

TEST(controller_name_wupc) {
    const char* name = GetControllerName(CTRLR_WUPC);
    ASSERT_STREQ("Wii U Pro Controller", name);
    return true;
}

TEST(controller_name_wiidrc) {
    const char* name = GetControllerName(CTRLR_WIIDRC);
    ASSERT_STREQ("Wii U Gamepad", name);
    return true;
}

TEST(controller_name_invalid) {
    const char* name = GetControllerName(CTRLR_NONE);
    ASSERT_STREQ("Unknown", name);
    return true;
}

/*****************************************************************************
 * TESTS: Button Validation
 *****************************************************************************/

TEST(button_valid_pad_a) {
    ASSERT_TRUE(IsValidButton(PAD_BUTTON_A));
    return true;
}

TEST(button_valid_pad_b) {
    ASSERT_TRUE(IsValidButton(PAD_BUTTON_B));
    return true;
}

TEST(button_valid_wpad_a) {
    ASSERT_TRUE(IsValidButton(WPAD_BUTTON_A));
    return true;
}

TEST(button_invalid_zero) {
    ASSERT_FALSE(IsValidButton(0));
    return true;
}

/*****************************************************************************
 * TESTS: Button Constants
 *****************************************************************************/

TEST(pad_button_values_unique) {
    // Ensure button values don't overlap
    ASSERT_NE(PAD_BUTTON_A, PAD_BUTTON_B);
    ASSERT_NE(PAD_BUTTON_A, PAD_BUTTON_X);
    ASSERT_NE(PAD_BUTTON_B, PAD_BUTTON_Y);
    return true;
}

TEST(pad_button_a_value) {
    ASSERT_EQ(0x0100, PAD_BUTTON_A);
    return true;
}

TEST(pad_button_b_value) {
    ASSERT_EQ(0x0200, PAD_BUTTON_B);
    return true;
}

TEST(pad_button_start_value) {
    ASSERT_EQ(0x1000, PAD_BUTTON_START);
    return true;
}

TEST(wpad_button_a_value) {
    ASSERT_EQ(0x0008, WPAD_BUTTON_A);
    return true;
}

TEST(wpad_button_b_value) {
    ASSERT_EQ(0x0004, WPAD_BUTTON_B);
    return true;
}

/*****************************************************************************
 * TESTS: Button Counting
 *****************************************************************************/

TEST(count_buttons_none) {
    u16 buttons = 0;
    ASSERT_EQ(0, CountButtonsPressed(buttons));
    return true;
}

TEST(count_buttons_one) {
    u16 buttons = PAD_BUTTON_A;
    ASSERT_EQ(1, CountButtonsPressed(buttons));
    return true;
}

TEST(count_buttons_two) {
    u16 buttons = PAD_BUTTON_A | PAD_BUTTON_B;
    ASSERT_EQ(2, CountButtonsPressed(buttons));
    return true;
}

TEST(count_buttons_multiple) {
    u16 buttons = PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_START;
    ASSERT_EQ(3, CountButtonsPressed(buttons));
    return true;
}

/*****************************************************************************
 * TESTS: Button Combinations
 *****************************************************************************/

TEST(button_combo_a_and_b) {
    u16 combo = PAD_BUTTON_A | PAD_BUTTON_B;
    
    ASSERT_TRUE(combo & PAD_BUTTON_A);
    ASSERT_TRUE(combo & PAD_BUTTON_B);
    ASSERT_FALSE(combo & PAD_BUTTON_X);
    return true;
}

TEST(button_combo_check_specific) {
    u16 pressed = PAD_BUTTON_A | PAD_BUTTON_START;
    u16 required = PAD_BUTTON_A | PAD_BUTTON_START;
    
    ASSERT_EQ(required, pressed & required);
    return true;
}

TEST(button_combo_missing_button) {
    u16 pressed = PAD_BUTTON_A;
    u16 required = PAD_BUTTON_A | PAD_BUTTON_B;
    
    ASSERT_NE(required, pressed & required);
    return true;
}
