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
	
	for (int i = 0; i < fileNames.size(); i++)
	{
		vector<string> res = strSplit(fileNames[i], ",");//切割
		vecData.push_back(res);
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


//某次使用了该特征分完后，之后便不再使用该特征，后续操作需要先将该种特征删除，然后更新得到新的数据集，再继续计算新的信息熵往再进行分
void ID3::decID3()
{
	

}


