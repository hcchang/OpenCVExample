#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>

int main(int argc, char** argv)
{
	cv::Mat img = cv::imread("lena.bmp");
	
	if (img.empty())
	{
		std::cout << "無法讀取檔案" << std::endl;
		return -1;
	}

	cv::Mat imgGray;

	cv::cvtColor(img, img, CV_RGB2GRAY);


	int M = cv::getOptimalDFTSize(img.rows);
	int N = cv::getOptimalDFTSize(img.cols);

	cv::Mat padded;
	cv::copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };

	cv::Mat complexImg;
	cv::merge(planes, 2, complexImg);

	cv::dft(complexImg, complexImg);

	

	// compute log(1 + sqrt(Re(DFT(img))**2 + Im(DFT(img))**2))
	split(complexImg, planes);
	magnitude(planes[0], planes[1], planes[0]);
	cv::Mat mag = planes[0];
	mag += cv::Scalar::all(1);
	log(mag, mag);

	// crop the spectrum, if it has an odd number of rows or columns
	mag = mag(cv::Rect(0, 0, mag.cols & -2, mag.rows & -2));

	int cx = mag.cols / 2;
	int cy = mag.rows / 2;

	// rearrange the quadrants of Fourier image
	// so that the origin is at the image center
	cv::Mat tmp;
	cv::Mat q0(mag, cv::Rect(0, 0, cx, cy));
	cv::Mat q1(mag, cv::Rect(cx, 0, cx, cy));
	cv::Mat q2(mag, cv::Rect(0, cy, cx, cy));
	cv::Mat q3(mag, cv::Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(mag, mag, 0, 1, cv::NORM_MINMAX);

	imshow("spectrum magnitude", mag);

	cv::waitKey(0);

	return 0;
}