#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;

void sum_rgb( const cv::Mat& src, cv::Mat& dst){
    vector<cv::Mat> planes;
    cv::split(src, planes);
    // BGR
    cv::Mat b = planes[0], g = planes[1], r = planes[2], s;
    // r, g, b , add equally weighted rgb value
    cv::addWeighted( r, 1./3., g, 1./3., 0.0, s );
    cv::addWeighted( s, 1., b, 1./3., 0.0, s);
    cv::threshold( s, dst, 100, 100, cv::THRESH_TRUNC );
}

void help(){
    cout << "Call: ./exa1001 ../../data/smirking-face_150150.png" << endl;
    cout << "Shows use of alpha blending (addWeighted) and threshold" << endl;
}

int main( int argc, char** argv){
    help();
    
    cv::Mat src = cv::imread(argv[1]), dst;
    if( src.empty() ) { cout << "can not load" << argv[1] << endl; return -1; }
    sum_rgb( src, dst );
    cv::imshow( "src", src );
    cv::imshow( "dst", dst );
    
    cv::waitKey( 0 );
    return 0;
}
