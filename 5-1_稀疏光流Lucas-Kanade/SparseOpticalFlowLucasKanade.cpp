#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(int argc, char** argv)
{
	
	cv::Mat imgA = cv::imread("Img1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat imgB = cv::imread("Img2.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	cv::resize(imgA, imgA, cv::Size(imgA.cols / 2, imgA.rows / 2));
	cv::resize(imgB, imgB, cv::Size(imgB.cols / 2, imgB.rows / 2));

	cv::Size img_sz = imgA.size();
	int win_size = 10;
	cv::Mat imgC = cv::imread("Img2.jpg", CV_LOAD_IMAGE_UNCHANGED);
	cv::resize(imgC, imgC, cv::Size(imgC.cols / 2, imgC.rows / 2));

	//�ˬd�Ϥ��O�_���n���S�x�I�ȱo�l��

	std::vector< cv::Point2f > cornersA, cornersB;
	const int MAX_CORNERS = 500;
	cv::goodFeaturesToTrack(imgA, cornersA, MAX_CORNERS,  0.01,5, cv::noArray(), 3, false, 0.04 );

	//�A���S�x�I����Ӫ�subpixel

	cv::cornerSubPix(imgA,cornersA, cv::Size(win_size, win_size), cv::Size(-1, -1), 
		cv::TermCriteria(cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,20,0.03 ));

	// �ϥ� Lucas Kanade ���y��k
	//
	std::vector<uchar> features_found;
	cv::calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, cv::noArray(), cv::Size(win_size * 2 + 1, win_size * 2 + 1),  
		5, cv::TermCriteria(cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS, 20, 0.3  ));

	//�N�C�ӯS�x�I�ݬO�_����X�������I�A�p�G���õe�Xpixel�����ʪ��Z��
	
	for (int i = 0; i < static_cast<int>(cornersA.size()); ++i) {
		if (!features_found[i]) {
			continue;
		}
		cv::line(imgC, cornersA[i], cornersB[i], cv::Scalar(0, 255, 0), 1);
	}

	cv::imshow("ImageA", imgA);
	cv::imshow("ImageB", imgB);
	cv::imshow("LK Optical Flow Example", imgC);
	cv::waitKey(0);

	return 0;
	cv::waitKey(0);

	return 0;
}