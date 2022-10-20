#include"GaussianNaiveBayes.h"
#include<iostream>
#include<fstream>
#include<math.h>
#include<vector>



std::vector<std::vector<double>> load_state(std::string file_name){
    //加载status文件
    std::ifstream in_state_(file_name.c_str(), std::ifstream::in);    //c_str()将string转化为字符串数组
    std::vector<std::vector<double>> state_out;
    std::string line;
    
    //逐行读取
    while(std::getline(in_state_, line)){
        std::istringstream iss(line);
        std::vector<double> x_coordinate;
        std::string token;
        //读取每行的每个属性元素
        while(std::getline(iss,token,',')){
            x_coordinate.push_back(stod(token));
        }
        state_out.push_back(x_coordinate);
    }
    return state_out;
}


std::vector<std::string> load_label(std::string file_name){
    //加载label文件
    std::ifstream in_label_(file_name.c_str(),std::ifstream::in);
    std::vector<std::string> label_out;
    std::string line;

    //逐行读取
    while(std::getline(in_label_,line)){
        std::istringstream iss(line);
        std::string label;
        iss >> label;
        label_out.push_back(label);
    }
    return label_out;
}


int main(){
    //加载数据集
    std::vector<std::vector<double>> train_data = load_state("data/train_states.txt");
    std::vector<std::vector<double>> test_data = load_state("data/test_states.txt");
    std::vector<std::string> train_label = load_label("data/train_labels.txt");
    std::vector<std::string> test_label = load_label("data/test_labels.txt");
    
    std::cout << "Train data number of elements " << train_data.size() << std::endl;
    std::cout << "Train data element size " << train_data[0].size() << std::endl;
    std::cout << "Train label number of elements " << train_label.size() << std::endl;

    GNB gnb = GNB();
    gnb.train(train_data, train_label);    //训练高斯朴素贝叶斯分类器

    std::cout << "Test data number of elements " << test_data.size() << std::endl;
    std::cout << "Test data element size " << test_data[0].size() << std::endl;
    std::cout << "Test label number of elements " << test_label.size() << std::endl;

    //利用训练好的模型进行分类
    int score = 0;
    for(int i=0;i<test_data.size();i++){
        std::vector<double> coordinate = test_data[i];
        std::string predicted = gnb.predict(coordinate);
        if(predicted.compare(test_label[i])==0){
            score += 1;
        }
    }

    //计算测试集准确率
    float fraction_correct = float(score) / test_label.size();
    std::cout << "You got " << (100*fraction_correct) << " correct" << std::endl;
    return 0;
}






