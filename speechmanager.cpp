#include "SpeechManager.h"
SpeechManager::SpeechManager()
{
	this->initSpeech();  //初始化
	this->createSpeaker();  //创建12名演讲者
	this->loadrecord();  //加载往届记录
}
SpeechManager::~SpeechManager()
{

}


void SpeechManager::ShowMenu()
{
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vv.clear();
	this->m_Speaker.clear();
	this->m_index = 1;
	this->m_record.clear();
}
void SpeechManager::createSpeaker()
{
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++)
	{
		string name = "选手";
		name += nameseed[i];
		Speaker sp;
		sp.m_name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.m_score[i] = 0;
		}
		this->v1.push_back(i+10001);
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

void SpeechManager::startSpeech()
{
	this->Draw();  //抽签
	this->speechContest();  //正式比赛
	this->showscore();  //显示晋级结果
	this->m_index++;
	this->Draw();  //抽签
	this->speechContest();  //正式比赛
	this->showscore();  //显示晋级结果

	this->saverecord();  //保存记录
	//实时更新
	this->initSpeech();  //初始化
	this->createSpeaker();  //创建12名演讲者
	this->loadrecord();  //加载往届记录
	cout << "本届比赛结束！" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::Draw()
{
	cout << "第 " << this->m_index << " 轮比赛选手正在抽签" << endl;
	cout << "——————————————————" << endl;
	cout << "抽签结果如下：" << endl;
	if (this->m_index == 1)
	{
		random_shuffle(v1.begin(), v1.end());  //打乱顺序
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)  //打印演讲顺序
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());  //打乱顺序
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)   //打印演讲顺序
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "——————————————————" << endl;
	system("pause");
	cout << endl;
}

void SpeechManager::speechContest()
{
	cout << "第 " << this->m_index << " 轮比赛正式开始！" << endl;
	multimap<double, int, greater<double>>groupscore;   //临时容器，存放小组成绩
	int num = 0;   //记录人员个数 6人一组
	vector<int>v_temp;
	if (this->m_index == 1)
	{
		v_temp = v1;
	}
	else
		v_temp = v2;
	for (vector<int>::iterator it = v_temp.begin(); it != v_temp.end(); it++)  //打分环节
	{
		deque<double>d;
		num++;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;   //随即打分：600—1000
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();    //去除最低分
		d.pop_front();   //去除最高分
		double sum = accumulate(d.begin(), d.end(), 0.0f);   //总分
		double avg = sum / (double)d.size();  //平均分
		this->m_Speaker[*it].m_score[this->m_index - 1] = avg;
		groupscore.insert(make_pair(avg, *it));  //将分数放到临时容器中
		if (num % 6 == 0)
		{
			cout << "第 " << num / 6 << " 小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end(); it++)  //6人的成绩
			{
				cout << "编号：" << it->second << " 姓名：" << this->m_Speaker[it->second].m_name << " 成绩：" << it->first << "测试成绩："<< this->m_Speaker[it->second].m_score[this->m_index-1]<<endl;
			}
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end()&&count<3; it++,count++)  //前三名的成绩
			{
				if (this->m_index == 1)
				{
					v2.push_back(it->second);
				}
				else
				{
					vv.push_back(it->second);
				}
			}
			groupscore.clear();  //清空容器，防止超过6个人
		}
	}
	cout << "第 " << this->m_index << " 轮比赛结束！" << endl;
	system("pause");

}
void SpeechManager::showscore()
{
	cout << "第 " << this->m_index << " 轮晋级选手如下：" << endl;
	vector<int>v;
	if (this->m_index == 1)
		v = v2;
	else
		v = vv;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "编号：" << *it << " 姓名：" << this->m_Speaker[*it].m_name << " 成绩：" << this->m_Speaker[*it].m_score[this->m_index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->ShowMenu();
}

void SpeechManager::saverecord()
{
	ofstream ofs;
	ofs.open("record.csv", ios::out | ios::app);  //追加方式写文件
	for (vector<int>::iterator it = vv.begin(); it != vv.end(); it++)
	{
		ofs << *it << "," 
			<< this->m_Speaker[*it].m_score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "前三名已经记录！" << endl;
	this->FileIsEmpty = false;
}

void SpeechManager::loadrecord()
{
	ifstream ifs("record.csv", ios::in);
	if (!ifs.is_open())
	{
		this->FileIsEmpty = true;
		//cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->FileIsEmpty = true;
		//cout << "文件为空！" << endl;
		ifs.close();
		return;
	}
	// 文件不为空
	this->FileIsEmpty = false;
	ifs.putback(ch);
	string data;
	int index = 0;
	while (ifs >> data)  //按行读取
	{
		//cout << data << endl;
		int pos = -1;  //查到逗号的位置变量
		int start = 0;
		vector<string>v;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//cout << "没有找到" << endl;
				break;
			}
			string tem = data.substr(start, pos - start);
			v.push_back(tem);
			cout << tem << endl;
			start = pos + 1;
		}
		this->m_record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

void SpeechManager::showrecord()
{
	if (this->FileIsEmpty)
	{
		cout << "文件不存在或为空！" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = m_record.begin(); it != m_record.end(); it++)
		{
			cout << "第 " << it->first + 1 << " 届" <<
				"冠军编号：" << it->second.front() << " 得分：" << it->second.at(1) << " "
				"亚军编号：" << it->second.at(2) << " 得分：" << it->second.at(3) << " "
				"季军编号：" << it->second.at(4) << " 得分：" << it->second.at(5) << endl;
			//cout << "vector的大小为："<< it->second.size() << endl;
		}
		
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearrecord()
{
	cout << "确定清空吗？" << endl;
	cout << "1：确定" << endl;
	cout<<"2：返回" << endl;
	int select=0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("record.csv", ios::trunc);
		ofs.close();
		cout << "清空成功！" << endl;
		this->initSpeech();  //初始化
		this->createSpeaker();  //创建12名演讲者
		this->loadrecord();  //加载往届记录
	}
	system("pause");
	system("cls");

}
void SpeechManager::ExitSystem()
{
	cout << "退出系统，欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}
