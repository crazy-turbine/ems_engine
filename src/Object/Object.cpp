#include "include/ems_engine/Object/Object.h"


//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
namespace ems_engine
{
	Object::Object(float x, float y, float w, float h)
		:rect(x,y,w,h)
	{		
	}

	void Object::setPos(float x, float y)
	{
		rect.x = x;
		rect.y = y;
		onPosChanged();
	}
	void Object::setSize(float w, float h)
	{
		rect.w = w;
		rect.h = h;
	}
	void Object::setRect(float x, float y, float w, float h)
	{
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
	}

	void Object::setDebugDrawEnabled(bool debug)
	{
		debug_mode = debug;
	}
	void Object::setDebugDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		debug_color = { r,g,b,a };
	}

	Position Object::getPos() const
	{
		return {rect.x,rect.y};
	}
	Size Object::getSize() const
	{
		return {rect.w,rect.h};
	}
	Rect Object::getRect() const
	{
		return rect;
	}

	bool Object::isDebugDrawEnabled() const
	{
		return debug_mode;
	}
	Color Object::getDebugDrawColor() const
	{
		return debug_color;
	}

}
