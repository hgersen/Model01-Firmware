// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for storing the keymap in EEPROM
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"

// Support for communicating with the host via a simple Serial protocol
#include "Kaleidoscope-FocusSerial.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
#include "Kaleidoscope-NumPad.h"

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

// put layer-toggle on thumb
#include "Kaleidoscope-Qukeys.h"

// Support for magic combos (key chords that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"

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
       MACRO_BSLASH
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
  * The third oene is layer 2.
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
enum { MTGAP, SHIFTED_MTGAP, SYMBOL, NUMPAD }; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

KEYMAPS(
  // primary layer
  [MTGAP] = KEYMAP_STACKED
  (M(MACRO_BSLASH),  Key_EXCLM,    Key_Tab,       Key_Quote,  Key_Slash,  Key_QUEST,   ___,
   Key_DOLLAR,       Key_UNDERSCR, Key_Y,         Key_O,      Key_U,      Key_LPAREN,  ___,
   Key_COLON,        Key_I,        Key_N,         Key_E,      Key_A,      Key_Period,
   Key_9,            Key_RPAREN,   Key_Semicolon, Key_0,      Key_Comma,  Key_Minus,   Key_Esc,
   OSM(LeftControl), LT(SYMBOL,Spacebar), Key_Enter, Key_LeftGui,
   OSL(SYMBOL),

   LockLayer(NUMPAD), Key_Q, Key_1, Key_G, Key_2, Key_5, Key_GREATER,
   ___,               Key_K, Key_D, Key_L, Key_C, Key_W, Key_Z,
                      Key_F, Key_H, Key_T, Key_S, Key_R, Key_DBLQUOTE,
   OSM(RightAlt),     Key_B, Key_P, Key_M, Key_V, Key_X, Key_J,
   Key_RightGui, Key_Backspace, OSL(SHIFTED_MTGAP), OSM(LeftAlt),
   OSL(SYMBOL)),

  // shift layer
  [SHIFTED_MTGAP] = KEYMAP_STACKED
  (Key_CARET,  Key_Backtick,  ___,           Key_STAR,      Key_PIPE,        Key_HASH,   ___,
   Key_AT,     Key_AND,       LSHIFT(Key_Y), LSHIFT(Key_O), LSHIFT(Key_U),   Key_LCB,    ___,
   Key_LESS,   LSHIFT(Key_I), LSHIFT(Key_N), LSHIFT(Key_E), LSHIFT(Key_A),   Key_Equals,
   Key_PRCNT,  Key_PLUS,      Key_6,         Key_3,         Key_LeftBracket, Key_8,      ___,
   LSHIFT(Key_LeftControl), LSHIFT(Key_Spacebar), LSHIFT(Key_Enter), ___,
   ___,

   M(MACRO_VERSION_INFO), LSHIFT(Key_Q), Key_RightBracket, LSHIFT(Key_G), Key_4,         Key_7,         Key_TILDE,
   ___,                   LSHIFT(Key_K), LSHIFT(Key_D),    LSHIFT(Key_L), LSHIFT(Key_C), LSHIFT(Key_W), LSHIFT(Key_Z),
                          LSHIFT(Key_F), LSHIFT(Key_H),    LSHIFT(Key_T), LSHIFT(Key_S), LSHIFT(Key_R), Key_RCB,
   ___,                   LSHIFT(Key_B), LSHIFT(Key_P),    LSHIFT(Key_M), LSHIFT(Key_V), LSHIFT(Key_X), LSHIFT(Key_J),
   ___, Key_Delete, ___, LSHIFT(Key_LeftAlt),
   ___),
   
  [SYMBOL] =  KEYMAP_STACKED
  (___, Key_F1,  Key_F2,         Key_F3,       Key_F4,        Key_F5,         ___,
   ___, XXX,     Key_Home,       Key_PageUp,   Key_F11,       Key_F12,        ___,
   ___, Key_End, Key_LeftArrow,  Key_UpArrow,  Key_DownArrow, Key_RightArrow,
   ___, XXX,     XXX,            XXX,          Key_PageDown,  Key_Spacebar,   ___,
   ___, ___, ___, ___,
   ___,
  
   ___, Key_F6,        Key_F7,          Key_F8,           Key_F9,          Key_F10,            ___,
   ___, XXX,           Key_mouseWarpNW, Key_mouseUp,      Key_mouseWarpNE, Key_mouseScrollUp,  ___,
        Key_mouseBtnL, Key_mouseL,      Key_mouseDn,      Key_mouseR,      Key_mouseBtnR,      ___,
   ___, Key_mouseBtnM, Key_mouseWarpSW, Key_mouseWarpEnd, Key_mouseWarpSE, Key_mouseScrollDn,  ___,
   ___, ___, ___, ___,
   ___),

  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   ___, ___,       Key_STAR,  Key_PLUS,   Key_PRCNT,  Key_CARET, ___,
   ___, Key_Tab,   Key_3,     Key_2,      Key_5,      Key_COLON, ___,
        Key_4,     Key_0,     Key_1,      Key_Period, Key_7,     Key_Minus,
   ___, Key_Comma, Key_8,     Key_9,      Key_6,      Key_Slash, ___,
   ___, ___, Key_Enter, ___,
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
  bool toggledOn = false;
  if (keyToggledOn(keyState)) {
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);
    toggledOn = true;
  }

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey, toggledOn);
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
    if (macroIndex == MACRO_BSLASH) {
        if (!keyToggledOff(keyState))
            return  MACRO_NONE;
        return MACRO(T(BSLASH));
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

/** This 'enum' is a list of all the magic combos used by the Model 01's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
 enum {
    // Toggle between Boot (6-key rollover; for BIOSes and early boot) and
    // NKRO
    // mode.
    COMBO_TOGGLE_NKRO_MODE
 };

/** A tmny wrapper, to be used by MagicCombo.
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = { R3C6, R2C6, R3C7 }
                 });

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is
  // the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to
  // aid in changing some settings of the keyboard, such as the
  // default layer (via the `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which
  // are very helpful in
  // both debugging, and in backing up one's EEPROM
  // contents.
  FocusEEPROMCommand,

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
  ActiveModColorEffect,

  // enable layer-toggle
  Qukeys,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks
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

  // To make the keymap editable without flashing new firmware, we store
  // additional layers in EEPROM. For now, we reserve space for five layers.
  // If
  // one wants to use these layers, just set the default layer to one in
  // EEPROM,
  // by using the `settings.defaultLayer` Focus command.
  EEPROMKeymap.setup(5, EEPROMKeymap.Mode::EXTEND);
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
