#include "decision.h"
using namespace DECTREE;

//�ַ����ָ��
vector<string> ID3::strSplit(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//��չ�ַ����Է������
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

//����ĳ��x��y���ִ���
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

//log�������� (xytimes, xtimes, featureLens)
inline double ID3::calLog(int num1, int num2)
{
	double fp = 1.0 * num1 / num2;
	return (-1.0)* fp * (log(fp) / log(2));
}

//��ʼ��
void ID3::init(string filepath)
{
	// ���� xxxdata.txt
	std::ifstream list_path(filepath);
	std::vector<std::string> fileNames;
	std::string stemp;
	while (getline(list_path, stemp))
	{
		fileNames.push_back(stemp);
	}
	
	for (int i = 0; i < fileNames.size(); i++)
	{
		vector<string> res = strSplit(fileNames[i], ",");//�и�
		vecData.push_back(res);
	}
}

//(&vecSingle) (1)�����������ǩ��Ӧ��ͬlable�Ĵ���; (2)�����������ǩ�ڴ�����ά�ȵĸ����ͱ���
vector<sinData> ID3::singleTimes()
{
	set<string> singleSetX;
	multiset<string> singleAllX;
	set<string> singleSetY;
	int lens = vecData[0].size();
	//����ͳ��ÿ������X
	for (int j = 0; j < lens-1; j++)
	{	
		for (int i = 0; i < vecData.size(); i++)
		{
			singleSetX.insert(vecData[i][j]);//��ÿ����һ������X��ȥ�غ�ģ�	
			singleAllX.insert(vecData[i][j]);//�����е�����X����ȥ�أ�
		}
	}
	//ͳ��ÿ����һ��X�ڸ��е�ALL X�����г��ֵĴ���	
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
		mmap.insert({xx, nums});//����ÿ����һ����x�Լ�����ֵĴ���
	}

	//����ͳ��label
	for (int i = 0; i < vecData.size(); i++)
	{
		singleSetY.insert(vecData[i][lens-1]);
	}

	vector<sinData> vec;// ���ݸ�ʽ����������+label+���ִ���
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

//����vecSingle--->vecSingleAll
vector<vector<sinData>> ID3::sortVec()
{
	
	vector<sinData> vecSingle = singleTimes();//�������
	vector<vector<sinData>> vecSingleAll;
	int len1 = vecData[0].size();
	int len2 = vecData.size();
	 
	set<string> yset;
	for (int i = 0; i < len2; i++)//���б���
	{
		yset.insert(vecData[i][len1-1]);
	}
	for (int i = 0; i < len1-1; i++)//���б���
	{
		set<string> xset;
		for (int j = 0; j < len2; j++)
		{
			xset.insert(vecData[j][i]);
		}
		//�����������ֵĴ��򣬰��з������������vector<sinData>
		vector<sinData> vv;//���з���洢
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
	//��ӡvecSingleAll
	/*for (int i = 0; i < vecSingleAll.size(); i++)
	{
		for (int j = 0; j < vecSingleAll[i].size(); j++)
		{
			cout << "(i, j)=" << "(" << i << ", " << j <<"): " << vecSingleAll[i][j].x << "---" << vecSingleAll[i][j].y << "---" << vecSingleAll[i][j].xytimes << "---" << vecSingleAll[i][j].xtimes << endl;
			
			
		}
	}*/
	return vecSingleAll;
}

//������Ϣ�� 
void ID3::calEntropy()
{
	vector<vector<sinData>> vecSingleAll = sortVec();//����

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
	//��������������Ϣ�ش���vecProb
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

	//vecProb��sort����



}


//ĳ��ʹ���˸����������֮��㲻��ʹ�ø�����������������Ҫ�Ƚ���������ɾ����Ȼ����µõ��µ����ݼ����ټ��������µ���Ϣ�����ٽ��з�
void ID3::decID3()
{
	

}


