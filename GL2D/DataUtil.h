#pragma once
#include <vector>
#include <string>

class DataUtil {
private:
	std::vector<std::string> RegexDataList;
	std::string DataVersionStr{ "Data Version" };

public:
	void Init();
	void CheckDataVersion();
	void ResetData();
	void WriteData(const std::string& target, int value);
	int LoadData(std::string target);
};
extern DataUtil dataUtil;