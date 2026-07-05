// 2026.3.21 ver.1.0.1
// MomentarySwitch V2 Library
// setup()内で初期化できるようにするためにinitialize()を追加。
// byteをuint8_tに変更。

// ==================================================
// プリプロセッサ
// ==================================================
#ifndef MOMENTARY_SWITCH_V2
#define MOMENTARY_SWITCH_V2

// ==================================================
// クラス
// ==================================================
class MomentarySwitchV2
{
    public:
        // ----------------------------------------
        // コンストラクタ
        // ----------------------------------------
        // 配列宣言用
        MomentarySwitchV2() { }
        // 通常
        MomentarySwitchV2(uint8_t pin, unsigned long holdWaitTime = 1000) {
            this->pin = pin;
            this->holdWaitTime = holdWaitTime;
            pinMode(pin, INPUT_PULLUP);
        }
        
        // ----------------------------------------
        // 列挙型
        // ----------------------------------------
        enum class Status {
            none,
            press,
            hold
        };
        
        // ----------------------------------------
        // メソッド
        // ----------------------------------------
        // 初期化
        void initialize(uint8_t pin, unsigned long holdWaitTime = 1000) {
            this->pin = pin;
            this->holdWaitTime = holdWaitTime;
            pinMode(pin, INPUT_PULLUP);
        }
        // スイッチの状態を判定
        Status check() {
            // 押されていないときはnoneを返す
            if(digitalRead(pin) == HIGH) {
                // 直前までホールドされていたときにはホールドフラグを解除
                if(holdStarting) {
                    holdContinued = false;
                    holdStarting = false;
                }
                return Status::none;
            }
            
            // ホールド継続していればholdを返す
            if(holdContinued) return Status::hold;
            
            // ホールド開始直後ならホールド継続判定を真にしてholdを返す
            if(holdStarting) {
                holdContinued = true;
                return Status::hold;
            }
            
            // 押されたときはループに入ってリリース/またはホールド待機時間まで待つ
            // つまり押されている間は処理を占有する
            nowClock = millis();
            while(millis() - nowClock < holdWaitTime) {
                if(digitalRead(pin) == HIGH) return Status::press;
            }
            holdStarting = true;
            return Status::hold;
        }
        // ホールド中かどうかを確認
        bool isHolding() {
            return holdContinued;
        }
        
        
    private:
        // ----------------------------------------
        // プロパティ
        // ----------------------------------------
        uint8_t pin;
        bool holdContinued = false;
        bool holdStarting = false;
        unsigned long holdWaitTime;
        unsigned long nowClock;
};
#endif