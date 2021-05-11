#include "split_channels.hpp"

std::map<std::string, cv::Mat> SplitChannels(const cv::Mat& image) {
	const std::string kRed = "red";
	const std::string kGreen = "green";
	const std::string kBlue = "blue";

	std::map<std::string, cv::Mat> images;

	images[kRed] = cv::Mat(image.rows, image.cols, CV_8UC3);
	images[kGreen] = cv::Mat(image.rows, image.cols, CV_8UC3);
	images[kBlue] = cv::Mat(image.rows, image.cols, CV_8UC3);

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);

			images.at(kRed).at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, pixel[2]);
			images.at(kGreen).at<cv::Vec3b>(i, j) = cv::Vec3b(0, pixel[1], 0);
			images.at(kBlue).at<cv::Vec3b>(i, j) = cv::Vec3b(pixel[0], 0, 0);
		}
	}

	return images;
}