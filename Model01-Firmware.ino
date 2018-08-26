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
       MACRO_ANY,
       F11
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
#define Key_POUND    LSHIFT(Key_3)

// layers as defined; need to be in the same order as actual definition
enum { RSTHD, SHIFTED_RSTHD, SYMBOL, NUMPAD }; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

KEYMAPS(
  // primary layer
  [RSTHD] = KEYMAP_STACKED
  (M(F11),         Key_F1,     Key_F2,   Key_F3,    Key_F4,  Key_F5,  Key_LEDEffectNext,
   Key_Tab,        Key_J,      Key_C,    Key_Y,     Key_F,   Key_K,   Key_Insert,
   Key_PageUp,     Key_R,      Key_S,    Key_T,     Key_H,   Key_D,
   Key_PageDown,   Key_Minus,  Key_V,    Key_G,     Key_P,   Key_B,   Key_Escape,
   Key_Backspace, Key_E, OSL(SYMBOL), Key_LeftGui,
   OSL(SYMBOL),

   M(MACRO_ANY),    Key_F6,  Key_F7,  Key_F8,       Key_F9,        Key_F10,   Key_Delete,
   Key_PrintScreen, Key_Z,   Key_L,   Key_Comma,    Key_U,         Key_Q,     OSM(RightAlt),
                    Key_M,   Key_N,   Key_A,        Key_I,         Key_O,     OSM(LeftControl),
   Key_Enter,       Key_X,   Key_W,   Key_Period,   Key_Semicolon, Key_Slash, OSM(LeftAlt),
   Key_RightGui, OSL(SHIFTED_RSTHD), Key_Spacebar, OSL(NUMPAD),
   OSL(NUMPAD)),

  // shift layer
  [SHIFTED_RSTHD] = KEYMAP_STACKED
  (___,             Key_F11,        Key_F12,       Key_F13,       Key_F14,       Key_F15,       ___,
   LSHIFT(Key_Tab), LSHIFT(Key_J),  LSHIFT(Key_C), LSHIFT(Key_Y), LSHIFT(Key_F), LSHIFT(Key_K), ___,
   Key_Home,        LSHIFT(Key_R),  LSHIFT(Key_S), LSHIFT(Key_T), LSHIFT(Key_H), LSHIFT(Key_D),
   Key_End,         Key_UNDERSCR,   LSHIFT(Key_V), LSHIFT(Key_G), LSHIFT(Key_P), LSHIFT(Key_B), ___,
   Key_Delete, LSHIFT(Key_E), ___, ___,
   ___,

   M(MACRO_VERSION_INFO), Key_F16,       Key_F17,       Key_F18,        Key_F19,        Key_F20,        ___,
   ___,                   LSHIFT(Key_Z), LSHIFT(Key_L), Key_TILDE,      LSHIFT(Key_U),  LSHIFT(Key_Q),  ___,
                          LSHIFT(Key_M), LSHIFT(Key_N), LSHIFT(Key_A),  LSHIFT(Key_I),  LSHIFT(Key_O),  ___,
   ___,                   LSHIFT(Key_X), LSHIFT(Key_W), Key_POUND,      Key_AT,         Key_BSLASH,   ___,
   ___, ___, LSHIFT(Key_Spacebar), ___,
   ___),
   
  [SYMBOL] =  KEYMAP_STACKED
  (___,       ___, ___, ___, ___, ___, ___,
   ___,       Key_PRCNT,    Key_LESS,    Key_DOLLAR,   Key_GREATER, XXX , ___,
   Key_COLON, Key_Quote,    Key_LPAREN,  Key_DBLQUOTE, Key_RPAREN,  Key_HASH,
   ___,       Key_Backtick, XXX,         Key_PLUS,     Key_STAR,    Key_CARET,   ___,
   ___, ___, ___, ___,
   ___,

   ___, ___, ___, ___, ___, ___, ___,
   ___, XXX,           Key_LeftBracket, Key_Equals,  Key_RightBracket, Key_AND,   ___,
        Key_LeftArrow, Key_DownArrow,   Key_UpArrow, Key_RightArrow,   Key_PIPE,  ___,
   ___, Key_AT,        Key_LCB,         Key_QUEST,   Key_RCB,          Key_EXCLM, ___,
   ___, ___, Key_Enter, ___,
   ___),

  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___,              Key_mouseScrollUp, Key_mouseWarpNW, Key_mouseUp,      Key_mouseWarpNE, XXX, ___,
   Key_mouseScrollL, Key_mouseBtnL,     Key_mouseL,      Key_mouseDn,      Key_mouseR,      Key_mouseBtnR,
   Key_mouseScrollR, Key_mouseScrollDn, Key_mouseWarpSW, Key_mouseWarpEnd, Key_mouseWarpSE, Key_mouseBtnM, ___,
   ___, Key_Enter, ___, ___,
   ___,

   ___, ___,       Key_PRCNT, Key_Equals, Key_STAR, Key_CARET, ___,
   ___, Key_PLUS,  Key_2,     ___,        Key_4,    Key_6,     ___,
        Key_Minus, Key_0,     Key_1,      Key_3,    Key_5,     ___,
   ___, Key_7,     Key_8,     ___,        Key_9,    ___,       ___,
   ___, ___, ___, ___,
   ___)

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
*/
    ) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

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
    if (macroIndex == F11) {
        if (!keyToggledOff(keyState))
            return  MACRO_NONE;
        return MACRO(T(F11));
    }
    
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

  // The HostPowerManagement plugin allows us to turn LEDs off when host
  // goes to sleep and resume them when it wakes up.
  HostPowerManagement,

  // activate oneshot
  OneShot,

  // use escape to cancel oneshot
  EscapeOneShot,

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

  // Improve cursor movements
  MouseKeys.speed = 4;
  MouseKeys.speedDelay = 0;
  MouseKeys.accelSpeed = 2;
  MouseKeys.accelDelay = 100;
  
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
