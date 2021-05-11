#include "color_blur.hpp"
#include <exception>
#include <iostream>

ColorBlur::ColorBlur(int channel) : channel(channel), sum(0), count(0) {
}

void ColorBlur::AddColor(const cv::Mat& image, int row, int col, int weight) {
	sum += image.at<cv::Vec3b>(row, col)[this->channel] * weight;
	count += weight;
}

void ColorBlur::AddRowColors(const cv::Mat& image, int row, int col, int radius, int weight) {
	this->AddColor(image, row, col, weight);

	for (int r = 1; r <= radius; r++) {
		int top_row = row - r;
		if (top_row >= 0) {
			this->AddColColors(image, top_row, col, radius, 1);
		}

		int bottom_row = row + r;
		if (bottom_row <= image.rows - 1) {
			this->AddColColors(image, bottom_row, col, radius, 1);
		}
	}
}

void ColorBlur::AddColColors(const cv::Mat& image, int row, int col, int radius, int weight) {
	this->AddColor(image, row, col, weight);

	for (int r = 1; r <= radius; r++) {
		int left_col = col - r;
		if (left_col >= 0) {
			this->AddColor(image, row, left_col, weight);
		}

		int right_col = col + r;
		if (right_col <= image.cols - 1) {
			this->AddColor(image, row, right_col, weight);
		}
	}
}

int ColorBlur::CalcBlur() {
	return sum / count;
}

cv::Mat ColorBlur::AddBlur(const cv::Mat& image, int radius, int weight) {
	cv::Mat blur_image(image.rows, image.cols, CV_8UC3);

	for (int row = 0; row < image.rows; row++) {
		for (int col = 0; col < image.cols; col++) {
			cv::Vec3b pixel = cv::Vec3b();

			for (int channel = 0; channel < pixel.channels; channel++) {
				ColorBlur blur(channel);

				blur.AddRowColors(image, row, col, radius, weight);

				pixel[channel] = blur.CalcBlur();
			}

			blur_image.at<cv::Vec3b>(row, col) = pixel;
		}
	}

	return blur_image;
}