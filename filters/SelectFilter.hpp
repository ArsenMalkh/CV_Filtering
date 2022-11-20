#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "MedianFilterI.h"
#include "MedianFilterNaive.h"
#include "MedianFilterHuang.h"
#include "MedianFilterConst.h"

namespace Filter {

enum MedianFilterType { NAIVE, HUANGE, CONSTANT, OPENCV };

class SelectFilter {
 private:
  static cv::Mat select_suitable_filter(const cv::Mat& input_mat, int R,
                                        MedianFilterType type) {
    
    std::vector<cv::Mat> BGR_mat_input(3);
    cv::split(input_mat, BGR_mat_input);
    std::vector<cv::Mat> BGR_mat_output(3);
    cv::Mat output_mat;
    
    MedianFilterI* filter;
    for (int color_index = 0; color_index < 3; ++color_index) {
      if (type == MedianFilterType::NAIVE) {
        filter = new MedianFilterNaive();
        BGR_mat_output[color_index] = (*filter)(BGR_mat_input[color_index], R);
      } else if (type == MedianFilterType::HUANGE) {
        filter = new MedianFilterHuang();
        BGR_mat_output[color_index] = (*filter)(BGR_mat_input[color_index], R);
      } else if (type == MedianFilterType::CONSTANT) {
        filter = new MedianFilterConst();
        BGR_mat_output[color_index] = (*filter)(BGR_mat_input[color_index], R);
      } else if (type == MedianFilterType::OPENCV) {
        cv::medianBlur(input_mat, output_mat, 2 * R + 1);
        return output_mat;
      }
      delete filter;
    }
    merge(BGR_mat_output, output_mat);
    return output_mat;
  }

 public:
  static cv::Mat get_filtered_image(const cv::Mat& input_mat, int R,
                                    std::string type_str) {
    MedianFilterType type;
    if (type_str == "naive") {
      type = MedianFilterType::NAIVE;
    } else if (type_str == "huang") {
      type = MedianFilterType::HUANGE;
    } else if (type_str == "const") {
      type = MedianFilterType::CONSTANT;
    } else if (type_str == "opencv") {
      type = MedianFilterType::OPENCV;
    } else {
      std::cout << "It's not correct name for median filter" << '\n';
      exit(0);
    }
    return select_suitable_filter(input_mat, R, type);
  }
};

};  // namespace Filter