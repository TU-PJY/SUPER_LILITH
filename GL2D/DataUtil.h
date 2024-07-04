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
	void WriteData(const std::string& DataName, int value);
	int LoadData(std::string DataName);
};
extern DataUtil dataUtil;