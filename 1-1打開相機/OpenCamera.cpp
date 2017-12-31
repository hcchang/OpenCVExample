#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
	cv::VideoCapture webCam(0);
	if (!webCam.isOpened())
		return -1;

	char key = 'i';
	cv::namedWindow("Image");

	while (key != 'o')
	{
		cv::Mat imgFrame;
		webCam >> imgFrame;

		cv::imshow("Image", imgFrame);
		
		key = cv::waitKey(30);
	}

	return 0;
}