#pragma once
#include "ObjectBase.h"

class Title : public OBJ_BASE {
private:
	unsigned int Image{};

public:
	Title();
	void Update(float FT);
	void Render();
};

