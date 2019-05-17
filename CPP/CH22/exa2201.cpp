#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

// Test Photo by Nicholas Green on Unsplash
// ./exa2201 ../nicholas-green-324622-unsplash.jpg ../haarcascade_frontalface_alt.xml
using namespace std;

void detectAndDraw(
        cv::Mat& img,
        cv::Ptr<cv::CascadeClassifier> classifer,
        double scale = 1.3
        ){
    enum {BLUE, AQUA, CYAN, GREEN };
    static cv::Scalar colors[]={
            cv::Scalar( 0,   0, 255 ),
            cv::Scalar( 0, 128, 255 ),
            cv::Scalar( 0, 255, 255 ),
            cv::Scalar( 0, 255,   0 )
            };

    cv::Mat gray( img.size(), CV_8UC1 );
    cv::Mat small_img( cvSize(cvRound(img.cols/scale), cvRound(img.rows/scale)), CV_8UC1 );
    cv::cvtColor( img, gray, cv::COLOR_BGR2GRAY );
    cv::resize( gray, small_img, small_img.size(), 0, 0, cv::INTER_LINEAR );
    cv::equalizeHist( small_img, small_img );

    vector<cv::Rect> objects;
    classifer->detectMultiScale(small_img, objects, 1.1, 2, CV_HAAR_DO_CANNY_PRUNING, cv::Size(30, 30));

    int i = 0;
    for( vector<cv::Rect>::iterator r=objects.begin(); r!=objects.end(); r++, ++i ){
        cv::Rect r_ = (*r);
        r_.x *= scale;
        r_.y *= scale;
        r_.width *= scale;
        r_.height *= scale;
        cv::rectangle( img, r_, colors[i%4] );
    }

}
int main( int argc, char *argv[] ){
    if(argc < 3){
        exit(1);
    }
    string img_file_name = string(argv[1]);


    cout << "OpenCV Version: " << CV_VERSION << endl;
    cout << "img_file_name: " << img_file_name << endl;
    cv::Mat img = cv::imread( img_file_name, CV_LOAD_IMAGE_COLOR );
    cv::resize( img, img, cv::Size(800, 600), 0, 0, cv::INTER_LINEAR );

    string cascade_file_name = string(argv[2]);
    cv::Ptr<cv::CascadeClassifier> clf( new cv::CascadeClassifier(cascade_file_name) );
    detectAndDraw(img, clf);

    cv::imshow("Photo by Nicholas Green on Unsplash", img);
    cv::waitKey(0);

    return 0;
}