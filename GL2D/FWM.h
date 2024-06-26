// FWM Version 3
#pragma once
#include "FWM_Log.h"
#include "ObjectBase.h"
#include <array>
#include <deque>
#include <ranges>
#include <algorithm>
#include <map>


typedef std::string(*Function)(void);
typedef void(*ControllerFunction)(void);
constexpr int Num = static_cast<int>(Layer::END);

enum class DeleteRange
{One, All};

enum class SearchRange
{One, All};


class FWM {
private:
	std::array<std::deque<OBJ_BASE*>, Num> Container;
	std::multimap<std::string, OBJ_BASE*> ObjectList;

	std::string						  RunningMode{};
	std::string                       PrevRunningMode{};

	bool							  RunningState{};
	bool							  ModeSwitchState{};

	bool							  FloatingModeRunningState{};
	bool                              FloatingOnlyState{};

	bool							  ModeSwitchReserveDescriptor{};
	bool                              FloatingModeReserveDescriptor{};
	bool                              FloatingModeEndReserveDescriptor{};

	float							  FrameTime{};

	Function						  ModeFunctionBuffer{};
	ControllerFunction				  ControllerBuffer{};
	ControllerFunction				  ControllerBackUpBuffer{};

public:
	FWM();
	std::string Mode();
	void Init(Function ModeFunction, ControllerFunction Controller=nullptr);
	void SetFrameTime(float ElapsedTime);
	void Routine();
	void SwitchMode(Function ModeFunction, ControllerFunction Controller=nullptr);
	void StartFloatingMode(Function ModeFunction, ControllerFunction Controller=nullptr, bool FloatingOnlyOption=false);
	void EndFloatingMode();
	void ResetControlState(OBJ_BASE* Object);
	void AddObject(OBJ_BASE* Object, std::string Tag, Layer AddLayer, bool SetFloatingObject=false);
	void SwapLayer(OBJ_BASE* Object, Layer From, Layer To);
	void DeleteSelf(OBJ_BASE* Object);
	void DeleteObject(std::string Tag, DeleteRange deleteRange);
	OBJ_BASE* Find(std::string Tag);
	OBJ_BASE* Find(std::string Tag, Layer LayerToSearch, int Index);
	size_t Size(Layer TargetLayer);

private:
	void UpdateObjectList(int i);
	void CheckDeleteFlag(int i);
	void ChangeMode();
	void ClearFloatingObject();
	void ClearAll();
	void UpdateObjectList();
};
extern FWM fw;