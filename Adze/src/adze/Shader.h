#pragma once

namespace adze {
	class Shader {
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void bind() const;
		void unbind() const;
	private:
		uint32_t rendererId;
	};
}

