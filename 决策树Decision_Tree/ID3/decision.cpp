#include "decision.h"
using namespace DECTREE;

//字符串分割函数
vector<string> ID3::strSplit(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//扩展字符串以方便操作
	int size = str.size();
	for (int i = 0; i<size; i++)
	{
		pos = str.find(pattern, i);
		if (pos<size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

//计算某对x和y出现次数
int ID3::calTimes(string x, string y)
{
	int lens = vecData[0].size();
	int num = 0;
	for (int i = 0; i < vecData.size(); i++)
	{
		for (int j = 0; j < lens - 1; j++)
		{
			if (x == vecData[i][j] && y == vecData[i][lens - 1])
			{
				num++;
			}
		}
	}
	return num;
}

//log函数计算 (xytimes, xtimes, featureLens)
inline double ID3::calLog(int num1, int num2)
{
	double fp = 1.0 * num1 / num2;
	return (-1.0)* fp * (log(fp) / log(2));
}

//初始化
void ID3::init(string filepath)
{
	// 载入 xxxdata.txt
	std::ifstream list_path(filepath);
	std::vector<std::string> fileNames;
	std::string stemp;
	while (getline(list_path, stemp))
	{
		fileNames.push_back(stemp);
	}

	//存入vecData中
	for (int i = 0; i < fileNames.size(); i++)
	{
		vector<string> res = strSplit(fileNames[i], ",");//切割
		vecData.push_back(res);
	}

	//单独存标签label
	int len = vecData[0].size();
	for (int i = 0; i < vecData.size(); i++)
	{
		labSet.insert(vecData[i][len - 1]);
	}

}

//(&vecSingle) (1)计算该特征标签对应不同lable的次数; (2)计算该特征标签在此特征维度的个数和比例
vector<sinData> ID3::singleTimes()
{
	set<string> singleSetX;
	multiset<string> singleAllX;
	set<string> singleSetY;
	int lens = vecData[0].size();
	//按列统计每个特征X
	for (int j = 0; j < lens-1; j++)
	{	
		for (int i = 0; i < vecData.size(); i++)
		{
			singleSetX.insert(vecData[i][j]);//存每个单一的特征X（去重后的）	
			singleAllX.insert(vecData[i][j]);//存所有的特征X（不去重）
		}
	}
	//统计每个单一的X在该列的ALL X特征中出现的次数	
	map<string, int> mmap;
	for (auto xx : singleSetX)
	{
		int nums = 0;
		for (auto xx_all : singleAllX)
		{
			if (xx == xx_all)
			{
				nums++;
			}
		}
		mmap.insert({xx, nums});//存入每个单一特征x以及其出现的次数
	}

	//单独统计label
	for (int i = 0; i < vecData.size(); i++)
	{
		singleSetY.insert(vecData[i][lens-1]);
	}

	vector<sinData> vec;// 数据格式：单个特征+label+出现次数
	for (auto e : singleSetX)
	{
		for (auto f : singleSetY)
		{
			sinData c;	
			int nums = calTimes(e, f);
			c.x = e;
			c.y = f;
			c.xytimes = nums;
			c.xtimes = mmap[e];
			if (nums > 0)
				vec.push_back(c);
		}
	}

	return vec;
}

//重排vecSingle--->vecSingleAll
vector<vector<sinData>> ID3::sortVec()
{
	
	vector<sinData> vecSingle = singleTimes();//计算次数
	vector<vector<sinData>> vecSingleAll;
	int len1 = vecData[0].size();
	int len2 = vecData.size();
	 
	set<string> yset;
	for (int i = 0; i < len2; i++)//按列遍历
	{
		yset.insert(vecData[i][len1-1]);
	}
	for (int i = 0; i < len1-1; i++)//按列遍历
	{
		set<string> xset;
		for (int j = 0; j < len2; j++)
		{
			xset.insert(vecData[j][i]);
		}
		//按照特征出现的次序，按列方向的特征排列vector<sinData>
		vector<sinData> vv;//按列方向存储
		for (auto xxx : xset)
		{
			for (auto yyy : yset)
			{
				for (int k = 0; k < vecSingle.size(); k++)
				{
					if (xxx == vecSingle[k].x && yyy == vecSingle[k].y)
					{		
						vv.push_back(vecSingle[k]);
					}
				}
			}
		}
		vecSingleAll.push_back(vv);
		vv.clear();
		xset.clear();
	}
	//打印vecSingleAll
	/*for (int i = 0; i < vecSingleAll.size(); i++)
	{
		for (int j = 0; j < vecSingleAll[i].size(); j++)
		{
			cout << "(i, j)=" << "(" << i << ", " << j <<"): " << vecSingleAll[i][j].x << "---" << vecSingleAll[i][j].y << "---" << vecSingleAll[i][j].xytimes << "---" << vecSingleAll[i][j].xtimes << endl;
			
			
		}
	}*/
	return vecSingleAll;
}

//计算信息熵 
void ID3::calEntropy()
{
	vector<vector<sinData>> vecSingleAll = sortVec();//重排

	vector<vector<point>> vecSet;
	int featureLens = vecData.size();
	for (int i = 0; i < vecSingleAll.size(); i++)
	{
		set<string> setstr;
		vector<point> xx;
		for (int j = 0; j < vecSingleAll[i].size(); j++)
		{
			setstr.insert(vecSingleAll[i][j].x);
		}
		for (auto e : setstr)
		{
			point cc;
			cc.xp = e;
			xx.push_back(cc);
		}
		vecSet.push_back(xx);
	}

	for (int i = 0; i < vecSet.size(); i++)
	{

		double pro = 0;
		double dd;
		for (int j = 0; j < vecSet[i].size(); j++)
		{

			for (int k = 0; k < vecSingleAll[i].size(); k++)
			{
				if (vecSet[i][j].xp == vecSingleAll[i][k].x)
				{
					pro += calLog(vecSingleAll[i][k].xytimes, vecSingleAll[i][k].xtimes);
					dd = 1.0 * vecSingleAll[i][k].xtimes / featureLens;
					
				}
			}
			vecSet[i][j].prob = dd*pro;
		}
	}
	//将所有特征的信息熵存入vecProb
	for (int i = 0; i < vecSet.size(); i++)
	{
		float pp = 0.0f;
		for (int j = 0; j < vecSet[i].size(); j++)
		{
			//cout << i << " " << j << " " << vecSet[i][j].xp << " " << vecSet[i][j].prob<< endl;
			pp += vecSet[i][j].prob;	
		}
		cout << pp << endl;
		vecProb.push_back(pp);
	}

	//vecProb做sort操作



}


//20210817
//计算总体信息熵（只考虑标签Y即可）(每一次决策后，都要重新计算决策后数据的总体信息熵)
double ID3::totalEntropy(vector<vector<string>>& vec)
{
	//每次给一批数据的标签，自动识别标签分类、统计标签次数、计算该批数据的总体信息熵
	set<string> lab;
	int len = vec[0].size();
	for (int i = 0; i < vec.size(); i++)
	{
		lab.insert(vec[i][len-1]);
	}
	map<string, int> labtimeMap;
	int totaltime = 0;
	for (auto e : lab)
	{
		int num = 0;
		for (int i = 0; i < vec.size(); i++)
		{
			if (e == vec[i][len - 1])
				num++;
		}
		totaltime += num;
		labtimeMap.insert({e, num});
	}
	//总体信息熵
	double totalEntp = 0;
	map<string, int>::iterator it = labtimeMap.begin();
	while (it != labtimeMap.end())
	{
		//cout << it->first << "，" << it->second << "： " << calLog(it->second, totaltime) << endl;
		totalEntp += calLog(it->second, totaltime);
		it++;
	}
	cout << "此时总体信息熵：" << totalEntp << endl;
	return totalEntp;
}


//决策后拆分数据函数
//根据该决策特征下特征标签的数目N，拆分出N个子数据集，每个子数据集再次计算总体信息熵和条件信息熵，接着计算得到下一次的决策特征




//计算特征标签的次数 --子函数
//row表示列数从0开始，取值[0, vecData[0].size()-1]
map<string, int> ID3::calFeature(vector<vector<string>>& vec, int row)
{
	
	set<string> fealab;//去重的元素
	for (int i = 0; i < vec.size(); i++)
	{
		fealab.insert(vec[i][row]);
	}
	map<string, int> labtimeMap;//某列中某个元素+其在该列的出现次数
	int totaltime = 0;
	for (auto e : fealab)
	{
		int num = 0;
		for (int i = 0; i < vec.size(); i++)
		{
			if (e == vec[i][row])
				num++;
		}
		totaltime += num;
		labtimeMap.insert({ e, num });
	}
	return labtimeMap;
}


//计算条件信息熵 (如何存储) vecData放着不动，每次从中取出数据进行条件信息熵计算
//注：第一次决策特征X定义为决策树的根节点
void ID3::condEntropy(vector<vector<string>>& vec)
{
	
	//1、某列特征X的总数目、每个特征标签的数目
	int totalSum = vec.size();
	int len = vec[0].size();
	vector<entropy> featProb;//存储最终特征标签的列数和其信息增益
	double totalEnt = totalEntropy(vec);//总体信息熵
	//计算第i列特征的条件信息熵
	for (int i = 0; i < vec[0].size()-1; i++)
	{
		map<string, int> eachF = calFeature(vec, i);
		map<string, int>::iterator mit = eachF.begin();
			
		sinData fb;
		vector<sinData> vvv;
		while (mit != eachF.end())
		{
			for (auto e : labSet)
			{
				int num = 0;
				for (int j = 0; j < vec.size(); j++)
				{
					/*if (mit->first == vec[j][i] && vec[j][len-1]==e)
					{
						num++;
					}*/
					num = (mit->first == vec[j][i] && vec[j][len - 1] == e) ? num + 1 : num;
				}
				fb.x = mit->first;
				fb.y = e;
				fb.xtimes = mit->second;
				fb.xytimes = num;
				vvv.push_back(fb);
			}
			mit++;
		}

		double dprob = 0;
		for (int k = 0; k < vvv.size(); k++)
		{
			double p = vvv[k].xtimes / totalSum;
			dprob += p * calLog(vvv[k].xytimes, vvv[k].xtimes);
		}

		entropy cc;
		cc.colum = i;
		//cc.prob = totalEnt-dprob;//信息增益=总体信息熵-条件信息熵
		cc.prob = dprob;//一列特征计算得到一个条件信息熵
		featProb.push_back(cc);
	}

	for (int m = 0; m < featProb.size(); m++)
	{
		cout << featProb[m].colum << ", " << featProb[m].prob << endl;
	}



}


void ID3::functionTest()
{
	
	condEntropy(vecData);
	
}



