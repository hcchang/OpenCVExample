#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>

int main(int argc, char** argv)
{
	cv::Mat img = cv::imread("building.jpg");
	cv::Mat img_gray;
	cv::Mat img_canny;
	std::vector<cv::Vec2f> HoughLines;

	cv::resize(img, img, cv::Size(512,512));

	cv::cvtColor(img,img_gray,CV_RGB2GRAY);

	cv::Canny(img_gray,img_canny,30,100,3,false);

	cv::HoughLines(img_canny, HoughLines, 1, CV_PI / 180, 150, 0, 0);

	cv::cvtColor(img_canny, img_canny, CV_GRAY2RGB);

	std::cout << "HoughLines size: " << HoughLines.size() << std::endl;

	for (size_t i = 0; i < HoughLines.size(); i++)
	{
		float rho = HoughLines[i][0], theta = HoughLines[i][1];
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		cv::line(img_canny, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
		
	}

	cv::imshow("HoughLine", img_canny);

	cv::waitKey(0);

	return 0;
}