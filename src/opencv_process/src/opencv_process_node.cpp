#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <opencv_process/d435_subscriber.hpp>

#include <opencv_process/image_converter.hpp>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "opencv_process_node");
    ros::NodeHandle nh;

    image_converter usbcam(nh, "/usb_cam/image_raw", 10, sensor_msgs::image_encodings::BGR8);

    while (1)
    {
        ros::spinOnce();
        if (usbcam.new_img_come())
        {
            cv::Mat src = usbcam.get_cv_img();
            cv::imshow("src", src);
        }
        cv::waitKey(1);
    }

    return 0;
}