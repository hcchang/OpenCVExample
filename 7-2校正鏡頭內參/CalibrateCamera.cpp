#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <string>


int main(int argc, char** argv)
{
	// 確認chessboard的角點 長和寬
	cv::Size boardSize;
	boardSize.width = 9;
	boardSize.height = 6;
	int imageNum = 9;
	float squareSize = 100.0; // millmeter

	std::vector<cv::Mat> images;

	std::vector<std::vector<cv::Point3f>> worldObj;
	std::vector<std::vector<cv::Point2f>> imgObj;

	cv::Mat cameraIntrinsic = cv::Mat::eye(3, 3, CV_64F);
	cv::Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F);

	std::vector<cv::Mat> rotatVecs, transVecs;

	//int to string
	for (int i = 0; i < imageNum; i++)
	{
		std::stringstream num; 
		num << i+1;
		std::string fileName = "left0" + num.str() + ".jpg";
		std::cout << "檔案名稱: " << fileName << std::endl;
		cv::Mat img = cv::imread(fileName, 0);
		images.push_back(img);
		if (images[i].empty())
		{
			std::cout << "讀圖失敗" << std::endl;
			return -1;
		}

		cv::imshow("image", images[i]);
		cv::waitKey(0);

		std::vector<cv::Point2f> corners;

		int count = cv::findChessboardCorners(images[i], boardSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
		cv::find4QuadCornerSubpix(images[i], corners, cvSize(11, 11));

		imgObj.push_back(corners);

		std::vector<cv::Point3f> objects;
		for (int _i = 0; _i < boardSize.height; _i++)
		{
			for (int _j = 0; _j < boardSize.width; _j++)
			{
				cv::Point3f point(_j*squareSize, _i*squareSize, 0);
				objects.push_back(point);
			}
		}

		worldObj.push_back(objects);

	}

	cv::Size imgSize(images[0].cols, images[0].rows);


	cv::calibrateCamera(worldObj, imgObj, imgSize, cameraIntrinsic, distCoeffs, rotatVecs, transVecs);

	bool calibratedValueOk = cv::checkRange(cameraIntrinsic) && cv::checkRange(distCoeffs);

	if (!calibratedValueOk)
	{
		std::cout << "校正失敗" << std::endl;
		return -1;
	}

	std::cout << "Camera Intrinsic: " << std::endl;
	std::cout << "Camera cx: " << cameraIntrinsic.at<double>(0, 2) <<  std::endl;
	std::cout << "Camera cy: " << cameraIntrinsic.at<double>(1, 2) << std::endl;
	std::cout << "Camera fx: " << cameraIntrinsic.at<double>(0, 0) << std::endl;
	std::cout << "Camera fy: " << cameraIntrinsic.at<double>(1, 1) << std::endl;

	std::cout << "Camera Distorsion: " << std::endl;
	std::cout << "Camera k1: " << distCoeffs.at<double>(0, 0) << std::endl;
	std::cout << "Camera k2: " << distCoeffs.at<double>(0, 1) << std::endl;
	std::cout << "Camera k3: " << distCoeffs.at<double>(0, 2) << std::endl;
	std::cout << "Camera p1: " << distCoeffs.at<double>(0, 3) << std::endl;
	std::cout << "Camera p2: " << distCoeffs.at<double>(0, 4) << std::endl;

	return 0;
}