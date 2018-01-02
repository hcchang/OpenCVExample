#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>

int main(int argc, char** argv)
{
	cv::Mat img = cv::imread("Image.png");
	cv::Mat img_gray;
	cv::Mat img_canny;

	cv::cvtColor(img,img_gray,CV_RGB2GRAY);

	cv::Canny(img_gray,img_canny,30,50,3,false);

	cv::imshow("Canny", img_canny);

	cv::waitKey(0);

	return 0;
}