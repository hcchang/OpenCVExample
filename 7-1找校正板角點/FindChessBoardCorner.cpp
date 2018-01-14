#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>


int main(int argc, char** argv)
{
	cv::Mat chessImg = cv::imread("chessboard.jpg");

	cv::Mat chessImgGray;

	int nx = 9;
	int ny = 6;

	std::vector<cv::Point2f > corners;

	if (!chessImg.data)
	{
		std::cout << "無法讀取影像" << std::endl;
		return -1;
	}

	cv::cvtColor(chessImg, chessImgGray, CV_RGB2GRAY);

	int count = cv::findChessboardCorners(chessImgGray, cv::Size(nx, ny), corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
	cv::find4QuadCornerSubpix(chessImgGray, corners, cvSize(11, 11));

	cv::drawChessboardCorners(chessImg, cv::Size(nx, ny), corners, count);

	cv::imshow("corner detection", chessImg);

	cv::waitKey(0);

	return 0;
}