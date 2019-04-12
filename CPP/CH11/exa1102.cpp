#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;

int main( int argc, char** argv){
    
    if (argc != 2){
        cout << "Perspective Wrap\nUsage: " << argv[0] << " <Imagename>\n" << endl;
        return -1;
    }

    cv::Mat src = cv::imread(argv[1]);
    if( src.empty() ) { cout << "can not load" << argv[1] << endl; return -1; }

    cv::Point2f srcQuad[] = {
        cv::Point2f(0,          0),
        cv::Point2f(src.cols-1, 0),
        cv::Point2f(src.cols-1, src.rows-1),
        cv::Point2f(0,          src.rows-1)
    };

    cv::Point2f dstQuad[] = {
        cv::Point2f(src.cols*0.05f, src.rows*0.33f),
        cv::Point2f(src.cols*0.9f,  src.rows*0.25f),
        cv::Point2f(src.cols*0.8f,  src.rows*0.9f),
        cv::Point2f(src.cols*0.2f,  src.rows*0.7f)
    };

    cv::Mat warp_mat = cv::getPerspectiveTransform(srcQuad, dstQuad);
    cv::Mat dst;
    cv::warpPerspective(src, dst, warp_mat, src.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

    for (int i = 0; i < 4; i++){
        cv::circle(dst, dstQuad[i], 5, cv::Scalar(255, 0, 255), -1, CV_AA);
    }

    cv::imshow( "Perspective Transform Test", dst );
    
    cv::waitKey( 0 );
    return 0;
}