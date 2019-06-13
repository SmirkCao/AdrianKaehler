#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;

int main( int argc, char** argv ){
    cv::RNG rng = cv::theRNG();
    cout << "A integer: " << int(rng) << endl;
    cout << "Another integer: " << (int)rng << endl;
    cout << "Another integer: " << int(rng) << endl;
    cout << "A float: " << (float)rng << endl;
    cout << "Another float: " << float(rng) << endl;

    return 0;
}