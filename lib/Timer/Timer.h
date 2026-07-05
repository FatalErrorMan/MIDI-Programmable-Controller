// 2026.3.21 ver.1.0.2
// Timer Library
// setup()内で初期化できるようにするためにinitialize()を追加。
// 空のコンストラクタを追加。

// ==================================================
// プリプロセッサ
// ==================================================
#ifndef TIMER
#define TIMER

// ==================================================
// クラス
// ==================================================
class Timer {
    public:
        // ----------------------------------------
        // 関数ポインタの型定義
        // ----------------------------------------
        typedef void (* pFunc)(void);
        
        // ----------------------------------------
        // コンストラクタ
        // ----------------------------------------
        Timer() {}
        Timer(unsigned long clock) {
          baseClock = millis();
          this->clock = clock;
        }
        Timer(unsigned long clock, pFunc callback) {
          baseClock = millis();
          this->clock = clock;
          this->callback = callback;
        }

        // ----------------------------------------
        //メソッド
        // ----------------------------------------
        // 初期化
        void initialize(unsigned long clock) {
          baseClock = millis();
          this->clock = clock;
        }
        void initialize(unsigned long clock, pFunc callback) {
          baseClock = millis();
          this->clock = clock;
          this->callback = callback;
        }
        // クロックの登録
        void setClock(unsigned long clock) {
            this->clock = clock;
        }
        // コールバック関数の登録
        void setCallback(pFunc callback) {
            this->callback = callback;
        }
        // クロックチェックとタスクの実行
        void execute() {
            //現在のクロックと基準クロックの差が目標クロック差以上ならタスクを実行
            if (millis() - baseClock >= clock) {
                callback();
                reset();
            }
        }
        // クロックチェックとタスクの実行(クロックリセットなし)
        void executeWithoutReset() {
            if (millis() - baseClock >= clock) callback();
        }
        // 基準クロックのリセット
        void reset() {
            baseClock = millis();
        }

    private:
        // ----------------------------------------
        // プロパティ
        // ----------------------------------------
        unsigned long baseClock;
        unsigned long clock;
        pFunc callback;
};
#endif