#ifndef GAUSSIAN_NAIVE_BAYES_H
#define GAUSSIAN_NAIVE_BAYES_H
#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<math.h>



class GNB{
public:
    std::vector<std::string> possible_labels = {"left","keep","right"};
  
    std::vector<double> left_means;
    std::vector<double> left_stddev;
    
    std::vector<double> keep_means;
    std::vector<double> keep_stddev;
    
    std::vector<double> right_means;
    std::vector<double> right_stddev;
    
    std::vector<std::vector<double>> feature_data_left;
    std::vector<std::vector<double>> feature_data_keep;
    std::vector<std::vector<double>> feature_data_right;

    GNB();    //构造函数
    virtual ~GNB();    //析构函数
    void train(std::vector<std::vector<double>> data, std::vector<std::string> labels);    //训练GNB
    std::string predict(std::vector<double>);    //测试GNB

};






#endif






