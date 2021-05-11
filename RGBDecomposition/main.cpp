#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <string>
#include "split_channels.hpp"
#include "split_filename.hpp"
#include "color_blur.hpp"

void Blur(const std::string& filename, int radius, int weight) {
	cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);

	cv::Mat blur_image = ColorBlur::AddBlur(image, radius, weight);

	auto[name, extension] = SplitFilename(filename);
	std::string blur_filename = name + "-blur-radius" + std::to_string(radius) + "-weight" + std::to_string(weight) + '.' + extension;
	cv::imwrite(blur_filename, blur_image);
}

void Rgb(const std::string& filename) {
	cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);

	std::map<std::string, cv::Mat> images = SplitChannels(image);

	for (auto const&[channel, image] : images) {
		auto[name, extension] = SplitFilename(filename);
		std::string split_filename = name + "-split-" + channel + '.' + extension;
		cv::imwrite(split_filename, image);
	}
}

int main(int argc, char* argv[])
{
	std::string arguments_error_message = "Wrong number of arguments.";

	if (argc < 3) {
		std::cout << arguments_error_message << std::endl;
		return 1;
	}

	char* command = argv[1];
	char* filename = argv[2];
	char* radius = argv[3];
	char* weight = argv[4];

	std::vector<std::string> commands = { "-rgb", "-blur" };

	auto it = std::find(commands.begin(), commands.end(), command);
	int command_index = it - commands.begin();

	switch (command_index)
	{
	case 0:
		Rgb(filename);
		break;

	case 1:
		if (!radius || !weight) {
			std::cout << arguments_error_message << std::endl;
			return 1;
		}

		Blur(filename, std::stoi(radius), std::stoi(weight));
		break;
	default:
		std::cout << "Invalid command." << std::endl;
		return 1;
	}

	return 0;
}