#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <algorithm>

const int numCharacters = 30;
const char strCharacters[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z' };

void train(CvANN_MLP&  ann, cv::Mat TrainData, cv::Mat classes, int nlayers)
{
	cv::Mat layers(1, 3, CV_32SC1);
	layers.at<int>(0) = TrainData.cols;
	layers.at<int>(1) = nlayers;
	layers.at<int>(2) = numCharacters;
	ann.create(layers, CvANN_MLP::SIGMOID_SYM, 1, 1);

	//Prepare trainClases
	//Create a mat with n trained data by m classes
	cv::Mat trainClasses;
	trainClasses.create(TrainData.rows, numCharacters, CV_32FC1);
	for (int i = 0; i < trainClasses.rows; i++)
	{
		for (int k = 0; k < trainClasses.cols; k++)
		{
			//If class of data i is same than a k class
			if (k == classes.at<int>(i))
				trainClasses.at<float>(i, k) = 1;
			else
				trainClasses.at<float>(i, k) = 0;
		}
	}
	cv::Mat weights(1, TrainData.rows, CV_32FC1, cv::Scalar::all(1));
	//Learn classifier
	ann.train(TrainData, trainClasses, weights);
}

#define HORIZONTAL    1
#define VERTICAL    0

cv::Mat ProjectedHistogram(cv::Mat img, int t)
{
	int sz = (t) ? img.rows : img.cols;
	cv::Mat mhist = cv::Mat::zeros(1, sz, CV_32F);

	for (int j = 0; j<sz; j++){
		cv::Mat data = (t) ? img.row(j) : img.col(j);
		mhist.at<float>(j) = countNonZero(data);
	}

	//Normalize histogram
	double min, max;
	minMaxLoc(mhist, &min, &max);

	if (max>0)
		mhist.convertTo(mhist, -1, 1.0f / max, 0);

	return mhist;
}

int main(int argc, char** argv)
{
	cv::Mat numImg = cv::imread("file0.bmp", 0);

	cv::Mat map_x, map_y;

	map_x.create(numImg.size(), CV_32FC1);
	map_y.create(numImg.size(), CV_32FC1);

	cv::Mat numImgProce;

	for (int i = 0; i < numImg.rows; i++)
	{
		for (int j = 0; j < numImg.cols; j++)
		{
			if (j > numImg.cols*0.15 && j < numImg.cols*0.85)
			{
				map_x.at<float>(i, j) = 1.428 * (j - numImg.cols*0.15) + 0.5;
			}
			else
			{
				map_x.at<float>(i, j) = 0;
			}

			map_y.at<float>(i, j) = i;
		}
	}

	cv::remap(numImg, numImgProce, map_x, map_y, CV_INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0));

	numImg = numImgProce.clone();

	cv::imwrite("input.jpg", numImg);
	
	if (!numImg.data)
	{
		std::cout << "無法讀取圖片" << std::endl;
		return -1;
	}

	CvANN_MLP  ann;

	cv::FileStorage fs;
	fs.open("OCR.xml", cv::FileStorage::READ);
	cv::Mat TrainingData;
	cv::Mat Classes;
	fs["TrainingDataF15"] >> TrainingData;
	fs["classes"] >> Classes;

	train(ann, TrainingData, Classes, 10);


	cv::Mat vhist = ProjectedHistogram(numImg, VERTICAL);
	cv::Mat hhist = ProjectedHistogram(numImg, HORIZONTAL);

	//Low data feature
	cv::Mat lowData;
	cv::resize(numImg, lowData, cv::Size(15, 15));


	//Last 10 is the number of moments components
	int numCols = vhist.cols + hhist.cols + lowData.cols*lowData.cols;

	cv::Mat out = cv::Mat::zeros(1, numCols, CV_32F);
	//Asign values to feature
	int j = 0;
	for (int i = 0; i<vhist.cols; i++)
	{
		out.at<float>(j) = vhist.at<float>(i);
		j++;
	}
	for (int i = 0; i<hhist.cols; i++)
	{
		out.at<float>(j) = hhist.at<float>(i);
		j++;
	}
	for (int x = 0; x<lowData.cols; x++)
	{
		for (int y = 0; y<lowData.rows; y++){
			out.at<float>(j) = (float)lowData.at<unsigned char>(x, y);
			j++;
		}
	}


	int resultClass = -1;
	cv::Mat output(1, numCharacters, CV_32FC1);
	ann.predict(out, output);
	cv::Point maxLoc;
	double maxVal;
	minMaxLoc(output, 0, &maxVal, 0, &maxLoc);

	resultClass = maxLoc.x;

	char resultChar = strCharacters[resultClass];

	std::cout << "result is: " << resultChar << std::endl;
	
	return 0;
}

