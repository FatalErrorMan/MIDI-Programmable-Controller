// ==================================================
// プリプロセッサ
// ==================================================
#ifndef MIDI_MESSAGE
#define MIDI_MESSAGE

// ==================================================
// MIDIメッセージクラス
// ==================================================
class MidiMessage
{
    public:
        // ----------------------------------------
        // コンストラクタ
        // ----------------------------------------
        // 配列宣言用
        MidiMessage() { }
        // 通常
        MidiMessage(byte programChange, byte controlChangeNumber, byte controlChangeValue)
        {
            this->programChange = programChange;
            for(int i = 0; i < max_controlChangeCount; i++)
            {
                this->controlChangeNumber[i] = controlChangeNumber;
                this->controlChangeValue[i] = controlChangeValue;
            }
        }

        // ----------------------------------------
        // プロパティ
        // ----------------------------------------
        bool enabled = false;
        byte programChange = 0;
        byte controlChangeNumber[max_controlChangeCount];
        byte controlChangeValue[max_controlChangeCount];
};

#endif