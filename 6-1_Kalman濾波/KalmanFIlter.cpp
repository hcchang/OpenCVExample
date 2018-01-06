#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>

#define phi2xy(mat) \
    cv::Point(cvRound(img.cols / 2 + img.cols / 3 * cos(mat.at<float>(0))), \
              cvRound(img.rows / 2 - img.cols / 3 * sin(mat.at<float>(0))))

int main(int argc, char** argv)
{
	//創建畫布
	cv::Mat img(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));

	//第一個參數是 狀態向量的維度 此為平面 由 角度和角速度 決定
	cv::KalmanFilter kalmanFilter(2, 1, 0);

	cv::Mat x_k(2, 1, CV_32F); //此為位置預測方程式
	cv::randn(x_k, 0., 1);
	//雜訊的部分
	cv::Mat w_k(2, 1, CV_32F);

	//觀測結果 角度 1維
	cv::Mat z_k = cv::Mat::zeros(1, 1, CV_32F);
	
	//建立轉移矩陣(F)
	float F[] = { 1, 1, 0, 1 };
	kalmanFilter.transitionMatrix = cv::Mat(2, 2, CV_32F, F).clone();

	//初始化其他的矩陣
	cv::setIdentity(kalmanFilter.measurementMatrix, cv::Scalar(1));
	cv::setIdentity(kalmanFilter.processNoiseCov, cv::Scalar(1e-5));
	cv::setIdentity(kalmanFilter.measurementNoiseCov, cv::Scalar(1e-1));
	cv::setIdentity(kalmanFilter.errorCovPost, cv::Scalar(1));

	//隨機初始化狀態
	cv::randn(kalmanFilter.statePost, 0.0, 0.1);

	char key = 'i';

	while (key != 'o')
	{
		//預測點的位置
		cv::Mat y_k = kalmanFilter.predict();

		cv::randn(z_k, 0.0, sqrt(static_cast<double>(kalmanFilter.measurementNoiseCov.at<float>(0, 0))));
		z_k = kalmanFilter.measurementMatrix*x_k + z_k;

		img = cv::Scalar::all(0);
		cv::circle(img, phi2xy(z_k), 4, cv::Scalar(128, 255, 255));  // 量測(觀測)結果 //黃色
		cv::circle(img, phi2xy(y_k), 4, cv::Scalar(255, 255, 255), 2);  // 預測結果 //白色
		cv::circle(img, phi2xy(x_k), 4, cv::Scalar(0, 0, 255));  // 實際結果 //紅色
		// planar co-ordinates and draw

		cv::imshow("KalmanFilter", img);

		kalmanFilter.correct(z_k);

		cv::randn(w_k, 0.0, sqrt(static_cast<double>(kalmanFilter.processNoiseCov.at<float>(0, 0))));
		x_k = kalmanFilter.transitionMatrix*x_k + w_k; //更新狀態函數 //不需要控制方程式

		key = cv::waitKey(100);
	}

	return 0;
}