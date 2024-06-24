#include "FontLoaderUtil.h"
#include <iostream>

std::wstring FontLoaderUtil::ToWstr(const std::string& str) {
    int SizeNeed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring Wstr(SizeNeed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &Wstr[0], SizeNeed);

    return Wstr;
}

bool FontLoaderUtil::ImportFont(const std::string& FontFilePath, DWORD& NumFonts) {
    std::wstring Path = ToWstr(FontFilePath);

    NumFonts = AddFontResourceEx(Path.c_str(), FR_PRIVATE, 0);

    if (NumFonts == 0) {
        std::cout << "Failed to load font from file." << std::endl;
        return false;
    }

    SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);

    return true;
}
