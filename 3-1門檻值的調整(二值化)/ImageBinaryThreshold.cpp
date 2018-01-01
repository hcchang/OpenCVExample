#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

int main(int argc, char** argv)
{
	cv::Mat img, imgResize;
	img = cv::imread("Image.jpg");

	//顯示一些影像的特性
	if (img.data)
	{
		//將影像縮小四倍
		int width = img.cols;
		int height = img.rows;

		cv::resize(img, imgResize, cv::Size(width/4, height/4));

		//利用vector來儲存不同channel的值
		std::vector<cv::Mat> splitImage;
		//將影像的RGB分開
		cv::split(imgResize, splitImage);

		cv::Mat dst;

		cv::threshold(splitImage[1], dst, 100, 255, cv::THRESH_BINARY); //大於100以上的亮度 給值255

		cv::imshow("Bchannel", splitImage[0]);
		cv::imshow("Gchannel", splitImage[1]);
		cv::imshow("Rchannel", splitImage[2]);

		cv::imshow("BinaryImage", dst);

		cv::waitKey(0);

	}
	else
	{
		std::cout << "讀不到影像" << std::endl;
		return -1;
	}

	return 0;
}