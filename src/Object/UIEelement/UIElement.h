#pragma once
#include "Object/Object.h"



namespace ems_engine
{
	class UIElement :public Object
	{
	public:
		void setAssetID(uint64_t textureID);
		uint64_t getAssetID() const;
	protected:
		UIElement() = default;
		UIElement(float x, float y, float w, float h, uint64_t textureID);

	private:
		uint64_t textureID_ = 0;
	};
}