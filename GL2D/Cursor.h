#pragma once
#include "ObjectBase.h"

class Cursor : public OBJ_BASE{
private:
	unsigned int Image{};

public:
	Cursor();
	void Render();
};

