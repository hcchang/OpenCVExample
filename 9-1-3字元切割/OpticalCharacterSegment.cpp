#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <algorithm>


bool verifyOCSizes(cv::Mat r){
	//Char sizes 45x77
	float aspect = 45.0f / 77.0f;
	float charAspect = (float)r.cols / (float)r.rows;
	float error = 0.35;
	float minHeight = 15;
	float maxHeight = 28;
	//We have a different aspect ratio for number 1, and it can be ~0.2
	float minAspect = 0.2;
	float maxAspect = aspect + aspect*error;
	//area of pixels
	float area = countNonZero(r);
	//bb area
	float bbArea = r.cols*r.rows;
	//% of pixel in area
	float percPixels = area / bbArea;

	std::cout << "Aspect: " << aspect << " [" << minAspect << "," << maxAspect << "] " << "Area " << percPixels << " Char aspect " << charAspect << " Height char " << r.rows << "\n";
	
	if (percPixels < 0.8 && charAspect > minAspect && charAspect < maxAspect && r.rows >= minHeight && r.rows < maxHeight)
		return true;
	else
		return false;

}

cv::Mat preprocessChar(cv::Mat in){
	//Remap image
	int h = in.rows;
	int w = in.cols;
	cv::Mat transformMat = cv::Mat::eye(2, 3, CV_32F);
	int m = std::max(w, h);
	transformMat.at<float>(0, 2) = m / 2 - w / 2;
	transformMat.at<float>(1, 2) = m / 2 - h / 2;

	cv::Mat warpImage(m, m, in.type());
	warpAffine(in, warpImage, transformMat, warpImage.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0));

	cv::Mat out;
	cv::resize(warpImage, out, cv::Size(20, 20));

	return out;
}

int main(int argc, char** argv)
{
	cv::Mat carPlate = cv::imread("carPlate.bmp", 0);
	
	if (!carPlate.data)
	{
		std::cout << "無法讀取圖片" << std::endl;
		return -1;
	}

	cv::Mat imgBinary;
	cv::threshold(carPlate, imgBinary, 60, 255, CV_THRESH_BINARY_INV);

	cv::imshow("Threshold plate", imgBinary);
	cv::waitKey(0);	

	cv::Mat imgContour;
	imgBinary.copyTo(imgContour);

	//Find contours of possibles characters
	std::vector< std::vector< cv::Point> > contours;
	findContours(imgContour,
		contours, // a vector of contours
		CV_RETR_EXTERNAL, // retrieve the external contours
		CV_CHAIN_APPROX_NONE); // all pixels of each contours

	// Draw blue contours on a white image
	cv::Mat result;
	imgBinary.copyTo(result);
	cvtColor(result, result, CV_GRAY2RGB);
	cv::drawContours(result, contours,
		-1, // draw all contours
		cv::Scalar(255, 0, 0), // in blue
		1); // with a thickness of 1

	//Start to iterate to each contour founded
	std::vector<std::vector<cv::Point> >::iterator itc = contours.begin();

	std::vector<cv::Mat> output;

	//Remove patch that are no inside limits of aspect ratio and area.
	int i = 0;
	while (itc != contours.end()) 
	{
		//Create bounding rect of object
		cv::Rect mr = cv::boundingRect(cv::Mat(*itc));
		rectangle(result, mr, cv::Scalar(0, 255, 0));
		//Crop image
		cv::Mat auxRoi(imgBinary, mr);
		if (verifyOCSizes(auxRoi))
		{
			auxRoi = preprocessChar(auxRoi); //20x20
			cv::Mat segChar = auxRoi.clone();
			output.push_back(segChar);
			rectangle(result, mr, cv::Scalar(0, 125, 255));

			cv::Mat largeChar;
			cv::resize(segChar, largeChar, cv::Size(200,200));

			cv::imshow("char", largeChar);
			cv::waitKey(0);

			std::string filename = "file";
			int num = i;
			std::stringstream numS;
			numS << i;
			filename = filename + numS.str() + ".bmp";

			cv::imwrite(filename, segChar);
			i++;
		}
		++itc;
	}
	std::cout << "Num chars: " << output.size() << "\n";
	
	cv::imshow("SEgmented Chars", result);
	

	return 0;
}

