#include "Shader.h"
namespace openge {
	Shader::Shader(const std::string& pathVertex, const std::string& pathFragment)
	{
		m_vertexSource = getContentPathShader(pathVertex);
		m_fragmentSource = getContentPathShader(pathFragment);
		compileShader();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_program);
	}

	void Shader::Bind()
	{
		glUseProgram(m_program);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	unsigned int Shader::getProgram() const
	{
		return m_program;
	}

	void Shader::setUniform4f(std::string name, float v1, float v2, float v3, float v4)
	{
		glUniform4f(getUniformLocation(name), v1, v2, v3, v4);
	}

	void Shader::setUniform1i(std::string name, int location)
	{
		glUniform1i(getUniformLocation(name), location);
	}

	void Shader::setUniform1f(std::string name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform3fv(std::string name, const Vector3& vec3) {
		glUniform3fv(getUniformLocation(name), 1, &vec3[0]);
	}

	void Shader::setUniform3f(std::string name, float x, float y, float z)
	{
		glUniform3f(getUniformLocation(name), x, y, z);
	}

	void Shader::setUniformMatrix4fv(std::string name, const Matrix4& mat)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::setUniformMatrix3fv(std::string name, const Matrix3& mat)
	{
		glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]); 
	}

	unsigned int Shader::createShader(std::string& sourceShader, GLenum type)
	{
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

	int Shader::getUniformLocation(std::string name)
	{
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
			return m_uniformLocationCache[name];
		}
		int location = glGetUniformLocation(m_program, name.c_str());
		if (location == -1) {
			std::cout << "Aviso: uniform " << name << " not exist!" << std::endl;
			return -1;
		}
		else {
			return location;
		}
	}

	void Shader::compileShader()
	{
		// link shaders
		m_program = glCreateProgram();

		unsigned int vertexShader = createShader(m_vertexSource, GL_VERTEX_SHADER);
		unsigned int fragmentShader = createShader(m_fragmentSource, GL_FRAGMENT_SHADER);

		glAttachShader(m_program, vertexShader);
		glAttachShader(m_program, fragmentShader);
		glLinkProgram(m_program);

		int success;
		char infoLog[512];
		glGetProgramiv(m_program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	std::string Shader::getContentPathShader(const std::string& path)
	{
		std::ifstream ifs(path.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

		std::ifstream::pos_type fileSize = ifs.tellg();
		ifs.seekg(0, std::ios::beg);

		std::vector<char> bytes(fileSize);
		ifs.read(&bytes[0], fileSize);

		return std::string(&bytes[0], fileSize);
	}
}