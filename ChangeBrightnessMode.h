// ==================================================
// プリプロセッサ
// ==================================================
#ifndef CHANGE_BRIGHTNESS_MODE
#define CHANGE_BRIGHTNESS_MODE

// ==================================================
// 前方宣言
// ==================================================
void increaseBrightness(void);
void decreaseBrightness(void);
void showBrightness(void);

// ==================================================
// 輝度調整モード
// ==================================================
void changeBrightnessMode()
{    
    // モードループ
    showBrightness();
    while(true)
    {
        // モード変更スイッチの処理
        status_modeChangeSwitch = modeChangeSwitch.check();
        switch(status_modeChangeSwitch)
        {
            case MomentarySwitchV2::Status::press:
                saveBrightness();
                currentMode = Mode::program;
                return;
            case MomentarySwitchV2::Status::hold:
                if(modeChangeSwitch.isHolding()) break;
                saveBrightness();
                currentMode = Mode::play;
                return;
            default:
                break;
        }

        // 上下スイッチの処理
        status_upSwitch = upSwitch.check();
        switch(status_upSwitch)
        {
            case MomentarySwitchV2::Status::press:
            case MomentarySwitchV2::Status::hold:
                increaseBrightness();
                showBrightness();
                break;
            default:
                break;
        }
        status_downSwitch = downSwitch.check();
        switch(status_downSwitch)
        {
            case MomentarySwitchV2::Status::press:
            case MomentarySwitchV2::Status::hold:
                decreaseBrightness();
                showBrightness();
                break;
            default:
                break;
        }

        // 各種コントロールの更新確認インターバル
        delay(time_checkInterval);
    };
}

// ==================================================
// 処理
// ==================================================
void increaseBrightness()
{
    if(currentBrightness < max_brightness - 1) currentBrightness++;
    else currentBrightness = 0;
    display.setBrightness(currentBrightness);
}
void decreaseBrightness()
{
    if(currentBrightness > 0) currentBrightness--;
    else currentBrightness = max_brightness - 1;
    display.setBrightness(currentBrightness);
}
void showBrightness()
{
    display.setSegments(display_changeBrightnessMode);
    display.showNumberDec(currentBrightness + 1, false, 1, 3);
}

#endif