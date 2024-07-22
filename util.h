#ifndef UTIL_H
#define UTIL_H

#include <opencv2/opencv.hpp>
#include <vector>

struct smallCircleRelatedInfo
{
    cv::Vec3f circle;
    double distance;
};

std::vector<cv::Vec3f> getAllCircle(cv::Mat grayimg);
std::vector<cv::Vec3f> sortCirclesByRadiusDescending(std::vector<cv::Vec3f> circles);
void drawCirclesOnMat(cv::Mat& image, const std::vector<cv::Vec3f>& circles);
std::vector<smallCircleRelatedInfo> calculateSmallCircleDistances(const cv::Vec3f& bigCircle, const std::vector<cv::Vec3f>& circles);
double calculateSingleContourPerimeter(const cv::Mat& grayImg);
void drawCircleConnections(cv::Mat& image, const cv::Vec3f& bigCircle,
const std::vector<smallCircleRelatedInfo>& smallCirclesAndDistance);
void drawPerimeterText(cv::Mat& image, double bigCirclePerimeter);

#endif // UTIL_H