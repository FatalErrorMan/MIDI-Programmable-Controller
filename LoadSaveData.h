// ==================================================
// プリプロセッサ
// ==================================================
#ifndef LOAD_SAVE_DATA
#define LOAD_SAVE_DATA

// ==================================================
// 各種データの読み込み/保存
// ==================================================
void saveBrightness()
{
    EEPROM.put(address_brightness, currentBrightness);
}
void saveActiveBankCount()
{
    EEPROM.put(address_activeBankCount, activeBankCount);
}
void saveBypassBank()
{
    EEPROM.put(address_bypassBank, bypassBank);
}
void saveBank(byte currentBankIndex)
{
    EEPROM.put(address_mainBank + size_bank * currentBankIndex, mainBank);
    EEPROM.put(address_subBank + size_bank * currentBankIndex, subBank);
}
void loadAllData()
{
    EEPROM.get(address_brightness, currentBrightness);
    EEPROM.get(address_activeBankCount, activeBankCount);
    EEPROM.get(address_bypassBank, bypassBank);
    EEPROM.get(address_mainBank, mainBank);  // 各パッチはバンク1を読み込む
    EEPROM.get(address_subBank, subBank);
}
void loadBank(byte currentBankIndex)
{
    EEPROM.get(address_mainBank + size_bank * currentBankIndex, mainBank);
    EEPROM.get(address_subBank + size_bank * currentBankIndex, subBank);
}

#endif