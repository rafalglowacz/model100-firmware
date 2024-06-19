// -*- mode: c++ -*-
#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-FirmwareVersion.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-NumPad.h"
#include "Kaleidoscope-LEDEffect-BootGreeting.h"
#include "Kaleidoscope-LEDEffect-SolidColor.h"
#include "Kaleidoscope-LEDEffect-Breathe.h"
#include "Kaleidoscope-LEDEffect-Chase.h"
#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-LED-Stalker.h"
#include "Kaleidoscope-LED-AlphaSquare.h"
#include "Kaleidoscope-LED-Palette-Theme.h"
#include "Kaleidoscope-Colormap.h"
#include "Kaleidoscope-IdleLEDs.h"
#include "Kaleidoscope-DefaultLEDModeConfig.h"
#include "Kaleidoscope-LEDBrightnessConfig.h"
#include "Kaleidoscope-HardwareTestMode.h"
#include "Kaleidoscope-HostPowerManagement.h"
#include "Kaleidoscope-MagicCombo.h"
#include "Kaleidoscope-USB-Quirks.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-DynamicMacros.h"
#include "Kaleidoscope-SpaceCadet.h"
#include "Kaleidoscope-LayerNames.h"
#include "Kaleidoscope-Steno.h"

enum {
  MACRO_VERSION_INFO,
  MACRO_ANY,
};


/** You can find the names
  * (if not yet the explanations) for all the standard `Key_` definitions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   keeping NUM and FN consistent and accessible on all layers
  */

enum {
  PRIMARY,
  NUMPAD,
  NUMPAD_ALT,
  MOVE,
  FUNCTION,
  MOUSE,
  SYMBOL,
  MAC_PRIMARY,
  MAC_NUMPAD,
  MAC_MOVE,
  MAC_FUNCTION,
  MAC_MOUSE,
};

/* This comment temporarily turns off astyle's indent enforcement
 * so we can make the keymaps actually resemble the physical key layout better
 */
// clang-format off

KEYMAPS(

  // Linux/Windows layout

  [PRIMARY] = KEYMAP_STACKED
  (___,          ___,   ___,   ___,   ___,   ___,   Key_LEDEffectNext,
   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,

   ShiftToLayer(MOVE), ShiftToLayer(NUMPAD), ShiftToLayer(FUNCTION), ___,
   ShiftToLayer(SYMBOL),


       M(MACRO_ANY), ___,   ___,   ___,       ___,        ___,           LockLayer(NUMPAD),
       Key_Enter,    Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
                     Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
       ___,          Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,

       ___, Key_Backspace, ShiftToLayer(MOUSE), Key_Spacebar,
       ShiftToLayer(NUMPAD_ALT)),

  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,


       ___, ___,                ___,   ___,   ___,   ___,                ___,
       ___, ___,                Key_7, Key_8, Key_9, Key_KeypadMultiply, Key_Enter,
            Key_KeypadSubtract, Key_4, Key_5, Key_6, Key_KeypadAdd,      Key_KeypadSubtract,
       ___, Key_0,              Key_1, Key_2, Key_3, Key_KeypadDivide,   ___,

       ___, ___, Key_Period, ___,
       Key_Comma),

  [NUMPAD_ALT] =  KEYMAP_STACKED
  (___, ___, ___,   ___,   ___,   ___, ___,
   ___, ___, LSHIFT(Key_7), LSHIFT(Key_8), LSHIFT(Key_9), LSHIFT(Key_0), ___,
   ___, ___, LSHIFT(Key_4), LSHIFT(Key_5), LSHIFT(Key_6), ___,
   ___, ___, LSHIFT(Key_1), LSHIFT(Key_2), LSHIFT(Key_3), LSHIFT(Key_0), ___,
   ___, ___, ___, ___,
   ___,


       ___, ___,                ___,   ___,   ___,   ___,                ___,
       ___, ___,                Key_7, Key_8, Key_9, Key_KeypadMultiply, Key_Enter,
            Key_KeypadSubtract, Key_4, Key_5, Key_6, Key_KeypadAdd,      Key_KeypadSubtract,
       ___, Key_0,              Key_1, Key_2, Key_3, Key_KeypadDivide,   ___,

       ___, ___, Key_Period, ___,
       Key_Comma),

  [MOVE] =  KEYMAP_STACKED
  (___,  ___,        ___,         ___,             ___,          ___,         ___,
   ___, LGUI(Key_1), LGUI(Key_2), LGUI(Key_3),     LGUI(Key_4),  LGUI(Key_5), ___,
   ___, Key_LeftGui, Key_LeftAlt, Key_LeftControl, Key_LeftShift, ___,
   ___, LGUI(Key_6), LGUI(Key_7), LGUI(Key_8),     LGUI(Key_9),  LGUI(Key_0), ___,

   ___, ___, ___, ___,
   ___,


       ___, ___,          ___,           ___,           ___,            ___, ___,
       ___, Key_PageUp,   Key_Home,      Key_UpArrow,   Key_End,        ___, ___,
            Key_PageDown, Key_LeftArrow, Key_DownArrow, Key_RightArrow, ___, ___,
       ___, ___,          ___,           ___,           ___,            ___, ___,

       Key_PcApplication, Key_Delete, ___, ___,
       ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___,                      ___,             ___,                         ___,                    ___,                     ___, ___,
   Consumer_VolumeIncrement, ___,             ___,                         ___,                    ___,                     ___, ___,
   Consumer_VolumeDecrement, Key_LeftControl, Key_LeftAlt,                 Key_LeftGui,            Key_LeftShift,           ___,
   Consumer_Mute,            ___,             Consumer_ScanPreviousTrack,  Consumer_ScanNextTrack, Consumer_PlaySlashPause, ___, ___,

   ___, ___, ___, MoveToLayer(MAC_PRIMARY),
   ___,


       ___, ___, ___, ___, ___, ___, ___,
       ___, ___, Key_F7, Key_F8, Key_F9, Key_F12, ___,
            ___, Key_F4, Key_F5, Key_F6, Key_F11, ___,
       ___, ___, Key_F1, Key_F2, Key_F3, Key_F10, ___,

       ___, ___, ___, Key_F12,
       ___),

  [MOUSE] =  KEYMAP_STACKED
  (___,               ___,             ___,           ___,           ___,           ___, ___,
   ___,               ___,             ___,           ___,           ___,           ___, ___,
   Key_mouseScrollUp, ___,             Key_mouseBtnR, Key_mouseBtnM, Key_mouseBtnL, ___,
   Key_mouseScrollDn, Key_LeftControl, Key_LeftAlt,   Key_LeftGui,   Key_LeftShift, ___, ___,

   ___, ___, ___, ___,
   ___,


       ___, ___,             ___,               ___,              ___,              ___,             ___,
       ___, ___,             Key_mouseScrollUp, Key_mouseUp,      ___,              ___,             ___,
            Key_mouseWarpNW, Key_mouseL,        Key_mouseDn,      Key_mouseR,       Key_mouseWarpNE, ___,
       ___, Key_mouseWarpSW, Key_mouseScrollDn, Key_mouseScrollL, Key_mouseScrollR, Key_mouseWarpSE, ___,

       ___, ___, ___, ___,
       ___),

  [SYMBOL] = KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,

   ___, ___, ___, ___,
   ___,


       ___, ___, ___,                  ___,                   ___,                ___,                ___,
       ___, ___, Key_LeftCurlyBracket, Key_RightCurlyBracket, ___,                ___,                ___,
            ___, Key_LeftBracket,      Key_RightBracket,      LSHIFT(Key_Comma),  LSHIFT(Key_Period), ___,
       ___, ___, ___,                  ___,                   ___,                Key_Backslash,      LSHIFT(Key_Backslash),

       ___, ___, ___, ___,
       ___),

  // MacOS layout

  [MAC_PRIMARY] = KEYMAP_STACKED
  (___,          ___,   ___,   ___,   ___,   ___,   Key_LEDEffectNext,
   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,

   ShiftToLayer(MAC_MOVE), ShiftToLayer(MAC_NUMPAD), ShiftToLayer(MAC_FUNCTION), ___,
   ShiftToLayer(SYMBOL),


       M(MACRO_ANY),  ___,   ___,   ___,       ___,           ___,           LockLayer(NUMPAD),
       Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                      Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
       ___,           Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,

       ___, Key_Backspace, ShiftToLayer(MAC_MOUSE), Key_Spacebar,
       ShiftToLayer(NUMPAD_ALT)),

  [MAC_NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,


       ___, ___,                ___,   ___,   ___,   ___,                ___,
       ___, ___,                Key_7, Key_8, Key_9, Key_KeypadMultiply, Key_Enter,
            Key_KeypadSubtract, Key_4, Key_5, Key_6, Key_KeypadAdd,      Key_KeypadSubtract,
       ___, Key_0,              Key_1, Key_2, Key_3, Key_KeypadDivide,   ___,

       ___, ___, Key_Period, ___,
       Key_Comma),

  [MAC_MOVE] =  KEYMAP_STACKED
  (___, ___,             ___,           ___,             ___,           ___,            ___,
   ___, HYPER(Key_F1),   HYPER(Key_F2), HYPER(Key_F3),   HYPER(Key_F4), HYPER(Key_F5),  ___,
   ___, Key_LeftControl, Key_LeftAlt,   Key_LeftGui,     Key_LeftShift, ___,
   ___, HYPER(Key_F6),   HYPER(Key_F7), HYPER(Key_F8),   HYPER(Key_F9), HYPER(Key_F10), ___,

   ___, ___, ___, ___,
   ___,


       ___, ___,          ___,           ___,           ___,            ___, ___,
       ___, Key_PageUp,   Key_Home,      Key_UpArrow,   Key_End,        ___, ___,
            Key_PageDown, Key_LeftArrow, Key_DownArrow, Key_RightArrow, ___, ___,
       ___, ___,          ___,           ___,           ___,            ___, ___,

       ___, Key_Delete, ___, ___,
       ___),

  [MAC_FUNCTION] =  KEYMAP_STACKED
  (___,                      ___,             ___,                         ___,                    ___,                     ___, ___,
   Consumer_VolumeIncrement, ___,             ___,                         ___,                    ___,                     ___, ___,
   Consumer_VolumeDecrement, Key_LeftControl, Key_LeftAlt,                 Key_LeftGui,            Key_LeftShift,           ___,
   Consumer_Mute,            ___,             Consumer_ScanPreviousTrack,  Consumer_ScanNextTrack, Consumer_PlaySlashPause, ___, ___,

   ___, ___, ___, MoveToLayer(PRIMARY),
   ___,


       ___, ___, ___, ___, ___, ___, ___,
       ___, ___, Key_F7, Key_F8, Key_F9, Key_F12, ___,
            ___, Key_F4, Key_F5, Key_F6, Key_F11, ___,
       ___, ___, Key_F1, Key_F2, Key_F3, Key_F10, ___,

       ___, ___, ___, Key_F12,
       ___),

  [MAC_MOUSE] =  KEYMAP_STACKED
  (___,               ___,         ___,           ___,             ___,           ___, ___,
   ___,               ___,         ___,           ___,             ___,           ___, ___,
   Key_mouseScrollUp, ___,         Key_mouseBtnR, Key_mouseBtnM,   Key_mouseBtnL, ___,
   Key_mouseScrollDn, Key_LeftGui, Key_LeftAlt,   Key_LeftControl, Key_LeftShift, ___, ___,

   ___, ___, ___, ___,
   ___,


       ___, ___,             ___,               ___,              ___,              ___,             ___,
       ___, ___,             Key_mouseScrollUp, Key_mouseUp,      ___,              ___,             ___,
            Key_mouseWarpNW, Key_mouseL,        Key_mouseDn,      Key_mouseR,       Key_mouseWarpNE, ___,
       ___, Key_mouseWarpSW, Key_mouseScrollDn, Key_mouseScrollL, Key_mouseScrollR, Key_mouseWarpSE, ___,

       ___, ___, ___, ___,
       ___),

) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// clang-format on

static void versionInfoMacro(uint8_t key_state) {
  if (keyToggledOn(key_state)) {
    Macros.type(PSTR("Keyboardio Model 100 - Firmware version "));
    Macros.type(PSTR(KALEIDOSCOPE_FIRMWARE_VERSION));
  }
}

static void anyKeyMacro(KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    event.key.setKeyCode(Key_A.getKeyCode() + (uint8_t)(millis() % 36));
    event.key.setFlags(0);
  }
}

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  switch (macro_id) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(event.state);
    break;

  case MACRO_ANY:
    anyKeyMacro(event);
    break;
  }
  return MACRO_NONE;
}


// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 100.

static kaleidoscope::plugin::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::plugin::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::plugin::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::plugin::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::plugin::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::plugin::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::plugin::LEDSolidColor solidViolet(130, 0, 120);

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    LEDControl.disable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.enable();
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/**
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

/**
 *  This enters the hardware test mode
 */
static void enterHardwareTestMode(uint8_t combo_index) {
  HardwareTestMode.runTests();
}

/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = {R3C6, R2C6, R3C7}},
                 {.action = enterHardwareTestMode,
                  // Left Fn + Prog + LED
                  .keys = {R3C6, R0C0, R0C6}});

KALEIDOSCOPE_INIT_PLUGINS(
  // ----------------------------------------------------------------------
  // Chrysalis plugins

  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The FirmwareVersion plugin lets Chrysalis query the version of the firmware
  // programmatically.
  FirmwareVersion,

  // The LayerNames plugin allows Chrysalis to display - and edit - custom layer
  // names, to be shown instead of the default indexes.
  LayerNames,

  // Enables setting, saving (via Chrysalis), and restoring (on boot) the
  // default LED mode.
  DefaultLEDModeConfig,

  // Enables controlling (and saving) the brightness of the LEDs via Focus.
  LEDBrightnessConfig,

  // ----------------------------------------------------------------------
  // Keystroke-handling plugins

  // The Qukeys plugin enables the "Secondary action" functionality in
  // Chrysalis. Keys with secondary actions will have their primary action
  // performed when tapped, but the secondary action when held.
  Qukeys,

  // SpaceCadet can turn your shifts into parens on tap, while keeping them as
  // Shifts when held. SpaceCadetConfig lets Chrysalis configure some aspects of
  // the plugin.
  SpaceCadet,
  SpaceCadetConfig,

  // Enables the "Sticky" behavior for modifiers, and the "Layer shift when
  // held" functionality for layer keys.
  OneShot,
  OneShotConfig,
  EscapeOneShot,
  EscapeOneShotConfig,

  // The macros plugin adds support for macros
  Macros,

  // Enables dynamic, Chrysalis-editable macros.
  DynamicMacros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,
  MouseKeysConfig,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo,

  // Enables the GeminiPR Stenography protocol. Unused by default, but with the
  // plugin enabled, it becomes configurable - and then usable - via Chrysalis.
  GeminiPR,

  // ----------------------------------------------------------------------
  // LED mode plugins

  // The boot greeting effect pulses the LED button for 10 seconds after the
  // keyboard is first connected
  BootGreetingEffect,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,

  // The rainbow effect changes the color of all of the keyboard's keys at the same time
  // running through all the colors of the rainbow.
  LEDRainbowEffect,

  // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
  // and slowly moves the rainbow across your keyboard
  LEDRainbowWaveEffect,

  // The chase effect follows the adventure of a blue pixel which chases a red pixel across
  // your keyboard. Spoiler: the blue pixel never catches the red pixel
  LEDChaseEffect,

  // These static effects turn your keyboard's LEDs a variety of colors
  solidRed,
  solidOrange,
  solidYellow,
  solidGreen,
  solidBlue,
  solidIndigo,
  solidViolet,

  // The breathe effect slowly pulses all of the LEDs on your keyboard
  LEDBreatheEffect,

  // The AlphaSquare effect prints each character you type, using your
  // keyboard's LEDs as a display
  AlphaSquareEffect,

  // The stalker effect lights up the keys you've pressed recently
  StalkerEffect,

  // The LED Palette Theme plugin provides a shared palette for other plugins,
  // like Colormap below
  LEDPaletteTheme,

  // The Colormap effect makes it possible to set up per-layer colormaps
  ColormapEffect,

  // The numpad plugin is responsible for lighting up the 'numpad' mode
  // with a custom LED effect
  NumPad,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // Turns LEDs off after a configurable amount of idle time.
  IdleLEDs,
  PersistentIdleLEDs,

  // ----------------------------------------------------------------------
  // Miscellaneous plugins

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the
  // left Fn button at the same time.
  HardwareTestMode  //,
);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Set the hue of the boot greeting effect to something that will result in a
  // nice green color.
  BootGreetingEffect.hue = 85;

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumPad.numPadLayer = NUMPAD;

  // We configure the AlphaSquare effect to use RED letters
  AlphaSquare.color = CRGB(255, 0, 0);

  // Set the rainbow effects to be reasonably bright, but low enough
  // to mitigate audible noise in some environments.
  LEDRainbowEffect.brightness(170);
  LEDRainbowWaveEffect.brightness(160);

  // Set the action key the test mode should listen for to Left Fn
  HardwareTestMode.setActionKey(R3C6);

  // The LED Stalker mode has a few effects. The one we like is called
  // 'BlazingTrail'. For details on other options, see
  // https://github.com/keyboardio/Kaleidoscope/blob/master/docs/plugins/LED-Stalker.md
  StalkerEffect.variant = STALKER(BlazingTrail);

  // To make the keymap editable without flashing new firmware, we store
  // additional layers in EEPROM. For now, we reserve space for eight layers. If
  // one wants to use these layers, just set the default layer to one in EEPROM,
  // by using the `settings.defaultLayer` Focus command, or by using the
  // `keymap.onlyCustom` command to use EEPROM layers only.
  // EEPROMKeymap.setup(8);

  // We need to tell the Colormap plugin how many layers we want to have custom
  // maps for. To make things simple, we set it to eight layers, which is how
  // many editable layers we have (see above).
  ColormapEffect.max_layers(8);

  // For Dynamic Macros, we need to reserve storage space for the editable
  // macros. A kilobyte is a reasonable default.
  DynamicMacros.reserve_storage(1024);

  // If there's a default layer set in EEPROM, we should set that as the default
  // here.
  // Layer.move(EEPROMSettings.default_layer());

  // To avoid any surprises, SpaceCadet is turned off by default. However, it
  // can be permanently enabled via Chrysalis, so we should only disable it if
  // no configuration exists.
  SpaceCadetConfig.disableSpaceCadetIfUnconfigured();

  // Editable layer names are stored in EEPROM too, and we reserve 16 bytes per
  // layer for them. We need one extra byte per layer for bookkeeping, so we
  // reserve 17 / layer in total.
  LayerNames.reserve_storage(17 * 8);

  // Unless configured otherwise with Chrysalis, we want to make sure that the
  // firmware starts with LED effects off. This avoids over-taxing devices that
  // don't have a lot of power to share with USB devices
  // DefaultLEDModeConfig.activateLEDModeIfUnconfigured(&LEDOff);

  DefaultLEDModeConfig.activateLEDModeIfUnconfigured(&LEDRainbowWaveEffect);

  QUKEYS(
    // Linux/Windows
    kaleidoscope::plugin::Qukey(PRIMARY, KeyAddr(2, 1), Key_LeftGui),      // A
    kaleidoscope::plugin::Qukey(PRIMARY, KeyAddr(2, 2), Key_LeftAlt),      // S
    kaleidoscope::plugin::Qukey(PRIMARY, KeyAddr(2, 3), Key_LeftControl),  // D
    kaleidoscope::plugin::Qukey(PRIMARY, KeyAddr(2, 4), Key_LeftShift),    // F

    kaleidoscope::plugin::Qukey(PRIMARY, KeyAddr(2, 11), Key_LeftShift),   // J
    kaleidoscope::plugin::Qukey(PRIMARY, KeyAddr(2, 12), Key_LeftControl), // K
    kaleidoscope::plugin::Qukey(PRIMARY, KeyAddr(2, 13), Key_LeftAlt),     // L
    kaleidoscope::plugin::Qukey(PRIMARY, KeyAddr(2, 14), Key_LeftGui),     // ;

    kaleidoscope::plugin::Qukey(PRIMARY, KeyAddr(1, 3),  Key_RightAlt),    // E
    kaleidoscope::plugin::Qukey(PRIMARY, KeyAddr(1, 12), Key_RightAlt),    // I

    // MacOS
    kaleidoscope::plugin::Qukey(MAC_PRIMARY, KeyAddr(2, 1), Key_LeftControl),  // A
    kaleidoscope::plugin::Qukey(MAC_PRIMARY, KeyAddr(2, 2), Key_LeftAlt),      // S
    kaleidoscope::plugin::Qukey(MAC_PRIMARY, KeyAddr(2, 3), Key_LeftGui),      // D
    kaleidoscope::plugin::Qukey(MAC_PRIMARY, KeyAddr(2, 4), Key_LeftShift),    // F

    kaleidoscope::plugin::Qukey(MAC_PRIMARY, KeyAddr(2, 11), Key_LeftShift),   // J
    kaleidoscope::plugin::Qukey(MAC_PRIMARY, KeyAddr(2, 12), Key_LeftGui),     // K
    kaleidoscope::plugin::Qukey(MAC_PRIMARY, KeyAddr(2, 13), Key_LeftAlt),     // L
    kaleidoscope::plugin::Qukey(MAC_PRIMARY, KeyAddr(2, 14), Key_LeftControl), // ;

    kaleidoscope::plugin::Qukey(MAC_PRIMARY, KeyAddr(1, 3),  Key_RightAlt),    // E
    kaleidoscope::plugin::Qukey(MAC_PRIMARY, KeyAddr(1, 12), Key_RightAlt),    // I
  );
}

void loop() {
  Kaleidoscope.loop();
}

// Template layer:
  // [NUMPAD] = KEYMAP_STACKED
  // (___, ___, ___, ___, ___, ___, ___,
  //  ___, ___, ___, ___, ___, ___, ___,
  //  ___, ___, ___, ___, ___, ___,
  //  ___, ___, ___, ___, ___, ___, ___,
  //  ___, ___, ___, ___,
  //  ___,
  //
  //
  //      ___, ___, ___, ___, ___, ___, ___,
  //      ___, ___, ___, ___, ___, ___, ___,
  //           ___, ___, ___, ___, ___, ___,
  //      ___, ___, ___, ___, ___, ___, ___,
  //
  //      ___, ___, ___, ___,
  //      ___),

