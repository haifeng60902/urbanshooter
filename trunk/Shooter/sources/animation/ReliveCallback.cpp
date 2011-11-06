#include <animation/ReliveCallback.h>

#include <time.h>

#include <osg/PositionAttitudeTransform>
#include <animation/CallbackManager.h>
#include <animation/RotationCallback.h>

ReliveCallback::ReliveCallback() :
	_first_traverse ( false),
	_relived( false )
{
	//generation the random duration to stay dead
	  srand ( time(NULL) );

	_dead_duration = rand() % 8 + 2; //2 to 8 second (2 must > 0.3 (rotation time to die) )

}

ReliveCallback::~ReliveCallback()
{
}

void  ReliveCallback::operator ()(osg::Node *node, osg::NodeVisitor *nv)
{

	//if it is not a PAT, do nothing
	osg::PositionAttitudeTransform * pat = dynamic_cast< osg::PositionAttitudeTransform* > (node);
	if(!pat)
		traverse(node, nv);


	osg::Timer_t actual_tick = osg::Timer::instance()->tick();

	//first traverse : init start_tick
	if(!_first_traverse)
	{
		_start_tick = actual_tick;
		_first_traverse = true;
	}
	else
	{

		//actual duration from begin
		double duration = osg::Timer::instance()->delta_s(_start_tick , actual_tick);

		if(duration >= _dead_duration)
		{
			if(!_relived)
			{
				_relived = true;
				//relive !
				CallbackManager::addNodeCallback(pat, new RotationCallback(osg::Y_AXIS, -osg::PI_2, 0.15));

				//continue traverse
				traverse(node,nv);
			
				return;
			}
			else
			{
				//now relive is done

				//auto remove itself
				CallbackManager::removeNodeCallback(node, "ReliveCallback", true);

			}
		}
		//else just wait

	}

	traverse( node, nv);
}