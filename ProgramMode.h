// ==================================================
// プリプロセッサ
// ==================================================
#ifndef PROGRAM_MODE
#define PROGRAM_MODE

// ==================================================
// 前方宣言
// ==================================================
void upEditStep(void);
void downEditStep(void);
void increaseEditIndex(void);
void decreaseEditIndex(void);
void showEditTarget(void);

// ==================================================
// プログラムモード
// ==================================================
void programMode()
{    
    // モード変更メッセージ表示
    display.setSegments(display_programMode);
    delay(time_waitDisplay);
    display.clear();

    // 編集画面の初期化
    delay(time_waitClear);
    currentEdit = Edit::bank;
    editPatchIndex = 0;
    editMidiChannelIndex = 0;
    editControlChangeIndex = 0;
    editIsMain = true;
    showEditTarget();

    // モードループ
    while(true)
    {
        // モード変更スイッチの処理
        status_modeChangeSwitch = modeChangeSwitch.check();
        switch(status_modeChangeSwitch)
        {
            case MomentarySwitchV2::Status::press:
                saveBank(currentBankIndex);
                currentMode = Mode::programBypass;
                return;
            case MomentarySwitchV2::Status::hold:
                if(modeChangeSwitch.isHolding()) break;
                saveBank(currentBankIndex);
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
                increaseEditIndex();
                showEditTarget();
                break;
            default:
                break;
        }
        status_downSwitch = downSwitch.check();
        switch(status_downSwitch)
        {
            case MomentarySwitchV2::Status::press:
            case MomentarySwitchV2::Status::hold:
                decreaseEditIndex();
                showEditTarget();
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
                upEditStep();
                showEditTarget();
                break;
            default:
                break;
        }
        status_rightSwitch = rightSwitch.check();
        switch(status_rightSwitch)
        {
            case MomentarySwitchV2::Status::press:
            case MomentarySwitchV2::Status::hold:
                downEditStep();
                showEditTarget();
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
void upEditStep()
{
    switch(currentEdit)
    {
        case Edit::patch:
            currentEdit = Edit::bank;
            break;
        case Edit::mainSub:
            currentEdit = Edit::patch;
            break;
        case Edit::channel:
            currentEdit = Edit::mainSub;
            break;
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
void downEditStep()
{
    switch(currentEdit)
    {
        case Edit::bank:
            currentEdit = Edit::patch;
            break;
        case Edit::patch:
            currentEdit = Edit::mainSub;
            break;
        case Edit::mainSub:
            currentEdit = Edit::channel;
            break;
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
void increaseEditIndex()
{
    switch(currentEdit)
    {
        case Edit::bank:
            saveBank(currentBankIndex);
            if(currentBankIndex < activeBankCount - 1) currentBankIndex++;
            else currentBankIndex = 0;
            loadBank(currentBankIndex);
            editPatchIndex = 0;
            editMidiChannelIndex = 0;
            editControlChangeIndex = 0;
            editIsMain = true;
            break;
        case Edit::patch:
            if(editPatchIndex < max_patchSelectionSwitchCount - 1) editPatchIndex++;
            else editPatchIndex = 0;
            editMidiChannelIndex = 0;
            editControlChangeIndex = 0;
            editIsMain = true;
            break;
        case Edit::mainSub:
            if(editIsMain) editIsMain = false;
            else editIsMain = true;
            editMidiChannelIndex = 0;
            editControlChangeIndex = 0;
            break;
        case Edit::channel:
            if(editMidiChannelIndex < max_midiChannel - 1) editMidiChannelIndex++;
            else editMidiChannelIndex = 0;
            editControlChangeIndex = 0;
            break;
        case Edit::onOff:
            if(editIsMain)
            {
                if(mainBank[editPatchIndex][editMidiChannelIndex].enabled) mainBank[editPatchIndex][editMidiChannelIndex].enabled = false;
                else mainBank[editPatchIndex][editMidiChannelIndex].enabled = true;
            }
            else
            {
                if(subBank[editPatchIndex][editMidiChannelIndex].enabled) subBank[editPatchIndex][editMidiChannelIndex].enabled = false;
                else subBank[editPatchIndex][editMidiChannelIndex].enabled = true;
            }
            break;
        case Edit::programChange:
            if(editIsMain)
            { 
                if(mainBank[editPatchIndex][editMidiChannelIndex].programChange < max_programChange) mainBank[editPatchIndex][editMidiChannelIndex].programChange++;
                else mainBank[editPatchIndex][editMidiChannelIndex].programChange = 0;
            }
            else
            { 
                if(subBank[editPatchIndex][editMidiChannelIndex].programChange < max_programChange) subBank[editPatchIndex][editMidiChannelIndex].programChange++;
                else subBank[editPatchIndex][editMidiChannelIndex].programChange = 0;
            }
            break;
        case Edit::controlChangeIndex:
            if(editControlChangeIndex < max_controlChangeCount - 1) editControlChangeIndex++;
            else editControlChangeIndex = 0;
            break;
        case Edit::controlChangeNumber:
            if(editIsMain)
            {
                if(mainBank[editPatchIndex][editMidiChannelIndex].controlChangeNumber[editControlChangeIndex] < max_controlChangeNumber) mainBank[editPatchIndex][editMidiChannelIndex].controlChangeNumber[editControlChangeIndex]++;
                else mainBank[editPatchIndex][editMidiChannelIndex].controlChangeNumber[editControlChangeIndex] = 0;
            }
            else
            {
                if(subBank[editPatchIndex][editMidiChannelIndex].controlChangeNumber[editControlChangeIndex] < max_controlChangeNumber) subBank[editPatchIndex][editMidiChannelIndex].controlChangeNumber[editControlChangeIndex]++;
                else subBank[editPatchIndex][editMidiChannelIndex].controlChangeNumber[editControlChangeIndex] = 0;
            }
            break;
        case Edit::controlChangeValue:
            if(editIsMain)
            {
                if(mainBank[editPatchIndex][editMidiChannelIndex].controlChangeValue[editControlChangeIndex] < max_controlChangeValue) mainBank[editPatchIndex][editMidiChannelIndex].controlChangeValue[editControlChangeIndex]++;
                else mainBank[editPatchIndex][editMidiChannelIndex].controlChangeValue[editControlChangeIndex] = 0;
            }
            else
            {
                if(subBank[editPatchIndex][editMidiChannelIndex].controlChangeValue[editControlChangeIndex] < max_controlChangeValue) subBank[editPatchIndex][editMidiChannelIndex].controlChangeValue[editControlChangeIndex]++;
                else subBank[editPatchIndex][editMidiChannelIndex].controlChangeValue[editControlChangeIndex] = 0;
            }
            break;
        default:
            break;
    }
}
void decreaseEditIndex()
{
    switch(currentEdit)
    {
        case Edit::bank:
            saveBank(currentBankIndex);
            if(currentBankIndex > 0) currentBankIndex--;
            else currentBankIndex = activeBankCount - 1;
            loadBank(currentBankIndex);
            editPatchIndex = 0;
            editMidiChannelIndex = 0;
            editControlChangeIndex = 0;
            editIsMain = true;
            break;
        case Edit::patch:
            if(editPatchIndex > 0) editPatchIndex--;
            else editPatchIndex = max_patchSelectionSwitchCount - 1;
            editMidiChannelIndex = 0;
            editControlChangeIndex = 0;
            editIsMain = true;
            break;
        case Edit::mainSub:
            if(editIsMain) editIsMain = false;
            else editIsMain = true;
            editMidiChannelIndex = 0;
            editControlChangeIndex = 0;
            break;
        case Edit::channel:
            if(editMidiChannelIndex > 0) editMidiChannelIndex--;
            else editMidiChannelIndex = max_midiChannel - 1;
            editControlChangeIndex = 0;
            break;
        case Edit::onOff:
            if(editIsMain)
            {
                if(mainBank[editPatchIndex][editMidiChannelIndex].enabled) mainBank[editPatchIndex][editMidiChannelIndex].enabled = false;
                else mainBank[editPatchIndex][editMidiChannelIndex].enabled = true;
            }
            else
            {
                if(subBank[editPatchIndex][editMidiChannelIndex].enabled) subBank[editPatchIndex][editMidiChannelIndex].enabled = false;
                else subBank[editPatchIndex][editMidiChannelIndex].enabled = true;
            }
            break;
        case Edit::programChange:
            if(editIsMain)
            {
                if(mainBank[editPatchIndex][editMidiChannelIndex].programChange > 0) mainBank[editPatchIndex][editMidiChannelIndex].programChange--;
                else mainBank[editPatchIndex][editMidiChannelIndex].programChange = max_programChange;
            }
            else
            {
                if(subBank[editPatchIndex][editMidiChannelIndex].programChange > 0) subBank[editPatchIndex][editMidiChannelIndex].programChange--;
                else subBank[editPatchIndex][editMidiChannelIndex].programChange = max_programChange;
            }
            break;
        case Edit::controlChangeIndex:
            if(editControlChangeIndex > 0) editControlChangeIndex--;
            else editControlChangeIndex = max_controlChangeCount - 1;
            break;
        case Edit::controlChangeNumber:
            if(editIsMain)
            {
                if(mainBank[editPatchIndex][editMidiChannelIndex].controlChangeNumber[editControlChangeIndex] > 0) mainBank[editPatchIndex][editMidiChannelIndex].controlChangeNumber[editControlChangeIndex]--;
                else mainBank[editPatchIndex][editMidiChannelIndex].controlChangeNumber[editControlChangeIndex] = max_controlChangeNumber;
            }
            else
            {
                if(subBank[editPatchIndex][editMidiChannelIndex].controlChangeNumber[editControlChangeIndex] > 0) subBank[editPatchIndex][editMidiChannelIndex].controlChangeNumber[editControlChangeIndex]--;
                else subBank[editPatchIndex][editMidiChannelIndex].controlChangeNumber[editControlChangeIndex] = max_controlChangeNumber;
            }
            break;
        case Edit::controlChangeValue:
            if(editIsMain)
            {
                if(mainBank[editPatchIndex][editMidiChannelIndex].controlChangeValue[editControlChangeIndex] > 0) mainBank[editPatchIndex][editMidiChannelIndex].controlChangeValue[editControlChangeIndex]--;
                else mainBank[editPatchIndex][editMidiChannelIndex].controlChangeValue[editControlChangeIndex] = max_controlChangeValue;
            }
            else
            {
                if(subBank[editPatchIndex][editMidiChannelIndex].controlChangeValue[editControlChangeIndex] > 0) subBank[editPatchIndex][editMidiChannelIndex].controlChangeValue[editControlChangeIndex]--;
                else subBank[editPatchIndex][editMidiChannelIndex].controlChangeValue[editControlChangeIndex] = max_controlChangeValue;
            }
            break;
        default:
            break;
    }
}
void showEditTarget()
{
    display.clear();
    switch(currentEdit)
    {
        case Edit::bank:
            display.setSegments(display_bank);
            display.showNumberDec(currentBankIndex + 1, false, calcDigit(currentBankIndex + 1), 2);
            break;
        case Edit::patch:
            display.setSegments(display_patch);
            display.showNumberDec(editPatchIndex + 1, false, 1, 2);
            break;
        case Edit::mainSub:
            if(editIsMain) display.setSegments(display_main);
            else display.setSegments(display_sub);
            break;
        case Edit::channel:
            display.setSegments(display_channel);
            display.showNumberDec(editMidiChannelIndex + 1, false, calcDigit(editMidiChannelIndex + 1), 2);
            break;
        case Edit::onOff:
            if(editIsMain)
            {
                if(mainBank[editPatchIndex][editMidiChannelIndex].enabled) display.setSegments(display_on);
                else display.setSegments(display_off);
            }
            else
            {
                if(subBank[editPatchIndex][editMidiChannelIndex].enabled) display.setSegments(display_on);
                else display.setSegments(display_off);
            }
            break;
        case Edit::programChange:
            display.setSegments(display_programChange);
            if(editIsMain)
            {
                display.showNumberDec(mainBank[editPatchIndex][editMidiChannelIndex].programChange, true, 3, 1);
            }
            else
            {
                display.showNumberDec(subBank[editPatchIndex][editMidiChannelIndex].programChange, true, 3, 1);
            }
            break;
        case Edit::controlChangeIndex:
            display.setSegments(display_controlChangeIndex);
            display.showNumberDec(editControlChangeIndex + 1, false, calcDigit(editControlChangeIndex + 1), 2);
            break;
        case Edit::controlChangeNumber:
            display.setSegments(display_controlChangeNumber);
            if(editIsMain)
            {
                display.showNumberDec(mainBank[editPatchIndex][editMidiChannelIndex].controlChangeNumber[editControlChangeIndex], true, 3, 1);
            }
            else
            {
                display.showNumberDec(subBank[editPatchIndex][editMidiChannelIndex].controlChangeNumber[editControlChangeIndex], true, 3, 1);
            }
            break;
        case Edit::controlChangeValue:
            display.setSegments(display_controlChangeValue);
            if(editIsMain)
            {
                display.showNumberDec(mainBank[editPatchIndex][editMidiChannelIndex].controlChangeValue[editControlChangeIndex], true, 3, 1);
            }
            else
            {
                display.showNumberDec(subBank[editPatchIndex][editMidiChannelIndex].controlChangeValue[editControlChangeIndex], true, 3, 1);
            }
            break;
        default:
            break;
    }
}

#endif