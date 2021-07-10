#include "dist.h"

//两数比较取最大
#ifndef MAX
#  define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

//三数比较取最大
inline double MAXCompareThree(double t1, double t2, double t3)
{
	double max1 = MAX(t1, t2);
	return MAX(max1, t3);
}

//初始化
void DISTANCE::Init()
{	
	default_random_engine randot(time(0)); //随机种子
	int low = 1;
	int upper = 20;
	uniform_real_distribution<double> dis(low, upper); //设置随机数范围
	pointbuff point1, point2;	//临时变量
	for (int i = 0; i < 10; i++) //生成10组(x,y,z)随机数对
	{
		point1.x = dis(randot);
		point1.y = dis(randot);
		point1.z = dis(randot);
	
		point2.x = dis(randot);
		point2.y = dis(randot);
		point2.z = dis(randot);
		
		test_vec1.push_back(point1);
		test_vec2.push_back(point2);
	}
}

//屏幕打印
void DISTANCE::DisPlay()
{
	cout <<  flag << "计算结果如下：" << endl;
	//cout << setiosflags(ios::fixed) << setprecision(2);
	cout << fixed << setprecision(2);
	for (int i = 0; i < dis_vec.size(); i++)
	{
		cout << "第一组数：" << "(" << test_vec1[i].x << "," << test_vec1[i].y << "," << test_vec1[i].z << ")" << "\t" << "  "
			<< "第二组数：" << "(" << test_vec2[i].x << "," << test_vec2[i].y << "," << test_vec2[i].z << ")" << "\t" << "  " << "距离：" << dis_vec[i] << "\t" << endl;
	}
	cout << endl;
	dis_vec.clear();//清除dis_vector的元素，但未释放内存。后续距离计算继续使用，不用重新分配内存空间。
	//vector<double>().swap(dis_vec); //释放dis_vec内存
}


// 闵可夫斯基距离定义 通式（p=1:曼哈顿距离，p=2：欧氏距离）
double DISTANCE::MinkowskiDis(pointbuff &t1, pointbuff &t2, int p)
{	
	return pow(pow(abs(t1.x - t2.x), p) + pow(abs(t1.y - t2.y), p) + pow(abs(t1.z - t2.z), p), 1/p);
}

//欧氏距离定义
double DISTANCE::EuclideanDis(pointbuff &t1, pointbuff &t2)
{
	return pow(pow(t1.x - t2.x, 2) + pow(t1.y - t2.y, 2) + pow(t1.z - t2.z, 2), 0.5);
}

// 欧氏距离调用
void DISTANCE::CalEuclideanDis()
{
	for (int i = 0; i < test_vec1.size(); i++)
	{
		dis_vec.push_back( EuclideanDis(test_vec1[i], test_vec2[i]));
	}
	flag = "欧氏距离";
}

//曼哈顿距离定义
double DISTANCE::ManhattanDis(pointbuff &t1, pointbuff &t2)
{
	return abs(t1.x - t2.x) + abs(t1.y - t2.y) + abs(t1.z - t2.z);
}

//曼哈顿距离调用
void DISTANCE::CalManhattanDis()
{
	for (int i = 0; i < test_vec1.size(); i++)
	{
		dis_vec.push_back(ManhattanDis(test_vec1[i], test_vec2[i]));
	}
	flag = "曼哈顿距离";
}

//切比雪夫距离定义
double DISTANCE::ChebyshevDis(pointbuff &t1, pointbuff &t2)
{
	//可用
	/*double xx = abs(t1.x - t2.x);
	double yy = abs(t1.y - t2.y);
	double zz = abs(t1.z - t2.z);
	double max1 = xx < yy ? yy : xx;
	double max2 = max1 < zz ? zz : max1;
	return max2;*/
	//可用
	//注意：此处的inline访问的是struct pointbuff
	return MAXCompareThree(abs(t1.x - t2.x), abs(t1.y - t2.y), abs(t1.z - t2.z));
}

// 切比雪夫距离调用
void DISTANCE::CalChebyshevDis()
{
	for (int i = 0; i < test_vec1.size(); i++)
	{
		dis_vec.push_back(ChebyshevDis(test_vec1[i], test_vec2[i]));
	}
	flag = "切比雪夫距离";
}


