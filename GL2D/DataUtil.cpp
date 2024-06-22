#include"DataUtil.h"
#include <regex>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <deque>

#define USE_CUSTOM_PATH

// game version
#define VERSION 2
constexpr const char* FolderName = "MyData";
constexpr const char* FileName = "Data.txt";


#ifndef USE_CUSTOM_PATH
// data file path
//C://user//user name//FolderName//FileName
std::filesystem::path FolderPath = std::filesystem::path(getenv("USERPROFILE")) / FolderName;
std::filesystem::path FilePath = FolderPath / FileName;
#endif

#ifdef USE_CUSTOM_PATH
// custom data file path
std::filesystem::path FolderPath = FolderName;
std::filesystem::path FilePath = FolderPath / FileName;
#endif

// list of strings to use when finding data
// there must be a one space in the middle of the string
// ex: (x)"ExampleData", (x)"ExampleData ", (x)" ExampleData", (o)"Example Data"
std::deque<std::string> DataList = 
{

};


void DataUtil::Init() {
	bool NewCreateState{};

	DataList.push_front(DataVersionStr);

	if (!std::filesystem::exists(FolderPath)) {
		NewCreateState = true;

		if (!std::filesystem::create_directory(FolderPath))
			exit(EXIT_FAILURE);
	}

	if (NewCreateState) {
		for (auto& D : DataList) {
			std::string Data = D;

			Data.insert(Data.begin(), '[');
			Data.insert(Data.end(), ']');
			Data.insert(Data.end(), '=');

			RegexDataList.push_back(Data);
		}

		std::ofstream OutFile(FilePath);
		if (OutFile.is_open())
			for (auto& D : RegexDataList)
				OutFile << D << 0 << std::endl;
		else  
			exit(EXIT_FAILURE);

		WriteData(DataVersionStr, VERSION);
	}

	CheckDataVersion();
}

void DataUtil::CheckDataVersion() {
	if (VERSION <= LoadData(DataVersionStr))
		return;

	for (auto& D : DataList) {
		std::string Data = D;

		Data.insert(Data.begin(), '[');
		Data.insert(Data.end(), ']');
		Data.insert(Data.end(), '=');

		RegexDataList.push_back(Data);
	}

	std::vector<int> BackUpDataList{};

	for (auto& D : DataList)
		BackUpDataList.push_back(LoadData(D));

	if (!std::filesystem::exists(FolderPath))
		exit(EXIT_FAILURE);

	std::ifstream InFile(FilePath);
	if (!InFile)
		exit(EXIT_FAILURE);

	std::string Line{};
	while (std::getline(InFile, Line)) {
		size_t Position = Line.find('=');

		if (Position != std::string::npos)
			std::string str = Line.substr(0, Position);
	}

	InFile.close();

	std::ofstream OutFile(FilePath);
	if (!OutFile)
		exit(EXIT_FAILURE);

	for (const auto& D : RegexDataList)
		OutFile << D << "0\n";

	OutFile.close();

	for (int i = 0; i < DataList.size(); ++i)
		WriteData(DataList[i], BackUpDataList[i]);
	
	WriteData(DataVersionStr, VERSION);
}

void DataUtil::ResetData() {
	if (!std::filesystem::exists(FolderPath))
		exit(EXIT_FAILURE);

	std::ifstream InFile(FilePath);
	if (!InFile)
		exit(EXIT_FAILURE);

	std::string Line{};
	while (std::getline(InFile, Line)) {
		size_t Position = Line.find('=');
		if (Position != std::string::npos)
			std::string str = Line.substr(0, Position);
	}

	InFile.close();

	std::ofstream OutFile(FilePath);
	if (!OutFile)
		exit(EXIT_FAILURE);

	for (const auto& D : RegexDataList)
		OutFile << D << "0\n";

	OutFile.close();

	WriteData("VersionData", VERSION);
}

void DataUtil::WriteData(const std::string& DataName, int DataValue) {
	auto It = std::find(DataList.begin(), DataList.end(), DataName);
	if (It == DataList.end())  
		exit(EXIT_FAILURE);

	if (!std::filesystem::exists(FolderPath))
		exit(EXIT_FAILURE);

	std::ifstream InFIle(FilePath);
	if (!InFIle)  
		exit(EXIT_FAILURE);

	std::string FileContent;

	if (InFIle) {
		FileContent = std::string((std::istreambuf_iterator<char>(InFIle)), std::istreambuf_iterator<char>());
		InFIle.close();
	}

	bool KeyFind = false;

	std::regex Pattern(R"(\[([\w\s]+)\]=(\d+))");
	std::smatch Match;
	std::string NewContent = FileContent;

	while (std::regex_search(FileContent, Match, Pattern)) {
		std::string Var = Match[1];
		std::string Value = Match[2];
		int CurrentValue = std::stoi(Value);

		if (Var == DataName) {
			std::string ReplaceStr = "[" + DataName + "]=" + std::to_string(DataValue);
			NewContent = std::regex_replace(NewContent, std::regex("\\[" + DataName + "\\]=" + Value), ReplaceStr);
			KeyFind = true;

			break;
		}

		FileContent = Match.suffix();
	}

	std::ofstream OutFile(FilePath);
	OutFile << NewContent;

	OutFile.close();
}

int DataUtil::LoadData(std::string DataName) {
	auto It = std::find(DataList.begin(), DataList.end(), DataName);
	if (It == DataList.end())  
		exit(EXIT_FAILURE);

	if (!std::filesystem::exists(FolderPath))
		exit(EXIT_FAILURE);
		
	std::ifstream InFIle(FilePath);
	if (!InFIle) 
		exit(EXIT_FAILURE);

	int DataGet{};

	std::string Line;
	std::regex Pattern(R"(\[(\w+\s+\w+)\]=(\d+))");

	while (std::getline(InFIle, Line)) {
		std::smatch Match;

		if (std::regex_search(Line, Match, Pattern)) {
			std::string Var = Match[1];
			std::string Value = Match[2];

			if (Var == DataName) {
				DataGet = stoi(Value);
				break;
			}
		}
	}

	InFIle.close();

	return DataGet;
}