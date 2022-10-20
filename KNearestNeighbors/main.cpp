#include "knn.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>



std::vector<Data> read_iris_data(const std::string &path){
    std::vector<Data> data;
    std::ifstream input(path);
    std::string line;
    //开始读取数据
    while(std::getline(input, line)){
        //逐行读取数据
        std::stringstream test(line);
        std::string segment;

        double *fields = new double[10];    //储存特征
        Data d;
        d.fields = fields;
        d.size = 4;
        int index = 0;
        while(std::getline(test, segment, ',')){
            //在一行内以逗号为间隔进行读取
            if(index == d.size){
                d.cls = segment;
                break;
            }
            fields[index] = std::stod(segment);
            index++;
        }
        data.push_back(d);
    }
    return data;
}





std::pair<std::vector<Data>, std::vector<Data>> split_data(std::vector<Data> data){
    //划分数据集为训练集、测试集
    std::vector<Data> training;
    std::vector<Data> test;
    size_t percentage70 = data.size()*0.7;
    size_t index = 0;
    while(index<percentage70){
        training.push_back(data[index]);
        index++;
    }
    while(index<data.size()){
        test.push_back(data[index]);
        index++;
    }
    return std::make_pair(training, test);
}


void normalize(std::vector<Data> data){
    //正则化特征数据
    double max = std::numeric_limits<double>::max();    //返回当前系统可取的最大double值
    double min = std::numeric_limits<double>::min();    //返回当前系统可取的最小double值
    double *mins = new double[data[0].size];    //记录所有样本每类特征的最小值
    double *maxes = new double[data[0].size];    //记录所有样本每类特征的最大值
    std::fill_n(mins,data[0].size,max);
    std::fill_n(maxes,data[0].size,min);

    //遍历样本记录mins和maxes
    for(auto sample:data){
        for(size_t i=0;i<sample.size;i++){
            if(sample.fields[i]>maxes[i]){
                //更新最大值
                maxes[i] = sample.fields[i];
            }
            if(sample.fields[i]<mins[i]){
                //更新最小值
                mins[i] = sample.fields[i];
            }
        }
    }

    //进行归一化操作
    for(auto sample:data){
        for(size_t i=0;i<sample.size;i++){
            sample.fields[i] = (sample.fields[i]-mins[i])/(maxes[i]-mins[i]);
        }
    }
}





void run_knn(std::vector<Data> test, std::vector<Data> training, size_t k){
    //运行knn分类
    Knn *knn  = new Knn();
    //计算测试集的准确率
    size_t correct = 0;
    for(auto test_data: test){
        std::string maxClass = knn->getNeighbours(test_data, training, k);
        if(maxClass.compare(test_data.cls)==0){
            //说明此时测试得到的结果与真值相同
            correct++;
        }
    }
    std::cout << correct << " of " << test.size() << "(" << static_cast<double>(100.0) *correct/static_cast<double>(test.size()) << ")" <<std::endl;
}




//主函数
int main(int argc, char **argv){
    std::srand(time(nullptr));
    auto dataset = read_iris_data("iris.data");
    normalize(dataset);
    std::random_shuffle(dataset.begin(),dataset.end());
    auto splitted_data = split_data(dataset);
    dataset.clear();
    run_knn(splitted_data.second, splitted_data.first, 10);
    return 0;
}












