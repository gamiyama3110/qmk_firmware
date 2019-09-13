#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "keymap_jp.h"

#define L0 0
#define L1 1
#define L2 2
#define L3 3

#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [L0] = LAYOUT_ergodox(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,
    XXXXXXX, KC_APP , KC_LALT, KC_LGUI, MO(L1),
    XXXXXXX, XXXXXXX,
    XXXXXXX,
    LT(KC_LSFT,KC_SPC), LT(L2,JP_MEISU), XXXXXXX,

    XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
    XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, XXXXXXX,
    XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX,
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,
    XXXXXXX,
    XXXXXXX, JP_MKANA, KC_ENT
  ),
  [L1] = LAYOUT_ergodox(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
    _______, KC_F11,  KC_F12,  _______, _______, _______, _______,
    _______, JP_DOT,  JP_SLSH, JP_ASTR, JP_MINS, JP_PLUS,
    _______, _______, JP_CIRC, JP_AT,   JP_MINS, LALT(JP_YEN), _______,
    _______, _______, _______, _______, _______,
    _______, RESET,
    _______,
    _______, _______, _______,

    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
    _______, _______, _______, _______, _______, _______, KC_DEL,
             KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, JP_SCLN, JP_COLN, JP_LBRC, JP_RBRC, JP_BSLS, _______,
                      _______, _______, _______, _______, _______,
    _______, _______,
    _______,
    _______, _______, _______
  ),
  [L2] = LAYOUT_ergodox(
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,
    _______, _______,
    _______,
    _______, _______, _______,

    _______, _______, _______, _______, _______, _______, _______,
    _______, KC_TAB,  KC_7,    KC_8,    KC_9,    _______, _______,
             KC_BSLS, KC_4,    KC_5,    KC_6,    KC_MINS, _______,
    _______, KC_ASTR, KC_1,    KC_2,    KC_3,    KC_PLUS, _______,
                      KC_0,    _______, KC_DOT,  _______, _______,
    _______, _______,
    _______,
    _______, _______, _______
  ),
  [L3] = LAYOUT_ergodox(
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,
    _______, _______,
    _______,
    _______, _______, _______,

    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,
                      _______, _______, _______, _______, _______,
    _______, _______,
    _______,
    _______, _______, _______
  ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(L0)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
          break;
        case 1:
          if (record->event.pressed) {
            ergodox_right_led_2_on();
            return MACRO(D(LSFT), T(END), U(LSFT), D(LCTL), T(C), U(LCTL), END);
          }
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case L0:
            ergodox_right_led_1_on();
            break;
        case L1:
            ergodox_right_led_3_on();
            break;
        default:
            // none
            break;
    }

};
