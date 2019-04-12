#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;

int main( int argc, char** argv){
    
    if (argc != 2){
        cout << "Hough Circle detect\nUsage: " << argv[0] << " <Imagename>\n" << endl;
        return -1;
    }

    cv::Mat src = cv::imread(argv[1], 1), image;
    if( src.empty() ) { cout << "can not load" << argv[1] << endl; return -1; }

    cv::cvtColor(src, image, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(image, image, cv::Size(5,5), 0, 0);

    vector<cv::Vec3f> circles;
    cv::HoughCircles(image, circles, cv::HOUGH_GRADIENT, 2, image.cols/10);

    for( size_t i = 0; i < circles.size(); ++i){
        cv::circle(src, cv::Point(cvRound(circles[i][0]), cvRound(circles[i][1])),
        cvRound(circles[i][2]),
        cv::Scalar(0,0,255),
        2,
        CV_AA);
    }

    cv::imshow( "Houch Circles", src );
    
    cv::waitKey();
    return 0;
}