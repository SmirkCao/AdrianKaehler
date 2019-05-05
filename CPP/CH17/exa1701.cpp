#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

static const int MAX_CORNERS = 1000;

#define phi2xy( mat)                                                     \
  cv::Point( cvRound(img.cols/2 + img.cols/2*cos(mat.at<float>(0))), \
             cvRound(img.rows/2 + img.cols/3*sin(mat.at<float>(0))))

int main( int argc, char** argv ){

    cv::Mat img(500, 500, CV_8UC3);
    cv::KalmanFilter kalman(2, 1, 0);

    cv::Mat x_k(2, 1, CV_32F);
    randn(x_k, 0,0.1);
    cout << "x_k: " << x_k <<endl;

    cv::Mat w_k(2, 1, CV_32F);
    cv::Mat z_k = cv::Mat::zeros(1, 1, CV_32F);
    cout<< "z_k : " << z_k << endl;

    float F[] = {1, 1, 0, 1};
    kalman.transitionMatrix = cv::Mat(2, 2, CV_32F, F).clone();
    cout << "F: " << F << endl;

    cv::setIdentity( kalman.measurementMatrix, cv::Scalar(1));
    cv::setIdentity( kalman.processNoiseCov, cv::Scalar(1e-5));
    cv::setIdentity( kalman.measurementNoiseCov, cv::Scalar(1e-1));
    cv::setIdentity( kalman.errorCovPost, cv::Scalar(1));
    
    randn(kalman.statePost, 0., 0.1);

    for(;;){
        cv::Mat y_k = kalman.predict();
        cv::randn(z_k, 0., sqrt((double)kalman.measurementNoiseCov.at<float>(0, 0)));
        z_k = kalman.measurementMatrix*x_k + z_k;

        img = cv::Scalar::all(0);
        cv::circle(img, phi2xy(z_k), 4, cv::Scalar(128, 255, 255));
        cv::circle(img, phi2xy(y_k), 4, cv::Scalar(255, 255, 255), 2);
        cv::circle(img, phi2xy(x_k), 4, cv::Scalar(0, 0, 255));
      
        cv::putText(img, "Yellow: noise", cv::Point(20, 30), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 255), 2, 8, 0);
        cv::putText(img, "White: Prediction", cv::Point(20, 60), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 255, 255), 2, 8, 0);
        cv::putText(img, "Red: GT", cv::Point(20, 90), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 255), 2, 8, 0);
      
        cv::imshow( "Kalman", img );

        kalman.correct(z_k);
        cv::randn(w_k, 0., sqrt((double)kalman.processNoiseCov.at<float>(0, 0)));
        x_k = kalman.transitionMatrix*x_k+w_k;
        if ((cv::waitKey( 100 )&255) == 27) break;    
    }
    
    return 0;

}