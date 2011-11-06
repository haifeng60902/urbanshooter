#ifndef _RELIVE_CALLBACK_H_
#define _RELIVE_CALLBACK_H_

#include <osg/NodeCallback>
#include <osg/Timer>

#include <animation/Macros.h>

//make the target live again !
class ReliveCallback : public osg::NodeCallback
{
public:

	METADATA(ReliveCallback);

	ReliveCallback();

	void operator()(osg::Node* node, osg::NodeVisitor* nv);

protected:
	~ReliveCallback();

private:

	double _dead_duration;

	osg::Timer_t _start_tick;
	bool _first_traverse;
	bool _relived;
};


#endif //_RELIVE_CALLBACK_H_
