#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
using namespace std;

bool stoppedSpades=false;
bool stoppedHearts=false;
bool stoppedClubs=false;
bool stoppedDiamonds=false;

bool containsKingSpades=false;
bool containsKingHearts=false;
bool containsKingClubs=false;
bool containsKingDiamonds=false;

int countSpades=0;
int countHearts=0;
int countClubs=0;
int countDiamonds=0;
int countAces=0;
int countKings=0;
int countQueens=0;
int countJacks=0;

typedef map<string, int> SuitMap;
typedef map<string, int>::iterator MapIter;

void stopSuit(char suit)
{
	if(suit == 'S') stoppedSpades=true;
	else if(suit == 'H') stoppedHearts=true;
	else if(suit == 'C') stoppedClubs=true;
	else if(suit == 'D') stoppedDiamonds=true;
}

int getCountForSuit(char suit)
{
	if(suit=='S') return countSpades;
	else if(suit=='H') return countHearts;
	else if(suit=='C') return countClubs;
	else if(suit=='D') return countDiamonds;
}

string getHighestSuit()
{
	string highestSuit="S";
	int max=countSpades;

	SuitMap suitCounts;
	suitCounts["S"]=countSpades;
	suitCounts["H"]=countHearts;
	suitCounts["C"]=countClubs;
	suitCounts["D"]=countDiamonds;

	for(MapIter it = suitCounts.begin(); it != suitCounts.end(); ++it)
	{
		if(it->second >= max)
		{
			max = it->second;
			highestSuit = it->first;
		}
	}

	return highestSuit;
}

void decideBid(vector<string> hand)
{
	string bidOutput = "";
	int score = 0;
	int scoreNoTrump = 0;
	string card;

	for(vector<string>::iterator vIt = hand.begin(); vIt != hand.end(); ++vIt) //count suits
	{
		card = *vIt;
		if(card[1] == 'S')
			countSpades++;
		else if(card[1] == 'H')
			countHearts++;
		else if(card[1] == 'C')
			countClubs++;
		else if(card[1] == 'D')
			countDiamonds++;
	}
	for(vector<string>::iterator vIt2 = hand.begin(); vIt2 != hand.end(); ++vIt2) //count cards
	{
		card = *vIt2;
		if(card[0] == 'A')
		{
			score += 4;
			stopSuit(card[1]); //because Ace
		}
		else if(card[0] == 'K')
		{
			score += 3;
			countKings++;
			if(getCountForSuit(card[1])<=1) //only card
			{
				score--;
			}
			if(getCountForSuit(card[1])>=2) //king and at least one other
			{
				stopSuit(card[1]);
			}
		}
		else if(card[0] == 'Q')
		{
			score += 2;
			countQueens++;
			if(getCountForSuit(card[1])<=2)
				score--;
			if(getCountForSuit(card[1])>=3)
				stopSuit(card[1]);
		}
		else if(card[0] == 'J')
		{
			score += 1;
			countJacks++;
			if(getCountForSuit(card[1])<=3)
				score--;
		}
	}

	scoreNoTrump = score;

	if(countSpades==2) score++;
	if(countHearts==2) score++;
	if(countClubs==2) score++;
	if(countDiamonds==2) score++;

	if(countSpades==0 || countSpades==1) score+=2;
	if(countHearts==0 || countHearts==1) score+=2;
	if(countClubs==0 || countClubs==1) score+=2;
	if(countDiamonds==0 || countDiamonds==1) score+=2;

	if(score<14)
		bidOutput+="PASS";
	else// if(score>=14)
	{
		bidOutput+="BID ";
		if(scoreNoTrump>=16 && stoppedSpades && stoppedHearts && stoppedClubs && stoppedDiamonds)
			bidOutput+="NO-TRUMP";
		else
			bidOutput+=getHighestSuit();
	}
	cout << bidOutput << endl;
}


int main()
{
	string input="";
	vector<string> cards;
	string c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13;

	while(cin.peek()!=-1)
	{
		stoppedSpades=stoppedHearts=stoppedClubs=stoppedDiamonds=false;

		containsKingSpades=containsKingHearts=containsKingClubs=containsKingDiamonds=false;

		countSpades=
		countHearts=
		countClubs=
		countDiamonds=
		countAces=
		countKings=
		countQueens=
		countJacks=0;

		cin >> c1 >> c2 >> c3 >> c4 >> c5 >> c6 >> c7 >> c8 >> c9 >> c10 >> c11 >> c12 >> c13;
		cards.clear();
		cards.push_back(c1);
		cards.push_back(c2);
		cards.push_back(c3);
		cards.push_back(c4);
		cards.push_back(c5);
		cards.push_back(c6);
		cards.push_back(c7);
		cards.push_back(c8);
		cards.push_back(c9);
		cards.push_back(c10);
		cards.push_back(c11);
		cards.push_back(c12);
		cards.push_back(c13);
		decideBid(cards);
		// cout << (stoppedSpades ? "spades stopped" : "nope") << endl;
		cin.ignore(1,'\n');
	}
	return 0;
}