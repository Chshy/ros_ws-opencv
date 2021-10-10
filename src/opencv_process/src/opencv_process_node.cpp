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


            cv::imshow("R", get_display_img(d435.Depth_sub.get_cv_img(),50,3000));

            // cv::Mat dep_32fc1 = d435.Depth_sub.get_cv_img();
            // cv::Mat dep_8uc1(dep_32fc1.rows, dep_32fc1.cols, CV_8UC1);
            // cv::Mat Dep_HSV(dep_32fc1.rows, dep_32fc1.cols, CV_8UC3);
            // //CV_8UC3;

            // // cv::GaussianBlur(dep_32fc1, dep_32fc1, cv::Size(5, 5), 1, 1);
            // // cv::medianBlur(dep_32fc1, dep_32fc1, 5);


            // double minv = 0.0, maxv = 0.0;
            // double *minp = &minv;
            // double *maxp = &maxv;
            // minMaxIdx(dep_32fc1, minp, maxp);

            // ROS_INFO("min=%f max=%f",minv,maxv);

            // dep_32fc1.convertTo(dep_8uc1, CV_8UC1, 120.0 / (maxv - minv)); //映射到0-120

            


            // std::vector<cv::Mat> channels_hsv;
            // cv::Mat blank_ch,full_ch;
            // blank_ch = cv::Mat::zeros(cv::Size(dep_8uc1.cols, dep_8uc1.rows), CV_8UC1);
            // full_ch = cv::Mat(cv::Size(dep_8uc1.cols, dep_8uc1.rows), CV_8UC1, 255);

            // channels_hsv.push_back(dep_8uc1);
            // channels_hsv.push_back(full_ch);
            // channels_hsv.push_back(full_ch);

            // cv::merge(channels_hsv, Dep_HSV);
            // cv::cvtColor(Dep_HSV, Dep_HSV, CV_HSV2BGR);
            // cv::imshow("R", Dep_HSV);




        }

        cv::waitKey(1);
    }

    return 0;
}