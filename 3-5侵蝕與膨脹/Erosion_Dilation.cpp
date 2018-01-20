#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>



int main(int argc, char** argv)
{
	cv::Mat img = cv::imread("test.jpg", 0);

	cv::Mat imgE, imgD;

	if (img.empty())
	{
		std::cout << "無法讀取圖片" << std::endl;
		return -1;
	}

	cv::Mat element1 = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(30, 30));

	cv::erode(img, imgE, element1);
	
	cv::imshow("erod", imgE);

	cv::waitKey(0);

	cv::Mat element2 = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(10, 10));

	cv::dilate(imgE, imgD, element2);

	cv::imshow("dilate", imgD);

	cv::waitKey(0);

	return 0;
}