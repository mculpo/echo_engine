#ifndef OPENGE_SHADER
#define OPENGE_SHADER
#include <core/core.h>
namespace echo {
	struct Shader {
		unsigned int mProgram;
		UniformLocationCache mUniformLocationCache;
		String  mFragmentSource;
		String  mVertexSource;
	};
}
namespace echo::shader {
#ifndef OPENGE_SHADERMANAGER
#define OPENGE_SHADERMANAGER

	void deleteProgram(Shader* shader);

	void bindProgram(Shader* shader);

	void unbindProgram();

	int getUniformLocation(Shader* shader, String name);

	unsigned int createShader(String& sourceShader, GLenum type);

	String getContentPathShader(const String& path);

	void setInt(Shader* shader, String name, int location);

	void setFloat(Shader* shader, String name, float value);

	void setVector3(Shader* shader, String name, const Vector3& vec3);

	void setVector3(Shader* shader, String name, float x, float y, float z);

	void setMatrix4(Shader* shader, String name, const Matrix4& mat);

	void setMatrix4(Shader* shader, String name, float v1, float v2, float v3, float v4);

	void setMatrix3(Shader* shader, String name, const Matrix3& mat);

	void compileShader(Shader* shader, const String& pathVertex, const String& pathFragment);


	void deleteProgram(Shader* shader) {
		glDeleteProgram(shader->mProgram);
	}

	void bindProgram(Shader* shader) {
		glUseProgram(shader->mProgram);
	}

	void unbindProgram() {
		glUseProgram(0);
	}

	int getUniformLocation(Shader* shader, String name)
	{
		if (shader->mUniformLocationCache.find(name) != shader->mUniformLocationCache.end()) {
			return shader->mUniformLocationCache[name];
		}
		int location = glGetUniformLocation(shader->mProgram, name.c_str());
		if (location == -1) {
			std::cout << "Aviso: uniform " << name << " not exist!" << std::endl;
			return -1;
		}
		else {
			return location;
		}
	}

	unsigned int createShader(String& sourceShader, GLenum type) {
		unsigned int shader = glCreateShader(type);
		const char* src = sourceShader.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);
		// check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::" << type << "::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		return shader;
	}

	String getContentPathShader(const String& path) {
		std::ifstream ifs(path.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

		std::ifstream::pos_type fileSize = ifs.tellg();
		ifs.seekg(0, std::ios::beg);

		std::vector<char> bytes(fileSize);
		ifs.read(&bytes[0], fileSize);

		return String(&bytes[0], fileSize);
	}
	void setInt(Shader* shader, String name, int location)
	{
		glUniform1i(getUniformLocation(shader, name), location);
	}

	void setFloat(Shader* shader, String name, float value)
	{
		glUniform1f(getUniformLocation(shader, name), value);
	}

	void setVector3(Shader* shader, String name, const Vector3& vec3) {
		glUniform3fv(getUniformLocation(shader, name), 1, &vec3[0]);
	}

	void setVector3(Shader* shader, String name, float x, float y, float z)
	{
		glUniform3f(getUniformLocation(shader, name), x, y, z);
	}

	void setMatrix4(Shader* shader, String name, const Matrix4& mat)
	{
		glUniformMatrix4fv(getUniformLocation(shader, name), 1, GL_FALSE, &mat[0][0]);
	}

	void setMatrix4(Shader* shader, String name, float v1, float v2, float v3, float v4)
	{
		glUniform4f(getUniformLocation(shader, name), v1, v2, v3, v4);
	}

	void setMatrix3(Shader* shader, String name, const Matrix3& mat)
	{
		glUniformMatrix3fv(getUniformLocation(shader, name), 1, GL_FALSE, &mat[0][0]);
	}

	void compileShader(Shader* shader, const String& pathVertex, const String& pathFragment) {

		shader->mProgram = glCreateProgram();

		shader->mVertexSource = getContentPathShader(pathVertex);
		shader->mFragmentSource = getContentPathShader(pathFragment);

		unsigned int vertexShader = createShader(shader->mVertexSource, GL_VERTEX_SHADER);
		unsigned int fragmentShader = createShader(shader->mFragmentSource, GL_FRAGMENT_SHADER);

		glAttachShader(shader->mProgram, vertexShader);
		glAttachShader(shader->mProgram, fragmentShader);
		glLinkProgram(shader->mProgram);

		int success;
		char infoLog[512];
		glGetProgramiv(shader->mProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader->mProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
#endif
}
#endif

