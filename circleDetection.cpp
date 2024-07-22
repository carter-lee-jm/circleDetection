#include <iostream>
#include <conio.h>
#include "util.h"
#include <opencv2/core/utils/logger.hpp>
int main()
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
    std::string filename = R"(Image\circle_pattern.png)";
    cv::Mat image = cv::imread(filename, cv::IMREAD_ANYCOLOR);

    if (image.empty())
    {
        std::cout << "load file failed" << std::endl;;
        return 1;
    }
    cv::Mat grayImg;
    cv::cvtColor(image, grayImg, cv::COLOR_BGR2GRAY);
    //get all circle;
    std::vector<cv::Vec3f> circles = getAllCircle(grayImg);
    //sort by Radius
    circles = sortCirclesByRadiusDescending(circles);
    //draw all circle
    drawCirclesOnMat(image, circles);

    //extract bigCircle
    cv::Vec3f bigCircle = circles[0];

    //erase bigCircle form vector then all is smallCircle
    circles.erase(circles.begin());

    std::vector<smallCircleRelatedInfo> smallCirclesAndDistance =
        calculateSmallCircleDistances(bigCircle, circles);

    drawCircleConnections(image, bigCircle, smallCirclesAndDistance);

    double bigCirclePerimeter = calculateSingleContourPerimeter(grayImg);

    drawPerimeterText(image, bigCirclePerimeter);

    cv::namedWindow("Result", cv::WINDOW_NORMAL);
    cv::imshow("Result", image);
    cv::imwrite("the_result.png", image);
    cv::waitKey();

    return 0;
}