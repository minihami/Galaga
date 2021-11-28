#include "UserScoreLayer.h"
#include <map>

bool UserScoreLayer::init()
{
	/*open scoreboard.txt*/
	FILE* fp = fopen("scoreboard.txt", "r");
	if (!fp)	/*if there is no scoreboard.txt*/
	{
		fp = fopen("scoreboard.txt", "w");	/*create scoreboard.txt and input naname, 0*/
		fprintf(fp, "Noname %d", 0);
		fclose(fp);

		scoreInfo.push_back(ScoreInfo("Noname", 0));	/*push the scoreInfo noname,0*/
		return true;
	}
	else
	{
		/*push score info into the scoreInfo vector*/
		while (!feof(fp))
		{
			char* name = (char*)malloc(sizeof(char) * 20);
			int score;
			fscanf(fp, "%s %d\n", name, &score);
		
			scoreInfo.push_back(ScoreInfo(name, score));
		}
		/*sore score infomation sorting - the number of compair ScoreInfo >32, heap sort, else quick sort. in this case always quick sort*/
		sort(scoreInfo.begin(), scoreInfo.end(), cmpScoreByAscending);
		
		fclose(fp);
	}

	/*initialization value*/
	userScore = -1;
	scoreInputFlag = false;
	userInputFlag = false;
	detachTextFlag = false;
	viewScoreFlag = false;

	scheduleUpdate();
	return true;
}

void UserScoreLayer::update(float delta)
{
	Vec2 visibleSize = Director::getInstance()->getVisibleSize();
	
	/*view current scoreboard*/
	if (viewScoreFlag == false)
	{
		viewScoreBoard();
		viewScoreFlag = true;
	}

	/*if user make top 10 record, make textfield to input the user name*/
	if (userInputFlag == false && (userScore > scoreInfo.rbegin()->score || scoreInfo.size()<10) && userScore != -1)
	{
		userInput = TextField::create("input yout name", "fonts/godoRounded.ttf", 32);
		userInput->setMaxLength(3);
		userInput->setMaxLengthEnabled(true);
		userInput->setPlaceHolderColor(ccc4(255, 255, 255, 255));
		userInput->setPosition(Vec2(visibleSize.x / 2, visibleSize.y  - 140 - userInput->getContentSize().height));
		
		Director::getInstance()->getRunningScene()->addChild(userInput, 20, "InputField");
		userInputFlag = true;
	}

	/*if user determine the name, remove textfield*/
	if (userInputFlag == true  && detachTextFlag == false)
	{
		if(userInput->getDetachWithIME() == true)
		{		
			strcpy(inputName, userInput->getString().c_str());
			if (strcmp(inputName,"") == 0 || strcmp(inputName, " ")==0 || strcmp(inputName, "  ")==0 || strcmp(inputName, "   ")==0)
			{
				inputName = "NONAME";
			}
			userInput->setDetachWithIME(false);
			Director::getInstance()->getRunningScene()->removeChildByName("InputField");
			detachTextFlag = true;
		}
	}

	/*if user wirte name record new scoreboard*/
	if (scoreInputFlag == false && userScore >= 0 && detachTextFlag == true)
	{
		writeNewScore(userScore);
		scoreInputFlag = true;
		viewScoreFlag = false;
	}
}

/*new score input and sort by score ascending*/
void UserScoreLayer::writeNewScore(int newScore)
{
	Vec2 visibleSize = Director::getInstance()->getVisibleSize();

	if (scoreInfo.rbegin()->score < newScore || scoreInfo.size()<10)
	{
		scoreInfo.push_back(ScoreInfo(inputName, newScore));
		sort(scoreInfo.begin(), scoreInfo.end(), cmpScoreByAscending);
		writeTopTen();
	}
	else return;
}

/*record top 10 user in scoreboard.txt*/
void UserScoreLayer::writeTopTen()
{
	FILE* fp = fopen("scoreboard.txt", "w");
	if (!fp)
	{
		log("can not create file\n");
		return;
	}
	else
	{
		int i = 0;
		vector<ScoreInfo>::iterator scoreIter;
		if (!scoreInfo.empty())
		{
			for (scoreIter = scoreInfo.begin(); scoreIter != scoreInfo.end(); ++scoreIter)
			{
				char* name = (char*)malloc(sizeof(char) * 20);
				name = scoreIter->name;
				int score = scoreIter->score;
				
				fprintf(fp, "%s %d\n", scoreIter->name, scoreIter->score);
				i++;
				if (i >= 10)
					break;
			}
		}
		fclose(fp);
	}
}

/*view scoreboard*/
void UserScoreLayer::viewScoreBoard()
{
	/*remove all score*/
	this->removeAllChildren();

	Vec2 visibleSize = Director::getInstance()->getVisibleSize();
	int i = 1;
	vector<ScoreInfo>::iterator scoreIter;
	for (scoreIter = scoreInfo.begin(); scoreIter != scoreInfo.end(); ++scoreIter)
	{
		char* numChar = (char*)malloc(sizeof(char) * 100);
		char* name = (char*)malloc(sizeof(char) * 100);
		char* scoreChar = (char*)malloc(sizeof(char) * 100);

		itoa(i, numChar, 10);
		name = scoreIter->name;
		itoa(scoreIter->score, scoreChar, 10);

		Label* tempNum = Label::createWithTTF(numChar, "fonts/godoRounded.ttf", 45);
		Label* tempName = Label::createWithTTF(name, "fonts/godoRounded.ttf", 45);
		Label* tempScore = Label::createWithTTF(scoreChar, "fonts/godoRounded.ttf", 45);
		
		tempNum->setAnchorPoint(Vec2(0, 0));
		tempName->setAnchorPoint(Vec2(0, 0));
		tempScore->setAnchorPoint(Vec2(0, 0));

		tempNum->setPosition(Vec2(visibleSize.x / 8, visibleSize.y - 190 - (tempNum->getContentSize().height + 5)*i));
		tempName->setPosition(Vec2(visibleSize.x / 3, visibleSize.y - 190 - (tempNum->getContentSize().height + 5)*i));
		tempScore->setPosition(Vec2(visibleSize.x * 3 / 5, visibleSize.y - 190 - (tempNum->getContentSize().height + 5)*i));
		
		this->addChild(tempNum);
		this->addChild(tempName);
		this->addChild(tempScore);
		
		i++;
		if (i > 10)
			break;
		
	}
}

/*compair using user's score and sort ascending*/
bool cmpScoreByAscending(const ScoreInfo &a, const ScoreInfo &b)
{
	return a.score > b.score;
}
