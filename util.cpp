#include "util.h"
#include <algorithm>

std::vector<cv::Vec3f> getAllCircle(cv::Mat grayimg)
{
    std::vector<cv::Vec3f> circles;
    double dp = 0.2;
    double minDist = 200;
    double param1 = 600;
    double param2 = 100;
    int minRadius = 20;
    int maxRadius = 850;
    HoughCircles(grayimg, circles, cv::HOUGH_GRADIENT, dp, minDist, param1, param2, minRadius, maxRadius);
    return circles;
}

std::vector<cv::Vec3f> sortCirclesByRadiusDescending(std::vector<cv::Vec3f> circles)
{
    std::sort(circles.begin(), circles.end(),
        [](const cv::Vec3f& a, const cv::Vec3f& b) {
            return a[2] > b[2];  // Descending order
        });
    return circles;
}

void drawCirclesOnMat(cv::Mat& image, const std::vector<cv::Vec3f>& circles)
{
    cv::Scalar color(255, 10, 255);
    int thickness = 3;
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 0.8;
    int textThickness = 2;

    for (size_t i = 0; i < circles.size(); i++)
    {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        cv::circle(image, center, radius, color, thickness);
        cv::circle(image, center, 5, color, -1);

        std::string coordText = "(" + std::to_string(center.x) + "," + std::to_string(center.y) + ")";
        int baseLine = 0;
        cv::Size textSize = cv::getTextSize(coordText, fontFace, fontScale, textThickness, &baseLine);
        cv::Point textOrg(center.x + 50, center.y);

        cv::rectangle(image, textOrg + cv::Point(0, baseLine),
            textOrg + cv::Point(textSize.width, -textSize.height),
            cv::Scalar(0, 0, 0), -1);
        cv::putText(image, coordText, textOrg, fontFace, fontScale, color, textThickness);
    }
}

std::vector<smallCircleRelatedInfo> calculateSmallCircleDistances(const cv::Vec3f& bigCircle, const std::vector<cv::Vec3f>& circles)
{
    std::vector<smallCircleRelatedInfo> smallCirclesAndDistance;
    for (const auto& smallCircle : circles)
    {
        smallCircleRelatedInfo info;
        info.circle = smallCircle;
        cv::Point2f bigCenter(bigCircle[0], bigCircle[1]);
        cv::Point2f smallCenter(smallCircle[0], smallCircle[1]);
        info.distance = cv::norm(bigCenter - smallCenter);
        smallCirclesAndDistance.push_back(info);
    }
    return smallCirclesAndDistance;
}

double calculateSingleContourPerimeter(const cv::Mat& grayImg)
{
    cv::Mat binarizerImg;
    cv::threshold(grayImg, binarizerImg, 100, 255, cv::THRESH_BINARY_INV);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binarizerImg, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    double perimeter = cv::arcLength(contours[0], true);
    return perimeter;
}

void drawCircleConnections(cv::Mat& image, const cv::Vec3f& bigCircle,
    const std::vector<smallCircleRelatedInfo>& smallCirclesAndDistance)
{
    // Set drawing parameters
    cv::Scalar lineColor(0, 0, 255);  // Red color
    cv::Scalar textColor(255, 255, 255);  // White color
    int lineThickness = 1;
    int textThickness = 2;
    double fontScale = 0.8;
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;

    // Get the center point of the big circle
    cv::Point bigCenter(cvRound(bigCircle[0]), cvRound(bigCircle[1]));

    for (const auto& smallCircleInfo : smallCirclesAndDistance)
    {
        // Get the center point of the small circle
        cv::Point smallCenter(cvRound(smallCircleInfo.circle[0]), cvRound(smallCircleInfo.circle[1]));

        // Draw the connection line
        cv::line(image, bigCenter, smallCenter, lineColor, lineThickness);

        // Calculate text position (midpoint of the line)
        cv::Point textPos((bigCenter.x + smallCenter.x) / 2, (bigCenter.y + smallCenter.y) / 2);

        // Prepare distance text
        std::string distanceText = cv::format("%.2f", smallCircleInfo.distance);

        // Get text size
        int baseline = 0;
        cv::Size textSize = cv::getTextSize(distanceText, fontFace, fontScale, textThickness, &baseline);

        // Draw text background (for better readability)
        cv::rectangle(image,
            textPos - cv::Point(textSize.width / 2, textSize.height / 2) - cv::Point(2, 2),
            textPos + cv::Point(textSize.width / 2, textSize.height / 2) + cv::Point(2, 2),
            cv::Scalar(0, 0, 0), -1);

        // Draw distance text
        cv::putText(image, distanceText, textPos - cv::Point(textSize.width / 2, -textSize.height / 2),
            fontFace, fontScale, textColor, textThickness, cv::LINE_AA);
    }
}

void drawPerimeterText(cv::Mat& image, double bigCirclePerimeter)
{
    // Set text properties
    cv::Scalar textColor(128, 128, 128);  // Gray color
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 2;  // Larger font size
    int thickness = 4;
    cv::Point textOrg(50, 50);  // Position at (100, 100)

    // Prepare the text string
    std::string text = "Perimeter: " + std::to_string(bigCirclePerimeter);

    // Draw the text
    cv::putText(image, text, textOrg, fontFace, fontScale, textColor, thickness);
}