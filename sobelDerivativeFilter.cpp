#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>

using namespace std;
using namespace cv;


/*
Sobel Derivative Filter
Derivative: Kenarlar daha belirgin
Sobel: 1. dereceden turevi alinir. Keskinlestirir.
Laplacian: 2. dereceden turevi alinir. 
-> Laplacian da kenarlar Sobele gore daha belirgin.
*/
void sobel() {

	Mat image = imread("Resources/test.jpg");

	if (!image.data) {
		cout << "Error loading image" << "\n";
	}

	Mat imgGray, ssobel, laplacian;

	Sobel(image, ssobel, CV_32F, 1, 1, 3, 1, 0, BORDER_DEFAULT);
	Laplacian(image, laplacian, CV_32F, 5, 1, 0, BORDER_DEFAULT);

	cvtColor(image, imgGray, COLOR_BGR2GRAY);

	Mat blurred = imgGray.clone();
	int filterSize = 5;
	int stdDev = 2.0;
	GaussianBlur(imgGray, blurred, Size(filterSize, filterSize), stdDev);

	float sobel_x[9] = { -1,0,1,-2,0,-2,-1,0,1 };
	Mat kernel_x = Mat(3, 3, CV_32F, sobel_x);

	float sobel_y[9] = { 1,2,1,0,0,0,-1,-2,-1 };
	Mat kernel_y = Mat(3, 3, CV_32F, sobel_y);


	Mat result_x, result_y;
	filter2D(blurred, result_x, -1, kernel_x, Point(-1, -1), 0, BORDER_DEFAULT);
	filter2D(blurred, result_y, -1, kernel_y, Point(-1, -1), 0, BORDER_DEFAULT);

	Mat magnitude = imgGray.clone();
	for (int i = 0; i < magnitude.rows; i++) {
		for (int j = 0; j < magnitude.cols; j++) {
			magnitude.at<unsigned char>(i, j) = sqrt(pow(result_x.at<unsigned char>(i, j), 2) +
				pow(result_y.at<unsigned char>(i, j), 2));
		}
	}


	imshow("Orijinal", image);
	imshow("My Sobel Resim", magnitude);
	imshow("Sobel Resim", ssobel);  //kaydettigi resim ile kodu calistirdigimde cikan resim farkli oldu.
	imshow("Laplacian Resim", laplacian);


	//tam olarak sobel filtresini uygulayamadým.
	int k = waitKey(0);
	if (k == 's')
	{
		imwrite("Resources/orijinal_resim.jpg", image);
		imwrite("Resources/sobel_resim.jpg", ssobel);
		imwrite("Resources/my_sobel_resim.jpg", magnitude);
		imwrite("Resources/laplacian_resim.jpg", laplacian);
		cout << "Resimler 'Resources' dosyasina kaydedildi.";
	}
}

int main() {
	sobel();
}