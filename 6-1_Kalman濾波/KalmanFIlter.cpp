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
	//�Ыصe��
	cv::Mat img(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));

	//�Ĥ@�ӰѼƬO ���A�V�q������ �������� �� ���שM���t�� �M�w
	cv::KalmanFilter kalmanFilter(2, 1, 0);

	cv::Mat x_k(2, 1, CV_32F); //������m�w����{��
	cv::randn(x_k, 0., 1);
	//���T������
	cv::Mat w_k(2, 1, CV_32F);

	//�[�����G ���� 1��
	cv::Mat z_k = cv::Mat::zeros(1, 1, CV_32F);
	
	//�إ��ಾ�x�}(F)
	float F[] = { 1, 1, 0, 1 };
	kalmanFilter.transitionMatrix = cv::Mat(2, 2, CV_32F, F).clone();

	//��l�ƨ�L���x�}
	cv::setIdentity(kalmanFilter.measurementMatrix, cv::Scalar(1));
	cv::setIdentity(kalmanFilter.processNoiseCov, cv::Scalar(1e-5));
	cv::setIdentity(kalmanFilter.measurementNoiseCov, cv::Scalar(1e-1));
	cv::setIdentity(kalmanFilter.errorCovPost, cv::Scalar(1));

	//�H����l�ƪ��A
	cv::randn(kalmanFilter.statePost, 0.0, 0.1);

	char key = 'i';

	while (key != 'o')
	{
		//�w���I����m
		cv::Mat y_k = kalmanFilter.predict();

		cv::randn(z_k, 0.0, sqrt(static_cast<double>(kalmanFilter.measurementNoiseCov.at<float>(0, 0))));
		z_k = kalmanFilter.measurementMatrix*x_k + z_k;

		img = cv::Scalar::all(0);
		cv::circle(img, phi2xy(z_k), 4, cv::Scalar(128, 255, 255));  // �q��(�[��)���G //����
		cv::circle(img, phi2xy(y_k), 4, cv::Scalar(255, 255, 255), 2);  // �w�����G //�զ�
		cv::circle(img, phi2xy(x_k), 4, cv::Scalar(0, 0, 255));  // ��ڵ��G //����
		// planar co-ordinates and draw

		cv::imshow("KalmanFilter", img);

		kalmanFilter.correct(z_k);

		cv::randn(w_k, 0.0, sqrt(static_cast<double>(kalmanFilter.processNoiseCov.at<float>(0, 0))));
		x_k = kalmanFilter.transitionMatrix*x_k + w_k; //��s���A��� //���ݭn�����{��

		key = cv::waitKey(100);
	}

	return 0;
}