#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>

#define phi2xy(mat) \
    cv::Point(cvRound(img.cols / 2 + img.cols / 3 * cos(mat.at<float>(0))), \
              cvRound(img.rows / 2 - img.cols / 3 * sin(mat.at<float>(0))))

int mouseX = 0;
int mouseY = 0;

static void onMouse(int _event, int _x, int _y, int _flags, void*)
{
	mouseX = _x;
	mouseY = _y;

	//std::cout << "x 影像座標: " << _x << std::endl;
	//std::cout << "y 影像座標: " << _y << std::endl;

}

int main(int argc, char** argv)
{
	//創建畫布
	cv::Mat img(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));

	//第一個參數是 狀態向量的維度 此為平面 由x, y, dx, dy決定 變量為 dx,dy
	cv::KalmanFilter kalmanFilter(4, 2, 0);

	cv::Mat x_k(4, 1, CV_32F); //此為位置預測方程式

	//雜訊的部分
	cv::Mat w_k(4, 1, CV_32F);

	//觀測結果 2維
	cv::Mat z_k = cv::Mat::zeros(2, 1, CV_32F);
	
	//建立轉移矩陣(F)
	float F[] = { 1, 0, 1, 0, // x, 0, dx, 0,
		          0, 1, 0, 1, // 0, y, 0, dy,
				  0, 0, 1, 0, // 0, 0, dx, 0,
	              0, 0, 0, 1};// 0, 0, 0, dy
	kalmanFilter.transitionMatrix = cv::Mat(4, 4, CV_32F, F).clone(); // F matrix (如果是擴展卡爾曼 需要經常更新此矩陣 為非線性) 

	//初始化其他的矩陣
	cv::setIdentity(kalmanFilter.measurementMatrix, cv::Scalar(1)); // H matrix
	cv::setIdentity(kalmanFilter.processNoiseCov, cv::Scalar(1e-5)); // Q matrix
	cv::setIdentity(kalmanFilter.measurementNoiseCov, cv::Scalar(1e-1)); // R matrix
	cv::setIdentity(kalmanFilter.errorCovPost, cv::Scalar(1)); // (P(k)) : P(k) = (I - K(k)*H)*P'(k)

	//隨機初始化狀態
	cv::randn(kalmanFilter.statePost, 0.0, 0.1);

	char key = 'i';

	cv::imshow("KalmanFilter", img);

	cvSetMouseCallback("KalmanFilter", onMouse);

	while (key != 'o')
	{
		//預測點的位置
		cv::Mat y_k = kalmanFilter.predict();

		z_k = kalmanFilter.measurementMatrix*x_k + z_k;

		cv::Point pz_k(z_k.at<float>(0), z_k.at<float>(1));
		cv::Point py_k(y_k.at<float>(0), y_k.at<float>(1));


		img = cv::Scalar::all(0);
		cv::circle(img, pz_k, 4, cv::Scalar(128, 255, 255));  // 量測(觀測)結果 //黃色
		cv::circle(img, py_k, 4, cv::Scalar(255, 255, 255), 2);  // 預測結果 //白色
		// planar co-ordinates and draw

		cv::imshow("KalmanFilter", img);

		z_k.at<float>(0) = mouseX;
		z_k.at<float>(1) = mouseY;

		kalmanFilter.correct(z_k);

		x_k = kalmanFilter.transitionMatrix*x_k + w_k; //更新狀態函數 //不需要控制方程式

		key = cv::waitKey(100);
	}

	return 0;
}