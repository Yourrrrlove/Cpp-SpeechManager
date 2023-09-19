#include<iostream>
#include "speechmanager.h"
using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	//测试选手信息
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	{
		cout << "编号：" << it->first << " 姓名：" << it->second.m_name << " 分数：" << it->second.m_score[0] << endl;
	}*/

	int choice;
	while (true)
	{
		sm.ShowMenu();
		cout << "请输入您的选择：";
		cin >> choice;
		switch (choice)
		{
		case 1: //开始比赛
			sm.startSpeech();
			break;
		case 2: //查看往届记录
			sm.showrecord();
			break;
		case 3: //清空记录
			sm.clearrecord();
			break;
		case 0: //退出系统
			sm.ExitSystem();
			break;
		default:
			system("cls"); //清屏
			break;
		}
	}


	system("pause");
	return 0;
}
