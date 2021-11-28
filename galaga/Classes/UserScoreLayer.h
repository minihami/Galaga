#pragma once
#include <cocos2d.h>
#include <vector>
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace std;
using namespace ui;

/* user's record infomation class (name, score) */
class ScoreInfo {	
public:
	char* name = (char*)malloc(sizeof(char)*20);
	int score;
	
	/*constructor of ScoreInfo*/
	ScoreInfo(char* name, int score)
	{
		this->name = name;
		this->score = score;
	}
};

class UserScoreLayer : public cocos2d::Layer
{
private:
	int userScore = -1;				/*check if user play game of not - if not played, score == -1*/
	bool scoreInputFlag = false;	/*check if user's record is recored*/
	bool userInputFlag = false;		/*check if user input user's name*/
	bool detachTextFlag = false;	/*check if user's input is over*/
	bool viewScoreFlag = false;		/*check if score is viewed*/
	vector<ScoreInfo> scoreInfo;	/*user's record vector(name and score)*/
	TextField* userInput;			/*user inputbox*/
	char* inputName = (char*)malloc(sizeof(char) * 20);

public:
	virtual bool init();

	/*new score input*/
	void writeNewScore(int newScore);

	/*save top 10*/
	void writeTopTen();

	/*view scoreboard*/
	void viewScoreBoard();

	CREATE_FUNC(UserScoreLayer);

	virtual void update(float delta);

	/*setting the user's ingame score*/
	void getUserScore(int input)
	{
		userScore = input;
	}

	/*deallocate memory for inputName*/
	void freeInputName()
	{
		free(inputName);
	}
};

/*compair using user's score and sort ascending*/
bool cmpScoreByAscending(const ScoreInfo &a, const ScoreInfo &b);
