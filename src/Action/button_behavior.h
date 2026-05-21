#pragma once
#include <string>
#include "src/Output/Render.h"
#include "src/Common/enum.h"


class SceneManager;

class button_behavior
{
public:
	button_behavior() {};
	virtual ~button_behavior() {};
	virtual void button_action() = 0;
	virtual void button_update() = 0;
protected:


};

