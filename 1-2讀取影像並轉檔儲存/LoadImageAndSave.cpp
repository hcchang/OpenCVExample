#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
	cv::Mat img;
	img = cv::imread("lena.bmp");

	cv::namedWindow("Image");

	//顯示一些影像的特性
	if (img.data)
	{
		std::cout << "影像的高: " << img.rows << std::endl;
		std::cout << "影像的寬: " << img.cols << std::endl;

		//顯示影像

		cv::imshow("Image", img);
		cv::waitKey(0);

		//將影像存成不同的格式ex: jpg
		cv::imwrite("out.jpg", img);

	}
	else
	{
		std::cout << "讀不到影像" << std::endl;
		return -1;
	}

	return 0;
}