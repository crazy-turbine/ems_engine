#pragma once
#include "Object.h"
#include <functional>

namespace ems_engine
{
	struct RenderConfig;
	class TextureObject :public Object
	{
	public:
		
		virtual void setCurrentTextureID(uint64_t textureID, size_t index = 0);
		virtual uint64_t getCurrentTextureID(size_t index = 0) const;
		virtual RenderConfig getRenderConfig() const;
		void setVisible(bool visible);
		bool isVisible() const;

		void setLayer(int layerID);
		int getLayer() const;

		void setOnTransformChangedCallback(std::function<void()> callback);

	protected:
		TextureObject() = default;
		TextureObject(float x, float y, float w, float h, uint64_t textureID);
		void onPosChanged() override;
		
		uint64_t current_textureID_ = 0;
	private:
		int layer = 0;
		bool visible_ = true;
		std::function<void()> on_transform_changed_callback;
	};
}