#pragma once
#include "Object/Object.h"



namespace ems_engine
{
	class UIElement :public Object
	{
	public:
		UIElement() = default;
		UIElement(float x, float y, float w, float h, uint64_t textureID);
		void setCurrentTextureID(uint64_t textureID);
		uint64_t getCurrentTextureID() const;
		void setVisible(bool visible);
		bool isVisible() const;
	protected:
		

	private:
		uint64_t current_textureID_ = 0;
		bool visible_ = true;
	};
}