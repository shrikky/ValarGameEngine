#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>
namespace Valar
{
	GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
	{


	}


	GLSLProgram::~GLSLProgram()
	{

	}

	void GLSLProgram::CompileShaders(const std::string vertexFilePath, const  std::string fragmentFilePath)
	{
		_programID = glCreateProgram();

		//Create the vertex shader object, and store its ID
		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexShaderID == 0) {
			fatalError("Vertex shader failed to be created!");
		}

		//Create the fragment shader object, and store its ID
		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0) {
			fatalError("Fragment shader failed to be created!");
		}

		std::ifstream VShaderFile(vertexFilePath);
		if (VShaderFile.fail())
		{
			perror(vertexFilePath.c_str());
			fatalError("failed to open " + vertexFilePath);
		}
		CompilerUtility(VShaderFile, _vertexShaderID);

		std::ifstream FShaderFile(fragmentFilePath);
		if (FShaderFile.fail())
		{
			perror(fragmentFilePath.c_str());
			fatalError("failed to open " + fragmentFilePath);
		}
		CompilerUtility(FShaderFile, _fragmentShaderID);

	}
	void GLSLProgram::CompilerUtility(std::ifstream& shaderFile, GLint shaderID)
	{

		std::string fileContents;
		std::string line;

		while (std::getline(shaderFile, line))
		{
			fileContents += line + "\n";
		}
		shaderFile.close();

		const char* contentsPtr = fileContents.c_str();
		glShaderSource(shaderID, 1, &contentsPtr, nullptr);
		glCompileShader(shaderID);

		GLint success = 0;

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(shaderID);

			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader failed to compile" + shaderID);
			return;
		}
	}
	void GLSLProgram::AddAttribute(const std::string & attributeName)
	{
		glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
	}

	void GLSLProgram::Use()
	{
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++)
			glEnableVertexAttribArray(i);
	}

	void GLSLProgram::Unuse()
	{
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++)
			glDisableVertexAttribArray(i);
	}

	void GLSLProgram::LinkShaders()
	{
		//Attach our shaders to our program
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		//Link our program
		glLinkProgram(_programID);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

			//We don't need the program anymore.
			glDeleteProgram(_programID);
			//Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			//print the error log and quit
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to link!");
		}

		//Always detach shaders after a successful link.
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}

	GLint GLSLProgram::GetUnitformLocation(const std::string& uniformName)
	{
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
		{
			fatalError("Uniform" + uniformName);
			return -1;
		}
		return location;
	}
}