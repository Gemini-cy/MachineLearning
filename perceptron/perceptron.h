#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <functional>


class Perceptron{
public:
    double lr;    //学习率
    std::vector<double> weights;    //权重

    Perceptron(int input_size, double lr=0.5);    //无权重载入的构造函数
    Perceptron(double lr, std::vector<double>& weights);    //有初始权值载入的构造函数（函数重载）
    void print_weights();    //打印输出感知机权重
    void init(int size);    //初始化权重
    int classifier(std::vector<double> inputs);    //对训练样本进行分类
    void train(std::vector<std::pair<std::vector<double>, int>> train_dataset);    //训练过程
    int predict(std::vector<double> data);    //预测函数




};




#endif
