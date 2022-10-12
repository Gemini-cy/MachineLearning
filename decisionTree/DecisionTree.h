#ifndef DECISIONTREE
#define DECISIONTRE
#include<vector>
#include<math.h>
using namespace std;



//training data 训练所用数据
class TrainData{
public:
    vector<vector<int>> Input;    //一行一条数据
    vector<int> Output;    //允许离散的输出值
    void InsertData(vector<int> data, int out){
        //输入一行数据和目标输出
        Input.push_back(data);    //特征
        Output.push_back(out);    //标签label
    }
};

//decision tree node 决策树节点
class Node{
public:
    int Attribute;    //属性序号
    bool IsLeaf;    //是否是叶节点
    vector<Node*> Num;    //子节点
    Node(int ID, bool a):Attribute(ID), IsLeaf(a){}
};


//decision tree 决策树
class Tree{
private:
    Node* root;    //根节点
    vector<vector<int>> AttrData;    //属性列表
    Node* CreateTree(TrainData data, vector<int> usedAttr);    //ID3算法生成树
    int MostNormalOutput(TrainData data);    //计算所有训练样本的类别数，并返回数量最多的种类
    int Best(TrainData data, vector<int> usedAttr);    //计算信息增益最高的属性
    double Entropy(TrainData data);    //计算经验熵
public:
    Tree();    //构造函数
    void GetOutput();    //输入一个案例，获得输出
};


//Tree的类构造函数
Tree::Tree(){
    /*输入属性列表，输入每个属性的分类属性个数即可*/
    int stop=0, num=0;
    while(!stop){
        vector<int> temp;
        cout<< "Attribute" << "[" << num << "]" << ":";
        int aa;
        cin>>aa;
        for(int i=0;i<aa;i++){
            temp.push_back(i);
        }
        AttrData.push_back(temp);
        cout<<"Stop?"<<endl;
        cin>>stop;
        num++;
    }

    /*输入训练数据，直接按顺序输入分类属性序号*/
    TrainData data;
    stop = 0;
    while(!stop){
        vector<int> train;
        cout<<"TrainData:";
        int aa = 0;
        for(unsigned int i=0;i<AttrData.size();i++){
            cin>>aa;
            train.push_back(aa);
        }
        cout<<"Output:";
        int aaa;
        cin>>aaa;
        data.InsertData(train, aaa);
        cout<<"Stop?"<<endl;
        cin>>stop;
    }

    vector<int> temp2;
    root = CreateTree(data, temp2);
    cout<<"Training......."<<endl;
}


//构建决策树
Node* Tree::CreateTree(TrainData data, vector<int> usedAttr){
    Node* root = new Node(0, 0);    //创建根节点
    
    /*1.如果输出标签都一样，则创建一个节点，值为该输出，且为叶节点;
        即当D中所有实例属于同一类，则T为单节点树*/
    bool stopFlag = 1;
    for(unsigned int i=1;i<data.Output.size();i++){
        if(data.Output[i]!=data.Output[i-1]) {
            stopFlag = 0;
            printf("Not all nodes are leaf nodes.\n");
        }
    }
    if(stopFlag){
        printf("All nodes are leaf nodes.\n");
        return new Node(data.Output[0], 1);
    }

    /*2.如果所有属性都用过，那么返回的节点的值为最普遍的输出，且为叶节点；
        若特征A为空，则T为单节点树，并将D中实例数最大的类作为该节点的类标记，返回T*/
    if(usedAttr.size()==AttrData.size()) return new Node(MostNormalOutput(data), 1);

    /*3.选出信息增益最高的属性（特征）作为节点；
        计算A中各特征对D的信息增益，选择信息增益最大的特征Ag*/
    int A = Best(data, usedAttr);
    usedAttr.push_back(A);    //加入已使用的属性
    root->Attribute = A;

    /*递归的在每个分类属性下新建一棵树*/
    for(unsigned int i=0;i<AttrData[A].size();i++){
        /*对Ag的每一个可能值ai,依Ag=ai将D分割为若干非空子集Di，
          将Di中实例数最大的类作为标记，构建子结点，由结点及其子结点构成树T，返回T*/
        TrainData tempExample;
        //遍历每个样本
        for(unsigned int j=0;j<data.Output.size();j++){
            if(i==data.Input[j][A]){
                tempExample.InsertData(data.Input[j],data.Output[j]);
            }
        }
        if(tempExample.Output.empty()){
            root->Num.push_back(new Node(MostNormalOutput(data),1));
        }else{
            root->Num.push_back(CreateTree(tempExample, usedAttr));
        }
    }
    return root;
}


//计算所有训练样本的类别数，返回数量最多的种类
int Tree::MostNormalOutput(TrainData data){
    vector<int> out;    //记录输出的种类
    vector<int> count;    //记录种类的数量

    /*1.统计当前所有训练样本的标签类别和数量*/
    for(unsigned int i=0;i<data.Output.size();i++){
        bool ex = 0;    //用来判断当前类标签是否出现过，出现过则变为1，则当前样本不放进out中，只是对应位置的count++
        int index = 0;    //当前样本与之前的哪个样本是同一类
        //遍历之前已经存在的标签，查询当前第i个样本标签是否重复
        for(unsigned int j=0;j<out.size();j++){
            if(out[j]==data.Output[i]){
                //出现重复
                ex = 1;
                index = j;
                break;     //此时后面的不需要遍历
            }
        }
        if(ex){
            //出现重复，count++
            count[index]++;
        }else{
            //将不同类标签放入out中，每个标签出现的次数初始值为1（count）
            out.push_back(data.Output[i]);
            count.push_back(1);
        }
    }

    /*2.计算数量最多的种类*/
    int maxIndex = 0;
    int maxCount = 0;
    for(unsigned int i=0;i<count.size();i++){
        if(count[i]>maxCount){
            maxCount = count[i];
            maxIndex = i;
        }
    }
    return out[maxIndex];

}




//计算经验熵
double Tree::Entropy(TrainData data){
    /*1.计算输出种类和数量*/
    vector<double> out;
    vectoe<double> count;
    for(unsigned int i=0;i<data.Output.size();i++){
        bool ex = 0;    //判断是否存在
        int index = 0;
        for(unsigned int j=0;j<out.size();j++){
            if(out[j]==data.Output[i]){
                //说明此时已有该种类
                ex = 1;
                index = j;
            }
        }
        if(ex){
            count[index]++;
        }
        else{
            out.push_back(data.Output[i]);
            count.push_back(1);
        }
    }

    /*2.计算信息熵*/
    double total=0;
    for(unsigned int i=0;i<count.size();i++){
        total = count[i];
    }
    double sum = 0;
    for(unsigned int i=0;i<count.size();i++){
        double a=0;
        if((count[i]/total)!=0){
            a = log2((count[i]/total));
        }
        sum -= (count[i]/total)*a;
    }
    return sum;
}


//计算信息增益
int Tree::Best(TrainData data, vector<int> usedAttr){
    vector<double> Gain;    //记录每一个属性的信息增益
    bool used;
    /*将使用过的属性的信息增益设置为0*/
    for(unsigned int i=0;i<AttrData.size();i++){
        used=0;
        for(unsigned int k=0;k<usedAttr.size();k++){
            if(i==usedAttr[k]){
                Gain.push_back(0.0);
                used=1;
            }
        }
        if(used) continue;
        else{
            /*计算信息增益*/
            double es = Entropy(data);
            //计算每一个特征的信息增益
            for(unsigned int j=0;j<AttrData[i].size();j++){
                TrainData tempData;    //根据特征A的取值将D划分为几个子集，这是其中一个子集的数据
                //遍历每一个样本
                for(unsigned int k=0;k<data.Input.size();k++){
                    if(j==data.Input[k][i]){
                        tempData.InsertData(data.Input[k], data.Output[k]);
                    }
                }
                if(!tempData.Input.empty()){
                    es -= (double(tempData.Input.size())/double(data.Input.size()))*Entropy(tempData)
                }
            }
            Gain.push_back(es);
        }
    }

    /*计算信息增益最高的属性*/
    int maxIndex = 0;
    double maxGain = 0;
    for(unsigned int i=0;i<Gain.size();i++){
        if(Gain[i]>maxGain){
            maxIndex = i;
            maxGain = Gain[i];
        }
    }
    return maxIndex;

}


//输出
void Tree::GetOutput(){
    vector<int> data;
    cout<<"TestData:";
    int aa = 0;
    for(unsigned int i=0;i<AttrData.size();i++){
        cin>>aa;
        data.push_back(aa);
    }
    if(root->IsLeaf){
        cout << "Output:" << root->Attribute << endl;
        return;
    }
    Node* current = root->Num[data[root->Attribute]];
    while(!current->IsLeaf){
        current = current->Num[data[current->Attribute]];
    }
    cout<< "Output:" << current->Attribute <<endl;
}


#endif
