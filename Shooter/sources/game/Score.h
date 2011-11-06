#ifndef _SCORE_H_
#define _SCORE_H_

//class the manage the score
class Score
{
public:
	Score() : _total( 0 ) {}
	~Score(){}

	int get(){ return _total;}

	//loose 50
	void addWrongShoot(){ _total -= 50; }

	//loose 1
	void addVoidShoot(){ _total -= 1; }

	//add 25
	void addTargetShoot(){ _total += 25; }

private:
	int _total;
};

#endif //_SCORE_H_
