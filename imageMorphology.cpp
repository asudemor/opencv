#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/*
Image Morphology
Dilate: Goruntuyu kalinlastirir. Parlaklastirir.
Erose:  Kenarlari inceltir. Karanliklastirir.
Opening: Goruntuyu temizliyoruz. Once duzensizlikleri silip sonra kalinlastiriyoruz.
Closing: Once dilation sonra erosion ile bosluklari temizliyoruz. 
Morphological turev = dilate(src) - erode(src)
*/


int main(int argc, char** argv) {

    Mat image, eerode, dil;

    image = imread("Resources/test.jpg");

    if (!image.data) {
        cout << "Error loading image" << "\n";
        return -1;
    }

    erode(image, eerode, Mat(), Point(-1, -1), 3, BORDER_DEFAULT, morphologyDefaultBorderValue());
    dilate(image, dil, Mat(), Point(-1, -1), 3, BORDER_DEFAULT, morphologyDefaultBorderValue());

    imshow("Orjinal Resim", image);
    imshow("Erode Resim", eerode);      //detaylar kayboldu
    imshow("Dilate Resim", dil);        //parlaklasti


    int k = waitKey(0); // Wait for a keystroke in the window
    if (k == 's')
    {
        imwrite("Resources/orijinal_resim.jpg", image);
        imwrite("Resources/erode_resim.jpg", eerode);
        imwrite("Resources/dilate_resim.jpg", dil);

        cout << "Resimler 'Resources' dosyasina kaydedildi.";

    }


    return 0;
}