#include "UIStateElement.h"
#include "Common/toHash.h"
#include <iostream>

namespace ems_engine
{
	UIStateElement::UIStateElement()
		:current_state("Default"_xxHash)
	{
		std::vector<uint64_t> tmp_visual_group = {0};
		setVisualGroup(std::move(tmp_visual_group), current_state);
	}
	UIStateElement::UIStateElement(float x, float y, float w, float h, const std::vector<std::string>& visual_group, std::string_view state, float fps)
		:UIElement(x, y, w, h, visual_group.empty() ? 0 : string_toHash(visual_group.at(0))), current_state(string_toHash(state)), frame_duration(FpsConvertToFrameDuration(fps))
	{
		setVisualGroup(visual_group, state);
	}

	void UIStateElement::update(float delta_sec)
	{
		update_timer += delta_sec;
		if (update_timer>=frame_duration)
		{
			current_frame++;
			if (current_frame >= current_visual_group->size())
				current_frame = 0;
			update();
			update_timer -= frame_duration;
		}
	}
	void UIStateElement::update()
	{
		setCurrentTextureID(current_visual_group->at(current_frame));
	}


	void UIStateElement::setCurrentVisualState(uint64_t state)
	{
		auto it = texture_state.find(state);
		if(it==texture_state.end())
		{
			std::cout << "[Error]:Visual State Not Found!" << std::endl;
			std::vector<uint64_t> tmp_visual_group;
			tmp_visual_group.push_back(0);
			setVisualGroup(tmp_visual_group, state);
		}
		current_visual_group = &it->second;
		current_state = state;
		current_frame = 0;
		update_timer = 0.0f;
		update();
	}
	void UIStateElement::setCurrentVisualState(std::string_view state)
	{
		setCurrentVisualState(string_toHash(state));
	}

	uint64_t UIStateElement::getCurrentVisualState() const
	{
		return current_state;
	}

	void UIStateElement::setVisualGroup(const std::vector<std::string>& visual_group, std::string_view state)
	{
		setVisualGroup(visual_group, string_toHash(state));
	}
	void UIStateElement::setVisualGroup(const std::vector<std::string>& visual_group, uint64_t state)
	{
		std::vector<uint64_t> tmp_visual_group;
		tmp_visual_group.reserve(visual_group.size());
		for (const auto& ID : visual_group)
		{
			tmp_visual_group.push_back(string_toHash(ID));
		}
		setVisualGroup(std::move(tmp_visual_group), state);
	}
	void UIStateElement::setVisualGroup(std::vector<uint64_t> visual_group, uint64_t state)
	{
		if (visual_group.empty())
		{
			visual_group.push_back(0);
			std::cout << "[Error]:visual_group is empty" << std::endl;
		}
		auto it = texture_state.insert_or_assign(state, std::move(visual_group));
		if(state == current_state)
			current_visual_group = &it.first->second;
	}

	void UIStateElement::setCurrentFrame(unsigned int frame)
	{
		if (frame >= current_visual_group->size())
		{
			std::cout << "[Error]:frame >= visual_group size!" << std::endl;
			return;
		}
		current_frame = frame;
		update();
	}

	unsigned int UIStateElement::getCurrentFrame() const
	{
		return current_frame;
	}

	void UIStateElement::setFps(float fps)
	{
		frame_duration = FpsConvertToFrameDuration(fps);
	}

	float UIStateElement::getFrameDuration() const
	{
		return frame_duration;
	}

	bool UIStateElement::FindTextureState(uint64_t state)
	{
		return texture_state.contains(state);
	}


	float UIStateElement::FpsConvertToFrameDuration(float fps)
	{
		if (fps <= 0)
		{
			std::cout << "[Error]:fps<=0" << std::endl;
			return 1.0f;
		}
		return 1.0f / fps;
	}

}