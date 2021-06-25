#pragma once

#include "adze/Core.h"
#include "adze/events/Event.h"

namespace adze {

	class ADZE_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void attach() {}
		virtual void detach() {}
		virtual void update() {}
		virtual void onEvent(Event& event) {}
		
		virtual void onImguiRender() {}

		inline const std::string& getName() const { return name; }
	protected:
		std::string name;
	};

} 