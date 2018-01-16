#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int x = 0;
int y = 0;

static void onMouse(int _event, int _x, int _y, int _flags, void*)
{

	std::cout << "x �v���y��: " << _x << std::endl;
	std::cout << "y �v���y��: " << _y << std::endl;

}

int main(int argc, char** argv)
{
	cv::Mat img;
	img = cv::imread("lena.bmp");

	cv::namedWindow("Image");

	if (!img.data)
	{
		std::cout << "�L�kŪ���v��" << std::endl;
		return -1;
	}

	cv::imshow("Image", img);

	cvSetMouseCallback("Image", onMouse);

	cv::waitKey(0);

	
	

	return 0;
}