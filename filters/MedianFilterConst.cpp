#include "MedianFilterConst.h"

#include <opencv2/opencv.hpp>

#include "Histogram.hpp"
#include "MedianFilterI.h"

namespace Filter {

cv::Mat MedianFilterConst::operator()(const cv::Mat& input_mat, int R) {
  
  cv::Mat output_mat = cv::Mat::zeros(input_mat.size(), input_mat.type());
  std::vector<Histogram> histograms(2*R + 1 + input_mat.cols, (2 * R + 1));

  for (int j = -R; j < input_mat.cols + R + 1; ++j) {
    for (int i = -R; i <= R; ++i) {
      histograms[j + R][get_index(input_mat, i, j)]++;
    }
  }

  Histogram hist((2 * R + 1) * (2 * R + 1));

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
      output_mat.at<uchar>(i, j) = (uchar)cur_hist.Median();

      cur_hist -= histograms[j];
      cur_hist += histograms[j + 2 * R + 1];
    }

    for (int j = -R; j < input_mat.cols + R + 1; ++j) {
      histograms[j + R][get_index(input_mat, i - R, j)]--;
      histograms[j + R][get_index(input_mat, i + R + 1, j)]++;
    }
  }

  return output_mat;
}

};  // namespace Filter