// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


enum layers {
    _BASE,
    _NUMPAD
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_4x4(
        KC_ESC,  KC_1,    KC_2,    KC_3,
        KC_TAB,  KC_Q,    KC_W,    KC_E,
        KC_LSFT, KC_A,    KC_S,    KC_D,
        MO(_NUMPAD), KC_Z, KC_X, KC_C
    ),

    [_NUMPAD] = LAYOUT_ortho_4x4(
        KC_P7, KC_P8,   KC_P9,   KC_PSLS,
        KC_P4, KC_P5,   KC_P6,   KC_PAST,
        KC_P1, KC_P2,   KC_P3,   KC_PMNS,
        KC_P0, KC_PDOT, KC_PENT, KC_PPLS
    )
};


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        tap_code(clockwise ? KC_VOLU : KC_VOLD);
    } else if (index == 1) {
        tap_code(clockwise ? KC_RIGHT : KC_LEFT);
    }
    return true;
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_clear();
    oled_write_ln(PSTR("Arwin Numpad"), false);

    // Show active layer
    switch (biton32(layer_state)) {
        case _BASE:
            oled_write_ln(PSTR("Keyboard"), false);
            break;
        case _NUMPAD:
            oled_write_ln(PSTR("Numpad"), false);
            break;
    }

    return false;
}
#endif
