#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
	cv::Mat img;
	img = cv::imread("lena.bmp");

	cv::namedWindow("Image");

	//��ܤ@�Ǽv�����S��
	if (img.data)
	{
		std::cout << "�v������: " << img.rows << std::endl;
		std::cout << "�v�����e: " << img.cols << std::endl;

		//��ܼv��

		cv::imshow("Image", img);
		cv::waitKey(0);

		//�N�v���s�����P���榡ex: jpg
		cv::imwrite("out.jpg", img);

	}
	else
	{
		std::cout << "Ū����v��" << std::endl;
		return -1;
	}

	return 0;
}