#include "FWM.h"
#include <ranges>
#include <algorithm>


FWM_Log FLog;

FWM::FWM() {
	if (DebugMessage) {
		std::cout << "======== FWL Message ========\n";
		std::cout << "FWL is prepared.\n";
	}
}

void FWM::SetFrameTime(float ElapsedTime) {
	FrameTime = ElapsedTime;
}

std::string FWM::Mode() {
	return RunningMode;
}

void FWM::Routine() {
	using namespace std;

	if (!ModeSwitchState && RunningState) {
		for (int i = 0; i < Num; ++i) {
			if (Container[i].empty())
				continue;

			for (auto It = begin(Container[i]); It != end(Container[i]);) {
				if (CheckDeleteFlag(It, i))
					continue;

				if (FloatingModeRunningState) {
					if (FloatingOnlyState) {
						if ((*It)->FloatingSpecifiedDescriptor) {
							(*It)->InputControl();
							(*It)->Update(FrameTime);
						}
					}

					else {
						if ((*It)->FloatingSpecifiedDescriptor)
							(*It)->InputControl();
						(*It)->Update(FrameTime);
					}
				}

				else {
					(*It)->InputControl();
					(*It)->Update(FrameTime);
				}

				(*It)->ProcessTransform();
				(*It)->Render();

				if (CheckDeleteFlag(It, i))
					continue;

				++It;
			}

			if (ModeSwitchReserveDescriptor) {
				ModeSwitchState = true;
				break;
			}
		}
	}

	if (ModeSwitchReserveDescriptor) {
		ChangeMode();
		ModeSwitchReserveDescriptor = false;
	}
}

void FWM::Init(Function ModeFunction, ControllerFunction Controller) {
	if (RunningState)
		return;

	RunningMode = ModeFunction();

	if(Controller)
		Controller();

	ControllerBackUpBuffer = Controller;

	FLog.CurrentMode = RunningMode;
	FLog.Log(LogType::FWL_INIT);

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

	if (FloatingOnlyOption)
		FloatingOnlyState = true;

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

void FWM::DeleteObject(std::string Tag, DeleteRange deleteRange, SearchRange searchRange, Layer LayerToSearch) {
	switch (searchRange) {
	case SearchRange::One:
		int layer;
		layer = static_cast<int>(LayerToSearch);

		switch (deleteRange) {
		case DeleteRange::One:
			for (auto& It : Container[layer]) {
				if (It->ObjectTag == Tag) {
					It->ObjectDeleteDescriptor = true;

					FLog.ObjectTag = It->ObjectTag;
					FLog.Log(LogType::DELETE_OBJECT);
					return;
				}
			}
			break;

		case DeleteRange::All:
			for (auto& It : Container[layer]) {
				if (It->ObjectTag == Tag) {
					It->ObjectDeleteDescriptor = true;

					FLog.ObjectTag = It->ObjectTag;
					FLog.Log(LogType::DELETE_OBJECT);
				}
			}
			break;
		}
		break;

	case SearchRange::All:
		switch (deleteRange) {
		case DeleteRange::One:
			for (auto& A : Container) {
				for (auto& It : A) {
					if (It->ObjectTag == Tag) {
						It->ObjectDeleteDescriptor = true;

						FLog.ObjectTag = It->ObjectTag;
						FLog.Log(LogType::DELETE_OBJECT);
						return;
					}
				}
			}
			break;

		case DeleteRange::All:
			for (auto& A : Container) {
				for (auto& It : A) {
					if (It->ObjectTag == Tag) {
						It->ObjectDeleteDescriptor = true;

						FLog.ObjectTag = It->ObjectTag;
						FLog.Log(LogType::DELETE_OBJECT);
					}
				}
			}
			break;
		}
		break;
	}
}

OBJ_BASE* FWM::Find(std::string Tag, SearchRange searchRange, Layer LayerToSearch) {
	switch (searchRange) {
	case SearchRange::One:
		int layer;
		layer = static_cast<int>(LayerToSearch);

		for (auto& It : Container[layer]) {
			if (It->ObjectTag == Tag)
				return It;
		}
		break;

	case SearchRange::All:
		for (auto& A : Container) {
			for (auto& It : A) {
				if (It->ObjectTag == Tag)
					return It;
			}
		}
		break;
	}

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

bool FWM::CheckDeleteFlag(std::deque<OBJ_BASE*>::iterator& It, int Layer) {
	if ((*It)->ObjectDeleteDescriptor) {
		delete* It;
		*It = nullptr;
		It = Container[Layer].erase(It);
		return true;
	}
	return false;
}

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
	using namespace std;

	for (int i = 0; i < Num; ++i) {
		for (auto It = begin(Container[i]); It != end(Container[i]);) {
			delete* It;
			*It = nullptr;
			It = Container[i].erase(It);
		}
	}
}