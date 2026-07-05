// ==================================================
// プリプロセッサ
// ==================================================
#ifndef DISPLAY_CHARACTERS
#define DISPLAY_CHARACTERS

// ==================================================
// ディスプレイ表示用ビットマスク
// ==================================================
// 開始メッセージ
// HELLo
const unsigned char display_hell[4] = {
    SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,
    SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,
    SEG_D | SEG_E | SEG_F,
    SEG_D | SEG_E | SEG_F
};
const unsigned char display_ello[4] = {
    SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,
    SEG_D | SEG_E | SEG_F,
    SEG_D | SEG_E | SEG_F,
    SEG_C | SEG_D | SEG_E | SEG_G
};
const unsigned char display_llo[4] = {
    SEG_D | SEG_E | SEG_F,
    SEG_D | SEG_E | SEG_F,
    SEG_C | SEG_D | SEG_E | SEG_G,
    0
};
const unsigned char display_lo[4] = {
    SEG_D | SEG_E | SEG_F,
    SEG_C | SEG_D | SEG_E | SEG_G,
    0,
    0
};
const unsigned char display_o[4] = {
    SEG_C | SEG_D | SEG_E | SEG_G,
    0,
    0,
    0
};

// モード切り替えメッセージ
// PLAY
const unsigned char display_playMode[4] = {
    SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,
    SEG_D | SEG_E | SEG_F,
    SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,
    SEG_B | SEG_C | SEG_D | SEG_F | SEG_G 
};
// ProG
const unsigned char display_programMode[4] = {
    SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,
    SEG_E | SEG_G,
    SEG_C | SEG_D | SEG_E | SEG_G,
    SEG_A | SEG_C | SEG_D | SEG_E | SEG_F
};
// bYPS
const unsigned char display_programBypassMode[4] = {
    SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
    SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,
    SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,
    SEG_A | SEG_C | SEG_D | SEG_F | SEG_G
};
// Ab
const unsigned char display_changeActiveBankCountMode[4] = {
    SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,
    SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
    0,
    0
};
// brt
const unsigned char display_changeBrightnessMode[4] = {
    SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
    SEG_E | SEG_G,
    SEG_D | SEG_E | SEG_F | SEG_G,
    0
};
// rX
const unsigned char display_recieveMode[4] = {
    SEG_E | SEG_G,
    SEG_A | SEG_D | SEG_G,
    0,
    0
};

// バンク切り替えメッセージ
// b-
const unsigned char display_bank[4] = {
    SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
    SEG_G,
    0,
    0
};

// プレイモードメッセージ
// P-
const unsigned char display_mainPatch[4] = {
    SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,
    SEG_G,
    0,
    0
};
// P≡
const unsigned char display_subPatch[4] = {
    SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,
    SEG_A | SEG_D | SEG_G,
    0,
    0
};
// oFF
const unsigned char display_bypass[4] = {
    SEG_C | SEG_D | SEG_E | SEG_G,
    SEG_A | SEG_E | SEG_F | SEG_G,
    SEG_A | SEG_E | SEG_F | SEG_G,
    0
};

// プログラムモードメッセージ
// P-
const unsigned char display_patch[4] = {
    SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,
    SEG_G,
    0,
    0
};
// MAIn
const unsigned char display_main[4] = {
    SEG_A | SEG_B | SEG_C | SEG_E | SEG_F,
    SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,
    SEG_B | SEG_C,
    SEG_C | SEG_E | SEG_G
};
// Sub
const unsigned char display_sub[4] = {
    SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
    SEG_C | SEG_D | SEG_E,
    SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
    0
};
// Ch
const unsigned char display_channel[4] = {
    SEG_A | SEG_D | SEG_E | SEG_F,
    SEG_C | SEG_E | SEG_F | SEG_G,
    0,
    0
};
// on
const unsigned char display_on[4] = {
    SEG_C | SEG_D | SEG_E | SEG_G,
    SEG_C | SEG_E | SEG_G,
    0,
    0
};
// oFF
const unsigned char display_off[4] = {
    SEG_C | SEG_D | SEG_E | SEG_G,
    SEG_A | SEG_E | SEG_F | SEG_G,
    SEG_A | SEG_E | SEG_F | SEG_G,
    0
};
// P
const unsigned char display_programChange[4] = {
    SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,
    0,
    0,
    0
};
// CC-
const unsigned char display_controlChangeIndex[4] = {
    SEG_A | SEG_D | SEG_E | SEG_F,
    SEG_A | SEG_D | SEG_E | SEG_F,
    SEG_G,
    0
};
// C
const unsigned char display_controlChangeNumber[4] = {
    SEG_A | SEG_D | SEG_E | SEG_F,
    0,
    0,
    0
};
// c
const unsigned char display_controlChangeValue[4] = {
    SEG_D | SEG_E | SEG_G,
    0,
    0,
    0
};

// 処理メッセージ
// ----
const unsigned char display_progressWait[4] = {
    SEG_G,
    SEG_G,
    SEG_G,
    SEG_G
};
// - -
const unsigned char display_progressFirst[4] = {
    SEG_G,
    0,
    SEG_G,
    0
};
//  - -
const unsigned char display_progressSecond[4] = {
    0,
    SEG_G,
    0,
    SEG_G
};
// donE
const unsigned char display_done[4] = {
    SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,
    SEG_C | SEG_D | SEG_E | SEG_G,
    SEG_C | SEG_E | SEG_G,
    SEG_A | SEG_D | SEG_E | SEG_F | SEG_G
};

#endif