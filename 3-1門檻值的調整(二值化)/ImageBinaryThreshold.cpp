#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

int main(int argc, char** argv)
{
	cv::Mat img, imgResize;
	img = cv::imread("Image.jpg");

	//��ܤ@�Ǽv�����S��
	if (img.data)
	{
		//�N�v���Y�p�|��
		int width = img.cols;
		int height = img.rows;

		cv::resize(img, imgResize, cv::Size(width/4, height/4));

		//�Q��vector���x�s���Pchannel����
		std::vector<cv::Mat> splitImage;
		//�N�v����RGB���}
		cv::split(imgResize, splitImage);

		cv::Mat dst;

		cv::threshold(splitImage[1], dst, 100, 255, cv::THRESH_BINARY); //�j��100�H�W���G�� ����255

		cv::imshow("Bchannel", splitImage[0]);
		cv::imshow("Gchannel", splitImage[1]);
		cv::imshow("Rchannel", splitImage[2]);

		cv::imshow("BinaryImage", dst);

		cv::waitKey(0);

	}
	else
	{
		std::cout << "Ū����v��" << std::endl;
		return -1;
	}

	return 0;
}