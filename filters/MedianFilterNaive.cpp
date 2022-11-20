#include "MedianFilterNaive.h"

#include <opencv2/opencv.hpp>

#include "Histogram.hpp"
#include "MedianFilterI.h"

namespace Filter {

cv::Mat MedianFilterNaive::operator()(const cv::Mat& input_mat, int R) {
  cv::Mat output_mat = cv::Mat::zeros(input_mat.size(), input_mat.type());
  int filter_size = (2 * R + 1) * (2 * R + 1);
  std::vector<int> filter(filter_size);

  for (int i = 0; i < input_mat.rows; ++i) {
    for (int j = 0; j < input_mat.cols; ++j) {

      for (int width = -R; width <= R; ++width) {
        for (int height = -R; height <= R; ++height) {
          int x = get_index(input_mat, i + width, j + height);
          filter.push_back(x);
        }
      }
      std::sort(filter.begin(), filter.end());
      output_mat.at<uchar>(i, j) = filter[(filter_size / 2)];
      filter.clear();
    }
  }

  return output_mat;
}

};  // namespace Filter