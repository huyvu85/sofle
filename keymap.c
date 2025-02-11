/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum sofle_layers {
    _WORKMAN,
    _QWERTY,
    _NUMBR,
    _SYMBL,
    _MAUS,
    _FUNC,
    _NAV
};

enum custom_keycodes {
    KC_WORKMAN = SAFE_RANGE,
    KC_QWERTY,
    KC_NUMBR, /* Number layer */
    KC_SYMBL, /* Symbol layer */
    KC_ENTSYM, /* Enter when click, SYMBL layer when hold */
    KC_BSNM,  /* Backspace when click, NUMBR layer when hold */
    KC_ESC_MS, /* Esc when click, MAUS layer when hold */
    KC_DELFUN, /* Del when click, Func layer when hold */
    KC_SPC_NAV
};

//Tap Dance Declarations
enum {
  TD_CUT,
  TD_SAVE,
  TD_PASTE,
  TD_ESC_PR,
  TD_DELBS
};

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC_PR]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_PSCR),
  [TD_CUT]  = ACTION_TAP_DANCE_DOUBLE(C(KC_C), C(KC_X)),
  [TD_SAVE]  = ACTION_TAP_DANCE_DOUBLE(C(KC_S), RCS(KC_S)),
  [TD_PASTE]  = ACTION_TAP_DANCE_DOUBLE(C(KC_V), KC_INS),
  [TD_DELBS]  = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_BSPC),
};

uint16_t td_hold_timer;  //tap dance timer variable
#define TD_HOLD_LIMIT 195

//hotkeys
#define REDO C(KC_Y)
#define UNDO C(KC_Z)
#define ESC_PR TD(TD_ESC_PR)    // Esc and Print
#define DEL_BS TD(TD_DELBS)     // Del and Backspace
#define COPY TD(TD_CUT)         // Cut and Copy
#define SAVE TD(TD_SAVE)        // Save and Save as
#define PASTE TD(TD_PASTE)      // Paste and Ins
#define HOME LT(1,KC_NO)        // Home and Numbr
#define END LCA_T(KC_END)       // End and Ctrl-Alt
#define PGDN LCA_T(KC_PGDN)     // PgDn and Ctrl-Alt

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Workman
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  DEL |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | Print|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | PASTE|   Q  |   D  |   R  |   W  |   B  |                    |   J  |   F  |   U  |   P  |   '  | PASTE|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | COPY |   A  |   S  |   H  |   T  |   G  |-------.    ,-------|   Y  |   N  |   E  |   O  |   I  |  COPY|
 * |------+------+------+------+------+------| MODE  |    | MUTE  |------+------+------+------+------+------|
 * | UNDO |   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   L  |   ,  |   .  |   /  | REDO |
 * `-----------------------------------------/       /     \       \----------------------------------------'
 *          | Home | End  |  ESC  |Space | / Tab    /       \ Enter \ | Bspc  | DEL  | PgDn | PgUp |
 *          | 'NUM'|      | 'MAUS'| 'NAV'|/ 'CTRL' /         \'SYMBL'\|'NUM'  |'FUN' |      | GUI  |
 *           `------------------------------------'           '-------'----------------------------'
 */
[_WORKMAN] = LAYOUT(
  DEL_BS, KC_F1,        KC_F2, KC_F3, KC_F4,        KC_F5,                                              KC_F6,       KC_F7,        KC_F8,        KC_F9,        KC_F10,        ESC_PR,
  PASTE,  KC_Q,         KC_D,  KC_R,  KC_W,         KC_B,                                               KC_J,        KC_F,         KC_U,         KC_P,         KC_QUOT,       PASTE,
  COPY,   ALGR_T(KC_A), LALT_T(KC_S), LCTL_T(KC_H), LSFT_T(KC_T), C_S_T(KC_G),                          RCS_T(KC_Y), RSFT_T(KC_N), RCTL_T(KC_E), LALT_T(KC_O), ALGR_T(KC_I),  COPY,
  UNDO,   KC_Z,         KC_X,         KC_M,         KC_C,         KC_V,   KC_QWERTY,           KC_MUTE, KC_K,        KC_L,         KC_COMM,      KC_DOT,       KC_SLSH,       REDO,
          HOME,         END,      KC_ESC_MS,  KC_SPC_NAV, LCTL_T(KC_TAB),                    KC_ENTSYM, KC_BSNM,     KC_DELFUN,    PGDN,         RGUI_T(KC_PGUP)
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
  KC_LALT,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_WORKMAN,
  KC_LSFT,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   KC_WORKMAN,         KC_MUTE,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_RSFT,
       HOME, KC_END, KC_ESC,  KC_SPC,  KC_LCTL,                             KC_ENT,   KC_BSPC, KC_DEL,  KC_PGDN, RGUI_T(KC_PGUP)
),

/* Number
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ×   |      |   7  |   8  |   9  |      |                    |      |      |      |      |      | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ÷   |  ;   |   4  |   5  |   6  |  =   |-------.    ,-------|      |      |      | RAlt | AltGr| LEFT |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |  °   |  `   |   1  |   2  |   3  |  \   |-------|    |-------|      |      |   ,  |   .  |   /  | RIGHT|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |   .  |  0   | /  -    /       \ Ent  \    | Bspc |  Del  |      |      |
 *            |      |      |      |      |/       /         \      \   |      |       |      |      |
 *             `----------------------------------'           '------'  '----------------------------'
 */
[_NUMBR] = LAYOUT(
  XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,KC_UP,
  ALGR(KC_EQL),  KC_LCBR, KC_7,  KC_8,  KC_9,  KC_RCBR,                           XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,XXXXXXX,KC_DOWN,
  SAGR(KC_EQL),  KC_SCLN, KC_4,  KC_5,  KC_6,  KC_EQL,                            RCS(KC_NO), KC_RSFT, KC_RCTL,KC_LALT,KC_ALGR,KC_LEFT,
  SAGR(KC_SCLN), KC_GRV,  KC_1,  KC_2,  KC_3,  KC_BSLS, XXXXXXX,                XXXXXXX, XXXXXXX,KC_SPC, KC_COMM,KC_DOT, KC_SLSH,KC_RIGHT,
           TG(_NUMBR), LCA(KC_NO), KC_DOT, KC_0, KC_MINS,              KC_ENT, KC_BSPC, KC_DEL, XXXXXXX, XXXXXXX
),
/* Symbol
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |  ¥   |  ³   |  €   |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  [   |  &   |  *   |  ²   |  ]   |                    |      |      |      |      |      |      |
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
  XXXXXXX, ALGR(KC_9), ALGR(KC_0), ALGR(KC_MINS), ALGR(KC_3), ALGR(KC_5),                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_LBRC,    KC_AMPR,    KC_ASTR,       ALGR(KC_2), KC_RBRC,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_COLN,    KC_DLR,     KC_PERC,       KC_CIRC,    KC_PLUS,                     XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_ALGR, XXXXXXX,
  XXXXXXX, KC_TILD,    KC_EXLM,    KC_AT,         KC_HASH,    KC_PIPE, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
               XXXXXXX, XXXXXXX,   KC_LPRN,   KC_RPRN, KC_UNDS,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),
/* Mouse
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
[_MAUS] = LAYOUT(
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                       KC_MYCM, KC_CALC, KC_MAIL, XXXXXXX,      XXXXXXX, KC_SLEP,
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                       XXXXXXX,   KC_MPRV,    KC_MPLY, KC_MSTP, KC_MNXT, KC_VOLU,
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                       XXXXXXX,   KC_MS_L,    KC_MS_D, KC_MS_U, KC_MS_R, KC_VOLD,
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       XXXXXXX, XXXXXXX,   KC_WH_L,    KC_WH_D, KC_WH_U, KC_WH_R, KC_MUTE,
         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,              KC_BTN1, KC_BTN2,   KC_BTN3,    XXXXXXX, XXXXXXX
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
  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                          XXXXXXX,XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                          UNDO,    C(KC_V), C(KC_C), C(KC_X), REDO,     XXXXXXX,
  KC_NO,  KC_ALGR, KC_LALT, KC_LCTL, KC_LSFT, C_S_T(KC_NO),                   KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_QWERTY,
  KC_NO,  KC_NO,   KC_LSFT, KC_TAB,  KC_SPC,  KC_NO,    KC_NO,       XXXXXXX, KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,   XXXXXXX,
                   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,       XXXXXXX, KC_BACKSPACE ,KC_DEL, XXXXXXX, XXXXXXX
),
/* Function
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F12 |  F7  |  F8  |  F9  | Print|                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F11 |  F4  |  F5  |  F6  | Scrlk|-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |  F10 |  F1  |  F2  |  F3  | Pause|-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            |      |      |      |      | /      /        \      \  |      |      |      |      |
 *            |      |      |      |      |/      /          \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_FUNC] = LAYOUT(
 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
 KC_VOLU,  KC_F12, KC_F7,  KC_F8,  KC_F9,  KC_PSCR,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
 KC_VOLD,  KC_F11, KC_F4,  KC_F5,  KC_F6,  KC_SCRL,                           XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_ALGR, XXXXXXX,
 KC_MUTE,  KC_F10, KC_F1,  KC_F2,  KC_F3,  KC_PAUS, XXXXXXX,               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, KC_APP, KC_SPC, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),
};

#ifdef OLED_ENABLE

/* 32 * 32 logo */
static void render_logo(void) {
    static const char PROGMEM communism_logo[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe2, 0xe2,
        0xe2, 0x42, 0x06, 0x06, 0x0e, 0x0c, 0x1c, 0x38, 0x78, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x18, 0x3c, 0x7c, 0xfe, 0xff, 0x7f, 0x3f, 0x1f, 0x3f, 0x7f, 0xfb, 0xf1,
        0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0xff, 0xff, 0xfe, 0xf8, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x40, 0xe0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x03, 0x0f, 0x1f, 0x3e, 0x7c, 0xf8, 0xf0, 0xe0, 0xc0, 0xc0, 0xf8, 0xff, 0xff, 0xff, 0x3f, 0x00,
        0x00, 0x38, 0x7c, 0x7e, 0x3f, 0x0f, 0x07, 0x03, 0x07, 0x0e, 0x1e, 0x1c, 0x3c, 0x3c, 0x3c, 0x3c,
        0x7c, 0x7c, 0x7c, 0x7c, 0x3c, 0x3e, 0x3f, 0x1f, 0x1f, 0x0f, 0x1f, 0x3f, 0x7d, 0x70, 0x20, 0x00
    };

    oled_write_raw_P(communism_logo, sizeof(communism_logo));
}

/* KEYBOARD PET START */

/* settings */
#    define MIN_WALK_SPEED      10
#    define MIN_RUN_SPEED       25

/* advanced settings */
#    define ANIM_FRAME_DURATION 200  // how long each frame lasts in ms
#    define ANIM_SIZE           96   // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

/* timers */
uint32_t anim_timer = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int   current_wpm = 0;
led_t led_usb_state;

bool isSneaking = false;
bool isJumping  = false;
bool showedJump = true;

/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
    /* Sit */
    static const char PROGMEM sit[2][ANIM_SIZE] = {/* 'sit1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'sit2', 32x22px */
                                                   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

    /* Walk */
    static const char PROGMEM walk[2][ANIM_SIZE] = {/* 'walk1', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'walk2', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Run */
    static const char PROGMEM run[2][ANIM_SIZE] = {/* 'run1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'run2', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   }};

    /* Bark */
    static const char PROGMEM bark[2][ANIM_SIZE] = {/* 'bark1', 32x22px */
                                                    {
                                                        0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'bark2', 32x22px */
                                                    {
                                                        0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Sneak */
    static const char PROGMEM sneak[2][ANIM_SIZE] = {/* 'sneak1', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
                                                     },

                                                     /* 'sneak2', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                     }};

    /* animation */
    void animate_luna(void) {
        /* jump */
        if (isJumping || !showedJump) {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y + 2);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y - 1);

            showedJump = true;
        } else {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y);
        }

        /* switch frame */
        current_frame = (current_frame + 1) % 2;

        /* current status */
        if (led_usb_state.caps_lock) {
            oled_write_raw_P(bark[current_frame], ANIM_SIZE);

        } else if (is_caps_word_on()) {
            oled_write_raw_P(bark[current_frame], ANIM_SIZE);

        } else if (isSneaking) {
            oled_write_raw_P(sneak[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[current_frame], ANIM_SIZE);

        } else {
            oled_write_raw_P(run[current_frame], ANIM_SIZE);
        }
    }

#    if OLED_TIMEOUT > 0
    /* the animation prevents the normal timeout from occuring */
    if (last_input_activity_elapsed() > OLED_TIMEOUT && last_led_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return;
    } else {
        oled_on();
    }
#    endif

    /* animation timer */
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_luna();
    }
}

/* KEYBOARD PET END */

static void print_logo_narrow(void) {
    render_logo();

    /* wpm counter */
    uint8_t n = get_current_wpm();
    char    wpm_str[4];
    oled_set_cursor(0, 14);
    wpm_str[3] = '\0';
    wpm_str[2] = '0' + n % 10;
    wpm_str[1] = '0' + (n /= 10) % 10;
    wpm_str[0] = '0' + n / 10;
    oled_write(wpm_str, false);

    oled_set_cursor(0, 15);
    oled_write("wpm", false);
}

static void print_status_narrow(void) {
    /* Print current mode */
    oled_set_cursor(0, 0);
    oled_write("key", false);
    oled_set_cursor(0, 2);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write("QWRTY", false);
            break;
        case _WORKMAN:
            oled_write("WRKMN", false);
            break;
        default:
            oled_write("_____", false);
    }
    /* Print current layer */
    oled_set_cursor(0, 5);
    oled_write("layer", false);
    oled_set_cursor(0, 7);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write("BASE ", false);
            break;
        case _WORKMAN:
            oled_write("BASE ", false);
            break;
        case _NUMBR:
            oled_write("NUM  ", false);
            break;
        case _SYMBL:
            oled_write("SYM  ", false);
            break;
        case _MAUS:
            oled_write("MAUS ", false);
            break;
        case _FUNC:
            oled_write("FUN  ", false);
            break;
        case _NAV:
            oled_write("NAV  ", false);
            break;
        default:
            oled_write("_____", false);
    }

    /* caps lock */
    oled_set_cursor(0, 10);
    oled_write("CPSLK", led_usb_state.caps_lock);

    /* KEYBOARD PET RENDER START */

    render_luna(0, 13);

    /* KEYBOARD PET RENDER END */
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

bool oled_task_user(void) {
    /* KEYBOARD PET VARIABLES START */

    current_wpm   = get_current_wpm();
    led_usb_state = host_keyboard_led_state();

    /* KEYBOARD PET VARIABLES END */

    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        print_logo_narrow();
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
                isSneaking = true;
                td_hold_timer = timer_read();  //  mark the time button was pressed
                layer_on(_NUMBR);                //  go to (layer)

            } else {                            //when button is released
                isSneaking = false;
                layer_off(_NUMBR);               //  leave (layer)
                if (timer_elapsed(td_hold_timer) < TD_HOLD_LIMIT)
                    tap_code16(KC_BSPC);        //  toggle key if held less than TD_HOLD_LIMIT ms

            }
            return false;
            break;
        case KC_ESC_MS:
            if (record->event.pressed) {        //when button is pressed
                td_hold_timer = timer_read();  //  mark the time button was pressed
                layer_on(_MAUS);                //  go to (layer)
            } else {                            //when button is released
                layer_off(_MAUS);               //  leave (layer)
                if (timer_elapsed(td_hold_timer) < TD_HOLD_LIMIT)
                    tap_code16(KC_ESC);        //  toggle key if held less than TD_HOLD_LIMIT ms
            }
            return false;
            break;
        case KC_SPC_NAV:
            if (record->event.pressed) {        //when button is pressed
                td_hold_timer = timer_read();  //  mark the time button was pressed
                layer_on(_NAV);                //  go to (layer)
            } else {                            //when button is released
                layer_off(_NAV);               //  leave (layer)
                if (timer_elapsed(td_hold_timer) < TD_HOLD_LIMIT)
                    tap_code16(KC_SPC);        //  toggle key if held less than TD_HOLD_LIMIT ms
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
        case LT(1,KC_NO):      //
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_HOME); // tap Home
            } else if (record->event.pressed) {
                layer_on(_NUMBR); // hold go to (layer)
            }
            return false;
            break;

        /* KEYBOARD PET STATUS START */
        case KC_LSFT:
        case KC_LCTL:
        case C_S_T(KC_INS):
        case LSA_T(KC_F1):
        case LCA_T(KC_F2):
        case LSFT_T(KC_T):
        case LCTL_T(KC_H):
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
            break;
        case KC_SPC:
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;

            /* KEYBOARD PET STATUS END */
    }
    return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_WORKMAN] = { ENCODER_CCW_CW(KC_RIGHT, KC_LEFT),          ENCODER_CCW_CW(KC_DOWN, KC_UP)  },
    [_QWERTY] =  { ENCODER_CCW_CW(KC_RIGHT, KC_LEFT),          ENCODER_CCW_CW(KC_DOWN, KC_UP) },
    [_NUMBR] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(XXXXXXX, XXXXXXX)  },
    [_SYMBL] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(XXXXXXX, XXXXXXX)  },
    [_MAUS] =    { ENCODER_CCW_CW(XXXXXXX, XXXXXXX),           ENCODER_CCW_CW(KC_WH_R, KC_WH_L)  },
    [_FUNC] =    { ENCODER_CCW_CW(KC_MPLY, KC_MSTP),           ENCODER_CCW_CW(XXXXXXX, XXXXXXX)  },
    [_NAV] =     { ENCODER_CCW_CW(XXXXXXX, XXXXXXX),           ENCODER_CCW_CW(LSG(KC_RIGHT), LSG(KC_LEFT)) },
};
#endif
