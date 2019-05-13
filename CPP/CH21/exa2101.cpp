#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
// #include <fstream>

using namespace std;

int main( int argc, char *argv[] ){


  const char* csv_file_name = argc >= 2 ? argv[1] : "../agaricus-lepiota.data";
  cout << "OpenCV Version: " << CV_VERSION << endl;
  cout << "csv_file_name: " << csv_file_name << endl;
  cv::Ptr<cv::ml::TrainData> data_set =
    cv::ml::TrainData::loadFromCSV(csv_file_name,
                                   0,
                                   0,
                                   1,
                                   "cat[0-22]"
                                   );

  int n_samples = data_set->getNSamples();

  if (n_samples == 0){
    cerr << "Could not read file: " << csv_file_name << endl;
    exit(-1);
  }else{
    cout << "Read " << n_samples << " samples from " << csv_file_name << endl;
  }

  data_set->setTrainTestSplitRatio( 0.9, false);
  int n_train_samples = data_set->getNTrainSamples();
  int n_test_samples = data_set->getNTestSamples();

  cout<<"Found " << n_train_samples << " Train Samples, and " << n_test_samples << "Test Samples." <<endl;

  cv::Ptr<cv::ml::RTrees> dtree = cv::ml::RTrees::create();
  float _priors[] = {1.0, 10.0};
  cv::Mat priors( 1, 2, CV_32F, _priors);

  dtree->setMaxDepth( 8 );
  dtree->setMinSampleCount( 10 );
  dtree->setRegressionAccuracy( 0.01f );
  dtree->setUseSurrogates( false );
  dtree->setMaxCategories( 15 );
  dtree->setCVFolds( 0 );
  dtree->setUse1SERule( true);
  dtree->setTruncatePrunedTree( true );
  dtree->setPriors(cv::Mat());

  dtree->train( data_set );
  cv::Mat results;
  float train_performance = dtree->calcError( data_set, false, results );

  vector<cv::String> names;
  data_set->getNames(names);
  cv::Mat flags = data_set->getVarSymbolFlags();
  {
    cv::Mat expected_responses = data_set->getResponses();
    int good=0, bad=0, total=0;

    for( int i=0; i<data_set->getNTrainSamples(); ++i){
      float received = results.at<float>(i, 0);
      float expected = expected_responses.at<float>(i, 0);
      cv::String r_str = names[(int)received];
      cv::String e_str = names[(int)expected];

      cout<<"Expected: "<<e_str <<", got: " <<r_str <<endl;
      if (received==expected) good++; else bad++; total++;
    }
    cout <<"Correct answers: " <<(float(good)/total) << "%" <<endl;
    cout <<"Incorrect answers: " << (float(bad)/total) << "%"<<endl;

  }

  float test_performance = dtree->calcError(data_set, true, results);
  cout << "Performance on training data: " << train_performance <<"%"<<endl;
  cout << "Performance on test data: " << test_performance <<"%"<<endl;

  return 0;

}