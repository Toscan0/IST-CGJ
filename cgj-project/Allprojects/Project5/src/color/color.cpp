#include "color.h"
color::color(){
	_colors.insert(std::pair<std::string, float*>(std::string("red"), _red));
	_colors.insert(std::pair<std::string, float*>(std::string("green"), _green));
	_colors.insert(std::pair<std::string, float*>(std::string("blue"), _blue));
	_colors.insert(std::pair<std::string, float*>(std::string("blue2"), _blue2));
	_colors.insert(std::pair<std::string, float*>(std::string("black"), _black));
	_colors.insert(std::pair<std::string, float*>(std::string("white"), _white));
	_colors.insert(std::pair<std::string, float*>(std::string("yellow"), _yellow));
	_colors.insert(std::pair<std::string, float*>(std::string("orange"), _orange));
	_colors.insert(std::pair<std::string, float*>(std::string("purple"), _purple));
	_colors.insert(std::pair<std::string, float*>(std::string("pink"), _pink));
	_colors.insert(std::pair<std::string, float*>(std::string("brown"), _brown));
	_colors.insert(std::pair<std::string, float*>(std::string("brown2"), _brown2));
}

float* color::getColorByName(std::string name)
{
	std::map <std::string, float*> ::iterator it = _colors.find(name);
	if (it == _colors.end()) { /* Not found */ }
	else { 
		/* Found, i->first is f, i->second is ++-- */
		return it->second;
	}
}