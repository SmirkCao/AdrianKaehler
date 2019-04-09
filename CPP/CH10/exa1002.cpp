#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;

void sum_rgb( const cv::Mat& src, cv::Mat& dst){
    vector<cv::Mat> planes;
    cv::split(src, planes);
    cv::Mat b = planes[0], g = planes[1], r = planes[2];
    cv::Mat s = cv::Mat::zeros(b.size(), CV_32F);
    cv::accumulate(b, s);
    cv::accumulate(g, s);
    cv::accumulate(r, s);

    cv::threshold( s, dst, 100, 100, cv::THRESH_TRUNC );
    cout << "type dst:" << dst.type() << ", type b:" << b.type() << endl;
    s.convertTo(dst, b.type());
    cout << dst.type() << endl;
}

void help(){
    cout << "Call: ./exa1002 smirking-face_150150.png" << endl;
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