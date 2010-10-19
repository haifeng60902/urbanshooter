#include <animation/ProgressiveTransparencyCallback.h>

#include <osg/Node>
#include <osg/StateSet>
#include <osg/Notify>

#include <render/Effects.h>
#include <animation/CallbackManager.h>

ProgressiveTransparencyCallback::ProgressiveTransparencyCallback(double alphaFrom, double alphaTo, double durationVisible, double durationBlur) :
	_alpha_from ( alphaFrom ),
	_alpha_to ( alphaTo ),
	_duration_visible( durationVisible ),
	_duration_blur( durationBlur ),
	_first_traverse ( false ),
	_material ( NULL )
{
}

ProgressiveTransparencyCallback::~ProgressiveTransparencyCallback()
{
}


void ProgressiveTransparencyCallback::operator ()(osg::Node *node, osg::NodeVisitor *nv)
{
	osg::Timer_t actual_tick = osg::Timer::instance()->tick();


	//first traverse : init start_tick
	if(!_first_traverse)
	{
		_start_tick = actual_tick;
		_first_traverse = true;

	}
	else
	{
		//when duration visible is done : start
		double duration = osg::Timer::instance()->delta_s(_start_tick , actual_tick);

		
		//End of callback duration
		if(duration >= (_duration_visible + _duration_blur))
		{
			
			Effects::setTransparency(node, _alpha_to);

			//continue traverse
			traverse(node,nv);
		
			//auto remove itself
			CallbackManager::removeNodeCallback(node, "ProgressiveTransparencyCallback", true);
			
			return;

		}
		else if(duration >= _duration_visible)
		{
			//start blur
			double transparency = _alpha_from + ( (( duration - _duration_visible) * (_alpha_to - _alpha_from )) / ( _duration_blur ) );

			Effects::setTransparency(node,transparency);
			
			
		}
		//else do nothing : let it be displayed

	}

	  
	traverse(node,nv);
	
}