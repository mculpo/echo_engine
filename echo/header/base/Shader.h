#pragma once
#include <core/core.h>
namespace openge {

	class Shader
	{
	public:
		Shader(const std::string& pathVertex, const std::string& pathFragment);
		~Shader();
		void Bind();
		void Unbind();
		unsigned int getProgram() const;
		void setUniform4f(std::string name, float v1, float v2, float v3, float v4);
		void setUniform1i(std::string name, int location);
		void setUniform1f(std::string name, float value);
		void setUniformMatrix4fv(std::string name, const Matrix4& mat);
		void setUniformMatrix3fv(std::string name, const Matrix3& mat);
		void setUniform3fv(std::string name, const Vector3& vec);
		void setUniform3f(std::string name, float x, float y, float z);
	private:
		std::string getContentPathShader(const std::string& path);
		void compileShader();
		unsigned int createShader(std::string& sourceShader, GLenum type);
		int getUniformLocation(std::string name);
	private:
		unsigned int m_program;
		std::string  m_fragmentSource;
		std::string  m_vertexSource;
		std::unordered_map<std::string, int> m_uniformLocationCache;
	};

}