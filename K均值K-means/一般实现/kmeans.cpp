#include "kmeans.h"

//初始化
void KMEAN::init(string filepath, int k)
{
	// 载入traindata.txt
	std::ifstream list_path(filepath);
	std::vector<std::string> fileNames;
	std::string stemp;
	while (getline(list_path, stemp))
	{
		fileNames.push_back(stemp);
	}
	vector<float> xx1;
	vector<float> xx2;
	for (int i = 0; i < fileNames.size(); i++)
	{
		const char* sep = ",";
		int posFirst = fileNames[i].find(sep);
		int posLast = fileNames[i].find_last_of(sep);
		//分别取出坐标x,y和label
		string xx = fileNames[i].substr(0, posFirst);
		string yy = fileNames[i].substr(posFirst + 1, posLast);
		//string lab = fileNames[i].substr(posLast + 1, fileNames[i].size());
		//int labint = atoi(lab.c_str());//atof
		point c;
		//c.x0 = 1.0;
		c.x1 = stod(xx);
		c.x2 = stod(yy);
		xx1.push_back(c.x1);
		xx2.push_back(c.x2);
		c.label = k + 1;  //用k+1作为data.label初始化
		vecData.push_back(c);
	}

	//排序
	bubbleSort(xx1);
	bubbleSort(xx2);
	float x1_min = xx1.front();
	float x2_min = xx2.front();
	vector<float>::iterator itx1 = xx1.end() - 1;
	vector<float>::iterator itx2 = xx2.end() - 1;
	float x1_max = *itx1;
	float x2_max = *itx2;

	//初始化veck：边界内随机取k组特征,并给簇标签
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 genx1(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::mt19937 genx2(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> disx1(x1_min, x1_max);
	std::uniform_real_distribution<> disx2(x2_min, x2_max);
	for (int i = 0; i < k; i++)
	{
		point cc;
		cc.x1 = disx1(genx1);
		cc.x2 = disx2(genx2);
		cc.label = i;	//k个质心的label为i即可，取值范围为[0,k-1]
		vecK.push_back(cc);
	}
}

//欧氏距离
float KMEAN::eluDistance(point data_pos, point k_pos)
{
	return pow(pow(data_pos.x1 - k_pos.x1, 2) + pow(data_pos.x2 - k_pos.x2, 2), 0.5);
}

//冒泡排序
void KMEAN::bubbleSort(vector<float> &sortVecori)
{
	int index = sortVecori.size() - 1;
	while (index > 1)
	{
		bool flag = true;//标志位：是否需要继续排序（因为会出现已经有序不用再排的情况）
		for (int i = 0; i < index; i++)//每次从头开始比较，最大的已经放到尾部
		{
			if (sortVecori[i]>sortVecori[i + 1])
			{
				swap(sortVecori[i], sortVecori[i + 1]);
				flag = false;//若false则表示无序，不能退出
			}
		}
		index--;
		//若为true则表示已经有序，可以直接退出，后续不用再排
		if (flag)
			break;
	}
}

//更新data.label为对应距离质心的label（中间循环更新）
void KMEAN::updataLabel(vector<point>& vecdata, vector<point>& veck, vector<int>& veclabel)
{
	//	1. 计算每个数据点的最近质心
	//  2. 更新每个数据点的label为该最近质心的label
	//  3. 标志位判断是否需要继续更新flag,只要有一个数据点的label更新前后发生变化,则要继续迭代下去,所有数据点label全不变，则停止迭代	
	for (int i = 0; i < vecdata.size(); i++)
	{
		//int frontlabel = vecdata[i].label;//更新之前数据点的label
		veclabel.push_back(vecdata[i].label);//更新之前数据点的label存入vector
		float mindis = eluDistance(vecdata[i], veck[0]);
		for (int j = 0; j < veck.size(); j++)
		{
			float eludis = eluDistance(vecdata[i], veck[j]);  
			if (eludis <= mindis)
			{
				vecdata[i].label = veck[j].label;//一直保持将最近距离质心的label给data.label
				mindis = eludis;
			}
		}
	}
}

//比较更新前后的data.label是否变化
bool KMEAN::compareLabel(vector<int>& veclabel, vector<point>& vecdata)
{
	for (int i = 0; i < veclabel.size(); i++)
	{
		if (veclabel[i] != vecdata[i].label)
			return flagChange;
	}
	flagChange = true;
	return flagChange;
}

// 更新每个簇的新质心,veck的label不用变
void KMEAN::updateK(vector<point>& vecdata, vector<point>& veck)
{
	//1.相同label为一个簇，相同簇计算特征平均坐标
	for (int i = 0; i < veck.size(); i++)
	{
		int num = 0;
		float avgx1 = 0.0f;
		float avgx2 = 0.0f;
		for (int j = 0; j < vecdata.size(); j++)
		{
			if ( veck[i].label == vecdata[j].label )
			{
				avgx1 += vecdata[j].x1;
				avgx2 += vecdata[j].x2;
				num++;
			}
		}
		cout << "num: " << num << endl;  //打印每一个簇的数据点个数
		avgx1 = avgx1 / num;
		avgx2 = avgx2 / num;
		veck[i].x1 = avgx1;//更新质心坐标
		veck[i].x2 = avgx2;
	}
}

//kmeans主调函数
void KMEAN::kmeansCluster(string savepath)
{
	//注意：frontlabel数组每次要清零！！！
	//质心更新结束条件：vecdata的label不再改变（说明每个数据点被分到了合适的簇）
	while (!flagChange)
	{
		updataLabel(vecData, vecK, frontlabel);//更新data的label,同时存储data更新前的label到frontlabel
		compareLabel(frontlabel, vecData); // 判断数据点更新前后data.label是否改变
		frontlabel.clear(); //在每次比对完data.label是否改变后，每次需要清零！！！
		//打印flag
		if (flagChange == true)//如果为true，说明更新前后data.label未改变，则退出while循环，不再更新
		{
			cout << "flagChange：" << flagChange  << " ,聚类结束,聚类结果写入本地文件..." << endl;
			break;
		}
		updateK(vecData, vecK);//更新k坐标

		//打印vecK质心坐标
		for (int i = 0; i < vecK.size(); i++)//debug
		{
			cout << i << ": " << vecK[i].x1 << "," << vecK[i].x2 << "," << vecK[i].label << endl;
		}

		cout << "flagChange：" << flagChange << endl;
	}

	//聚类结果写入本地txt
	ofstream fout(savepath);
	for (int i = 0; i < vecData.size(); i++)
	{
		fout << vecData[i].x1 << "," << vecData[i].x2 << "," << vecData[i].label << endl;
	}
	cout << "写入结束，程序退出！" << endl;
}
