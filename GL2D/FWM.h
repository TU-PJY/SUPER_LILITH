// FWM Version 3
#pragma once
#include "FWM_Log.h"
#include "ObjectBase.h"
#include <array>
#include <deque>
#include <ranges>
#include <algorithm>

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
	void DeleteSelf(OBJ_BASE* Object);
	void DeleteObject(std::string Tag, DeleteRange deleteRange, SearchRange searchRange, Layer LayerToSearch);
	OBJ_BASE* Find(std::string Tag, SearchRange searchRange, Layer LayerToSearch = Layer::L1);
	OBJ_BASE* Find(std::string Tag, Layer LayerToSearch, int Index);
	size_t Size(Layer TargetLayer);

private:
	bool CheckDeleteFlag(std::deque<OBJ_BASE*>::iterator& It, int Layer);
	void ChangeMode();
	void ClearFloatingObject();
	void ClearAll();
};