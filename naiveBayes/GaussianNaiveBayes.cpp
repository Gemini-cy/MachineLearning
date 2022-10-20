#include"GaussianNaiveBayes.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include<math.h>
#include<vector>


const double LANE_WIDTH = 4.0;
const int NUM_FEATURES = 4;

void add_feature(std::vector<std::vector<double>> &feature_data, const std::vector<double> data_input){
    //对特征进行处理，并添加特征
    std::vector<double> temp_data = data_input;
    temp_data[1] = data_input[1] / LANE_WIDTH;
    feature_data.push_back(temp_data);
}


std::vector<double> calculate_mean(std::vector<vector<double>> feature_data){
    //计算每个属性的均值
    std::vector<double> mean_values(NUM_FEATURES);
    size_t num_elements = feature_data.size();
    for(size_t i=0;i<num_elements;i++){
        std::vector<double> temp_data = feature_data[i];
        for(int j=0;j<NUM_FEATURES;j++){
            mean_values[j] += temp_data[j];
        }
    }
    for(int j=0;j<NUM_FEATURES;j++){
        mean_values[j] /= num_elements;
    }
    return mean_values;
}


std::vector<double> calculate_stddev(std::vector<std::vector<double>> feature_data, std::vector<double> mean_values){
    //计算每个属性的标准差
    std::vector<double> sigma_values(NUM_FEATURES);
    size_t num_elements = feature_data.size();
    for(size_t i=0;i<num_elements;i++){
        std::vector<double> temp_data = feature_data[i];
        for(int j=0;j<NUM_FEATURES;j++){
            sigma_values[j] += std::pow((temp_data[j]-mean_values[j]),2) / num_elements;
        }
    }
    for(int j=0;j<NUM_FEATURES;j++){
        sigma_values[j] = std::sqrt(sigma_values[j]);
    }
    return sigma_values;
}


double calculate_prob(std::vector<double> feature_data, std::vector<double> means,std::vector<double> stddev){
    //计算每个样本的条件概率
    //朴素贝叶斯的条件独立性：
    //prob(x1,x2,x3,x4|class) = p(x1|calss)*p(x2|class)*p(x3|class)*p(x4|class)
    double temp_var = 1.0;
    double pdf_gaussian = 1.0;
    for(int i=0;i<NUM_FEATURES;i++){
        double x = feature_data[i];
        double mean = means[i];    //均值
        double sigma = stddev[i];    //标准差

        temp_var = (1/(sigma*std::sqrt(2*std::M_PI)))*exp(-0.5*std::pow((x-mean)/sigma,2));
        pdf_gaussian *= temp_var;
    }
    return pdf_gaussian;
}


/*
 *初始化GNB
 * */
//构造函数
GNB::GNB(){}
//析构函数
GNB::~GNB(){}

void GNB::train(std::vector<std::vector<double>> data, std::vector<std::string> labels){
    //训练得到各类别的先验概率p(class) -- 服从高斯分布，由均值和方差决定
    std::vector<std::vector<double>> feature_data_left;
    std::vector<std::vector<double>> feature_data_keep;
    std::vector<std::vector<double>> feature_data_right;

    for(int i=0;i<labels.size();i++){
        //遍历训练样本
        std::cout << labels[i] << std::endl;
        std::vector<double> data_input = data[i];
        if(labels[i] == "left") add_feature(feature_data_left, data_input);
        else if(labels[i]=="keep") add_feature(feature_data_keep, data_input);
        else if(labels[i]=="right") add_feature(feature_data_right, data_input);
    }

    //计算每类样本的均值和方差
    left_means = calculate_mean(feature_data_left);
    left_stddev = calculate_stddev(feature_data_left, left_means);

    keep_means = calculate_mean(feature_data_keep);
    keep_stddev = calculate_stddev(feature_data_keep, keep_means);

    right_means = calculate_mean(feature_data_right);
    right_stddev = calculate_stddev(feature_data_right, right_means);

    std::cout << "\nTraining Complete...\n" <<std::endl;
}


std::string GNB::predict(std::vector<double> sample){
    //预测单个样本属于哪一类
    //计算每个类的后验概率p(class|x)
    std::vector<double> prob_classes;
    prob_classes.push_back(calculate_prob(sample,left_means,left_stddev));
    prob_classes.push_back(calculate_prob(sample,keep_means,keep_stddev));
    prob_classes.push_back(calculate_prob(sample,right_means,right_stddev));

    int idx = 0;
    double best_p = 0;

    for(int p=0;p<prob_classes.size();p++){
        if(prob_classes[p]>best_p){
            best_p = prob_classes[p];
            idx = p;
        }
    }
    return possible_labels[idx];
}

















