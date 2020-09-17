#include QMK_KEYBOARD_H
#include "led_controller.h"

#define _BASE 0
#define _FN   1
#define _VI   2
#define _NAV  3
#define _LED  4

#define _______                                             KC_TRNS
#define _________                                           KC_TRNS
#define ___________                                         KC_TRNS
#define _____________                                       KC_TRNS
#define _________________                                   KC_TRNS
#define _________________________________________________   KC_TRNS

/* [] = LAYOUT_60_ansi_split_bs_rshift(
      _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,\
      ___________,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,___________,\
      _____________,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_________________,\
      _________________,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_____________,_______,\
      _________,_________,_________,_________________________________________________,_________,_________,_________,_________)
*/

#define UD_NEXT RALT(KC_RGHT)
#define UD_PREV LALT(KC_LEFT)
#define UD_NSCN RGUI(RCTL(KC_RGHT))
#define UD_PSCN LGUI(LCTL(KC_LEFT))
#define UD_TAB  LT(_NAV,KC_TAB)
#define UD_SEMI LT(_VI,KC_SCLN)
#define F_SOLO  F(MODE_SINGLE)
#define F_PAGE  F(MODE_PAGE)
#define F_FLASH F(MODE_FLASH)
#define F_BRITE F(BRIGHT)
#define F_DIM   F(DIM)
#define F_ALL   F(ALL)
#define F_LED   F(BACKLIGHT)

#define max_pages 5

enum ic60_keycodes {
  BACKLIGHT,
  BRIGHT,
  DIM,
  ALL,
  MODE_SINGLE,
  MODE_PAGE,
  MODE_FLASH
};

uint8_t current_layer_global = 0;
uint8_t led_mode_global = MODE_PAGE;
uint8_t backlight_status_global = 0; //init on/off state of backlight
uint32_t led_layer_state = 0;

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |{3}  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|{2}|  '|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |{1}|
     * |-----------------------------------------------------------'
     * |{1}  |Gui|Alt  |         Space         |Alt  |Gui|{4}|{3}  |
     * `-----------------------------------------------------------'
     */
    [_BASE] = LAYOUT_60_ansi_split_bs_rshift(
      KC_ESC ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,KC_EQL ,KC_BSLS, KC_GRV,\
      UD_TAB     ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_LBRC,KC_RBRC,    KC_BSPC,\
      KC_LCTL      ,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_H   ,KC_J   ,KC_K   ,KC_L   ,UD_SEMI,KC_QUOT,           KC_ENT,\
      KC_LSFT          ,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,      KC_RSFT,MO(_FN),\
      MO(_FN)  ,KC_LGUI  ,KC_LALT  ,                      KC_SPC,                     KC_RALT  ,KC_RGUI  , MO(_LED),  MO(_NAV)),

    /* Layer 1: HHKB mode (HHKB Fn)
     * ,-----------------------------------------------------------.
     * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
     * |-----------------------------------------------------------|
     * |      |VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |        |NXT|PVT|PLY|STP|   |  +|  -|End|PgD|Dow|      |   |
     * `-----------------------------------------------------------'
     * |     |Gui|Alt  |         Space         |Alt  |Gui|   |     |
     * `-----------------------------------------------------------'
     */
    [_FN] = LAYOUT_60_ansi_split_bs_rshift(
      KC_PWR ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8,  KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_INS , KC_DEL,\
      KC_CAPS    ,_______,_______,_______,_______,_______,_______,_______,KC_PSCR,KC_SLCK,KC_PAUS,KC_UP  ,_______,    KC_BSPC,\
      _____________,KC_VOLD,KC_VOLU,KC_MUTE,_______,_______,KC_PAST,KC_PSLS,KC_HOME,KC_PGUP,KC_LEFT,KC_RGHT,           KC_ENT,\
      _________________,KC_MPRV,KC_MNXT,KC_MPLY,KC_MSTP,_______,KC_PPLS,KC_PMNS,KC_END ,KC_PGDN,KC_DOWN,_____________,_______,\
      _________,_________,_________,_________________________________________________,_________,_________,_________,_________),

    /* Layer 2: Semi-VI
     * ,-----------------------------------------------------------.
     * | - |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * |-----------------------------------------------------------|
     * |     |   |   |End|   |   |Hom|PgU|PgD|End|   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |Hom|   |PgD|   |   |Lef|Dow| Up|Rig|   |   |Enter   |
     * |-----------------------------------------------------------|
     * |        |   |Del|   |   |   |App|End|Hom|   |   |      |   |
     * `-----------------------------------------------------------'
     * |     |   |     |                       |     |   |   |     |
     * `-----------------------------------------------------------'
     */
    [_VI] = LAYOUT_60_ansi_split_bs_rshift(
      _______,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8,  KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_INS , KC_DEL,\
     ___________,_______,_______,KC_END ,_______,_______,KC_HOME,KC_PGDN,KC_PGUP,KC_END ,_______,_______,_______,___________,\
      _____________,KC_HOME,_______,KC_PGDN,_______,_______,KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,_______,_______,_________________,\
      _________________,_______,KC_DEL ,_______,_______,_______,KC_APP ,KC_END ,KC_HOME,_______,_______,_____________,_______,\
      _________,_________,_________,_________________________________________________,_________,_________,_________,_________),

    /* Layer 3: Window Nav
     * ,-----------------------------------------------------------.
     * | - | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |     |<--|-->|End|   |   |   |PgU|   |   |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |Hom|   |PgD|   |   |   |   |   |   |WnL|WnR|        |
     * |-----------------------------------------------------------|
     * |        |   |Del|   |   |   |   |   |   |   |   |      |   |
     * `-----------------------------------------------------------'
     * |     |   |     |                       |     |   |   |     |
     * `-----------------------------------------------------------'
     */
    [_NAV] = LAYOUT_60_ansi_split_bs_rshift(
      _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, KC_DEL,\
      ___________,UD_PREV,UD_NEXT,KC_END ,_______,_______,_______,KC_PGUP,_______,_______,_______,_______,_______,___________,\
      _____________,KC_HOME,_______,KC_PGDN,_______,_______,_______,_______,_______,_______,UD_PSCN,UD_NSCN,_________________,\
      _________________,_______,KC_DEL ,_______,_______,_______,_______,_______,_______,_______,_______,_____________,_______,\
      _________,_________,_________,_________________________________________________,_________,_________,_________,_________),

    [_LED] = LAYOUT_60_ansi_split_bs_rshift(
      _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,\
      ___________,F_SOLO ,F_PAGE ,F_FLASH,_______,_______,_______,_______,_______,_______,_______,_______,_______,___________,\
      _____________,F_BRITE,F_DIM  ,F_ALL  ,_______,_______,_______,_______,_______,_______,_______,_______,_________________,\
      _________________,F_LED  ,_______,_______,_______,_______,_______,_______,_______,_______,_______,_____________,_______,\
      _________,_________,_________,_________________________________________________,_________,_________,_________,_________)
};

//id for user defined functions and macros
enum function_id {
    NONE
};

enum macro_id {
    ACTION_LEDS_ALL,
    ACTION_LEDS_BACKLIGHT,
    ACTION_LEDS_BRIGHT,
    ACTION_LEDS_DIM,
    ACTION_LEDS_SINGLE,
    ACTION_LEDS_PAGE,
    ACTION_LEDS_FLASH
};

uint8_t led_nav[9] = {
  31,32,33,         37,
  47,   51,                  58,61,
      65
};
uint8_t led_vi[15] = {
        33,      36,37,38,41,
  47,   51,      54,55,56,57,
      65,         71,72,73
};
uint8_t led_fn[22] = {
  11,
  28,                     38,41,42,43,   45,
     47,48,51,      54,55,56,57,58,61,   62,
                     71,72,73,74,75
};

uint8_t led_led[7] = {
  31,32,33,
  47,48,51,
   64
};

const uint16_t PROGMEM fn_actions[] = {
  [ALL]         = ACTION_FUNCTION(ACTION_LEDS_ALL),
  [BACKLIGHT]   = ACTION_FUNCTION(ACTION_LEDS_BACKLIGHT),
  [BRIGHT]      = ACTION_FUNCTION(ACTION_LEDS_BRIGHT),
  [DIM]         = ACTION_FUNCTION(ACTION_LEDS_DIM),
  [MODE_SINGLE] = ACTION_FUNCTION(ACTION_LEDS_SINGLE),
  [MODE_PAGE]   = ACTION_FUNCTION(ACTION_LEDS_PAGE),
  [MODE_FLASH]  = ACTION_FUNCTION(ACTION_LEDS_FLASH)
};

/* custom action function */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  msg_t msg;

  switch(id) {
    case ACTION_LEDS_ALL:
      if(record->event.pressed) {
        led_mode_global = led_mode_global == ALL ? MODE_SINGLE : ALL;
        msg=TOGGLE_ALL;
        chMBPostI(&led_mailbox, msg);
      }
      break;

    case ACTION_LEDS_BACKLIGHT:
      if(record->event.pressed) {
        backlight_status_global ^= 1;
        msg=(backlight_status_global << 8) | TOGGLE_BACKLIGHT;
        chMBPostI(&led_mailbox, msg);
      }
      break;

    case ACTION_LEDS_BRIGHT:
      if(record->event.pressed) {
        msg=(1 << 8) | STEP_BRIGHTNESS;
        chMBPostI(&led_mailbox, msg);
      }
      break;

    case ACTION_LEDS_DIM:
      if(record->event.pressed) {
        msg=(0 << 8) | STEP_BRIGHTNESS;
        chMBPostI(&led_mailbox, msg);
      }
      break;

    //set led_mode for matrix_scan to toggle leds
    case ACTION_LEDS_SINGLE:
      led_mode_global = MODE_SINGLE;
      break;
    case ACTION_LEDS_PAGE:
      led_mode_global = MODE_PAGE;
      break;
    case ACTION_LEDS_FLASH:
      led_mode_global = MODE_FLASH;
      break;

  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  return MACRO_NONE;
};


bool process_record_user (uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {
    led_controller_init();

    write_led_page(_NAV, led_nav, 9);
    chThdSleepMilliseconds(10);

    write_led_page(_VI, led_vi, 15);
    chThdSleepMilliseconds(10);

    write_led_page(_FN, led_fn, 22);
    chThdSleepMilliseconds(10);

    write_led_page(_LED, led_led, 7);
    chThdSleepMilliseconds(10);
};

void matrix_scan_user(void) {
  uint8_t page;
  uint8_t led_pin_byte;
  msg_t msg;

  if (backlight_status_global == 0) {//backlight is off, skip the rest
    return;
  }

  if (led_layer_state != layer_state && led_mode_global != ALL) {
    //check mode
    //Turn on layer indicator or page depending on mode
    switch(led_mode_global) {
      case MODE_FLASH: //flash preset page leds then single indicator
        page = biton32(layer_state) > max_pages ? 7 : biton32(layer_state);
        msg=(page << 8) | DISPLAY_PAGE;
        chMBPostI(&led_mailbox, msg);
        chThdSleepMilliseconds(500);
        //flow to display single layer leds

      case MODE_SINGLE: //light layer indicators for all active layers
        led_pin_byte = layer_state & 0xFF;
        msg=(7 << 8) | DISPLAY_PAGE;
        chMBPostI(&led_mailbox, msg);
        msg=(1 << 16) | (led_pin_byte << 8) | SET_FULL_ROW;
        chMBPostI(&led_mailbox, msg);
        break;

      case MODE_PAGE: //display pre-defined led page
        page = biton32(layer_state) > max_pages ? 7 : biton32(layer_state);
        msg=(page << 8) | DISPLAY_PAGE;
        chMBPostI(&led_mailbox, msg);
        break;
    }
    led_layer_state = layer_state;
  }
};
