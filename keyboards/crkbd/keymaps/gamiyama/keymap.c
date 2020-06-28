#include QMK_KEYBOARD_H
#include "keymap_jp.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.      ,-----------------------------------------------------.
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
     KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN, JP_COLN, \
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
                                KC_LGUI, LOWER,   KC_SPC,         KC_ENT,  RAISE,   KC_RALT \
                             //`--------------------------'      `--------------------------'
  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.      ,-----------------------------------------------------.
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
     _______, JP_DOT,  JP_SLSH, JP_ASTR, JP_MINS, JP_PLUS,        JP_SCLN, JP_COLN, JP_LBRC, JP_RBRC, JP_BSLS, _______, \
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
     _______, _______, JP_CIRC, JP_AT,   JP_YEN,  LALT(JP_YEN),   JP_SCLN, JP_COLN, _______, _______, _______, _______, \
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
                                _______, ADJUST , _______,        _______, _______, _______ \
                             //`--------------------------'      `--------------------------'
  ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.      ,-----------------------------------------------------.
     KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,  \
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
     _______, KC_F11,  KC_F12,  _______, _______, _______,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______,        KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, \
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
                                _______, _______, _______,        _______, _______, _______ \
                             //`--------------------------'      `--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.      ,-----------------------------------------------------.
     RESET,   RGBRST,  _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, \
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
     RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,        _______, _______, _______, _______, _______, _______, \
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
hogehoge.com
     RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______,        _______, _______, _______, _______, _______, _______, \
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
                                _______, _______, _______,        _______, _______, _______ \
                             //`--------------------------'      `--------------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

static bool lower_pressed = false;
static bool raise_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        lower_pressed = true;
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);

        if (lower_pressed) {
          register_code(JP_MEISU);
          unregister_code(JP_MEISU);
        }
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);

        if (raise_pressed) {
          register_code(JP_MKANA);
          unregister_code(JP_MKANA);
          
        }
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    default:
      if (record->event.pressed) {
        lower_pressed = false;
        raise_pressed = false;
      }
      break;
  }
  return true;
}