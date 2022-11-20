#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "filters/SelectFilter.hpp"

int main(int argc, char** argv) {
  if (argc < 5) {
    std::cout << "You should write!!!" << '\n';
    std::cout
        << "<input image>---<output image>---<R>---<naive|huange|const|opencv>"
        << '\n';
    return 0;
  }

  std::string input_image = argv[1];
  std::string output_image = argv[2];
  int R = std::strtol(argv[3], NULL, 10);
  std::string type = argv[4];

  cv::Mat image_mat = cv::imread(input_image);
  if (image_mat.empty()) {
    std::cout << "We couldn't find the image, please be careful" << std::endl;
    return 0;
  }

  auto start_time = std::chrono::steady_clock::now();
  cv::Mat output_image_mat =
      Filter::SelectFilter::get_filtered_image(image_mat, R, type);
  auto end_time = std::chrono::steady_clock::now();

  auto diff_time = end_time - start_time;
  std::cout
      << std::chrono::duration_cast<std::chrono::milliseconds>(diff_time).count()
      << std::endl;

  cv::imwrite(output_image, output_image_mat);
  return 0;
}