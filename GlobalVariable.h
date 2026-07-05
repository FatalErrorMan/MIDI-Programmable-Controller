// ==================================================
// プリプロセッサ
// ==================================================
#ifndef GLOBAL_VARIABLE
#define GLOBAL_VARIABLE
#include <EEPROM.h>
#include <MIDI.h>
#include <TM1637Display.h>
#include <Timer.h>
#include <MomentarySwitchV2.h>
#include "DisplayCharacters.h"
#include "MidiMessage.h"
#include "GlobalConst.h"
#include "GlobalEnum.h"

// ==================================================
// 変数
// ==================================================
// MIDI
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midi1);
// コントロール
TM1637Display display(pin_displayClk, pin_displayDio);
MomentarySwitchV2 patchSelectionSwitch[4] = {
    MomentarySwitchV2(pin_patchSelectionSwitch[0], time_switchHold),
    MomentarySwitchV2(pin_patchSelectionSwitch[1], time_switchHold),
    MomentarySwitchV2(pin_patchSelectionSwitch[2], time_switchHold),
    MomentarySwitchV2(pin_patchSelectionSwitch[3], time_switchHold)
};
MomentarySwitchV2 bankSelectionSwitch(pin_bankSelectionSwitch, time_switchHold);
MomentarySwitchV2 modeChangeSwitch(pin_modeChangeSwitch, time_switchHold);
MomentarySwitchV2 upSwitch(pin_upSwitch, time_switchHold);
MomentarySwitchV2 downSwitch(pin_downSwitch, time_switchHold);
MomentarySwitchV2 leftSwitch(pin_leftSwitch, time_switchHold);
MomentarySwitchV2 rightSwitch(pin_rightSwitch, time_switchHold);
// バンク
MidiMessage bypassBank[max_midiChannel];
MidiMessage mainBank[max_patchSelectionSwitchCount][max_midiChannel];
MidiMessage subBank[max_patchSelectionSwitchCount][max_midiChannel];
// 状態
Mode currentMode = Mode::play;
Edit currentEdit = Edit::bank;
byte currentBankIndex = 0;
byte currentPatchIndex = 0;
byte currentBrightness = 0;
byte activeBankCount = 1;
byte editPatchIndex = 0;
byte editMidiChannelIndex = 0;
byte editControlChangeIndex = 0;
bool editIsMain = true;
MomentarySwitchV2::Status status_patchSelectionSwitch[4];
MomentarySwitchV2::Status status_bankSelectionSwitch;
MomentarySwitchV2::Status status_modeChangeSwitch;
MomentarySwitchV2::Status status_upSwitch;
MomentarySwitchV2::Status status_downSwitch;
MomentarySwitchV2::Status status_leftSwitch;
MomentarySwitchV2::Status status_rightSwitch;
PatchState patchState[4] = { PatchState::bypass, PatchState::bypass, PatchState::bypass, PatchState::bypass };
// シリアル通信用バッファ
char serialBuffer;
// 点滅用タイマー
Timer timer_blinkProgressDisplay(500);
// フラグ
bool isEdited = false;
bool toggleDisplayStatus = false;

#endif
