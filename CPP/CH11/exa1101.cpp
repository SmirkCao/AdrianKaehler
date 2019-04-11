#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;

int main( int argc, char** argv){

    if(argc != 2){
        cout << "Warp affine\n Usage: " << argv[0] << " <imagename>\n" << endl;
        return -1;
    }

    cv::Mat src = cv::imread(argv[1], 1);
    if( src.empty() ) { cout << "can not load" << argv[1] << endl; return -1; }

    cv::Point2f srcTri[] = {
        cv::Point2f(0,0),
        cv::Point2f(src.cols-1, 0),
        cv::Point2f(0, src.rows-1)
    };

    cv::Point2f dstTri[] = {
        cv::Point2f(src.cols*0.f,   src.rows*0.33f),
        cv::Point2f(src.cols*0.85f, src.rows*0.25f),
        cv::Point2f(src.cols*0.15f, src.rows*0.7f)
    };
    
    cv::Mat warp_mat = cv::getAffineTransform(srcTri, dstTri);
    cout << warp_mat << endl;
    cv::Mat dst, dst2;
    cv::warpAffine(src, dst, warp_mat, src.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());
    for( int i = 0; i < 3; ++i)
        cv::circle(dst, dstTri[i], 5, cv::Scalar(255, 0, 255), -1, CV_AA);
    cv::imshow( "Afine Transform Test", dst );
    
    for ( int frame=0;;++frame ){
        cv::Point2f center(src.cols*0.5f, src.rows*0.5f);
        double angle = frame*3%360, scale = (cos((angle - 60)*CV_PI/180) + 1.05)*0.8;

        cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, scale);

        cv::warpAffine(src, dst, rot_mat, src.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());
        cv::imshow("Rotated Image", dst);
        if (cv::waitKey(30) >= 0)
            break;
    }
    cv::waitKey( 0 );
    return 0;
}
