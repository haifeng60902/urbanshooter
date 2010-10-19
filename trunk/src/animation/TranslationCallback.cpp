#include <TranslationCallback.h>

#include <osg/PositionAttitudeTransform>

#include <Hud/CallbackManager.h>

TranslationCallback::TranslationCallback(osg::Vec3d goal, double duration) :
	_goal ( goal ),
	_duration ( duration ),
	_first_traverse ( false)
{
}


TranslationCallback::~TranslationCallback()
{
}

void TranslationCallback::operator ()(osg::Node *node, osg::NodeVisitor *nv)
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

		//memorize the actual position
		_origin_position = pat->getPosition();
	}
	else
	{

		//actual duration from begin
		double duration = osg::Timer::instance()->delta_s(_start_tick , actual_tick);

		if(duration < _duration)
		{

			//compute the position at runtime and set it
			osg::Vec3d route = _goal - _origin_position;

			//compute and set the position
			osg::Vec3d actual_pos = route * (duration / _duration);
			pat->setPosition(actual_pos);
		}
		else
		{
			//if finished, remove itself

			pat->setPosition(_goal);

			//continue traverse
			traverse(node,nv);
		
			//auto remove itself
			CallbackManager::removeNodeCallback(node, "TranslationCallback", true);
			
			return;
		}

	}

	traverse( node, nv);
}