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

static cv::Ptr<cv::ml::TrainData>
        prepare_train_data( const cv::Mat& data, const cv::Mat& responses, int n_train_samples)
{
    cv::Mat sample_idx = cv::Mat::zeros( 1, data.rows, CV_8U );
    cv::Mat train_samples = sample_idx.colRange(0, n_train_samples);
    train_samples.setTo(cv::Scalar::all(1));

    int n_vars = data.cols;
    cv::Mat var_type( n_vars+1, 1, CV_8U );
    var_type.setTo(cv::Scalar::all(cv::ml::VAR_ORDERED));
    var_type.at<uchar>(n_vars) = cv::ml::VAR_CATEGORICAL;

    return cv::ml::TrainData::create(
            data,
            cv::ml::ROW_SAMPLE,
            responses,
            cv::noArray(),
            sample_idx,
            cv::noArray(),
            var_type);
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

    int n_samples_all = data.rows;
    int n_train_samples = (int)(n_samples_all*0.8);
    int var_count = data.cols;

    cv::Ptr<cv::ml::TrainData> tdata = prepare_train_data(data, responses, n_train_samples);

    cout << "Training the classifier (may take a few minutes)...\n";
    cv::Ptr<cv::ml::RTrees> model = cv::ml::RTrees::create();
    model->setMaxDepth(10);
    model->setMinSampleCount(10);
    model->setMaxCategories(15);
    model->setCalculateVarImportance(true);
    model->setActiveVarCount(4);
    model->setTermCriteria(
            cv::TermCriteria(
                    cv::TermCriteria::MAX_ITER+cv::TermCriteria::EPS,
                    100,
                    0.001f));
    model->train(tdata);
    cout << endl;

    // Test
    double train_hr = 0, test_hr = 0;

    for( i = 0; i < n_samples_all; i++ )
    {
        cv::Mat sample = data.row(i);
        float r = model->predict( sample );
        r = abs(r - responses.at<int>(i)) <= FLT_EPSILON ? 1.f : 0.f;
        if( i < n_train_samples )
            train_hr += r;
        else
            test_hr += r;
    }

    test_hr /= n_samples_all - n_train_samples;
    train_hr = n_train_samples > 0 ? train_hr/n_train_samples : 1.;

    printf( "Recognition rate: train = %.1f%%, test = %.1f%%\n", train_hr*100., test_hr*100. );


    cout << "Number of trees: " << model->getRoots().size() << endl;
    cv::Mat var_importance = model->getVarImportance();

    double rt_imp_sum = sum( var_importance )[0];
    printf("var#\timportance (in %%):\n");
    int n = (int)var_importance.total();
    for( int i = 0; i < n; i++ )
        printf( "%-2d\t%-4.1f\n", i, 100.f*var_importance.at<float>(i)/rt_imp_sum);

    return 0;

}