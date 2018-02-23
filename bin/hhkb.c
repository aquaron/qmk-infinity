/*
 * HHKB Layout + VI style SCLN + Tab nav
 */
#include "keymap_common.h"


#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Fn4  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn0|
     * `-----------------------------------------------------------'
     *       |Gui|Alt  |         Space         |Alt  |Gui|
     *       `-------------------------------------------'
     */
    [0] = \
    KEYMAP(ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV,   \
           FN4, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC,       \
           LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN3 ,QUOT,ENT,             \
           LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,FN0,             \
                LGUI,LALT,          SPC,                RALT,RGUI),

    /* Layer 1: HHKB mode (HHKB Fn)
     * ,-----------------------------------------------------------.
     * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
     * |-----------------------------------------------------------|
     * |      |VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |  +|  -|End|PgD|Dow|      |   |
     * `-----------------------------------------------------------'
     *       |   |     |                       |     |   |
     *       `-------------------------------------------'
     */
    [1] = \
    KEYMAP(PWR, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL,   \
           CAPS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS, UP, TRNS, BSPC,      \
           TRNS,VOLD,VOLU,MUTE,TRNS,TRNS,PAST,PSLS,HOME,PGUP,LEFT,RGHT,PENT,            \
           TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PPLS,PMNS,END, PGDN,DOWN,TRNS,TRNS,            \
                TRNS,TRNS,          TRNS,               TRNS,TRNS),

    /* Layer 2: Semi-VI
     * ,-----------------------------------------------------------.
     * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |     |Fn5|Fn6|End|   |   |Hom|PgU|PgD|End|   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |Hom|   |PgD|   |   |Lef|Dow| Up|Rig|   |   |Enter   |
     * |-----------------------------------------------------------|
     * |        |   |Del|   |   |   |App|End|Hom|   |   |      |   |
     * `-----------------------------------------------------------'
     *       |   |     |                       |     |   |
     *       `-------------------------------------------'
     */
    [2] = \
    KEYMAP(TRNS,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL,   \
           TRNS,FN5 ,FN6 ,END ,TRNS,TRNS,HOME,PGDN,PGUP,END ,TRNS,TRNS,TRNS, TRNS,      \
           TRNS,HOME,TRNS,PGDN,TRNS,TRNS,LEFT,DOWN,  UP,RGHT,TRNS,TRNS,TRNS,            \
           TRNS,TRNS,DEL ,TRNS,TRNS,TRNS,APP ,END ,HOME,TRNS,TRNS,TRNS,TRNS,            \
                TRNS,TRNS,          TRNS,               TRNS,TRNS),

    /* Layer 3: Window Nav
     * ,-----------------------------------------------------------.
     * |   |   |   |   |End|   |   |   |   |Hom|   |   |   |   |Del|
     * |-----------------------------------------------------------|
     * |     |Fn5|Fn6|End|   |   |   |   |PgU|   |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |Hom|   |PgD|   |   |Lef|Dow| Up|Rig|Fn7|Fn8|        |
     * |-----------------------------------------------------------|
     * |        |   |Del|   |   |   |App|   |   |   |   |      |   |
     * `-----------------------------------------------------------'
     *       |   |     |                       |     |   |
     *       `-------------------------------------------'
     */
    [3] = \
    KEYMAP(TRNS,TRNS,TRNS,TRNS,END ,TRNS,TRNS,TRNS,TRNS,TRNS,HOME,TRNS,TRNS,TRNS,DEL,   \
           TRNS,FN5 ,FN6 ,END ,TRNS,TRNS,TRNS,PGUP,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS,      \
           TRNS,HOME,TRNS,PGDN,TRNS,TRNS,LEFT,DOWN,  UP,RGHT,FN7 ,FN8 ,TRNS,            \
           TRNS,TRNS,DEL ,TRNS,TRNS,TRNS,APP ,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,            \
                TRNS,TRNS,          TRNS,               TRNS,TRNS)
};



/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const action_t fn_actions[] __attribute__ ((section (".keymap.fn_actions"))) = {
    [0]  = ACTION_LAYER_MOMENTARY(1),
    [1]  = ACTION_LAYER_MOMENTARY(2),
    [2]  = ACTION_LAYER_MOMENTARY(3),
    [3]  = ACTION_LAYER_MOMENTARY(4),
    [4]  = ACTION_LAYER_MOMENTARY(5),
    [5]  = ACTION_LAYER_MOMENTARY(6),
    [6]  = ACTION_LAYER_MOMENTARY(7),
    [7]  = ACTION_LAYER_TOGGLE(1),
    [8]  = ACTION_LAYER_TOGGLE(2),
    [9]  = ACTION_LAYER_TOGGLE(3),
    [10] = ACTION_LAYER_TAP_TOGGLE(1),
    [11] = ACTION_LAYER_TAP_TOGGLE(2),
    [12] = ACTION_LAYER_TAP_TOGGLE(3),
    [13] = ACTION_LAYER_TAP_KEY(1, KC_BSLASH),
    [14] = ACTION_LAYER_TAP_KEY(2, KC_TAB),
    [15] = ACTION_LAYER_TAP_KEY(3, KC_ENTER),
    [16] = ACTION_LAYER_TAP_KEY(4, KC_SPACE),
    [17] = ACTION_LAYER_TAP_KEY(5, KC_SCOLON),
    [18] = ACTION_LAYER_TAP_KEY(6, KC_QUOTE),
    [19] = ACTION_LAYER_TAP_KEY(7, KC_SLASH),
    [20] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_SPACE),
    [21] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_SPACE),
    [22] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_QUOTE),
    [23] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ENTER),
    [24] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),
    [25] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_BSPACE),
    [26] = ACTION_MODS_ONESHOT(MOD_LCTL),
    [27] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_ESC),
    [28] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_BSPACE),
    [29] = ACTION_MODS_ONESHOT(MOD_LSFT),
    [30] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_GRAVE),
    [31] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_BSLASH),
};
#else
const action_t fn_actions[] PROGMEM = {
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_LAYER_MOMENTARY(2),
    [2] = ACTION_LAYER_MOMENTARY(3),
    [3] = ACTION_LAYER_TAP_KEY(2, KC_SCLN),
    [4] = ACTION_LAYER_TAP_KEY(3, KC_TAB),
    [5] = ACTION_MODS_KEY(MOD_LALT, KC_LEFT),
    [6] = ACTION_MODS_KEY(MOD_LALT, KC_RGHT),
    [7] = ACTION_MODS_KEY(MOD_LGUI | MOD_LCTL, KC_LEFT),
    [8] = ACTION_MODS_KEY(MOD_LGUI | MOD_LCTL, KC_RGHT)
};
#endif
