#include "dist.h"

/*
要取得[a,b)的随机整数，使用(rand() % (b-a))+ a;
要取得[a,b]的随机整数，使用(rand() % (b-a+1))+ a;
要取得(a,b]的随机整数，使用(rand() % (b-a))+ a + 1;
*/

#define random(a,b) (rand()%(b-a+1)+a)

#ifndef MIN
#  define MIN(a,b)  ((a) > (b) ? (b) : (a))
#endif

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
	uniform_real_distribution<double> dis(1, 20); //设置随机数范围
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


//汉明距离定义
int DISTANCE::HammingDis(unsigned x, unsigned y)
{
	int num = 0;
	for (unsigned xor = x^y; xor > 0; xor>>1)//异或
	{
		if (xor & 1)//按位与
			num++;
	}
	return num;
}

//编辑距离定义
int DISTANCE::CalEditDis(string s1, string s2)
{
	//两个输入字符串不相等
	int len1 = s1.size();
	int len2 = s2.size();

	// 1、两者中有一个长度为零，则返回另一个长度
	if (len1 == 0 || len2 == 0)
	{
		return len1 == 0 ? len2 : len1;
	}
	//2、创建DP数组
	vector<vector<int>> dp(len1+1, vector<int>(len2+1, 0)); 

	//3、边界状态初始化
	for (int i = 0; i < len1 + 1; i++)
	{
		dp[i][0] = i;
	}
	for (int j = 0; j < len2 + 1; j++)
	{
		dp[0][j] = j;
	}

	//4、两种情况判断
	//min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1
	for (int i = 1; i < len1 + 1; i++)
	{
		for (int j = 1; j < len2 + 1; j++)
		{
			if (s1[i - 1] == s2[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1];
			}
			else
			{
				dp[i][j] = MIN(MIN(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1])+1;
			}
		}
	}
	return dp[len1][len2];
}


//杰卡德初始化
void DISTANCE::JaccardInit(vector<point2d> &vec1, vector<point2d> &vec2)
{
	int begin = 1;
	int end = 7;
	srand((int)time(0));//生成随机整数
	point2d point1, point2;	//临时变量
	for (int i = 0; i < 10; i++) //生成10组(val1, val2, val3, val4)随机数对
	{
		point1.val1 = random(begin, end);
		point1.val2 = random(begin, end);
		point1.val3 = random(begin, end);
		point1.val4 = random(begin, end);

		point2.val1 = random(begin, end);
		point2.val2 = random(begin, end);
		point2.val3 = random(begin, end);
		point2.val4 = random(begin, end);

		vec1.push_back(point1);
		vec2.push_back(point2);
	}
	
}

//杰卡德相似系数/距离计算定义定义
void DISTANCE::JaccardSimilarity(point2d &p1, point2d &p2, double& jasssim, double& jassdis) //9、杰卡德相似系数定义
{
	// 1、求解两个集合的交集和并集（注意：此处只要求出交集并集的元素个数即可）
	// 方法1：利用map：key已存在，不加入，且值+1，key不存在加入键值对，值设置为1
	// 最后map判断：所有的key为并集，val>1的key为交集
	
	//方法2：set求并集，两个集合长度之和-并集元素个数=交集元素个数
	set<int> s_set;
	s_set.insert(p1.val1);
	s_set.insert(p1.val2);
	s_set.insert(p1.val3);
	s_set.insert(p1.val4);
	s_set.insert(p2.val1);
	s_set.insert(p2.val2);
	s_set.insert(p2.val3);
	s_set.insert(p2.val4);
	
	
	int numbj = s_set.size();//并集个数
	int numjj = 2 * 4 - numbj;//交集个数
	jasssim = numjj*1.0 / numbj;  //浮点除法
	jassdis = 1 - jasssim;
}

//杰卡德系数和距离调用
void DISTANCE::CalJaccardSimilarity()
{
	vector<point2d> vec_point1, vec_point2;
	vector<vector<double>> vce_res;//存储最后的相似系数和距离计算结果 二维vector
	JaccardInit(vec_point1, vec_point2);
	for (int i = 0; i < vec_point1.size(); i++)
	{
		vector<double> vec_single;
		double sim, dis;
		JaccardSimilarity(vec_point1[i], vec_point2[i], sim, dis);
		vec_single.push_back(sim);
		vec_single.push_back(dis);
		vce_res.push_back(vec_single);
	}
	//display
	
	cout << "杰卡德相似系数和杰卡德距离" << "计算结果如下：" << endl;
	//cout << setiosflags(ios::fixed) << setprecision(2);
	cout << fixed << setprecision(3);
	for (int i = 0; i < vce_res.size(); i++)
	{
		cout << "第" << i+1 << "组数：" << "POINT_A: "<< "(" << vec_point1[i].val1 << "," << vec_point1[i].val2 << "," << vec_point1[i].val3 << "," << vec_point1[i].val4 << ")" << "\t" << "  "
			<<"POINT_B: " << "(" << vec_point2[i].val1 << "," << vec_point2[i].val2 << "," << vec_point2[i].val3 << "," << vec_point2[i].val4 << ")" << "\t" << "  " << "相似系数：" << vce_res[i][0] << "\t" <<  "距离： " << vce_res[i][1] << "\t" << endl;
	}
	cout << endl;
	
}
