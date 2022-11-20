#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

namespace Filter {

class Histogram {
 private:
  std::vector<int> histogram_;
  int size_;

 public:
  Histogram(int size) : size_(size) { histogram_.resize(256); }

  int& operator[](int index) { return histogram_[index]; }

  Histogram& operator+=(const Histogram& hist) {
    for (int i = 0; i < this->histogram_.size(); ++i) {
      this->histogram_[i] += hist.histogram_[i];
    }
    return *this;
  }
  Histogram& operator-=(const Histogram& hist) {
    for (int i = 0; i < this->histogram_.size(); ++i) {
      this->histogram_[i] -= hist.histogram_[i];
    }
    return *this;
  }
  int Median() {
    int prefix_sum = 0;
    int index = 0;
    for (index = 0; index < histogram_.size(); ++index) {
      prefix_sum += histogram_[index];
      if (prefix_sum >= size_ / 2) {
        break;
      }
    }
    return index;
  }
};

static int get_index(const cv::Mat& mat, int i, int j) {
  int index_i = std::clamp(i, 0, mat.rows - 1);
  int index_j = std::clamp(j, 0, mat.cols - 1);
  return mat.at<uchar>(index_i, index_j);
}

};  // namespace Filter
