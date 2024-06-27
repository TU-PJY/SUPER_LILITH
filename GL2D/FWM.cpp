#include "FWM.h"
#include <ranges>
#include <algorithm>


FWM_Log FLog;

FWM::FWM() {
	if (DebugMessage) {
		std::cout << "======== FWM Message ========\n";
		std::cout << "FWM is prepared.\n\n";
	}
}

void FWM::SetFrameTime(float ElapsedTime) {
	FrameTime = ElapsedTime;
}

std::string FWM::Mode() {
	return RunningMode;
}

void FWM::Routine() {
	if (!ModeSwitchState && RunningState) {
		for (int i = 0; i < Num; ++i) {
			for (auto It = begin(Container[i]); It != end(Container[i]);) {
				if (!FloatingModeRunningState) {
					(*It)->Update(FrameTime);
					(*It)->Render();
				}

				else {
					if (FloatingOnlyState && (*It)->FloatingSpecifiedDescriptor)
						(*It)->Update(FrameTime);
					else
						(*It)->Update(FrameTime);

					(*It)->Render();
				}

				if (ModeSwitchReserveDescriptor)
					break;

				++It;
			}

			if (ModeSwitchReserveDescriptor) {
				ModeSwitchState = true;
				break;
			}

			std::erase_if(Container[i], [](OBJ_BASE*& Object) {
				bool IsDeleteTarget = Object->ObjectDeleteDescriptor;
				if (IsDeleteTarget) {
					delete Object;
					Object = nullptr;
				}
				return IsDeleteTarget;
				});

			std::erase_if(ObjectList, [](const std::pair<std::string, OBJ_BASE*>& Object) {return !Object.second; });
		}
	}

	else 
		ChangeMode();
}

void FWM::Init(Function ModeFunction, ControllerFunction Controller) {
	if (RunningState)  
		return;

	RunningMode = ModeFunction();

	if(Controller)  Controller();

	ControllerBackUpBuffer = Controller;

	FLog.CurrentMode = RunningMode;
	FLog.Log(LogType::FWL_INIT);

	for (int i = 0; i < Num; ++i)
		AddObject(new FWM_DUMMY, "FWM_DUMMY", static_cast<Layer>(i));

	RunningState = true;
}

void FWM::SwitchMode(Function ModeFunction, ControllerFunction Controller) {
	if (!RunningState)  
		return;

	ModeFunctionBuffer = ModeFunction;
	ControllerBuffer = Controller;
	ControllerBackUpBuffer = Controller;

	FLog.PrevMode = RunningMode;

	ModeSwitchReserveDescriptor = true;

	if (FloatingModeRunningState)
		FLog.Log(LogType::END_FLOATING_MODE);
}

void FWM::StartFloatingMode(Function ModeFunction, ControllerFunction Controller, bool FloatingOnlyOption) {
	if (!RunningState || FloatingModeRunningState)  
		return;

	ModeFunctionBuffer = ModeFunction;

	FLog.PrevMode = RunningMode;

	FloatingModeReserveDescriptor = true;
	ModeSwitchReserveDescriptor = true;

	FloatingOnlyState = FloatingOnlyOption;

	FLog.IsOnlyFloating = FloatingOnlyState;
}

void FWM::EndFloatingMode() {
	if (!RunningState || !FloatingModeRunningState)  
		return;

	FLog.PrevMode = RunningMode;

	FloatingModeEndReserveDescriptor = true;
	ModeSwitchReserveDescriptor = true;
}

void FWM::ResetControlState(OBJ_BASE* Object) {
	Object->ResetControlState();
}

void FWM::AddObject(OBJ_BASE* Object, std::string Tag, Layer AddLayer, bool SetFloatingObject) {
	Container[static_cast<int>(AddLayer)].push_back(Object);
	Object->ObjectTag = Tag;

	ObjectList.insert(std::make_pair(Tag, Object));

	FLog.ObjectTag = Tag;
	FLog.Log(LogType::ADD_OBJECT);

	if (SetFloatingObject) {
		Object->FloatingSpecifiedDescriptor = true;
		FLog.Log(LogType::SET_FLOATING_OBJECT);
	}
}

void FWM::DeleteSelf(OBJ_BASE* Object) {
	Object->ObjectDeleteDescriptor = true;

	FLog.ObjectTag = Object->ObjectTag;
	FLog.Log(LogType::DELETE_OBJECT);
}

void FWM::DeleteObject(std::string Tag, DeleteRange deleteRange) {
	if (deleteRange == DeleteRange::One) {
		auto It = ObjectList.lower_bound(Tag);
		if (It != end(ObjectList))
			It->second->ObjectDeleteDescriptor = true;
	}

	else if (deleteRange == DeleteRange::All) {
		for (auto It = begin(ObjectList); It != end(ObjectList);) {
			if (It->first == Tag) {
				It->second->ObjectDeleteDescriptor = true;
				continue;
			}
			++It;
		}
	}
}

OBJ_BASE* FWM::Find(std::string Tag) {
	auto It = ObjectList.lower_bound(Tag);
	if (It != end(ObjectList))
		return It->second;

	return nullptr;
}

OBJ_BASE* FWM::Find(std::string Tag, Layer LayerToSearch, int Index) {
	int layer = static_cast<int>(LayerToSearch);

	if (Index >= Container[layer].size())
		return nullptr;

	if (Container[layer][Index]->ObjectTag == Tag)
		return Container[layer][Index];

	return nullptr;
}

size_t FWM::Size(Layer TargetLayer) {
	return Container[static_cast<int>(TargetLayer)].size();
}

//////// private ///////////////

void FWM::ChangeMode() {
	if (FloatingModeReserveDescriptor) {
		PrevRunningMode = RunningMode;
		RunningMode = ModeFunctionBuffer();

		if(ControllerBuffer)
			ControllerBuffer();

		FloatingModeRunningState = true;

		FLog.CurrentMode = RunningMode;
		FLog.Log(LogType::START_FLOATING_MODE);
	}

	if (FloatingModeEndReserveDescriptor) {
		ClearFloatingObject();
		RunningMode = PrevRunningMode;

		if(ControllerBackUpBuffer)  
			ControllerBackUpBuffer();

		FloatingModeRunningState = false;
		FloatingOnlyState = false;

		FLog.CurrentMode = RunningMode;
		FLog.Log(LogType::END_FLOATING_MODE);
	}
	
	if(!FloatingModeReserveDescriptor && !FloatingModeEndReserveDescriptor) {
		ClearAll();
		RunningMode = ModeFunctionBuffer();

		if(ControllerBuffer)  
			ControllerBuffer();

		FLog.CurrentMode = RunningMode;
		FloatingOnlyState = false;
	}

	FLog.IsOnlyFloating = FloatingOnlyState;

	if (FLog.CurrentMode == FLog.PrevMode)
		FLog.ErrorLog(LogType::ERROR_SAME_MODE);

	FLog.CurrentMode = RunningMode;
	FLog.Log(LogType::MODE_SWITCH);

	FloatingModeReserveDescriptor = false;
	FloatingModeEndReserveDescriptor = false;
	ModeSwitchReserveDescriptor = false;
	ModeSwitchState = false;
}

void FWM::ClearFloatingObject() {
	for (int i = 0; i < Num; ++i) {
		for (auto It = begin(Container[i]); It != end(Container[i]);) {
			if ((*It)->FloatingSpecifiedDescriptor) {
				delete* It;
				*It = nullptr;
				It = Container[i].erase(It);
				continue;
			}

			++It;
		}
	}
}

void FWM::ClearAll() {
	for (int i = 0; i < Num; ++i) {
		for (auto It = begin(Container[i]); It != end(Container[i]);) {
			if ((*It)->ObjectTag != "FWM_DUMMY") {
				delete* It;
				*It = nullptr;
				It = Container[i].erase(It);

				continue;
			}

			++It;
		}
	}

	ObjectList.clear();
}