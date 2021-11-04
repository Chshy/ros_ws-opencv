#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <opencv_process/d435_subscriber.hpp>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "opencv_process_node");
    ros::NodeHandle nh;

    d435_subscriber d435(nh);

    while (1)
    {
        ros::spinOnce();

        if (d435.new_img_pair_come())
        {
            cv::Mat RGB_src = d435.getCam(D435_RGB_Cam);
            cv::Mat Dep_src = d435.getCam(D435_Depth_Cam, 50, 1000);
            cv::Mat Dep_display = d435.getDepDisplay(Dep_src);
            cv::Mat Binding;
            cv::addWeighted(RGB_src, 0.5, Dep_display, 0.5, 3, Binding);
            cv::imshow("binding", Binding);
            // //先用（9，9）的闭运算清除深度图中的空洞
            // cv::morphologyEx(Dep_src, Dep_src, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9)));
            // //然后用非对称卷积核找竖直方向的countor
            // //可视场地内容适当缩短长边
            // cv::morphologyEx(Dep_src, Dep_src, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 159)));
            // cv::morphologyEx(Dep_src, Dep_src, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 159)));
            // Dep_display = d435.getDepDisplay(Dep_src);
            // cv::addWeighted(RGB_src, 0.5, Dep_display, 0.5, 3, Binding);
            // cv::imshow("process", Binding);
        }

        cv::waitKey(1);
    }

    return 0;
}