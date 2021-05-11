#pragma once
#include <opencv2/core/mat.hpp>
#include <string>
#include <map>

std::map<std::string, cv::Mat> SplitChannels(const cv::Mat& image);