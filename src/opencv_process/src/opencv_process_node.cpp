#include <cv_bridge/cv_bridge.h>

#include <opencv2/opencv.hpp>

#include <opencv2/highgui.hpp>

#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/core/base.hpp>

#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <opencv_process/d435_subscriber.hpp>

#include <opencv_process/dep_img_proc.hpp>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "opencv_process_node");
    ros::NodeHandle nh;

    d435_subscriber d435(nh);

    while (1)
    {
        ros::spinOnce();

        if (d435.RGB_sub.new_img_come())
        {
            cv::imshow("rgb", d435.RGB_sub.get_cv_img());
            // std::cout << "rgb = " << d435.RGB_sub.get_cv_img().type() << std::endl;
        }

        if (d435.Depth_sub.new_img_come())
        {

            cv::imshow("R", get_display_img(d435.Depth_sub.get_cv_img(), 50, 3000));
        }

        cv::waitKey(1);
    }

    return 0;
}