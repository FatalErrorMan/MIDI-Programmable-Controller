// ==================================================
// プリプロセッサ
// ==================================================
#ifndef GLOBAL_CONST
#define GLOBAL_CONST

// ==================================================
// 定数
// ==================================================
// ピン番号
constexpr byte pin_displayClk = 41;
constexpr byte pin_displayDio = 43;
constexpr byte pin_patchSelectionSwitch[4] = {2, 3, 4, 5};
constexpr byte pin_bankSelectionSwitch = 6;
constexpr byte pin_modeChangeSwitch = 40;
constexpr byte pin_upSwitch = 42;
constexpr byte pin_downSwitch = 44;
constexpr byte pin_leftSwitch = 46;
constexpr byte pin_rightSwitch = 48;
// 時間
constexpr int time_switchHold = 1000;
constexpr int time_checkInterval = 100;
constexpr int time_checkSerialData = 100;
constexpr int time_waitDisplay = 500;
constexpr int time_waitClear = 200;
constexpr int time_waitScroll = 300;
// 最大値
constexpr byte max_brightness = 8;
constexpr byte max_bankCount = 10;
constexpr byte max_midiChannel = 5;
constexpr byte max_programChange = 127;
constexpr byte max_controlChangeNumber = 127;
constexpr byte max_controlChangeValue = 127;
constexpr byte max_controlChangeCount = 4;
constexpr byte max_patchSelectionSwitchCount = 4;

// プリプロセッサ
#include "MidiMessage.h"

// EEPROM保存先アドレス
constexpr int size_patch = 10 * max_midiChannel;
constexpr int size_bank = size_patch * max_patchSelectionSwitchCount;
constexpr unsigned int address_brightness = 0;
constexpr unsigned int address_activeBankCount = 1;
constexpr unsigned int address_bypassBank = 2;
constexpr unsigned int address_mainBank = address_bypassBank + size_patch;
constexpr unsigned int address_subBank = address_mainBank + size_bank * max_bankCount;
// 受信フラグ
constexpr char flag_start = -128; // byte = 128 (C#のシリアル通信型)
constexpr char flag_end = -1;     // byte = 255 (C#のシリアル通信型)

#endif
