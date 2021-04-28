#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/*
General Image Transforms
resize(): Goruntunun boyutunu degistirir.
Goruntuyu buyuturken piksellerin arasi acilir resize() piksellerin arasindaki bosluklarý doldurur.
Canny: Kenarlarin keskinligini alir, soluklastirir. Hedef kenarlari bulmak.
-> Gurltuler yuksek frakanslidir ve biz onlari canny ile azaltiriz.
*/

/*
En son test ederken LNK1168 hatasi aldim. O yuzden ciktilari ekleyemedim.
*/

int main(int argc, char** argv) {
       
    //iki farkli sekilde uyguladim.
    Mat image = imread("Resources/test.jpg");
    Mat img = imread("Resources/test.jpg");
    Mat imgResize, imgCrop, dst_resize, dst_rotate, imgCanny, imgGray, imgBlur;

    resize(img, imgResize, Size(), 0.5, 0.5);

    Rect roi(200, 100, 400, 300);
    imgCrop = img(roi);
   
    Point2f srcQuad[] = {
        Point2f(0, 0), 
        Point2f(image.cols - 1, 0), 
        Point2f(image.cols - 1, image.rows - 1), 
        Point2f(0, image.rows - 1) 
    };

    Point2f dstQuad[] = {
        Point2f(image.cols * 0.05f, image.rows * 0.33f),
        Point2f(image.cols * 0.9f, image.rows * 0.25f),
        Point2f(image.cols * 0.8f, image.rows * 0.9f),
        Point2f(image.cols * 0.2f, image.rows * 0.7f)
    };

    Mat warp_mat = getPerspectiveTransform(srcQuad, dstQuad);
    Mat dst;
    warpPerspective(image, dst, warp_mat, image.size(), INTER_LINEAR,
        BORDER_CONSTANT, Scalar());
    for (int i = 0; i < 4; i++)
        circle(dst, dstQuad[i], 5, Scalar(255, 0, 255), -1);

    resize(image, dst_resize, Size(2500, 1500), 0, 0, INTER_LINEAR);

    double angle = -45;
  
    Point2f center((image.cols - 1) / 2.0, (image.rows - 1) / 2.0);
    Mat rot = getRotationMatrix2D(center, angle, 1.0);
    
    Rect2f bbox = cv::RotatedRect(Point2f(), image.size(), angle).boundingRect2f();

    rot.at<double>(0, 2) += bbox.width / 2.0 - image.cols / 2.0;
    rot.at<double>(1, 2) += bbox.height / 2.0 - image.rows / 2.0;

    warpAffine(image, dst_rotate, rot, bbox.size());

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);		// (3,3), 3 , 0
	Canny(imgBlur, imgCanny, 50, 150);					// 25, 75
    Canny(imgBlur, imgCanny, 25, 75);

    imshow("Orjinal Resim", image);
    imshow("Perspective Transform Test", dst);
    imshow("Resize Resim", dst_resize);      
    imshow("Rotate Resim", dst_rotate);
    imshow("Orjinal Resim2", img);
    imshow("Image Resize Resim", imgResize);
    imshow("Image Crop Resim", imgCrop);
    imshow("Image Canny", imgCanny);


    int k = waitKey(0); // Wait for a keystroke in the window
    if (k == 's')
    {
        imwrite("Resources/orijinal_resim.jpg", image);
        imwrite("Resources/resize_resim.jpg", dst);
        imwrite("Resources/rotate_resim.jpg", dst_resize);
        imwrite("Resources/perspective_transform_resim.jpg", dst_rotate);
        imwrite("Resources/orijinal_resim2.jpg", dst_rotate);
        imwrite("Resources/image_resize_resim.jpg", imgResize);
        imwrite("Resources/image_crop_resim.jpg", imgCrop);
        imwrite("Resources/canny_resim.jpg", imgCanny);
        cout << "Resimler 'Resources' dosyasina kaydedildi.";
    }
    return 0;
}