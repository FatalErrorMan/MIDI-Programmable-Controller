// ==================================================
// プリプロセッサ
// ==================================================
#ifndef CHANGE_ACTIVE_BANK_COUNT_MODE
#define CHANGE_ACTIVE_BANK_COUNT_MODE

// ==================================================
// 前方宣言
// ==================================================
void increaseActiveBankCount(void);
void decreaseActiveBankCount(void);
void showActiveBankCount(void);

// ==================================================
// 有効バンク数設定モード
// ==================================================
void changeActiveBankCountMode()
{
    // モードループ
    showActiveBankCount();
    while(true)
    {
        // モード変更スイッチの処理
        status_modeChangeSwitch = modeChangeSwitch.check();
        switch(status_modeChangeSwitch)
        {
            case MomentarySwitchV2::Status::press:
                saveActiveBankCount();
                currentMode = Mode::changeBrightness;
                return;
            case MomentarySwitchV2::Status::hold:
                if(modeChangeSwitch.isHolding()) break;
                saveActiveBankCount();
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
                increaseActiveBankCount();
                showActiveBankCount();
                break;
            default:
                break;
        }
        status_downSwitch = downSwitch.check();
        switch(status_downSwitch)
        {
            case MomentarySwitchV2::Status::press:
            case MomentarySwitchV2::Status::hold:
                decreaseActiveBankCount();
                showActiveBankCount();
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
void increaseActiveBankCount()
{
    if(activeBankCount < max_bankCount) activeBankCount++;
    else activeBankCount = 1;
}
void decreaseActiveBankCount()
{
    if(activeBankCount > 1) activeBankCount--;
    else activeBankCount = max_bankCount;
}
void showActiveBankCount()
{
    display.setSegments(display_changeActiveBankCountMode);
    display.showNumberDec(activeBankCount, false, calcDigit(activeBankCount), 2);
}

#endif