#include "adzepch.h"
#include "Shader.h"


#include <glad/glad.h>

namespace adze {
	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) {
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar *source = (const GLchar *)vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if(isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
	
			// We don't need the shader anymore.
			glDeleteShader(vertexShader);
			
			ADZE_CORE_ERROR("{0}", infoLog.data());
			ADZE_CORE_ASSERT(false, "Vertex Shader compilation failure!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar *)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
	
			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			ADZE_CORE_ERROR("{0}", infoLog.data());
			ADZE_CORE_ASSERT(false, "Fragment Shader compilation failure!");

			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		rendererId = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(rendererId, vertexShader);
		glAttachShader(rendererId, fragmentShader);

		// Link our program
		glLinkProgram(rendererId);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(rendererId, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(rendererId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(rendererId, maxLength, &maxLength, &infoLog[0]);
	
			// We don't need the program anymore.
			glDeleteProgram(rendererId);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			ADZE_CORE_ERROR("{0}", infoLog.data());
			ADZE_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(rendererId, vertexShader);
		glDetachShader(rendererId, fragmentShader);
	}

	Shader::~Shader() {
		glDeleteProgram(rendererId);
	}

	void Shader::bind() const {
		glUseProgram(rendererId);
	}

	void Shader::unbind() const {
		glUseProgram(0);
	}
}