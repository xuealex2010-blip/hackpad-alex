// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H




// Tap Dance declarations
enum {
    TD_DOT_ENTER,
};

//Tap and Double Tap Code
// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for DOT, twice for backspace
    [TD_DOT_ENTER] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_ENTER),
};



//Tap and Hold Code
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
            #ifndef PERMISSIVE_HOLD
            && !state->interrupted
            #endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold)                                        \
{                                                                               \
    .fn        = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, \
    .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}),               \
}

tap_dance_action_t tap_dance_actions[] = {
    [TAP_HOLD] = ACTION_TAP_DANCE_TAP_HOLD(KC_BACKSPACE, MO(1)),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;
    tap_dance_state_t* state;

    switch (keycode) {
        case TD(TAP_HOLD):
            action = tap_dance_get(QK_TAP_DANCE_GET_INDEX(keycode));
            state = tap_dance_get_state(QK_TAP_DANCE_GET_INDEX(keycode));
            if (!record->event.pressed && state != NULL && state->count && !state->finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
    return true;
}


//Encoder Setup
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)},
    [1] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
};
#endif

//Standard Matrix
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │   │   │   │TAB│
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │___│___│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_numpad_5x4(
        KC_NO, KC_NO, KC_NO, KC_TAB,
        KC_7,   KC_8, KC_9, KC_SLSH,
        KC_4,   KC_5,   KC_6, KC_ASTR,
        KC_1,   KC_2,   KC_3,   KC_MINS,
        KC_0,   TD(TD_DOT_BACKSPACE),   _______, KC_PLUS
    ),

    /*
     * ┌───┬───┬───┬───┐
     * │   │   │   │MTE│
     * ├───┼───┼───┼───┤
     * │F13│F14│F15│F16│
     * ├───┼───┼───┼───┤
     * │F17│F18│F19│F20│
     * ├───┼───┼───┼───┤
     * │F21│F22│F23│F24│
     * ├───┼───┼───┼───┤
     * │BKS│___│___│   │
     * └───┴───┴───┴───┘
     */
    [1] = LAYOUT_numpad_5x4(
        KC_NO,  KC_NO,    KC_NO,  KC_MUTE,
        KC_F13, KC_F14,   KC_F15, KC_F16
        KC_F17, KC_F18,   KC_F19, KC_F20,
        KC_F21, KC_F22,   KC_F23, KC_F24,
        KC_NO, KC_NO,  _______, KC_NO
    )
};
