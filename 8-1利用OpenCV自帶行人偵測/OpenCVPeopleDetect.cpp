#include <iostream>
#include <stdexcept>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <string>


int main(int argc, char** argv)
{
	cv::HOGDescriptor _hog;
	_hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());

	const std::string _videoName = "vtest.avi";

	cv::VideoCapture _video(_videoName);
	cv::Mat _imgMat;

	//_video.open(0);
	if (!_video.isOpened())
	{
		std::cout << "無法讀取影片" << std::endl;
		return -1;
	}
	
	for (;;)
	{
		_video >> _imgMat;

		if (_imgMat.empty())
			return -1;

		std::vector<cv::Rect> found, found_filtered;
		double t = (double)cv::getTickCount();

		_hog.detectMultiScale(_imgMat, found, 0, cv::Size(8, 8), cv::Size(32, 32), 1.05, 2);

		t = (double)cv::getTickCount() - t;
		
		std::cout << "偵測時間: " << (t*1000. / cv::getTickFrequency()) << " ms" << std::endl;

		for (size_t i = 0; i < found.size(); i++)
		{
			cv::Rect r = found[i];

			size_t j;
			
			// 在大的偵測框內，不需要裡面再有小偵測框
			for (j = 0; j < found.size(); j++)
				if (j != i && (r & found[j]) == r)
					break;

			if (j == found.size())
				found_filtered.push_back(r);
		}

		for (size_t i = 0; i < found_filtered.size(); i++)
		{
			cv::Rect r = found_filtered[i];

			//一般HOG的偵測會比實際的大，所以縮小偵測的範圍
			r.x += cvRound(r.width*0.1);
			r.width = cvRound(r.width*0.8);
			r.y += cvRound(r.height*0.07);
			r.height = cvRound(r.height*0.8);
			rectangle(_imgMat, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
		}

		cv::imshow("people detection", _imgMat);
		cv::waitKey(30);
	}

	return 0;
}

