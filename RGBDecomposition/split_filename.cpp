#include "split_filename.hpp"

std::pair<std::string, std::string> SplitFilename(const std::string& filename) {
	std::string name = filename.substr(0, filename.size() - 4);
	std::string extension = filename.substr(name.size() + 1);

	return std::make_pair(name, extension);
}