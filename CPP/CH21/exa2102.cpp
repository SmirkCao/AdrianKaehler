#include "opencv2/opencv.hpp"
#include "opencv2/ml.hpp"

#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

static bool
read_num_class_data( const string& filename, int var_count,
        cv::Mat* _data, cv::Mat* _responses ){
    const int M = 1024;
    char buf[M+2];

    cv::Mat el_ptr(1, var_count, CV_32F);
    int i;
    vector<int> responses;

    _data->release();
    _responses->release();

    FILE* f = fopen( filename.c_str(), "rt" );
    if( !f )
    {
        cout << " Could not read the data " << filename << endl;
        return false;
    }

    for(;;)
    {
        char* ptr;
        if( !fgets( buf, M, f) || !strchr( buf, ','))
            break;
        responses.push_back((int)buf[0]);
        ptr = buf+2;
        for( i = 0; i < var_count; i++ )
        {
            int n = 0;
            sscanf( ptr, "%f%n", &el_ptr.at<float>(i), &n );
            ptr += n + 1;

        }
        if( i < var_count )
            break;
        _data->push_back(el_ptr);
    }
    fclose(f);
    cv::Mat(responses).copyTo(*_responses);

    cout << "The data " << filename << " is loaded.\n";

    return true;
}
int main(int argc, char *argv[]) {


    const char *csv_file_name = argc >= 2 ? argv[1] : "../letter-recognition.data";
    cout << "OpenCV Version: " << CV_VERSION << endl;
    cout << "csv_file_name: " << csv_file_name << endl;

    const int class_count = 26;
    cv::Mat data;
    cv::Mat responses;
    cv::Mat weak_responses;

    read_num_class_data( csv_file_name, 16, &data, &responses );
    int i, j, k;

    cv::Ptr<cv::ml::Boost> model;
    int n_samples_all = data.rows;
    int n_train_samples = (int)(n_samples_all*0.5);
    int var_count = data.cols;

    // OvR handling multiple classification.
    cv::Mat new_data( n_train_samples*class_count, var_count+1, CV_32F);
    cv::Mat new_responses( n_train_samples*class_count, 1, CV_32S );

    cout << "Unrolling the data...\n" << endl;
    for( i = 0; i < n_train_samples; i++)
    {
        const float* data_row = data.ptr<float>(i);
        for( j = 0; j < class_count; j++)
        {
            float* new_data_row = (float*)new_data.ptr<float>(i*class_count+j);
            memcpy(new_data_row, data_row, var_count* sizeof(data_row[0]));
            new_data_row[var_count] = (float)j;
            // one-hot encoding
            new_responses.at<int>(i*class_count + j) = responses.at<int>(i) == j+'A';
        }
    }

    cv::Mat var_type( 1, var_count+2, CV_8U );
    var_type.setTo(cv::Scalar::all(cv::ml::VAR_ORDERED));
    var_type.at<uchar>(var_count) = var_type.at<uchar>(var_count+1) = cv::ml::VAR_CATEGORICAL;
    cv::Ptr<cv::ml::TrainData> tdata = cv::ml::TrainData::create(
            new_data,
            cv::ml::ROW_SAMPLE,
            new_responses,
            cv::noArray(),
            cv::noArray(),
            cv::noArray(),
            var_type);

    // for unbalanced samples
    vector<double> priors(2);
    priors[0] = 1;
    priors[1] = 25;


    cout << "Training the classifier (may take a few minutes)...\n";
    model = cv::ml::Boost::create();
    model->setBoostType(cv::ml::Boost::GENTLE);
    model->setWeakCount(100);
    model->setWeightTrimRate(0.95);
    model->setMaxDepth(5);
    model->setUseSurrogates(false);
    model->setPriors(cv::Mat(priors));
    model->train(tdata);
    cout << endl;

    cv::Mat temp_sample( 1, var_count+1, CV_32F );
    float* tptr = temp_sample.ptr<float>();

    double train_hr = 0, test_hr = 0;

    for( i = 0; i < n_samples_all; i++ )
    {
        int best_class = 0;
        double max_sum = -DBL_MAX;
        const float* ptr = data.ptr<float>(i);
        for( k = 0; k < var_count; k++ )
            tptr[k] = ptr[k];
        // for every class predict once
        for( j = 0; j < class_count; j++ )
        {
            // 拼接原始数据加类别
            tptr[var_count] = (float)j;
            float s = model->predict( temp_sample, cv::noArray(), cv::ml::StatModel::RAW_OUTPUT );
            // 记录最大响应的j
            if( max_sum < s )
            {
                max_sum = s;
                best_class = j + 'A';
            }
        }

        double r = abs(best_class - responses.at<int>(i)) < FLT_EPSILON ? 1 : 0;
        if( i < n_train_samples )
            train_hr += r;
        else
            test_hr += r;
    }

    test_hr /= n_samples_all-n_train_samples;
    train_hr = n_train_samples > 0 ? train_hr/n_train_samples : 1.;

    printf( "Recofnition rate: train = %.1f%%, test= %.1f%%\n", train_hr*100., test_hr*100.);

    cout << "Number of trees: " << model->getRoots().size() << endl;

    return 0;

}