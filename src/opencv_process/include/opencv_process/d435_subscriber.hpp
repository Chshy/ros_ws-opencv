#pragma once

#include <opencv2/highgui.hpp>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <string.h>

#include <opencv_process/image_converter.hpp>

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

    

public:
    image_converter RGB_sub;
    image_converter Depth_sub;

    d435_subscriber(ros::NodeHandle &_nh, const std::string &RGB_topic, const std::string &Depth_topic, uint32_t queue_size);
    ~d435_subscriber();
    cv::Mat getCam(D435_Cam_Type cam);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////


// 构造函数
d435_subscriber::d435_subscriber(ros::NodeHandle &_nh,
                                 const std::string &RGB_topic = "/camera/color/image_raw",
                                 const std::string &Depth_topic = "/camera/aligned_depth_to_color/image_raw",
                                 uint32_t queue_size = 10)
                                 
                                : RGB_sub(_nh, RGB_topic, queue_size, sensor_msgs::image_encodings::BGR8)
                                , Depth_sub(_nh, Depth_topic, queue_size, sensor_msgs::image_encodings::TYPE_32FC1)
{
    nh = _nh;
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
        return this->RGB_sub.get_cv_img();

    case D435_Depth_Cam:
        return this->Depth_sub.get_cv_img();
    }
}


/////

//////////////////////////////////////////////////////////////////////////////////////////////
