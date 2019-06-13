#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;

int main( int argc, char** argv ){
    cv::RNG rng = cv::theRNG();
    cout << "three uniform float:\t" << float(rng.uniform(0., 1.)) << "\t"
    << float(rng.uniform(0., 1.)) << "\t"
    << float(rng.uniform(0., 1.)) << endl;

    cout << "three gaussian double:\t" << double(rng.gaussian(1.)) << "\t"
    << double(rng.gaussian(1.)) << "\t"
    << double(rng.gaussian(1.)) << endl;

    cout << "three uniform byte:\t" << unsigned(rng.uniform(0, 255)) << "\t"
    << unsigned(rng.uniform(0, 255)) << "\t"
    << unsigned(rng.uniform(0, 255)) << endl;

    return 0;
}