// 2024.9.15 ver.2.0.1
// MIDI Programmable Controller

// ==================================================
// プリプロセッサ
// ==================================================
#include "GlobalEnum.h"
#include "GlobalConst.h"
#include "GlobalVariable.h"
#include "GlobalFunction.h"
#include "LoadSaveData.h"
#include "PlayMode.h"
#include "ProgramMode.h"
#include "ProgramBypassMode.h"
#include "ChangeActiveBankCountMode.h"
#include "ChangeBrightnessMode.h"
#include "RecieveMode.h"

// ==================================================
// セットアップ
// ==================================================
void setup()
{
    // MIDI処理開始
    midi1.begin(MIDI_CHANNEL_OMNI);
    // パッチデータ通信用シリアルポートの接続開始
    Serial.begin(9600);

    // 全データの読み込み
    loadAllData();
    
    // ディスプレイ初期化
    display.clear();
    display.setBrightness(currentBrightness);

    // 起動メッセージ表示
    for(int i = 0; i < 4; i++)
    {
        display.setSegments(display_hell, 1 + i, 3 - i);
        delay(time_waitScroll);
    }
    display.setSegments(display_ello);
    delay(time_waitScroll);
    display.setSegments(display_llo);
    delay(time_waitScroll);
    display.setSegments(display_lo);
    delay(time_waitScroll);
    display.setSegments(display_o);
    delay(time_waitScroll);
    display.clear();
    delay(time_waitClear);
}

// ==================================================
// メインループ
// ==================================================
void loop()
{
    // ループ開始
    switch(currentMode)
    {
        case Mode::play:
            playMode();
            break;
        case Mode::program:
            programMode();
            break;
        case Mode::programBypass:
            programBypassMode();
            break;
        case Mode::changeActiveBankCount:
            changeActiveBankCountMode();
            break;
        case Mode::changeBrightness:
            changeBrightnessMode();
            break;
        case Mode::recieve:
            recieveMode();
            break;
        default:
            break;
    }
}
