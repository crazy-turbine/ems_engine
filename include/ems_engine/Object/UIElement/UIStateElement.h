#pragma once
#include <string_view>
#include "UIElement.h"
#include <unordered_map>
#include <cstdint>
#include <vector>

namespace ems_engine
{
	class UIStateElement :public UIElement
	{
	public:
		UIStateElement();
		UIStateElement(float x, float y, float w, float h, const std::vector<std::string>& visual_group, std::string_view state, float fps);
		
		void update(float delta_sec) override;
		
		void setCurrentVisualState(uint64_t state);
		void setCurrentVisualState(std::string_view state);
		
		void setVisualGroup(const std::vector<std::string>& visual_group, std::string_view state);
		void setVisualGroup(const std::vector<std::string>& visual_group, uint64_t state);
		void setVisualGroup(std::vector<uint64_t> visual_group, uint64_t state);

		uint64_t getCurrentVisualState() const;

		void setCurrentFrame(unsigned int frame);
		unsigned int getCurrentFrame() const;

		void setFps(float fps);
		float getFrameDuration() const;

	protected:
		bool FindTextureState(uint64_t state);

	private:
		void update();
		float FpsConvertToFrameDuration(float fps);
		//<state,visual_group<textureID>>
		std::unordered_map<uint64_t, std::vector<uint64_t>> texture_state;
		uint64_t current_state;
		const std::vector<uint64_t>* current_visual_group = nullptr;
		unsigned int current_frame = 0;
		float update_timer = 0.0f;
		float frame_duration = 1.0f;

	};
}