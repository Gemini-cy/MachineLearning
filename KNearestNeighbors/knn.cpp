#include "knn.h"
#include<map>
#include<iostream>


std::string Knn::getNeighbours(Data d, std::vector<Data> data_list, size_t k){
    //使用size_t是方便跨平台移植，因为不同平台int的取值范围可能有所不同
    double *top_k_distances = new double[k];    //分为k类
    int *top_k_indexes = new int[k];
    std::fill_n(top_k_indexes, k, -1);    //fill_n的作用是给你一个起始点，然后再给你一个数值count和val，把从起始点开始以此赋予count个元素val的值

    //开始遍历data元素
    for(size_t index=0;index<data_list.size();index++){
        //计算当前样本d和所有样本之间的距离--l2欧氏距离
        double distance = d.distance(data_list[index]);
        size_t ind = 0;
        //寻找当前样本的k个临近的训练集
        while(ind < k && top_k_indexes[ind]!=-1 && top_k_distances[ind] < distance){
            //说明此时找到的样本不属于k个距离当前样本d的
            //且按照升序排列，如1 2 3 4 5
            ind++;
        }
        //如果找到满足k个较近的，进行替换
        if(ind < k){
            int shift_index = k-1;
            while(shift_index > ind){
                //去掉当前最大的，并把选到的这个样本放进去
                top_k_indexes[shift_index] = top_k_indexes[shift_index-1];
                top_k_indexes[shift_index] = top_k_indexes[shift_index-1];
                shift_index--;
            }
            top_k_indexes[ind] = index;
            top_k_distances[ind] = index;
        }
    }

    //开始统计当前样本d近邻的k个元素中最多的类
    size_t index=0;
    std::map<std::string, int> top_k_class_map;
    while(index<k && top_k_indexes[index]!=-1){
        //遍历近邻的k个元素
        top_k_class_map[data_list[top_k_indexes[index]].cls]++;
        index++;
    }
    int max = -1;
    std::string maxClass;
    for(auto pair:top_k_class_map){
        if(pair.second > max){
            max = pair.second;
            maxClass = pair.first;
        }
    }
    return maxClass;
}




