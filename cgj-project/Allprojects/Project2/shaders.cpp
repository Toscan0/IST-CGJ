#include "shaders.h"

std::string shaders::readShaderFile(const char *shader_file)
{
	//open file in read mode
	std::ifstream file(shader_file);
	if (!file) {
		return std::string();
	}

	file.ignore(std::numeric_limits<std::streamsize>::max());
	auto size = file.gcount();

	if (size > 0x10000) {
		return std::string();
	}

	file.clear();
	file.seekg(0, std::ios_base::beg);

	std::stringstream sstr;
	sstr << file.rdbuf();
	file.close();

	return sstr.str();
}