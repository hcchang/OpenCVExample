#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
	cv::Mat img = cv::Mat(512,512,CV_8UC3,cv::Scalar(255,255,255));

	cv::namedWindow("Image");

	std::cout << "�v������: " << img.rows << std::endl;
	std::cout << "�v�����e: " << img.cols << std::endl;

	//�e�u
	cv::Point p1(50, 50);
	cv::Point p2(150, 150);
	cv::Scalar s1(255, 0, 0); //B
	cv::line(img, p1,p2,s1);
	//�e�b�Y�u
	cv::Point p3(150, 150);
	cv::Point p4(150, 250);
	cv::Scalar s2(0, 0, 255); //R
	cv::arrowedLine(img, p3, p4, s2);
	//�e��
	cv::Point center(256, 256);
	cv::Scalar s3(0, 255, 255); 
	cv::circle(img, center, 50, s3);
	//�e��
	cv::Point p5(250, 150);
	cv::Point p6(350, 250);
	cv::Scalar s4(255, 255, 0);
	cv::rectangle(img, p5, p6, s4);
	//�e���
	cv::ellipse(img, cv::Point(350, 350), cv::Size(70, 40), 30, 0, 360, cv::Scalar(0, 255, 0));
	//�g��r
	cv::putText(img, "Hello", cv::Point(0, 300), 2, 3, cv::Scalar(0, 0, 0));
	
	//��ܼv��

	cv::imshow("Image", img);
	cv::waitKey(0);

	//�N�v���s�����P���榡ex: jpg
	cv::imwrite("out.jpg", img);

	return 0;
}