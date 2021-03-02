#pragma once

namespace util
{
	std::string ReadFile(const std::string& path)
	{
		std::string line;
		std::ifstream file(path);

		if (!file.is_open())
			throw std::runtime_error("Failed to open file (" + path + ")");

		std::stringstream output;
		output << file.rdbuf();

		return output.str();
	}
}
