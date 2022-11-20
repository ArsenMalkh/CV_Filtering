#pragma once

#include <opencv2/opencv.hpp>
#include <string>

namespace Filter {

class MedianFilterI {
 public:
  MedianFilterI() = default;
  virtual ~MedianFilterI() = default;
  virtual cv::Mat operator()(const cv::Mat& input_mat_, int R) = 0;
};

};  // namespace Filter