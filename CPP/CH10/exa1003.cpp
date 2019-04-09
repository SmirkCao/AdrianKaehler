#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;

int main( int argc, char** argv){
    
    if(argc != 7){
        cout <<
        "Usage: " << argv[0] << " fixed_threshold invert(0=off|1=on)"
        "adaptive_type(0=mean|1=gaussian) block_size offset image\n"
        "Example: " << argv[0] << " 80 1 1 31 15 ../../data/1.jpg\n"; 
        return -1;
    }

    double fixed_threshold = (double)atof(argv[1]);
    int threshold_type = atoi(argv[2]) ? cv::THRESH_BINARY : cv::THRESH_BINARY_INV;
    int adaptive_method = atoi(argv[3]) ? cv::ADAPTIVE_THRESH_MEAN_C : cv::ADAPTIVE_THRESH_GAUSSIAN_C;
    int block_size = atoi(argv[4]);
    double offset = (double)atof(argv[5]);
    // ref:https://docs.opencv.org/3.4.4/d4/da8/group__imgcodecs.html#ga61d9b0126a3e57d9277ac48327799c80
    // imreadModes
    cv::Mat Igray = cv::imread(argv[6], cv::IMREAD_GRAYSCALE);

    if( Igray.empty() ) { cout << "can not load" << argv[6] << endl; return -1; }
    
    cv::Mat It, Iat, Iotsu;
    cv::threshold(Igray, It, fixed_threshold, 255, threshold_type);
    cv::adaptiveThreshold(Igray, Iat, 255, adaptive_method, threshold_type, block_size, offset);
    cv::threshold(Igray, Iotsu, fixed_threshold, 255, threshold_type+cv::THRESH_OTSU);

    cv::imshow( "Raw", Igray );
    cv::imshow( "Threshold", It );
    cv::imshow( "Adaptive Threshold", Iat );
    cv::imshow( "OTSU", Iotsu );
    
    cv::waitKey( 0 );
    return 0;
}