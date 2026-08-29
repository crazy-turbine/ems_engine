#pragma once
#include "src/Common/struct.h"

//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
namespace ems_engine
{

	class Object
	{
	public:
		virtual ~Object() = default;
		void setPos(float x, float y);
		void setSize(float w, float h);
		void setRect(float x, float y, float w, float h);

		void setDebugDrawEnabled(bool debug_mode);
		void setDebugDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		
		Position getPos() const;
		Size getSize() const;
		Rect getRect() const;

		bool isDebugDrawEnabled() const;
		Color getDebugDrawColor() const;

		virtual void update(float delta_sec) {};

		Object(const Object&) = delete;
		Object& operator = (const Object&) = delete;
		Object(Object&&) = delete;
		Object& operator=(Object&&) = delete;
	protected:
		Object() = default;
		Object(float x, float y, float w, float h);
		virtual void onPosChanged() {};
	private:
		Rect rect{};
		bool debug_mode = false;
		Color debug_color{ 255, 0, 0, 128 };
	};
}
