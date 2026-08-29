// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H




// Tap Dance declarations
enum {
    TD_DOT_ENTER,
    QUOT_LAYR
};



// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;


// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(tap_dance_state_t *state, void *user_data);
void ql_reset(tap_dance_state_t *state, void *user_data);




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
     *             ┌───┐
     *             │TAB│
     * ┌───┬───┬───┼───┤
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
        KC_NO,  KC_NO,              KC_NO,     KC_TAB,
        KC_7,   KC_8,               KC_9,      KC_SLSH,
        KC_4,   KC_5,               KC_6,      KC_ASTR,
        KC_1,   KC_2,               KC_3,      KC_MINS,
        KC_0,   TD(TD_DOT_ENTER),   QUOT_LAYR, KC_PLUS
    ),

    /*
     *             ┌───┐
     *             │MTE│
     * ┌───┬───┬───┼───┤
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
        KC_NO,  KC_NO,    KC_NO,   KC_MUTE,
        KC_F13, KC_F14,   KC_F15,  KC_F16,
        KC_F17, KC_F18,   KC_F19,  KC_F20,
        KC_F21, KC_F22,   KC_F23,  KC_F24,
        KC_NO,  KC_NO,    KC_TRNS, KC_NO
    )
};


//More Tap and Hold Layer Code

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_BACKSPACE);
            break;
        case TD_SINGLE_HOLD:
            layer_on(1);
            break;
        default:
            break;
    }
}

void ql_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(1);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [QUOT_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset),
    [TD_DOT_ENTER] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_ENTER)
};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 175;
        default:
            return TAPPING_TERM;
    }
}
