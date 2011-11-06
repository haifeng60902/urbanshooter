#ifndef _SCORE_H_
#define _SCORE_H_

#include <osg/timer>

//class the manage the score
class Score
{
public:
	//start with 10s
	Score() : _total( 0 ) , _total_time(5)
	{
		_go = false;
	}


	~Score(){}

	int get(){ return _total;}

	//loose 50
	void addWrongShoot(){ _total -= 50; }

	//loose 5
	void addVoidShoot(){ _total -= 5; }

	//add 25 and add 1second
	void addTargetShoot(){ _total += 25; _total_time += 1; }

	int getRemainingtTime()
	{
		if(_go)
		{
			int remain = _total_time - osg::Timer::instance()->delta_s(_startTick, osg::Timer::instance()->tick());
			if(remain <=0)
				remain = 0; //end of the game !
			return remain;
		}
		else
			return _total_time;
	}

	void go()
	{
		if(!_go)
		{
			_go = true;
			_startTick = osg::Timer::instance()->tick();
		}
	}


private:
	int _total;

	int _total_time;
	osg::Timer_t _startTick;
	bool _go;
};

#endif //_SCORE_H_
