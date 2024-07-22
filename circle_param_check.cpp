#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

const int MAX_DP = 10;
const int MAX_MIN_DIST = 500;
const int MAX_PARAM1 = 300;
const int MAX_PARAM2 = 200;
const int MAX_RADIUS = 1000;

int main()
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
    std::string filename = R"(C:\CODE\1.image\circle_pattern.png)";
    cv::Mat image = cv::imread(filename, cv::IMREAD_ANYCOLOR);

    if (image.empty())
    {
        std::cout << "load file failed" << std::endl;
        return 1;
    }

    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    cv::namedWindow("Circles", cv::WINDOW_NORMAL);
    cv::resizeWindow("Circles", 800, 600);

    int dp = 2; // dp * 0.1 to get actual value
    int minDist = 100;
    int param1 = 800;
    int param2 = 100;
    int minRadius = 20;
    int maxRadius = 900;

    cv::createTrackbar("dp * 10", "Circles", &dp, MAX_DP);
    cv::createTrackbar("minDist", "Circles", &minDist, MAX_MIN_DIST);
    cv::createTrackbar("param1", "Circles", &param1, MAX_PARAM1);
    cv::createTrackbar("param2", "Circles", &param2, MAX_PARAM2);
    cv::createTrackbar("minRadius", "Circles", &minRadius, MAX_RADIUS);
    cv::createTrackbar("maxRadius", "Circles", &maxRadius, MAX_RADIUS);

    while (true)
    {
        cv::Mat output = image.clone();
        std::vector<cv::Vec3f> circles;

        double dpValue = dp * 0.1; // Convert to actual dp value
        cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, dpValue, minDist, param1, param2, minRadius, maxRadius);

        for (size_t i = 0; i < circles.size(); i++)
        {
            cv::Vec3i c = circles[i];
            cv::Point center = cv::Point(c[0], c[1]);
            int radius = c[2];
            cv::circle(output, center, radius, cv::Scalar(255, 20, 147), 3, cv::LINE_AA);
        }

        cv::imshow("Circles", output);

        // Display current parameter values
        cv::Mat paramDisplay = cv::Mat::zeros(100, 400, CV_8UC3);
        cv::putText(paramDisplay, "dp: " + std::to_string(dpValue), cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        cv::putText(paramDisplay, "minDist: " + std::to_string(minDist), cv::Point(10, 40), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        cv::putText(paramDisplay, "param1: " + std::to_string(param1), cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        cv::putText(paramDisplay, "param2: " + std::to_string(param2), cv::Point(10, 80), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        cv::putText(paramDisplay, "minRadius: " + std::to_string(minRadius), cv::Point(200, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        cv::putText(paramDisplay, "maxRadius: " + std::to_string(maxRadius), cv::Point(200, 40), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
        cv::imshow("Parameters", paramDisplay);

        char key = (char)cv::waitKey(10);
        if (key == 27) // ESC key
            break;
    }

    cv::destroyAllWindows();
    return 0;
}