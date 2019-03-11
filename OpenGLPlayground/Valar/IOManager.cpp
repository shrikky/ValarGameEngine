#include "IOManager.h"
#include <fstream>
namespace Valar
{
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}
		//seek to the end
		file.seekg(0, std::ios::end);

		unsigned int fileSize = (unsigned int)file.tellg();
		file.seekg(0, std::ios::beg);

		fileSize -= (unsigned int)file.tellg();

		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);
		file.close();

		return true;
	}

}