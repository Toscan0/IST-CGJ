#include "readShaders.h"

std::string read_shader_file(const char *shader_file)
{
	// no feedback is provided for stream errors / exceptions.
	// https://goo.gl/4xy7to
	std::ifstream file(shader_file);
	if (!file) return std::string();

	file.ignore(std::numeric_limits<std::streamsize>::max());
	auto size = file.gcount();

	if (size > 0x10000) // 64KiB sanity check for shaders:
		return std::string();

	file.clear();
	file.seekg(0, std::ios_base::beg);

	std::stringstream sstr;
	sstr << file.rdbuf();
	file.close();

	return sstr.str();
}