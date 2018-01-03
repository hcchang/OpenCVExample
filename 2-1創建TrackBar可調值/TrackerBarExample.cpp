#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

/// Global Variables
const int r_slider_max = 100;
const int g_slider_max = 100;
const int b_slider_max = 100;
int r_slider=50;
int g_slider=50;
int b_slider=50;


cv::Mat img;
cv::Mat imgResize;
cv::Mat imgOut;


void on_trackbarR(int value, void*)
{
	imgOut = imgOut.clone();

	int tmpValue = 0;

	for (int i = 0; i < imgResize.rows; i++)
	{
		for (int j = 0; j < imgResize.cols; j++)
		{
			tmpValue = (int)imgResize.at<cv::Vec3b>(i, j)[2] * (value) / 100;
			imgOut.at<cv::Vec3b>(i, j)[2] = tmpValue;
		}
	}

	imshow("ImageRGBChannel", imgOut);
}

void on_trackbarG(int value, void*)
{
	imgOut = imgOut.clone();

	int tmpValue = 0;

	for (int i = 0; i < imgResize.rows; i++)
	{
		for (int j = 0; j < imgResize.cols; j++)
		{
			tmpValue = (int)imgResize.at<cv::Vec3b>(i, j)[1] * (value) / 100;
			imgOut.at<cv::Vec3b>(i, j)[1] = tmpValue;
		}
	}

	imshow("ImageRGBChannel", imgOut);
}

void on_trackbarB(int value, void*)
{
	imgOut = imgOut.clone();

	int tmpValue = 0;

	for (int i = 0; i < imgResize.rows; i++)
	{
		for (int j = 0; j < imgResize.cols; j++)
		{
			tmpValue = (int)imgResize.at<cv::Vec3b>(i, j)[0] * (value) / 100;
			imgOut.at<cv::Vec3b>(i, j)[0] = tmpValue;
		}
	}

	imshow("ImageRGBChannel", imgOut);
}

int main(int argc, char** argv)
{
	/// Read image ( same size, same type )
	img = cv::imread("Image.jpg");

	if (!img.data) { 
		std::cout << "無法讀到檔案" << std::endl;
		return -1; 
	}

	//將影像縮小四倍
	int width = img.cols;
	int height = img.rows;

	cv::resize(img, imgResize, cv::Size(width / 4, height / 4));

	imgOut = imgResize.clone();
	/// Initialize values
	r_slider = 0;
	g_slider = 0;
	b_slider = 0;

	/// Create Windows
	cv::namedWindow("ImageRGBChannel", 1);

	/// Create Trackbars
	char* RTrackbarName = "RChannel";
	char* GTrackbarName = "GChannel";
	char* BTrackbarName = "BChannel";

	cv::createTrackbar(RTrackbarName, "ImageRGBChannel", &r_slider, r_slider_max, on_trackbarR);
	cv::createTrackbar(GTrackbarName, "ImageRGBChannel", &g_slider, g_slider_max, on_trackbarG);
	cv::createTrackbar(BTrackbarName, "ImageRGBChannel", &b_slider, b_slider_max, on_trackbarB);

	/// Show some stuff
	on_trackbarR(r_slider, 0);
	on_trackbarG(g_slider, 0);
	on_trackbarB(b_slider, 0);


	/// Wait until user press some key
	cv::waitKey(0);
	return 0;
}