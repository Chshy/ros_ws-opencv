#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui.hpp>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <opencv_process/d435_subscriber.hpp>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "opencv_process_node");
    ros::NodeHandle nh;
    d435_subscriber d435(nh);

    // ros::spin();

    while (1)
    {
        ros::spinOnce();

        cv::Mat rgb = d435.getCam(D435_RGB_Cam);
        cv::Mat dep = d435.getCam(D435_Depth_Cam);

        if (rgb.rows > 0)
        {
            std::cout << rgb.rows << " " << rgb.cols << std::endl;
            cv::imshow("RGB_Cam", d435.getCam(D435_RGB_Cam));
        }
        // if (dep.rows > 0)
        // {
        //     std::cout << dep.rows << " " << dep.cols << std::endl;
        //     cv::imshow("Depth_Cam", d435.getCam(D435_Depth_Cam));
        // }
        // cv::Mat img = d435.getCam(D435_RGB_Cam);

        // std::cout << img.rows << " " << img.cols << std::endl;

        // cv::imshow("img",img);

        cv::waitKey(1);
    }

    return 0;
}