#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/core.hpp>

cv::Mat get_display_img(cv::Mat dep_32fc1, float min_distance, float max_distance) //mm
{

    // threshold(dep_32fc1,dep_32fc1_threshold,)
    // cv::ThresholdTypes;

    // cv::Mat dep_32fc1_threshold(dep_32fc1.rows, dep_32fc1.cols, CV_32FC1);
    cv::Mat valve_cover(dep_32fc1.rows, dep_32fc1.cols, CV_8UC1);
    inRange(dep_32fc1, min_distance, max_distance, valve_cover);

    cv::Mat dep_8uc1(dep_32fc1.rows, dep_32fc1.cols, CV_8UC1);
    cv::Mat Dep_HSV(dep_32fc1.rows, dep_32fc1.cols, CV_8UC3);

    dep_32fc1.convertTo(dep_8uc1, CV_8UC1, 120.0 / max_distance);
    
    std::vector<cv::Mat> channels_hsv;
    cv::Mat blank_ch, full_ch;
    blank_ch = cv::Mat::zeros(cv::Size(dep_8uc1.cols, dep_8uc1.rows), CV_8UC1);
    full_ch = cv::Mat(cv::Size(dep_8uc1.cols, dep_8uc1.rows), CV_8UC1, 255);

    channels_hsv.push_back(dep_8uc1);
    channels_hsv.push_back(full_ch);
    channels_hsv.push_back(valve_cover);

    cv::merge(channels_hsv, Dep_HSV);
    cv::cvtColor(Dep_HSV, Dep_HSV, CV_HSV2BGR);
    return Dep_HSV;
}