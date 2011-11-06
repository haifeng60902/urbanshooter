#ifndef _SCORE_H_
#define _SCORE_H_

#include <osg/timer>

//class the manage the score
class Score
{
public:
	//start with 10s
	Score() : _total( 0 ) , _total_time(12)
	{
		_startTick = osg::Timer::instance()->tick();
	}


	~Score(){}

	int get(){ return _total;}

	//loose 50
	void addWrongShoot(){ _total -= 50; }

	//loose 1
	void addVoidShoot(){ _total -= 1; }

	//add 25 and add 1second
	void addTargetShoot(){ _total += 25; _total_time += 1; }

	int getRemainingtTime()
	{
		int remain = _total_time - osg::Timer::instance()->delta_s(_startTick, osg::Timer::instance()->tick());
		if(remain <=0)
			remain = 0; //end of the game !
		return remain;
	}

private:
	int _total;

	int _total_time;
	osg::Timer_t _startTick;
};

#endif //_SCORE_H_
