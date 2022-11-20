#include "MedianFilterHuang.h"

#include <opencv2/opencv.hpp>

#include "Histogram.hpp"
#include "MedianFilterI.h"

namespace Filter {

cv::Mat MedianFilterHuang::operator()(const cv::Mat& input_mat, int R) {
  cv::Mat output_mat = cv::Mat::zeros(input_mat.size(), input_mat.type());
  
  int filter_size = (2 * R + 1) * (2 * R + 1);

  Histogram hist(filter_size);

  for (int height = -R - 1; height <= R - 1; ++height) {
    for (int width = -R; width <= R; ++width) {
      hist[get_index(input_mat, height, width)]++;
    }
  }

  for (int i = 0; i < input_mat.rows; ++i) {
    for (int width = -R; width <= R; ++width) {
      hist[get_index(input_mat, i - R - 1, width)]--;
      hist[get_index(input_mat, i + R, width)]++;
    }

    Histogram cur_hist = hist;

    for (int j = 0; j < input_mat.cols; ++j) {
      output_mat.at<uchar>(i, j) = cur_hist.Median();

      for (int height = -R; height <= R; ++height) {
        cur_hist[get_index(input_mat, i + height, j - R)]--;
        cur_hist[get_index(input_mat, i + height, j + R + 1)]++;
      }
    }
  }

  return output_mat;
}

};  // namespace Filter