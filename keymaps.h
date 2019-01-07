/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The PROG key is special, since it is how you indicate to the board that you
  * want to flash the firmware. However, it can be remapped to a regular key.
  * When the keyboard boots, it first looks to see whether the PROG key is held
  * down; if it is, it simply awaits further flashing instructions. If it is
  * not, it continues loading the rest of the firmware and the keyboard
  * functions normally, with whatever binding you have set to PROG. More detail
  * here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum { BL13, SFT_BL13, NUMPAD, FUNCTION }; // layers

// include my custom key definitions
#include "keydefs.h"

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

KEYMAPS(

  [BL13] = KEYMAP_STACKED
  (Key_CARET,     Key_AND, Key_Equals, Key_LPAREN, Key_PLUS, Key_TILDE, Key_LEDEffectNext,
   Key_Q,         Key_W,   Key_L,      Key_D,      Key_C,    Key_V,     ___,
   Key_Escape,    Key_N,   Key_R,      Key_T,      Key_S,    Key_F,
   Key_LeftShift, Key_Z,   Key_M,      Key_P,      Key_G,    Key_J,     LockLayer(SFT_BL13),
   Key_LeftControl, LT(SFT_BL13,Tab), Key_Backspace, Key_LeftGui,
   ShiftToLayer(NUMPAD),

   ___,               Key_BSLASH, Key_STAR,   Key_RPAREN,    Key_DOLLAR,   Key_PRCNT, Key_Backtick,
   ___,               Key_K,      Key_U,      Key_O,         Key_Y,        Key_B,     Key_Slash,
                      Key_Comma,  Key_A,      Key_E,         Key_I,        Key_H,     Key_Quote,
   LockLayer(NUMPAD), Key_Minus,  Key_Period, Key_Semicolon, Key_DBLQUOTE, Key_X,     LT(SFT_BL13,Tab),
   Key_RightGui, LT(FUNCTION,Enter), LT(NUMPAD,Spacebar), Key_LeftAlt,
   Key_LeftControl),

  [SFT_BL13] = KEYMAP_STACKED
  (___,                ___,           ___,           ___,           ___,           ___,           ___,
   LSHIFT(Key_Q),      LSHIFT(Key_W), LSHIFT(Key_L), LSHIFT(Key_D), LSHIFT(Key_C), LSHIFT(Key_V), ___,
   LSHIFT(Key_Escape), LSHIFT(Key_N), LSHIFT(Key_R), LSHIFT(Key_T), LSHIFT(Key_S), LSHIFT(Key_F),
   ___,                LSHIFT(Key_Z), LSHIFT(Key_M), LSHIFT(Key_P), LSHIFT(Key_G), LSHIFT(Key_J), ___,
   LSHIFT(Key_LeftControl), LSHIFT(Key_Tab), LSHIFT(Key_Backspace), LSHIFT(Key_LeftGui),
   ShiftToLayer(NUMPAD),

   ___, ___,           ___,           ___,           ___,           ___,           ___,
   ___, LSHIFT(Key_K), LSHIFT(Key_U), LSHIFT(Key_O), LSHIFT(Key_Y), LSHIFT(Key_B), Key_POUND,
        Key_QUEST,     LSHIFT(Key_A), LSHIFT(Key_E), LSHIFT(Key_I), LSHIFT(Key_H), Key_AT,
   ___, Key_UNDERSCR,  Key_EXCLM,     Key_COLON,     Key_PIPE ,     LSHIFT(Key_X), ___,
   LSHIFT(Key_RightGui), ___, LSHIFT(Key_Spacebar), LSHIFT(Key_LeftAlt),
   LSHIFT(Key_LeftControl)),

  [NUMPAD] =  KEYMAP_STACKED
  (___, ___,             ___,      ___,           ___,          ___,              ___,
   ___, Key_LESS,        Key_LCB,  M(MACRO_TION), Key_RCB,      Key_GREATER,      ___,
   ___, Key_LeftBracket, Key_Home, Key_PageUp,    Key_PageDown, Key_End,
   ___, Key_8,           Key_6,    Key_2,         Key_4,        Key_RightBracket, ___,
   ___, Key_Spacebar, Key_Delete, ___,
   ___,

   M(MACRO_VERSION_INFO), ___,           ___,           ___,         ___,            ___,      ___,
   ___,                   Key_7,         Key_3,         Key_0,       Key_1,          Key_5,    ___,
                          Key_LeftArrow, Key_DownArrow, Key_UpArrow, Key_RightArrow, Key_9,    ___,
   ___,                   ___,           ___,           ___,         ___,            Key_HASH, ___,
   ___, ___, ___, ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, Key_F9, Key_F10, Key_F11, Key_F12, ___,
        ___, Key_F1, Key_F2,  Key_F3,  Key_F4, ___,
   ___, ___, Key_F5, Key_F6,  Key_F7,  Key_F8, ___,
   ___, ___, ___, ___,
   ___),

/*
  [TEMPLATE] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___),

*/) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*
