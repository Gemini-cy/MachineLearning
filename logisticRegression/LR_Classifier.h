#ifndef LR_CLASSIFIER_H
#define LR_CLASSIFIER_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <random>
#include <math.h>
#include <algorithm>


//储存iris数据
struct IrisData{
    double *fields;
    int feature_num;
    int label;
    int data_num;
};

std::vector<IrisData> read_iris_data(const std::string &path);    //读取iris数据
std::pair<std::vector<IrisData>,std::vector<IrisData>> split_data(std::vector<IrisData> data);    //划分训练集测试集


//逻辑回归
class LogisticRegression{
public:
    std::vector<double> weights;
    double learning_rate;

    LogisticRegression(int size, double lr);    //构造函数
    ~LogisticRegression();    //析构函数
    void print_weights();    //打印输出权重信息
    void init_weights(int size);    //权重参数初始化
    void train(std::vector<IrisData> train_data, int epoch);    //训练过程
    void predict(std::vector<IrisData> test_data);    //测试过程
};







#endif

