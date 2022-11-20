#pragma once

#include "MedianFilterI.h"

namespace Filter {

class MedianFilterHuang : public MedianFilterI {
 public:
  cv::Mat operator()(const cv::Mat& input_mat_, int R) override;
};

}  // namespace Filter