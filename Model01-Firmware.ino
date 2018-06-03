// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for an "LED off mode"
#include "LED-Off.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-Model01-TestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for one-shot keys
#include "Kaleidoscope-OneShot.h"

// Let escape cancel oneshot
#include "Kaleidoscope-Escape-OneShot.h"

// visualize modifiers
#include "Kaleidoscope-LED-ActiveModColor.h"

// multiple keys by tapping
#include "Kaleidoscope-TapDance.h"

/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_VERSION_INFO,
       MACRO_ANY
     };

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
  *   the special nature of the PROG key
  *   keeping NUM and FN consistent and accessible on all layers
  *
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

// make keys easier to read; based on UK keyboard
#define Key_AT       LSHIFT(Key_Quote)
#define Key_STAR     LSHIFT(Key_8)
#define Key_DOLLAR   LSHIFT(Key_4)
#define Key_CARET    LSHIFT(Key_6)
#define Key_PRCNT    LSHIFT(Key_5)
#define Key_EXCLM    LSHIFT(Key_1)
#define Key_QUEST    LSHIFT(Key_Slash)
#define Key_DBLQUOTE LSHIFT(Key_2)
#define Key_AND      LSHIFT(Key_7)
#define Key_LPAREN   LSHIFT(Key_9)
#define Key_RPAREN   LSHIFT(Key_0)
#define Key_UNDERSCR LSHIFT(Key_Minus)
#define Key_PLUS     LSHIFT(Key_Equals)
#define Key_LCB      LSHIFT(Key_LeftBracket)
#define Key_RCB      LSHIFT(Key_RightBracket)
#define Key_HASH     Key_NonUsPound
#define Key_TILDE    LSHIFT(Key_NonUsPound)
#define Key_BSLASH   Key_NonUsBackslashAndPipe
#define Key_PIPE     LSHIFT(Key_NonUsBackslashAndPipe)
#define Key_COLON    LSHIFT(Key_Semicolon)
#define Key_GREATER  LSHIFT(Key_Period)
#define Key_LESS     LSHIFT(Key_Comma)

// layers as defined; need to be in the same order as actual definition
enum { RSTHD, SHIFTED_RSTHD, FUNCTION }; // layers

enum { BRACKETS, PARENS, CBRACES }; // tapdance

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

KEYMAPS(
  // primary layer
  [RSTHD] = KEYMAP_STACKED
  (___,           Key_LCB,   Key_AT, Key_STAR, Key_DOLLAR, Key_CARET, Key_LEDEffectNext,
   Key_Backtick,  Key_J,     Key_C,  Key_Y,    Key_F,      Key_K,     Key_LESS,
   Key_Tab,       Key_R,     Key_S,  Key_T,    Key_H,      Key_D,
   Key_Escape,    Key_Slash, Key_V,  Key_G,    Key_P,      Key_B,     TD(BRACKETS),
   Key_Backspace, Key_E, Key_Enter, OSM(LeftAlt),
   OSL(FUNCTION),

   M(MACRO_ANY), Key_PRCNT, Key_EXCLM, Key_NonUsPound,  Key_AND,    Key_RCB,    ___,
   Key_Enter,    Key_Z,     Key_L,     Key_Comma,       Key_U,      Key_Q,      Key_BSLASH,
                 Key_M,     Key_N,     Key_A,           Key_I,      Key_O,      Key_DBLQUOTE,
   TD(PARENS),   Key_X,     Key_W,     Key_Period,      Key_Equals, Key_Minus,  ___,
   Key_Tab, OSL(SHIFTED_RSTHD), Key_Spacebar, OSM(LeftControl),
   OSL(FUNCTION)),

  // shift layer
  [SHIFTED_RSTHD] = KEYMAP_STACKED
  (___,        Key_F7,         Key_F5,        Key_F3,        Key_F1,        Key_F9,        ___,
   Key_TILDE,  LSHIFT(Key_J),  LSHIFT(Key_C), LSHIFT(Key_Y), LSHIFT(Key_F), LSHIFT(Key_K), Key_GREATER,
   ___,        LSHIFT(Key_R),  LSHIFT(Key_S), LSHIFT(Key_T), LSHIFT(Key_H), LSHIFT(Key_D),
   ___,        Key_QUEST,      LSHIFT(Key_V), LSHIFT(Key_G), LSHIFT(Key_P), LSHIFT(Key_B), ___,
   Key_Delete, LSHIFT(Key_E), ___, ___,
   ___,

   M(MACRO_VERSION_INFO), Key_F10,       Key_F2,        Key_F4,         Key_F6,         Key_F8,         ___,
   Key_Enter,             LSHIFT(Key_Z), LSHIFT(Key_L), Key_Semicolon,  LSHIFT(Key_U),  LSHIFT(Key_Q),  Key_PIPE,
                          LSHIFT(Key_M), LSHIFT(Key_N), LSHIFT(Key_A),  LSHIFT(Key_I),  LSHIFT(Key_O),  Key_Quote,
   ___,                   LSHIFT(Key_X), LSHIFT(Key_W), Key_COLON,      Key_PLUS,       Key_UNDERSCR,   ___,
   ___, ___, LSHIFT(Key_Spacebar), ___,
   ___),

  /*
  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadSubtract, ___,
   ___,                    ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      ___,
                           ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         ___,
   ___,                    ___, Key_Keypad0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
   ___, ___, ___, ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,        Key_F5,           XXX,
   Key_Tab,  ___,              Key_mouseUp, ___,        Key_mouseBtnR, Key_mouseWarpEnd, Key_mouseWarpNE,
   Key_Home, Key_mouseL,       Key_mouseDn, Key_mouseR, Key_mouseBtnL, Key_mouseWarpNW,
   Key_End,  Key_PrintScreen,  Key_Insert,  ___,        Key_mouseBtnM, Key_mouseWarpSW,  Key_mouseWarpSE,
   ___, Key_Delete, ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_F12,
                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  ___,              ___,
   Key_PcApplication,          Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   ___, ___, Key_Enter, ___,
   ___)

*/
 [FUNCTION] =  KEYMAP_STACKED
  ( ___, Key_F17,  Key_F15,        Key_F13,       Key_F11,        Key_F19,   XXX,
   ___, ___,       Key_PageUp,     Key_UpArrow,   Key_PageDown,   ___,       ___,
   ___, Key_Home,  Key_LeftArrow,  Key_DownArrow, Key_RightArrow, Key_End,
   ___, ___,       ___,            ___,           Key_Comma,        ___,     ___,
   ___, Key_Enter, Key_Delete, ___,
   ___,

    ___, Key_F20,   Key_F12, Key_F14,  Key_F16,  Key_F18,    ___,
    ___, Key_STAR,  Key_7,   Key_8,    Key_9,    Key_PLUS,   ___,
         Key_0,     Key_4,   Key_5,    Key_6,    Key_Period, Key_Equals,
   ___,  Key_Slash, Key_1,   Key_2,    Key_3,    Key_Minus,  ___,
   ___, ___, ___, ___,
   ___)

    ) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

// define tapdances
void tapDanceAction(uint8_t tap_dance_index, byte row, byte col, uint8_t tap_count,
                    kaleidoscope::TapDance::ActionType tap_dance_action) {
    switch (tap_dance_index) {
    case BRACKETS:
        return tapDanceActionKeys(tap_count, tap_dance_action,
                                  Key_LeftBracket, Key_RightBracket);
    case PARENS:
        return tapDanceActionKeys(tap_count, tap_dance_action,
                                  Key_LPAREN, Key_RPAREN);
    case CBRACES:
        return tapDanceActionKeys(tap_count, tap_dance_action,
                                  Key_LCB, Key_RCB);
    }
}

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  if (keyToggledOn(keyState))
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey);
}

/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;

  case MACRO_ANY:
    anyKeyMacro(keyState);
    break;
  }
  return MACRO_NONE;
}

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
  BootGreetingEffect,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the left Fn button at the same time.
  TestMode,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,

  // The numpad plugin is responsible for lighting up the 'numpad' mode
  // with a custom LED effect
  //NumPad,

  // The macros plugin adds support for macros
  Macros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,

  // The HostPowerManagement plugin enables waking up the host from suspend,
  // and allows us to turn LEDs off when it goes to sleep.
  HostPowerManagement,

  // activate oneshot
  OneShot,

  // use escape to cancel oneshot
  EscapeOneShot,

  // enable tapdance
  TapDance,

  // show active modifiers
  ActiveModColorEffect
);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */

void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  // NumPad.numPadLayer = NUMPAD;

  // We want the keyboard to be able to wake the host up from suspend.
  HostPowerManagement.enableWakeup();

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
