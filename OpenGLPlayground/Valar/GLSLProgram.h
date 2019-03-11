#pragma once
#include <string>
#include <GL/glew.h>
namespace Valar
{
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void CompileShaders(const  std::string filePath, const  std::string fragmentFilePath);
		void LinkShaders();
		void CompilerUtility(std::ifstream& shaderFile, GLint shaderID);
		void AddAttribute(const std::string& attributeName);
		GLint GetUnitformLocation(const std::string& uniformName);
		void Use();
		void Unuse();

	private:
		int _numAttributes;
		GLuint  _programID;
		GLuint  _vertexShaderID;
		GLuint  _fragmentShaderID;
	};

}

