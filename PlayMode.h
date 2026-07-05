// ==================================================
// プリプロセッサ
// ==================================================
#ifndef PLAY_MODE
#define PLAY_MODE

// ==================================================
// 前方宣言
// ==================================================
void increaseBank(void);
void decreaseBank(void);
void showBank(void);
bool increasePatch(void);
bool decreasePatch(void);
void selectPatch_press(void);
void selectPatch_hold(void);
void resetAllStatus(void);

// ==================================================
// プレイモード
// ==================================================
void playMode()
{
    // モード変更メッセージ表示
    display.setSegments(display_playMode);
    delay(time_waitDisplay);
    display.clear();
    delay(time_waitClear);
    resetAllStatus();
    loadBank(currentBankIndex);
    
    // モードループ
    while(true)
    {
        // モード変更スイッチの処理
        status_modeChangeSwitch = modeChangeSwitch.check();
        switch(status_modeChangeSwitch)
        {
            case MomentarySwitchV2::Status::press:
                currentMode = Mode::recieve;
                return;
            case MomentarySwitchV2::Status::hold:
                if(modeChangeSwitch.isHolding()) break;
                currentMode = Mode::program;
                return; 
            default:
                break;
        }
        
        // バンク選択スイッチの処理
        status_bankSelectionSwitch = bankSelectionSwitch.check();
        switch(status_bankSelectionSwitch)
        {
            case MomentarySwitchV2::Status::press:
                increaseBank();
                loadBank(currentBankIndex);
                showBank();
                patchState[currentPatchIndex] = PatchState::bypass;
                break;
            case MomentarySwitchV2::Status::hold:
                if(bankSelectionSwitch.isHolding()) break;
                decreaseBank();
                loadBank(currentBankIndex);
                showBank();
                patchState[currentPatchIndex] = PatchState::bypass;
                break;
            default:
                break;
        }

        // パッチ選択スイッチの処理
        for(int i = 0; i < max_patchSelectionSwitchCount; i++)
        {
            status_patchSelectionSwitch[i] = patchSelectionSwitch[i].check();
            switch(status_patchSelectionSwitch[i])
            {
                case MomentarySwitchV2::Status::press:
                    currentPatchIndex = i;
                    display.clear();
                    selectPatch_press();
                    break;
                case MomentarySwitchV2::Status::hold:
                    if(patchSelectionSwitch[i].isHolding()) break;
                    currentPatchIndex = i;
                    display.clear();
                    selectPatch_hold();
                    break;
                default:
                    break;
            }
        }

        // 上下スイッチの処理
        status_upSwitch = upSwitch.check();
        switch(status_upSwitch)
        {
            case MomentarySwitchV2::Status::press:
                increaseBank();
                loadBank(currentBankIndex);
                showBank();
                patchState[currentPatchIndex] = PatchState::bypass;
                break;
            default:
                break;
        }
        status_downSwitch = downSwitch.check();
        switch(status_downSwitch)
        {
            case MomentarySwitchV2::Status::press:
                decreaseBank();
                loadBank(currentBankIndex);
                showBank();
                patchState[currentPatchIndex] = PatchState::bypass;
                break;
            default:
                break;
        }

        // 左右スイッチの処理
        status_leftSwitch = leftSwitch.check();
        switch(status_leftSwitch)
        {
            case MomentarySwitchV2::Status::press:
                if(decreasePatch())
                {
                    display.clear();
                    selectPatch_press();
                }
                else resetAllStatus();
                break;
            case MomentarySwitchV2::Status::hold:
                if(leftSwitch.isHolding()) break;
                display.clear();
                selectPatch_press();
                break;
            default:
                break;
        }
        status_rightSwitch = rightSwitch.check();
        switch(status_rightSwitch)
        {
            case MomentarySwitchV2::Status::press:
                if(increasePatch())
                {
                    display.clear();
                    selectPatch_press();
                }
                else resetAllStatus();
                break;
            case MomentarySwitchV2::Status::hold:
                if(rightSwitch.isHolding()) break;
                display.clear();
                selectPatch_press();
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
void increaseBank()
{
    if(currentBankIndex < activeBankCount - 1) currentBankIndex++;
    else currentBankIndex = 0;
}
void decreaseBank()
{
    if(currentBankIndex > 0) currentBankIndex--;
    else currentBankIndex = activeBankCount - 1;
}
void showBank()
{
    display.setSegments(display_bank);
    display.showNumberDec(currentBankIndex + 1, false, calcDigit(currentBankIndex + 1), 2);
    delay(time_waitDisplay);
    display.clear();
}
bool increasePatch()
{
    if(currentPatchIndex < max_patchSelectionSwitchCount - 1) { currentPatchIndex++; return true; }
    else return false;
}
bool decreasePatch()
{
    if(currentPatchIndex > 0) { currentPatchIndex--; return true; }
    else return false;
}
void selectPatch_press()
{
    switch (patchState[currentPatchIndex])
    {
        case PatchState::main:
            // サブパッチ送信
            for(int i = 0; i < max_midiChannel; i++)
            {
                if(!subBank[currentPatchIndex][i].enabled) continue;
                midi1.sendProgramChange(subBank[currentPatchIndex][i].programChange, i + 1);
                for(int j = 0; j < max_controlChangeCount; j++)
                {
                    midi1.sendControlChange(subBank[currentPatchIndex][i].controlChangeNumber[j], subBank[currentPatchIndex][i].controlChangeValue[j], i + 1);
                }                
            }
            for(int i = 0; i < max_patchSelectionSwitchCount; i++)
            {
                if(i != currentPatchIndex) patchState[i] = PatchState::bypass;
                else patchState[i] = PatchState::sub;
            }
            display.setSegments(display_subPatch);
            display.showNumberDec(currentPatchIndex + 1, false, 1, 2);
            break;
        case PatchState::bypass:
        case PatchState::sub:
            // メインパッチ送信
            for(int i = 0; i < max_midiChannel; i++)
            {
                if(!mainBank[currentPatchIndex][i].enabled) continue;
                midi1.sendProgramChange(mainBank[currentPatchIndex][i].programChange, i + 1);
                for(int j = 0; j < max_controlChangeCount; j++)
                {
                    midi1.sendControlChange(mainBank[currentPatchIndex][i].controlChangeNumber[j], mainBank[currentPatchIndex][i].controlChangeValue[j], i + 1);
                }
            }
            for(int i = 0; i < max_patchSelectionSwitchCount; i++)
            {
                if(i != currentPatchIndex) patchState[i] = PatchState::bypass;
                else patchState[i] = PatchState::main;
            }
            display.setSegments(display_mainPatch);
            display.showNumberDec(currentPatchIndex + 1, false, 1, 2);
            break;
        default:
            break;
    }
}
void selectPatch_hold()
{
    switch (patchState[currentPatchIndex])
    {
        case PatchState::main:
        case PatchState::sub:
            // オフ(バイパスパッチ送信)
            for(int i = 0; i < max_midiChannel; i++)
            {
                if(!bypassBank[i].enabled) continue;
                midi1.sendProgramChange(bypassBank[i].programChange, i + 1);
                for(int j = 0; j < max_controlChangeCount; j++)
                {
                    midi1.sendControlChange(bypassBank[i].controlChangeNumber[j], bypassBank[i].controlChangeValue[j], i + 1);
                }
            }
            patchState[currentPatchIndex] = PatchState::bypass;
            display.setSegments(display_bypass);
            break;
        case PatchState::bypass:
            // サブパッチ送信
            for(int i = 0; i < max_midiChannel; i++)
            {
                if(!subBank[currentPatchIndex][i].enabled) continue;
                midi1.sendProgramChange(subBank[currentPatchIndex][i].programChange, i + 1);
                for(int j = 0; j < max_controlChangeCount; j++)
                {
                    midi1.sendControlChange(subBank[currentPatchIndex][i].controlChangeNumber[j], subBank[currentPatchIndex][i].controlChangeValue[j], i + 1);
                }                
            }
            for(int i = 0; i < max_patchSelectionSwitchCount; i++)
            {
                if(i != currentPatchIndex) patchState[i] = PatchState::bypass;
                else patchState[i] = PatchState::sub;
            }
            display.setSegments(display_subPatch);
            display.showNumberDec(currentPatchIndex + 1, false, 1, 2);
            break;
        default:
            break;
    }
}
void resetAllStatus()
{
    for(int i = 0; i < max_patchSelectionSwitchCount; i++) patchState[i] = PatchState::bypass;
    for(int i = 0; i < max_midiChannel; i++)
    {
        if(!bypassBank[i].enabled) continue;
        midi1.sendProgramChange(bypassBank[i].programChange, i + 1);
        for(int j = 0; j < max_controlChangeCount; j++)
        {
            midi1.sendControlChange(bypassBank[i].controlChangeNumber[j], bypassBank[i].controlChangeValue[j], i + 1);
        }
    }
    display.setSegments(display_bypass);
}

#endif