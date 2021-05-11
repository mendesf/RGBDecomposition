#pragma once
#include <opencv2/core/mat.hpp>

class ColorBlur {
public:
	static cv::Mat AddBlur(const cv::Mat& image, int radius, int weight);

private:
	int channel;
	int sum;
	int count;

	void AddColor(const cv::Mat& image, int row, int col, int weight);

public:
	ColorBlur(int channel);
	void AddColColors(const cv::Mat& image, int row, int col, int radius, int weight);
	void AddRowColors(const cv::Mat& image, int row, int col, int radius, int weight);
	int CalcBlur();
};