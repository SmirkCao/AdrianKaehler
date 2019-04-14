#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

struct AreaCmp{
    AreaCmp(const vector<float>& _areas) : areas(&_areas){}
    bool operator()(int a, int b) const {return (*areas)[a] > (*areas)[b];}
    const vector<float>* areas;
};

int main( int argc, char** argv){
    cv::Mat img, img_edge, img_color;
    // imread flags
    // https://docs.opencv.org/3.1.0/d4/da8/group__imgcodecs.html#ga61d9b0126a3e57d9277ac48327799c80
    if( argc != 2 || (img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE)).empty() ) {
        cout << "\nExample 8_2 Drawing Contours\nCall is:\n./exa1402 image\n\n";
        return -1;
    }

    cv::threshold(img, img_edge, 128, 255, cv::THRESH_BINARY);
    
    cv::imshow("Image after threshold", img_edge );
    vector< vector<cv::Point> > contours;
    vector< cv::Vec4i > hierarchy;

    cv::findContours(
        img_edge,
        contours,
        hierarchy,
        cv::RETR_LIST,
        cv::CHAIN_APPROX_SIMPLE
    );

    cout << "\n\nHit any key to draw the next contour, ESC to quit\n\n";
    cout << "Total Countours Detected: " << contours.size() << endl;

    vector<int> sortIdx(contours.size());
    vector<float> areas(contours.size());
    for( int n=0; n<(int)contours.size(); n++){
        sortIdx[n] = n;
        areas[n] = cv::contourArea(contours[n], false);
    }

    sort(sortIdx.begin(), sortIdx.end(), AreaCmp(areas) );
    for(int n=0; n<(int)sortIdx.size();n++){
        int idx = sortIdx[n];
        cv::cvtColor( img, img_color, cv::COLOR_GRAY2BGR);
        cv::drawContours(img_color,
        contours,
        idx,
        cv::Scalar(0,0,255),
        2,
        8,
        hierarchy,
        0);
        cout << "Contours #" << idx << ": area=" << areas[idx] 
        << ", nvertices="
        << contours[idx].size()
        << endl;
        cv::imshow(argv[0], img_color);
        int k;
        if ((k=cv::waitKey()&255) == 27)
            break;
    }
    cout << "Finished all contours\n";
    cv::waitKey(0);
}