#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/core.hpp>

cv::Mat get_display_img(cv::Mat dep_32fc1, float min_distance, float max_distance) //mm
{
    //valve_cover为二值化图像，有效范围内的为255，外的为0，用于标记可信数据(其实是在显示图像上把没用的数据覆盖掉)
    cv::Mat valve_cover(dep_32fc1.rows, dep_32fc1.cols, CV_8UC1);
    inRange(dep_32fc1, min_distance, max_distance, valve_cover);

    //用于数据处理
    //dep_16uc1是16bit单通道图像，与dep_32fc1之间等值(因为dep_32fc1只出现整数且最大值为65535)
    cv::Mat dep_16uc1(dep_32fc1.rows, dep_32fc1.cols, CV_16UC1);
    dep_32fc1.convertTo(dep_16uc1, CV_16UC1);

    //去除不信任数据
    threshold(dep_32fc1,dep_32fc1,min_distance,0xFFFF,CV_THRESH_TOZERO);//将比最小信任距离小的点归零
    threshold(dep_32fc1,dep_32fc1,max_distance,0xFFFF,CV_THRESH_TOZERO_INV);//将比最大信任距离大的点归零
    
    //显示用图像
    cv::Mat Dep_HSV(dep_32fc1.rows, dep_32fc1.cols, CV_8UC3);
    //dep_8uc1为8bit单通道图像，用于显示
    cv::Mat dep_8uc1(dep_32fc1.rows, dep_32fc1.cols, CV_8UC1);
    //转换格式，将最大信任值以内的数值（包括小于最小信任值的）归一化到120（仍然可能出现大于120的值）
    dep_32fc1.convertTo(dep_8uc1, CV_8UC1, 120.0 / max_distance);

    //用于显示的部分
    std::vector<cv::Mat> channels_hsv;
    cv::Mat blank_ch, full_ch;
    blank_ch = cv::Mat::zeros(cv::Size(dep_8uc1.cols, dep_8uc1.rows), CV_8UC1);
    full_ch = cv::Mat(cv::Size(dep_8uc1.cols, dep_8uc1.rows), CV_8UC1, 255);
    //合成HSV图像
    channels_hsv.push_back(dep_8uc1);
    channels_hsv.push_back(full_ch);
    channels_hsv.push_back(valve_cover);
    return Dep_HSV;
}