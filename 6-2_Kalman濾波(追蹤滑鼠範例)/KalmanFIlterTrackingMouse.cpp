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

	//std::cout << "x �v���y��: " << _x << std::endl;
	//std::cout << "y �v���y��: " << _y << std::endl;

}

int main(int argc, char** argv)
{
	//�Ыصe��
	cv::Mat img(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));

	//�Ĥ@�ӰѼƬO ���A�V�q������ �������� ��x, y, dx, dy�M�w �ܶq�� dx,dy
	cv::KalmanFilter kalmanFilter(4, 2, 0);

	cv::Mat x_k(4, 1, CV_32F); //������m�w����{��

	//���T������
	cv::Mat w_k(4, 1, CV_32F);

	//�[�����G 2��
	cv::Mat z_k = cv::Mat::zeros(2, 1, CV_32F);
	
	//�إ��ಾ�x�}(F)
	float F[] = { 1, 0, 1, 0, // x, 0, dx, 0,
		          0, 1, 0, 1, // 0, y, 0, dy,
				  0, 0, 1, 0, // 0, 0, dx, 0,
	              0, 0, 0, 1};// 0, 0, 0, dy
	kalmanFilter.transitionMatrix = cv::Mat(4, 4, CV_32F, F).clone(); // F matrix (�p�G�O�X�i�d���� �ݭn�g�`��s���x�} ���D�u��) 

	//��l�ƨ�L���x�}
	cv::setIdentity(kalmanFilter.measurementMatrix, cv::Scalar(1)); // H matrix
	cv::setIdentity(kalmanFilter.processNoiseCov, cv::Scalar(1e-5)); // Q matrix
	cv::setIdentity(kalmanFilter.measurementNoiseCov, cv::Scalar(1e-1)); // R matrix
	cv::setIdentity(kalmanFilter.errorCovPost, cv::Scalar(1)); // (P(k)) : P(k) = (I - K(k)*H)*P'(k)

	//�H����l�ƪ��A
	cv::randn(kalmanFilter.statePost, 0.0, 0.1);

	char key = 'i';

	cv::imshow("KalmanFilter", img);

	cvSetMouseCallback("KalmanFilter", onMouse);

	while (key != 'o')
	{
		//�w���I����m
		cv::Mat y_k = kalmanFilter.predict();

		z_k = kalmanFilter.measurementMatrix*x_k + z_k;

		cv::Point pz_k(z_k.at<float>(0), z_k.at<float>(1));
		cv::Point py_k(y_k.at<float>(0), y_k.at<float>(1));


		img = cv::Scalar::all(0);
		cv::circle(img, pz_k, 4, cv::Scalar(128, 255, 255));  // �q��(�[��)���G //����
		cv::circle(img, py_k, 4, cv::Scalar(255, 255, 255), 2);  // �w�����G //�զ�
		// planar co-ordinates and draw

		cv::imshow("KalmanFilter", img);

		z_k.at<float>(0) = mouseX;
		z_k.at<float>(1) = mouseY;

		kalmanFilter.correct(z_k);

		x_k = kalmanFilter.transitionMatrix*x_k + w_k; //��s���A��� //���ݭn�����{��

		key = cv::waitKey(100);
	}

	return 0;
}