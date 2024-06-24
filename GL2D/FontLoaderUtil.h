#pragma once
#include <windows.h>
#include <string>

class FontLoaderUtil{
public:
	bool ImportFont(const std::string& fontFilePath, DWORD& numFonts);

private:
	std::wstring ToWstr(const std::string& str);
};
extern FontLoaderUtil fontloaderUtil;
