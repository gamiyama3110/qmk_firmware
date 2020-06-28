#include QMK_KEYBOARD_H
#include "version.h"
#include "sendstring_jis.h"

// JIS keyboard
#define JK_CIRC KC_EQL      // ^
#define JK_AT   KC_LBRC     // @
#define JK_LBRC KC_RBRC     // [
#define JK_CLN  KC_QUOT     // :
#define JK_RBRC KC_BSLS     // ]
#define JK_BSLS KC_RO       // Backslash(\)
#define JK_DQT  S(KC_2)     // "
#define JK_AMPR S(KC_6)     // &
#define JK_SQT  S(KC_7)     // '
#define JK_LPRN S(KC_8)     // (
#define JK_RPRN S(KC_9)     // )
#define JK_S0   S(KC_0)     // Tilde(~) at IBM 5576-A01 spec
#define JK_EQ   S(KC_MINS)  // =
#define JK_TLD  S(JK_CIRC)  // ~
#define JK_PIPE S(KC_JYEN)  // |
#define JK_GRV  S(JK_AT)    // `
#define JK_LCBR S(JK_LBRC)  // {
#define JK_PLUS S(KC_SCLN)  // +
#define JK_ASTR S(JK_CLN)   // *
#define JK_RCBR S(JK_RBRC)  // }
#define JK_QUES S(KC_SLSH)  // ?
#define JK_UNDS S(JK_BSLS)  // _

enum fortitude60_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT( \
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,  \
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN, JP_COLN, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
                    _______, KC_RALT, LOWER, KC_SPC,    _______, _______, KC_ENT,  RAISE,   KC_LGUI, _______\
),

[_LOWER] = LAYOUT( \
  _______, KC_EXLM, JK_DQT,  KC_HASH, KC_DLR,  KC_PERC,                   JK_AMPR, JK_SQT,  JK_LPRN, JK_RPRN, JP_MINS, KC_BSPC, \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_DEL,  \
  _______, _______, _______, JP_ASTR, JP_MINS, JP_PLUS,                   JP_ASTR, JK_EQ,   JK_TLD,  JK_GRV,  JK_PIPE, JK_UNDS, \
  _______, _______, JP_CIRC, JP_AT,JP_YEN,LALT(JP_YEN), RESET,   _______, JK_LBRC, JK_RBRC, JK_LCBR, JK_RCBR, _______, _______, \
                    _______, _______, _______, _______, _______, _______, _______,  ADJUST, _______, _______\
),

[_RAISE] = LAYOUT( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,  \
  _______, KC_F11,  KC_F12,  _______, _______, _______,                    _______, _______, _______, _______, _______, KC_DEL,  \
  _______, _______, _______, _______, _______, _______,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, \
                    _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______\
),

[_ADJUST] =  LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______\
)


};

static bool lower_pressed = false;
static bool raise_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        lower_pressed = true;
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (lower_pressed) {
          register_code(JP_MEISU);
          unregister_code(JP_MEISU);
        }
        lower_pressed = false;
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (raise_pressed) {
          register_code(JP_MKANA);
          unregister_code(JP_MKANA);
        }
        raise_pressed = false;
      }
      return false;
    default:
      if (record->event.pressed) {
        lower_pressed = false;
        raise_pressed = false;
      }
      break;
  }
  return true;
}
