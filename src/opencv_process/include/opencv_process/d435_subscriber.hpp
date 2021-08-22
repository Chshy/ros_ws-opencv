#pragma once

#include <opencv2/highgui.hpp>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <string.h>











enum D435_Cam_Type
{
    D435_RGB_Cam = 0,
    D435_Depth_Cam = 1
};

class d435_subscriber
{
private:
    // 句柄
    ros::NodeHandle nh;
    // 订阅Topic
    ros::Subscriber RGB_sub;
    ros::Subscriber Depth_sub;

    // 未转换的图像
    sensor_msgs::Image RGB_Cam_ros;
    sensor_msgs::Image Depth_Cam_ros;

    // 转换后的图像
    cv::Mat RGB_Cam;
    cv::Mat Depth_Cam;

    static const std::string converted_format[2];

public:
    d435_subscriber(ros::NodeHandle &_nh, const std::string &RGB_topic, const std::string &Depth_topic, uint32_t queue_size);
    ~d435_subscriber();
    cv::Mat getCam(D435_Cam_Type cam);
    void RGB_cb(const sensor_msgs::Image::ConstPtr &msg);
    void Depth_cb(const sensor_msgs::Image::ConstPtr &msg);
};

// 构造函数
d435_subscriber::d435_subscriber(ros::NodeHandle &_nh,
                                 const std::string &RGB_topic = "/camera/color/image_raw",
                                 const std::string &Depth_topic = "/camera/depth/image_rect_raw",
                                 uint32_t queue_size = 10)
{
    nh = _nh;
    RGB_sub = nh.subscribe<sensor_msgs::Image>(RGB_topic, queue_size, &d435_subscriber::RGB_cb, this);
    Depth_sub = nh.subscribe<sensor_msgs::Image>(Depth_topic, queue_size, &d435_subscriber::Depth_cb, this);
}

// 析构函数
d435_subscriber::~d435_subscriber()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////

// 提取图像
cv::Mat d435_subscriber::getCam(D435_Cam_Type cam = D435_RGB_Cam)
{
    switch (cam)
    {
    case D435_RGB_Cam:
        return this->RGB_Cam;

    case D435_Depth_Cam:
        return this->Depth_Cam;
    }
}





//////////////////////////////////////////////////////////////////////////////////////////////

// 回调函数

void d435_subscriber::RGB_cb(const sensor_msgs::Image::ConstPtr &msg)
{
    static const std::string converted_format = sensor_msgs::image_encodings::BGR8;

    ROS_INFO("RGB_CB");
    try
    {
        ROS_INFO("RGB:%s", msg->encoding.c_str());
        this->RGB_Cam = cv_bridge::toCvShare(msg, converted_format)->image;
    }
    catch (cv_bridge::Exception &e)
    {
        ROS_ERROR("RGB:Could not convert from '%s' to '%s'.", msg->encoding.c_str(), converted_format);
    }
    return;
}
void d435_subscriber::Depth_cb(const sensor_msgs::Image::ConstPtr &msg)
{
    static const std::string converted_format = sensor_msgs::image_encodings::TYPE_32FC1;

    ROS_INFO("DEP_CB");
    try
    {
        ROS_INFO("DEPTH:%s", msg->encoding.c_str());
        this->Depth_Cam = cv_bridge::toCvShare(msg, converted_format)->image;
    }
    catch (cv_bridge::Exception &e)
    {
        ROS_ERROR("DEPTH:Could not convert from '%s' to '%s'.", msg->encoding.c_str(), converted_format);
    }
    return;
}







