#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

static const int MAX_CORNERS = 1000;


int main( int argc, char** argv ){

    if ( argc != 3){
        cout << "Call: " << argv[0] << "[image1][image2]" << endl; 
        cout << "Demonstrates Pyramid Lucas-Kanade optical flow." << endl;
        exit( -1 );
    }

    cv::Mat imgA = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    cv::Mat imgB = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);
    cv::Size img_sz = imgA.size();
    int win_size = 10;
    cv::Mat imgC = cv::imread(argv[2], cv::IMREAD_UNCHANGED);

    vector< cv::Point2f> cornersA, cornersB;
    const int MAX_CORNERS = 500;
    cv::goodFeaturesToTrack(
        imgA,
        cornersA,
        MAX_CORNERS,
        0.01,
        5,
        cv::noArray(),
        3,
        false,
        0.04
    );
    
    cv::cornerSubPix(
        imgA,
        cornersA,
        cv::Size(win_size, win_size),
        cv::Size(-1, -1),
        cv::TermCriteria(
            cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,
            20,
            0.3
        )
    );

    vector<uchar> features_found;
    cv::calcOpticalFlowPyrLK(
        imgA,
        imgB,
        cornersA,
        cornersB,
        features_found,
        cv::noArray(),
        cv::Size(win_size*2+1, win_size*2+1),
        5,
        cv::TermCriteria(
            cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,
            20,
            0.3
        )
    );

    for ( int i = 0; i < (int)cornersA.size(); i++ ){
        if( !features_found[i] )
            continue;
        cv::line(imgC, cornersA[i], cornersB[i], cv::Scalar(0, 255, 0), 2, CV_AA);
    }


    cv::imshow( "image A", imgA );
    cv::imshow( "image B", imgB );
    cv::imshow( "LK Optical Flow Example", imgC );
    cv::waitKey( 0 );
    return 0;

}