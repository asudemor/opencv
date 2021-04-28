#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/*
Gaussian Smoothing Filter
Smoothing: Bulaniklastirma, sonutlastirme
Median Filtrer: medyana gore
Gaussian Filtrer: varyans ve ortalamaya gore
*/

void gaussianSmoothing() {


	Mat image = imread("Resources/test.jpg");
	//float gauss_data[25] = { 1, 4, 7, 4, 1,
	//						4, 16, 26, 16, 4,
	//						7, 26, 41, 26, 7,
	//						4, 16, 26, 16, 4,
	//						1, 4, 7, 4, 1 };

	float gauss_data[25] = { 1 , 4 , 6 , 4 , 1 ,
						 4 , 16 , 24 , 16 , 4 ,
						 6 , 24 , 36 , 24 , 6 ,
						 4 , 16 , 24 , 16 , 4 ,
						 1 , 4 , 6 , 4 , 1 };

	float median_data[25] = { 1, 1, 1,
							  1, 1, 1,
							  1, 1, 1 };


	Mat kernel1 = Mat(5, 5, CV_32F, gauss_data);
	Mat kernel2 = Mat(3, 3, CV_32F, median_data);


	for (int i = 0; i < 25; i++) {
		gauss_data[i] /= 256;		//273
	}


	for (int i = 0; i < 9; i++) {
		median_data[i] /= 7;
	}



	Mat resGau, gaussian, resBlu, bblur, resMed, median, resBil, bilateral;

	filter2D(image, resGau, -1, kernel1, Point(-1, -1), 0, BORDER_DEFAULT);
	filter2D(image, resMed, -1, kernel2);

	blur(image, bblur, Size(13, 13), Point(-1, -1));
	medianBlur(image, median, 13);
	bilateralFilter(image, bilateral, 50, 50, 50);
	GaussianBlur(image, gaussian, Size(9, 9), (-1.0, -1.0));    //Size(7, 7), 5, 0 ----  Size(3, 3), 3 , 0 ------- Size(5, 5), 5, 0)

	imshow("Orjinal Resim", image);
	imshow("My Gaussian Resim", resGau);
	imshow("My Median Resim", resMed);
	imshow("Gaussian Resim", gaussian);
	imshow("Blur Resim", bblur);
	imshow("Median Resim", median);
	imshow("Bilateral Resim", bilateral);	//daha keskin

	int k = waitKey(0); // Wait for a keystroke in the window
	if (k == 's')
	{
		imwrite("Resources/orijinal_resim.jpg", image);
		imwrite("Resources/my_gaussian_blur_resim.jpg", resGau);
		imwrite("Resources/my_median_blur_resim.jpg", resMed);
		imwrite("Resources/gaussian_blur_resim.jpg", gaussian);
		imwrite("Resources/blur_resim.jpg", bblur);
		imwrite("Resources/median_blur_resim.jpg", median);
		imwrite("Resources/bilateral_filter_resim.jpg", bilateral);

		cout << "Resimler 'Resources' dosyasina kaydedildi.";
	}

}

int main() {
	gaussianSmoothing();

	//Benim olusturdugum filtre daha az bulaniklastirdi.
}






