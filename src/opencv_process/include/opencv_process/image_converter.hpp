#pragma once

#include <opencv2/highgui.hpp>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <string.h>

class image_converter
{
private:
    ros::NodeHandle nh;
    ros::Subscriber ros_topic_sub;
    std::string converted_format;

    sensor_msgs::Image ros_img;
    cv::Mat cv_img;

    uint32_t ros_img_ind;
    uint32_t cv_img_ind;
    bool cv_img_read;

public:
    image_converter(ros::NodeHandle &_nh, const std::string &_topic, uint32_t queue_size, const std::string &_format);
    ~image_converter();
    void img_cb(const sensor_msgs::Image::ConstPtr &msg);
    void convert();
    cv::Mat get_cv_img(bool do_convert, bool do_mark);
    bool new_img_come();
};

image_converter::image_converter(ros::NodeHandle &_nh,
                                 const std::string &_topic,
                                 uint32_t queue_size = 10,
                                 const std::string &_format = sensor_msgs::image_encodings::BGR8)
{
    nh = _nh;

    converted_format = _format;
    ros_img_ind = 0;
    cv_img_ind = 0;
    cv_img_read = true;

    ros_topic_sub = nh.subscribe<sensor_msgs::Image>(_topic, queue_size, &image_converter::img_cb, this);
}

image_converter::~image_converter()
{
}


void image_converter::img_cb(const sensor_msgs::Image::ConstPtr &msg)
{
    ros_img = *msg;
    ros_img_ind++;
    return;
}

void image_converter::convert()
{
    if (cv_img_ind != ros_img_ind)
    {
        try
        {
            this->cv_img = cv_bridge::toCvCopy(ros_img, converted_format)->image;
        }
        catch (cv_bridge::Exception &e)
        {
            ROS_ERROR("Could not convert from '%s' to '%s'.", ros_img.encoding.c_str(), converted_format.c_str());
        }
        cv_img_read = false;
    }
    return;
}

cv::Mat image_converter::get_cv_img(bool do_convert = true, bool do_mark = true)
{
    if (do_convert)
    {
        convert();
    }
    if (do_mark)
    {
        cv_img_read = true;
    }
    return this->cv_img;
}

bool image_converter::new_img_come()
{
    return (ros_img_ind != cv_img_ind);
}
