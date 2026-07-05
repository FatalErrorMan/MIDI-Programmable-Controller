// ==================================================
// プリプロセッサ
// ==================================================
#ifndef GLOBAL_ENUM
#define GLOBAL_ENUM

// ==================================================
// 列挙型
// ==================================================
// モード
enum class Mode
{
    play,
    program,
    programBypass,
    changeActiveBankCount,
    changeBrightness,
    recieve
};
// パッチ選択の状態
enum class PatchState
{
    bypass,
    main,
    sub
};
// エディット中の要素
enum class Edit
{
    bank,
    patch,
    mainSub,
    channel,
    onOff,
    programChange,
    controlChangeIndex,
    controlChangeNumber,
    controlChangeValue
};

#endif
