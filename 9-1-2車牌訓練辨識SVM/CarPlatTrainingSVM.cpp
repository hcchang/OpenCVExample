#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>



int main(int argc, char** argv)
{
	int imgHeight = 33;
	int imgWidth = 110;

	std::string imgFileNameBatch = "fileName.txt";

	cv::Mat trainingImages;
	std::vector<int> trainingLabels;

	std::fstream fileBatch(imgFileNameBatch, std::ios::in);

	if (!fileBatch)
		return -1;

	while (!fileBatch.eof())
	{
		std::string fileName;
		fileBatch >> fileName;
		std::cout << "fileName: " << fileName << std::endl;

		cv::Mat imgTmp = cv::imread(fileName, 0);
		if (imgTmp.empty())
			return -1;
		int label = -1;
		fileBatch >> label;
		std::cout << "label: " << label << std::endl;

		imgTmp = imgTmp.reshape(1, 1);
		trainingImages.push_back(imgTmp);
		trainingLabels.push_back(label);
	}

	fileBatch.close();

	cv::Mat trainingData;
	cv::Mat classes;
		 
	cv::Mat(trainingImages).copyTo(trainingData);
	trainingData.convertTo(trainingData, CV_32FC1);
	cv::Mat(trainingLabels).copyTo(classes);

	cv::FileStorage fso("SVM.xml", cv::FileStorage::WRITE);
	fso << "TrainingData" << trainingData;
	fso << "classes" << classes;
	fso.release();

	cv::FileStorage fs;
	fs.open("SVM.xml", cv::FileStorage::READ);
	cv::Mat SVM_TrainingData;
	cv::Mat SVM_Classes;
	fs["TrainingData"] >> SVM_TrainingData;
	fs["classes"] >> SVM_Classes;

	std::cout << "svmClassifier1: " << std::endl;

	//Set SVM params
	CvSVMParams SVM_params;
	SVM_params.svm_type = CvSVM::C_SVC;
	SVM_params.kernel_type = CvSVM::LINEAR; //CvSVM::LINEAR;
	SVM_params.degree = 0;
	SVM_params.gamma = 1;
	SVM_params.coef0 = 0;
	SVM_params.C = 1;
	SVM_params.nu = 0;
	SVM_params.p = 0;
	SVM_params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 1000, 0.01);
	//Train SVM
	CvSVM svmClassifier(SVM_TrainingData, SVM_Classes, cv::Mat(), cv::Mat(), SVM_params);

	std::cout << "svmClassifier2: " <<  std::endl;

	cv::Mat imgReCheckPlate = cv::imread("plate.bmp", 0);
	cv::Mat imgReCheckNoPlate = cv::imread("noplate.bmp", 0);
	cv::Mat p = imgReCheckPlate.reshape(1, 1);
	cv::Mat pN = imgReCheckNoPlate.reshape(1, 1);
	p.convertTo(p, CV_32FC1);
	pN.convertTo(pN, CV_32FC1);

	int responsep = (int)svmClassifier.predict(p);
	int responsepN = (int)svmClassifier.predict(pN);

	std::cout << "p result is : " << responsep << std::endl;
	std::cout << "pN result is : " << responsepN << std::endl;

	return 0;
}

