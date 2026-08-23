#pragma once
#include "Object/Object.h"



namespace ems_engine
{
	class UIElement :public Object
	{
	public:
		UIElement() = default;
		UIElement(float x, float y, float w, float h, uint64_t textureID);
		virtual void setCurrentTextureID(uint64_t textureID, size_t index = 0);
		virtual uint64_t getCurrentTextureID(size_t index = 0) const;
		void setVisible(bool visible);
		bool isVisible() const;
	protected:
		uint64_t current_textureID_ = 0;
	private:
		
		bool visible_ = true;
	};
}