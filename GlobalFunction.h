// ==================================================
// プリプロセッサ
// ==================================================
#ifndef GLOBAL_FUNCTION
#define GLOBAL_FUNCTION

// ==================================================
// 処理
// ==================================================
// 桁数計算
byte calcDigit(int target)
{
    byte digit = 0;
    do
    {
        target = target / 10;
        digit++;
    } 
    while(target != 0);
    return digit;
}

#endif
