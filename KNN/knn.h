#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct pointbuf
{
	double x;
	double y;
};

//定义KNN类
class KNN
{
public:
	void Init(int k, double testx, double texty, string path); //初始化函数
	void GetDistanceAll();
	void SmallSort();         // 欧氏距离从小到大排序
	void SeekProb();		// 输出前k个距离中，占据最大概率的标签label
private:
	int m_k;	//k值大小
	pointbuf pointtest;//待测数据
	vector<pointbuf> m_vec;// 存放traindata中x,y坐标
	vector<double> dic_vec;//存放计算欧氏距离后的vector
	vector<int> m_label;//存放traindata中标签0或1
	map<double, int> dic_map; //对dis_vec和m_label排序
	double GetDistance(pointbuf &, pointbuf ); //计算两个坐标点pointbuf之间的欧氏距离
	
};
