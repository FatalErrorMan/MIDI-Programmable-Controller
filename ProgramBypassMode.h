// ==================================================
// プリプロセッサ
// ==================================================
#ifndef PROGRAM_BYPASS_MODE
#define PROGRAM_BYPASS_MODE

// ==================================================
// 前方宣言
// ==================================================
void upEditStep_bypass(void);
void downEditStep_bypass(void);
void increaseEditIndex_bypass(void);
void decreaseEditIndex_bypass(void);
void showEditTarget_bypass(void);

// ==================================================
// バイパスプログラムモード
// ==================================================
void programBypassMode()
{
    // モード変更メッセージ表示
    display.setSegments(display_programBypassMode);
    delay(time_waitDisplay);
    display.clear();

    // 編集画面の初期化
    delay(time_waitClear);
    currentEdit = Edit::channel;
    editMidiChannelIndex = 0;
    editControlChangeIndex = 0;
    showEditTarget_bypass();

    // モードループ
    while(true)
    {
        // モード変更スイッチの処理
        status_modeChangeSwitch = modeChangeSwitch.check();
        switch(status_modeChangeSwitch)
        {
            case MomentarySwitchV2::Status::press:
                saveBypassBank();
                currentMode = Mode::changeActiveBankCount;
                return;
            case MomentarySwitchV2::Status::hold:
                if(modeChangeSwitch.isHolding()) break;
                saveBypassBank();
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
                increaseEditIndex_bypass();
                showEditTarget_bypass();
                break;
            default:
                break;
        }
        status_downSwitch = downSwitch.check();
        switch(status_downSwitch)
        {
            case MomentarySwitchV2::Status::press:
            case MomentarySwitchV2::Status::hold:
                decreaseEditIndex_bypass();
                showEditTarget_bypass();
                break;
            default:
                break;
        }

        // 左右スイッチの処理
        status_leftSwitch = leftSwitch.check();
        switch(status_leftSwitch)
        {
            case MomentarySwitchV2::Status::press:
            case MomentarySwitchV2::Status::hold:
                upEditStep_bypass();
                showEditTarget_bypass();
                break;
            default:
                break;
        }
        status_rightSwitch = rightSwitch.check();
        switch(status_rightSwitch)
        {
            case MomentarySwitchV2::Status::press:
            case MomentarySwitchV2::Status::hold:
                downEditStep_bypass();
                showEditTarget_bypass();
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
void upEditStep_bypass(void)
{
    switch(currentEdit)
    {
        case Edit::onOff:
            currentEdit = Edit::channel;
            break;
        case Edit::programChange:
            currentEdit = Edit::onOff;
            break;
        case Edit::controlChangeIndex:
            currentEdit = Edit::programChange;
            break;
        case Edit::controlChangeNumber:
            currentEdit = Edit::controlChangeIndex;
            break;
        case Edit::controlChangeValue:
            currentEdit = Edit::controlChangeNumber;
            break;
        default:
            break;
    }
}
void downEditStep_bypass(void)
{
    switch(currentEdit)
    {
        case Edit::channel:
            currentEdit = Edit::onOff;
            break;
        case Edit::onOff:
            currentEdit = Edit::programChange;
            break;
        case Edit::programChange:
            currentEdit = Edit::controlChangeIndex;
            break;
        case Edit::controlChangeIndex:
            currentEdit = Edit::controlChangeNumber;
            break;
        case Edit::controlChangeNumber:
            currentEdit = Edit::controlChangeValue;
            break;
        default:
            break;
    }
}
void increaseEditIndex_bypass()
{
    switch(currentEdit)
    {
        case Edit::channel:
            if(editMidiChannelIndex < max_midiChannel - 1) editMidiChannelIndex++;
            else editMidiChannelIndex = 0;
            editControlChangeIndex = 0;
            break;
        case Edit::onOff:
            if(bypassBank[editMidiChannelIndex].enabled) bypassBank[editMidiChannelIndex].enabled = false;
            else bypassBank[editMidiChannelIndex].enabled = true;
            break;
        case Edit::programChange:
            if(bypassBank[editMidiChannelIndex].programChange < max_programChange) bypassBank[editMidiChannelIndex].programChange++;
            else bypassBank[editMidiChannelIndex].programChange = 0;
            break;
        case Edit::controlChangeIndex:
            if(editControlChangeIndex < max_controlChangeCount - 1) editControlChangeIndex++;
            else editControlChangeIndex = 0;
            break;
        case Edit::controlChangeNumber:
            if(bypassBank[editMidiChannelIndex].controlChangeNumber[editControlChangeIndex] < max_controlChangeNumber) bypassBank[editMidiChannelIndex].controlChangeNumber[editControlChangeIndex]++;
            else bypassBank[editMidiChannelIndex].controlChangeNumber[editControlChangeIndex] = 0;
            break;
        case Edit::controlChangeValue:
            if(bypassBank[editMidiChannelIndex].controlChangeValue[editControlChangeIndex] < max_controlChangeValue) bypassBank[editMidiChannelIndex].controlChangeValue[editControlChangeIndex]++;
            else bypassBank[editMidiChannelIndex].controlChangeValue[editControlChangeIndex] = 0;
            break;
        default:
            break;
    }
}
void decreaseEditIndex_bypass()
{
    switch(currentEdit)
    {
        case Edit::channel:
            if(editMidiChannelIndex > 0) editMidiChannelIndex--;
            else editMidiChannelIndex = max_midiChannel - 1;
            editControlChangeIndex = 0;
            break;
        case Edit::onOff:
            if(bypassBank[editMidiChannelIndex].enabled) bypassBank[editMidiChannelIndex].enabled = false;
            else bypassBank[editMidiChannelIndex].enabled = true;
            break;
        case Edit::programChange:
            if(bypassBank[editMidiChannelIndex].programChange > 0) bypassBank[editMidiChannelIndex].programChange--;
            else bypassBank[editMidiChannelIndex].programChange = max_programChange;
            break;
        case Edit::controlChangeIndex:
            if(editControlChangeIndex > 0) editControlChangeIndex--;
            else editControlChangeIndex = max_controlChangeCount - 1;
            break;
        case Edit::controlChangeNumber:
            if(bypassBank[editMidiChannelIndex].controlChangeNumber[editControlChangeIndex] > 0) bypassBank[editMidiChannelIndex].controlChangeNumber[editControlChangeIndex]--;
            bypassBank[editMidiChannelIndex].controlChangeNumber[editControlChangeIndex] = max_controlChangeNumber;
            break;
        case Edit::controlChangeValue:
            if(bypassBank[editMidiChannelIndex].controlChangeValue[editControlChangeIndex] > 0) bypassBank[editMidiChannelIndex].controlChangeValue[editControlChangeIndex];
            bypassBank[editMidiChannelIndex].controlChangeValue[editControlChangeIndex] = max_controlChangeValue;
            break;
        default:
            break;
    }
}
void showEditTarget_bypass()
{
    display.clear();
    switch(currentEdit)
    {
        case Edit::channel:
            display.setSegments(display_channel);
            display.showNumberDec(editMidiChannelIndex + 1, false, calcDigit(editMidiChannelIndex + 1), 2);
            break;
        case Edit::onOff:
            if(bypassBank[editMidiChannelIndex].enabled) display.setSegments(display_on);
            else display.setSegments(display_off);
            break;
        case Edit::programChange:
            display.setSegments(display_programChange);
            display.showNumberDec(bypassBank[editMidiChannelIndex].programChange, true, 3, 1);
            break;
        case Edit::controlChangeIndex:
            display.setSegments(display_controlChangeIndex);
            display.showNumberDec(editControlChangeIndex + 1, false, calcDigit(editControlChangeIndex + 1), 2);
            break;
        case Edit::controlChangeNumber:
            display.setSegments(display_controlChangeNumber);
            display.showNumberDec(bypassBank[editMidiChannelIndex].controlChangeNumber[editControlChangeIndex], true, 3, 1);
            break;
        case Edit::controlChangeValue:
            display.setSegments(display_controlChangeValue);
            display.showNumberDec(bypassBank[editMidiChannelIndex].controlChangeValue[editControlChangeIndex], true, 3, 1);
            break;
        default:
            break;
    }
}

#endif