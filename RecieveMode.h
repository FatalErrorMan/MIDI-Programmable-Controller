// ==================================================
// プリプロセッサ
// ==================================================
#ifndef RECIEVE_MODE
#define RECIEVE_MODE

// ==================================================
// 前方宣言
// ==================================================
void executeRecieving(void);
char readSerialWait(void);
void toggleDisplayProgressMessage(void);

// ==================================================
// バンクデータ受信モード
// ==================================================
void recieveMode()
{
    // モード変更メッセージ表示
    display.setSegments(display_recieveMode);

    // モードループ
    while(true)
    {
        // モード変更スイッチの処理
        status_modeChangeSwitch = modeChangeSwitch.check();
        switch(status_modeChangeSwitch)
        {
            case MomentarySwitchV2::Status::press:
                currentMode = Mode::play;
                return;
            case MomentarySwitchV2::Status::hold:
                if(modeChangeSwitch.isHolding()) break;
                delay(time_checkInterval);
                executeRecieving();
                return;
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
// 受信の実行
void executeRecieving()
{
    // 処理中画面表示用タイマーの登録
    timer_blinkProgressDisplay.setCallback(toggleDisplayProgressMessage);
    display.setSegments(display_progressWait);
    // 送信開始フラグのチェック
    while((serialBuffer = readSerialWait()) != flag_start)
    {
        if(serialBuffer == flag_end) goto done;
    }

    // --------------------------------------------------
    // 送信内容を受信して現在のバンクデータを上書き
    // (終了フラグがあればその時点で受信終了)
    // --------------------------------------------------
    // バイパスバンク
    for(int i = 0; i < max_midiChannel; i++)
    {
        // 処理中メッセージの表示
        timer_blinkProgressDisplay.execute();
        // ON/OFF
        if((serialBuffer = readSerialWait()) == flag_end) goto done;
        bypassBank[i].enabled = serialBuffer;
        // プログラムチェンジ
        if((serialBuffer = readSerialWait()) == flag_end) goto done;
        bypassBank[i].programChange = serialBuffer;
        // コントロールチェンジ
        for(int j = 0; j < max_controlChangeCount; j++)
        {
            if((serialBuffer = readSerialWait()) == flag_end) goto done;
            bypassBank[i].controlChangeNumber[j] = serialBuffer;
            if((serialBuffer = readSerialWait()) == flag_end) goto done;
            bypassBank[i].controlChangeValue[j] = serialBuffer;
        }
    }
    saveBypassBank();
    // ノーマルバンク
    for(int i = 0; i < max_bankCount; i++)
    {
        for(int j = 0; j < max_patchSelectionSwitchCount; j++)
        {
            for(int k = 0; k < max_midiChannel; k++)
            {
                // 処理中メッセージの表示
                timer_blinkProgressDisplay.execute();
                // ON/OFF
                if((serialBuffer = readSerialWait()) == flag_end) goto done;
                mainBank[j][k].enabled = serialBuffer;
                if((serialBuffer = readSerialWait()) == flag_end) goto done;
                subBank[j][k].enabled = serialBuffer;
                // プログラムチェンジ
                if((serialBuffer = readSerialWait()) == flag_end) goto done;
                mainBank[j][k].programChange = serialBuffer;
                if((serialBuffer = readSerialWait()) == flag_end) goto done;
                subBank[j][k].programChange = serialBuffer;
                // コントロールチェンジ
                for(int l = 0; l < max_controlChangeCount; l++)
                {
                    if((serialBuffer = readSerialWait()) == flag_end) goto done;
                    mainBank[j][k].controlChangeNumber[l] = serialBuffer;
                    if((serialBuffer = readSerialWait()) == flag_end) goto done;
                    subBank[j][k].controlChangeNumber[l] = serialBuffer;
                    if((serialBuffer = readSerialWait()) == flag_end) goto done;
                    mainBank[j][k].controlChangeValue[l] = serialBuffer;
                    if((serialBuffer = readSerialWait()) == flag_end) goto done;
                    subBank[j][k].controlChangeValue[l] = serialBuffer;
                }
            }
        }
        saveBank(i);
    }
    // 終了メッセージの表示
    done:
    display.setSegments(display_done);
    delay(time_waitDisplay);
}

// 入力があるまで読み込み待ちする
char readSerialWait()
{
    while(true)
    {
        // シリアルポートに入力がある場合１文字読み込む
        if(Serial.available())
        {
            return Serial.read();
        }
        // ループ防止用緊急終了措置
        status_modeChangeSwitch = modeChangeSwitch.check();
        switch(status_modeChangeSwitch)
        {
            case MomentarySwitchV2::Status::hold:
                // 読み込み終了フラグを強制送信
                if(modeChangeSwitch.isHolding()) break;
                return flag_end;
            default:
                break;
        }
        // シリアルポートの入力がない場合の再確認待ち時間
        delay(time_checkSerialData);
    }
}

// 処理中メッセージの表示/非表示切り替え
void toggleDisplayProgressMessage()
{
    toggleDisplayStatus = !toggleDisplayStatus;
    if(toggleDisplayStatus) display.setSegments(display_progressFirst);
    else display.setSegments(display_progressSecond);
}

#endif