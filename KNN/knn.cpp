#include "knn.h"

void KNN::Init(int k, double testx, double testy, string path)
{/*
 1、k值初始化；
 2、待测数据test初始化
 3、traindata数据存入vector初始化；
 */
	// 1、k值初始化
	m_k = k;  
	// 2、待测数据pointbuf初始化
	pointtest.x = testx;
	pointtest.y = testy;
	// 载入teaindata.txt
	std::ifstream list_path(path);
	std::vector<std::string> fileNames;
	std::string stemp;
	while (getline(list_path, stemp))
	{
		fileNames.push_back(stemp);
	}
	// 3、vector初始化
	for (int i = 0; i < fileNames.size(); i++)
	{
		const char* sep = ",";  //字符分割
		int posFirst = fileNames[i].find(sep);
		int posLast = fileNames[i].find_last_of(sep);
		//分别取出坐标x,y和label
		string xx = fileNames[i].substr(0, posFirst);
		string yy = fileNames[i].substr(posFirst + 1, posLast);
		string lab = fileNames[i].substr(posLast + 1, fileNames[i].size());;
		pointbuf c;	//临时变量
		int label = atoi(lab.c_str());//atof
		c.x = stod(xx);
		c.y = stod(yy);
		m_vec.push_back(c);
		m_label.push_back(label);
	}
}

double KNN::GetDistance(pointbuf &t1, pointbuf t2)
{
	return pow(pow(t1.x - t2.x, 2) + pow(t1.y - t2.y, 2), 0.5);
}

void KNN::GetDistanceAll()
{
	for (int i = 0; i < m_vec.size(); i++)
	{
		dic_vec.push_back(get_distance(m_vec[i], pointtest));
	}

	//map<pointbuf, const char*>::iterator iter;
	//for (iter = m_map.begin(); iter != m_map.end(); iter++)
	//{	
	//	//cout << iter->first.x << "  " << iter->second << endl;
	//	double dis = get_distance(pointtest, iter->first);
	//	mm_map.insert(pair<double, const char*>(dis, iter->second));
	//}
}
//利用map自身特性：按照key从小到大排序（假设计算得到的dic均不相同）
void KNN::SmallSort()
{
	for (int i = 0; i < dic_vec.size(); i++)
	{
		dic_map.insert(make_pair(dic_vec[i], m_label[i]));
	}
}

void KNN::SeekProb()
{
	//1、取出前k个dis的label给vector
	int n = 0;
	vector<int> k_label;
	map<double, int>::iterator iter;
	//打印：所有的distance和对应的label
	for (iter = dic_map.begin(); iter != dic_map.end(); iter++)
	{
		cout << iter->first << "---" << iter->second << endl;
	}

	//取前m_k个label并打印
	for (iter = dic_map.begin(); iter != dic_map.end(); iter++)
	{
		n++;
		if (n <= m_k)
			k_label.push_back(iter->second);
		else
			break;
	}
	//2、计算概率最大的label
	int sum_a = 0;
	int sum_b = 0;
	for (int i = 0; i < m_k; i++)
	{
		cout << k_label[i] << endl;
		if (k_label[i] == 0)
			sum_a++;
		else
			sum_b++;
	}
	int m_label = (sum_a > sum_b) ? 0 : 1;
	cout << "测试数据所属类别为： " << m_label;
	cout << endl << "测试结束!" << endl;
}