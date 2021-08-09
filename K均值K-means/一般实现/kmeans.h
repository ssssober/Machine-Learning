#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <random>
using namespace std;

/*
*** *** Function:	kmeans算法的一般实现（C++）
*** *** Author	:	TheDetial
*** *** Platform:	win10+vs2013/ macOs+g++11
*** *** Time	:	2021/8/6、2021/8/9
*** *** Result	:	已通过
*** *** Website	:
*/

/*
Kmeans:无监督聚类
一般实现：仅适用于简单数据聚类
算法步骤：
1、 随机取k个质心（特征值的边界以内）;
2、 计算每个数据点距离k个质心的欧氏距离（距离算法的选择会影响到最后的结果）;
3、 把每个数据点分配到距离最近的质心，此时数据被分为k个簇;
4、 更新质心：计算每个簇的均值做为该簇的质心;
5、 重复步骤2;
6、 直到每个数据的分配簇后的簇标签不再变化，停止迭代;
*/

//数据点结构体
struct point
{
	float x1;	//特征1
	float x2;	//特征2
	int label;	//label=簇索引,质心更新,label同步更新;
};

//kmeans类
class KMEAN
{
public:
	void init(string filepath, int k);			//初始化
	void kmeansCluster(string savepath);		//kmeans主调函数
private:
	vector<point> vecData;												//存储原始数据
	vector<point> vecK;													//k个质心坐标和簇索引
	vector<int> frontlabel;												//更新之前data的label，用于和更新之后比较
 	float eluDistance(point, point);									//欧氏距离 
	void bubbleSort(vector<float>& vec);								//冒泡排序从小到大（边界:求特征最大最小值）
	void updataLabel(vector<point>& vecdata, vector<point>& veck, vector<int>& veclabel);	//更新数据点的标签为：距离最近质心的标签
	void updateK(vector<point>& vecdata, vector<point>& veck);   		//计算每个簇的平均，并更新质心坐标
	bool compareLabel(vector<int>& veclabel,  vector<point>& vecdata);	//data更新前的lable和更新后的lable对比
	bool flagChange=false;	//数据点的lable更新前后是否改变的标志位,若true则聚类结束,程序退出
};