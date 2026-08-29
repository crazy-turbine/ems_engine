#include "TextureObject.h"
#include "Common/struct.h"

namespace ems_engine
{
	TextureObject::TextureObject(float x, float y, float w, float h, uint64_t textureID)
		:Object(x, y, w, h), current_textureID_(textureID)
	{
	}
	void TextureObject::setCurrentTextureID(uint64_t textureID, size_t index)
	{
		current_textureID_ = textureID;
	}
	uint64_t TextureObject::getCurrentTextureID(size_t index) const
	{
		return current_textureID_;
	}
	RenderConfig TextureObject::getRenderConfig() const
	{
		RenderConfig render_data;
		render_data.x = getPos().x;
		render_data.y = getPos().y;
		render_data.w = getSize().w;
		render_data.h = getSize().h;
		render_data.alpha = getAlpha();
		render_data.textureID = getCurrentTextureID();
		return render_data;
	}
	void TextureObject::setVisible(bool visible)
	{
		visible_ = visible;
	}
	bool TextureObject::isVisible() const
	{
		return visible_;
	}
	void TextureObject::setAlpha(uint8_t alpha)
	{
		alpha_ = alpha;
	}
	uint8_t TextureObject::getAlpha() const
	{
		return alpha_;
	}
	void TextureObject::setLayer(int layerID)
	{
		layer = layerID;
		on_transform_changed_callback();
	}
	int TextureObject::getLayer() const
	{
		return layer;
	}

	void TextureObject::setOnTransformChangedCallback(std::function<void()> callback)
	{
		on_transform_changed_callback = callback;
	}
	void TextureObject::onPosChanged()
	{
		on_transform_changed_callback();
	}
}