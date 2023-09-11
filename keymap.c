#include QMK_KEYBOARD_H

enum sofle_layers {
    _WORKMAN,
    _QWERTY,
    _NUMBR,
    _SYMBL,
    _NAV,
    _FUNC
};

enum custom_keycodes {
    KC_WORKMAN = SAFE_RANGE,
    KC_QWERTY,
    KC_NUMBR, /* Number layer */ 
    KC_SYMBL, /* Symbol layer */ 
    KC_ENTSYM, /* Enter when click, SYMBL layer when hold */
    KC_BSNM,  /* Backspace when click, NUMBR layer when hold */ 
    KC_ESCNAV, /* Esc when click, Nav layer when hold */   
    KC_DELFUN /* Del when click, Func layer when hold */  
};

//Tap Dance Declarations
enum {
  TD_Q = 0,
  TD_CUT,
  TD_SAVE,
  TD_PASTE
};

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  [TD_Q]  = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_DEL),
  [TD_CUT]  = ACTION_TAP_DANCE_DOUBLE(C(KC_C), C(KC_X)),
  [TD_SAVE]  = ACTION_TAP_DANCE_DOUBLE(C(KC_S), RCS(KC_S)),
  [TD_PASTE]  = ACTION_TAP_DANCE_DOUBLE(C(KC_V), KC_CAPS)
};

uint16_t td_hold_timer;  //tap dance timer variable
#define TD_HOLD_LIMIT 200

//hotkeys
#define FIND LCTL(KC_F)
#define REDO C(KC_Y)
#define UNDO LCTL(KC_Z)  
#define COPY TD(TD_CUT)         // Cut and Copy
#define SAVE TD(TD_SAVE)        // Save and Save as
#define PASTE TD(TD_PASTE)      // Paste and Capslock
#define HOME LT(3,KC_NO)        // Home and Numlock
#define MUTESLEEP LT(5,KC_NO)   // Mute and Sleep

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Workman
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  INS |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | Print|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | PASTE|   Q  |   D  |   R  |   W  |   B  |                    |   J  |   F  |   U  |   P  |   '  | SAVE |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | COPY |   A  |   S  |   H  |   T  |   G  |-------.    ,-------|   Y  |   N  |   E  |   O  |   I  | FIND |
 * |------+------+------+------+------+------| MODE  |    | MUTE  |------+------+------+------+------+------|
 * | UNDO |   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   L  |   ,  |   .  |   /  | REDO |
 * `-----------------------------------------/       /     \       \----------------------------------------'
 *          | Home | End  |  ESC  |Space | / Tab    /       \ Enter \ | Bspc  | DEL  |      |      |
 *          | Numbr|      | 'NAV' |      |/ 'CTRL' /         \'SYMBL'\|'NUM'  |'FUN' |      |      |
 *           `------------------------------------'           '-------'----------------------------'
 */
[_WORKMAN] = LAYOUT(
  C_S_T(KC_INS), LSA_T(KC_F1), LCA_T(KC_F2), KC_F3,        KC_F4,        KC_F5,                                     KC_F6,   KC_F7,        KC_F8,        KC_F9,        KC_F10,        KC_PSCR,
  PASTE,         TD(TD_Q),     KC_D,         KC_R,         KC_W,         KC_B,                                      KC_J,    KC_F,         KC_U,         KC_P,         KC_QUOT,       SAVE,
  COPY,          ALGR_T(KC_A), LALT_T(KC_S), LCTL_T(KC_H), LSFT_T(KC_T), KC_G,                                      KC_Y,    RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_O), ALGR_T(KC_I),  FIND,
  UNDO,          KC_Z,         KC_X,         KC_M,         KC_C,         KC_V,   KC_QWERTY,              MUTESLEEP, KC_K,    KC_L,         KC_COMM,      KC_DOT,       KC_SLSH,       REDO,
                               HOME,      KC_END,       KC_ESCNAV,    KC_SPC, LCTL_T(KC_TAB),            KC_ENTSYM,  KC_BSNM, KC_DELFUN,    KC_PGUP,     LGUI_T(KC_PGDN)
),

/*
 * Qwerty
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | PSCR |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Vol+ |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LAlt  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  | Vol- |
 * |------+------+------+------+------+------| MODE  |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | Mute |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Home | End  | Esc  | Spc  | / CTRL  /       \ Enter\  | Bspc | DEL  |      | GUI  |
 *            |      |      |      |      |/       /         \      \ | 'NUM'|      |      |      |
 *             `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
  KC_GRV,    KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_PSCR,
  KC_TAB,    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      XXXXXXX,
  KC_LALT,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   XXXXXXX,
  KC_LSFT,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   KC_WORKMAN,         XXXXXXX,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_RGUI,
           KC_HOME, KC_END, KC_ESC,  KC_SPC,  KC_LCTL,                     KC_ENT,   KC_BSPC, KC_DEL,  KC_PGUP, KC_PGDN
),

/* Number
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  [   |   7  |   8  |   9  |  ]   |                    |      |      |      |      |      | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  ;   |   4  |   5  |   6  |  =   |-------.    ,-------|      |      |      | RAlt | AltGr|      |
 * |------+------+------+------+------+------| MODE  |    |       |------+------+------+------+------+------|
 * |      |  `   |   1  |   2  |   3  |  \   |-------|    |-------|      |      |   ,  |   .  |   /  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |   .  |  0   | /  -    /       \ Ent  \    | Bspc |  Del  |      |      |
 *            |      |      |      |      |/       /         \      \   |      |       |      |      |
 *             `----------------------------------'           '------'  '----------------------------'
 */
[_NUMBR] = LAYOUT(
  XXXXXXX,  KC_F1,   KC_F2, KC_F3, KC_F4, KC_F5,                         KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,KC_F11,
  XXXXXXX,  KC_LBRC, KC_7,  KC_8,  KC_9,  KC_RBRC,                       XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,XXXXXXX,KC_F12,
  XXXXXXX,  KC_SCLN, KC_4,  KC_5,  KC_6,  KC_EQL,                        XXXXXXX, XXXXXXX, XXXXXXX,KC_RALT,KC_ALGR,XXXXXXX,
  XXXXXXX,  KC_GRV,  KC_1,  KC_2,  KC_3,  KC_BSLS, XXXXXXX,   XXXXXXX, XXXXXXX,XXXXXXX, KC_COMM,KC_DOT, KC_SLSH,XXXXXXX,
           TG(_NUMBR), XXXXXXX, KC_DOT, KC_0, KC_MINS,           KC_ENT, KC_BSPC, KC_DEL, XXXXXXX, XXXXXXX
),
/* Symbol
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  ¥  |  ²   |  ³   |  £   |  €    |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  {   |  &   |  *   |  (   |  }   |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  :   |  $   |  %   |  ^   |  +   |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |  ~   |  !   |  @   |  #   |  |   |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            |      |      |   (  |   )  | /  _   /        \      \  |      |      |      |      |
 *            |      |      |      |      |/      /          \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_SYMBL] = LAYOUT(
  XXXXXXX, ALGR(KC_MINS), ALGR(KC_2), ALGR(KC_3), SAGR(KC_4), ALGR(KC_5),                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  ALGR(KC_LBRC), KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  ALGR(KC_RBRC), KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,                                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE, XXXXXXX,                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                    KC_PGUP, KC_PGDN, KC_LPRN, KC_RPRN, KC_UNDS,                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),
/* Navigation
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            |      |      |      |   )  | /      /        \      \  |      |      |      |      |
 *            |      |      |      |      |/      /          \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_NAV] = LAYOUT(
  MEH(KC_9), MEH(KC_1), MEH(KC_2), MEH(KC_3), MEH(KC_4), MEH(KC_5),                            ALGR(KC_6), ALGR(KC_7), ALGR(KC_8), XXXXXXX, XXXXXXX,  XXXXXXX,
  MEH(KC_8), MEH(KC_Q), MEH(KC_D), MEH(KC_R), MEH(KC_W), MEH(KC_B),                                 XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX,
  MEH(KC_7), MEH(KC_A), MEH(KC_S), MEH(KC_H), MEH(KC_T), MEH(KC_G),                                 XXXXXXX,    KC_MS_L,    KC_MS_D,    KC_MS_U,    KC_MS_R,     XXXXXXX,
  MEH(KC_6),  MEH(KC_Z), MEH(KC_X), MEH(KC_M), MEH(KC_C), MEH(KC_V), XXXXXXX,               XXXXXXX, XXXXXXX,    KC_WH_L,    KC_WH_D,    KC_WH_U,    KC_WH_R,     XXXXXXX,
                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_BTN1, KC_BTN2,    KC_BTN3,    XXXXXXX,    XXXXXXX
),
/* Function
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F12 |  F7  |  F8  |  F9  |  ÷   |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F11 |  F4  |  F5  |  F6  |  ×   |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |  F10 |  F1  |  F2  |  F3  |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            |      |      |      |      | /      /        \      \  |      |      |      |      |
 *            |      |      |      |      |/      /          \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_FUNC] = LAYOUT(
 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
 KC_VOLU,  KC_F12, KC_F7,  KC_F8,  KC_F9,  SAGR(KC_EQL),                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
 KC_VOLD,  KC_F11, KC_F4,  KC_F5,  KC_F6,  ALGR(KC_EQL),                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
 KC_MUTE,  KC_F10, KC_F1,  KC_F2,  KC_F3,  XXXXXXX, XXXXXXX,               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),
};

#ifdef OLED_ENABLE


static void render_logo(void) {
    static const char PROGMEM my_logo[] = {
        // 'logo', 128x32px
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x30, 0x30, 0xf0, 0xfc, 0xff, 
        0xfc, 0xf0, 0x30, 0x30, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 
        0x00, 0x98, 0xcc, 0x4c, 0xce, 0xcc, 0x38, 0x00, 0x00, 0x00, 0x60, 0xe0, 0xf0, 0x60, 0x00, 0x00, 
        0x00, 0x00, 0x80, 0x00, 0x80, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 
        0x80, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x07, 0x03, 0x01, 0x01, 
        0x01, 0x03, 0x07, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x98, 0xcc, 0x66, 0x66, 0xcc, 0x08, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 
        0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x01, 0x07, 0x7c, 0xe0, 0xe0, 0x38, 0x0f, 0x03, 0x00, 0x00, 0x7f, 0x00, 0x70, 0xfe, 
        0x0f, 0x0d, 0x0c, 0x07, 0x03, 0x01, 0x80, 0x00, 0x00, 0x00, 0xf8, 0x07, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0xf0, 0xff, 0x1f, 0x03, 0x00, 0x60, 0x1f, 0xe0, 0xfc, 0x86, 0xc3, 0x61, 0x31, 0xfc, 0xff, 
        0x03, 0x00, 0xc0, 0xff, 0x0f, 0x01, 0xc0, 0x7f, 0x0f, 0x01, 0x01, 0xff, 0xcf, 0xc0, 0xe0, 0x60, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0e, 0x38, 0xe0, 0x80, 0x80, 0xe0, 0x30, 0x1c, 0x06, 0x03, 
        0x00, 0x18, 0xff, 0x81, 0x00, 0x00, 0x00, 0xe3, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x3b, 
        0xff, 0x19, 0x01, 0x83, 0xc7, 0x7c, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x70, 0xce, 0x03, 0x01, 0x01, 
        0x00, 0x00, 0x00, 0x10, 0xf8, 0xff, 0x18, 0x18, 0x18, 0x0c, 0xfc, 0x3f, 0x0f, 0x0c, 0x0c, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
        0x03, 0x03, 0x1f, 0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 
        0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 
        0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x0c, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 
        0x03, 0x00, 0x00, 0x00, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(my_logo, sizeof(my_logo));
}


static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("MODE\n"), false); 
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwert"), false);
            break;
        case _WORKMAN:
            oled_write_ln_P(PSTR("Wrkmn"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);

    // Print current layer
    oled_write_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _WORKMAN:
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _SYMBL:
            oled_write_P(PSTR("Symbl\n"), false);
            break;
        case _NUMBR:
            oled_write_P(PSTR("Numbr\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Nav\n"), false);
            break;
        case _FUNC:
            oled_write_P(PSTR("Func\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef\n"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master() == 1) {
        print_status_narrow();
    } else {
        render_logo();
        oled_scroll_left();  // Turns on scrolling
    }
    return false;
}

#endif



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case KC_WORKMAN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WORKMAN);
            }
            return false;
            break;
        case KC_NUMBR:
            if (record->event.pressed) {
                layer_on(_NUMBR);
                update_tri_layer(_NUMBR, _SYMBL, _NAV);
            } else {
                layer_off(_NUMBR);
                update_tri_layer(_NUMBR, _SYMBL, _NAV);
            }
            return false;
            break;
        case KC_SYMBL:
            if (record->event.pressed) {
                layer_on(_SYMBL);
                update_tri_layer(_NUMBR, _SYMBL, _NAV);
            } else {
                layer_off(_SYMBL);
                update_tri_layer(_NUMBR, _SYMBL, _NAV);
            }
            return false;
            break;
        case KC_ENTSYM:
            if (record->event.pressed) {        //when button is pressed
                td_hold_timer = timer_read();  //  mark the time button was pressed
                layer_on(_SYMBL);                //  go to (layer)
            } else {                            //when button is released
                layer_off(_SYMBL);               //  leave (layer)
                if (timer_elapsed(td_hold_timer) < TD_HOLD_LIMIT)
                    tap_code16(KC_ENT);        //  toggle key if held less than TD_HOLD_LIMIT ms
            }
            return false;
            break;
        case KC_BSNM:
            if (record->event.pressed) {        //when button is pressed
                td_hold_timer = timer_read();  //  mark the time button was pressed
                layer_on(_NUMBR);                //  go to (layer)
            } else {                            //when button is released
                layer_off(_NUMBR);               //  leave (layer)
                if (timer_elapsed(td_hold_timer) < TD_HOLD_LIMIT)
                    tap_code16(KC_BSPC);        //  toggle key if held less than TD_HOLD_LIMIT ms
            }
            return false;
            break;
        case KC_ESCNAV:
            if (record->event.pressed) {        //when button is pressed
                td_hold_timer = timer_read();  //  mark the time button was pressed
                layer_on(_NAV);                //  go to (layer)
            } else {                            //when button is released
                layer_off(_NAV);               //  leave (layer)
                if (timer_elapsed(td_hold_timer) < TD_HOLD_LIMIT)
                    tap_code16(KC_ESC);        //  toggle key if held less than TD_HOLD_LIMIT ms
            }
            return false;
            break;
        case KC_DELFUN:
            if (record->event.pressed) {        //when button is pressed
                td_hold_timer = timer_read();  //  mark the time button was pressed
                layer_on(_FUNC);                //  go to (layer)
            } else {                            //when button is released
                layer_off(_FUNC);               //  leave (layer)
                if (timer_elapsed(td_hold_timer) < TD_HOLD_LIMIT)
                    tap_code16(KC_DEL);        //  toggle key if held less than TD_HOLD_LIMIT ms
            }
            return false;
            break;
        case LT(5,KC_NO):      // Mute and Sleep
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_MUTE); // tap Mute
            } else if (record->event.pressed) {
                tap_code16(KC_SLEP); // hold Sleep
            }
            return false;
            break;
        case LT(3,KC_NO):      // Home and Numlock
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_HOME); // tap Home
            } else if (record->event.pressed) {
                layer_on(_NUMBR); // hold Numlock
            }
            return false;
            break;
    }
    return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_WORKMAN] =   { ENCODER_CCW_CW(KC_RIGHT, KC_LEFT),          ENCODER_CCW_CW(KC_DOWN, KC_UP)  },
    [_QWERTY] = {    ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [_NUMBR] =  {    ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(XXXXXXX, XXXXXXX)  },
    [_SYMBL] =  {    ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(XXXXXXX, XXXXXXX)  },
    [_NAV] =  {      ENCODER_CCW_CW(KC_CALC, XXXXXXX),           ENCODER_CCW_CW(KC_MYCM, KC_MAIL)  },
    [_FUNC] =  {     ENCODER_CCW_CW(KC_MPLY, KC_MSTP),           ENCODER_CCW_CW(KC_MFFD, KC_MRWD)  }, 
};
#endif


