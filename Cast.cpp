#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/**
 * @brief Get the Diff object
 * 
 * @param img1 
 * @param img2 
 * @return *** cv::Mat = abs(img1 - img2)
 */
cv::Mat getDiff(const cv::Mat& img1, const cv::Mat& img2) {
    cv::Mat img1_gray = cv::Mat(img1.size(), 0);
    cv::Mat img2_gray = cv::Mat(img1.size(), 0);
    cv::Mat diff_img = cv::Mat(img1.size(), 0);

    cvtColor(img1, img1_gray, cv::COLOR_RGB2GRAY);
    cvtColor(img2, img2_gray, cv::COLOR_RGB2GRAY);
    
    cv::absdiff(img1_gray, img2_gray, diff_img);
    cv::threshold(diff_img, diff_img, 100, 255, 0);
    cv::dilate(diff_img, diff_img, cv::Mat());
    cv::erode(diff_img, diff_img, cv::Mat());

    cv::imwrite("debug/diff_img.png", diff_img);

    return diff_img;
}

/**
 * @brief Get the Object according to diff image
 * 
 * @param img 
 * @param out_img 
 * @return true 
 * @return false 
 */
bool getObject(const cv::Mat& img, cv::Mat& out_img) {
    // out_img.resize(img.size());
    std::vector<std::vector<cv::Point>> v;
	std::vector<cv::Vec4i> hierarchy;
	cv::Rect rect;
    findContours(img, v, hierarchy, 0, 0);
	for (int i = 0; i < hierarchy.size(); i++)
	{
		rect = cv::boundingRect(v.at(i));
		// rect.height *= 1.5;
		cv::rectangle(out_img, rect, cv::Scalar(0, 255, 0), 2);
	}
    cv::imwrite("debug/out_img.png", out_img);
    return true;
}

int main() {
    std::cout << "running" << std::endl;

    std::string str1 = "./image.png";
    std::string str2 = "./image1.png";

    cv::Mat img1 = cv::imread(str1, 1);
    cv::Mat img2 = cv::imread(str2, 1);
    
    std::cout << "img1 type = " << img1.type() << std::endl;

    // 计算差值
    cv::Mat diff_img = getDiff(img1, img2);
    cv::Mat out_img = cv::Mat(diff_img.size(), 0);

    bool res = getObject(diff_img, out_img);

    return 0;
}