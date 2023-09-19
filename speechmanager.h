#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<deque>
#include<algorithm>
#include<numeric>
#include<fstream>
#include<ctime>
#include "speechmanager.h"
#include "speaker.h"
using namespace std;

class SpeechManager
{
public:
	SpeechManager();

	void ShowMenu();  //展示菜单
	void ExitSystem();  //退出系统
	void initSpeech();  //初始化容器和属性
	void createSpeaker();  //创建选手
	void Draw();
	void startSpeech();  //开始比赛
	void speechContest();
	void showscore();
	void saverecord();
	void loadrecord();
	void showrecord();  //打印往届内容
	void clearrecord();  //清空csv记录文件
	vector<int>v1;  //存放第一轮选手编号
	vector<int>v2;  //存放晋级选手编号
	vector<int>vv;  //存放前三名编号
	map<int, Speaker>m_Speaker;  //存放编号：姓名键值对
	map<int, vector<string>>m_record;
	int m_index;
	bool FileIsEmpty;
	~SpeechManager();

	

};
