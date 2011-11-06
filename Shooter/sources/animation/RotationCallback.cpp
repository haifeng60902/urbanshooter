#include <animation/RotationCallback.h>

#include <osg/PositionAttitudeTransform>

#include <animation/CallbackManager.h>

RotationCallback::RotationCallback(osg::Vec3d axis, double angle, double duration) :
	_axis ( axis ),
	_angle ( angle ),
	_duration ( duration ),
	_first_traverse ( false)
{
}


RotationCallback::~RotationCallback()
{
}

void RotationCallback::operator ()(osg::Node *node, osg::NodeVisitor *nv)
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
		_original_rotation = pat->getAttitude();
	}
	else
	{

		//actual duration from begin
		double duration = osg::Timer::instance()->delta_s(_start_tick , actual_tick);

		if(duration < _duration)
		{

			//compute the rotation at runtime and set it
			osg::Quat target(_angle, _axis);
			osg::Quat rot;
			rot.slerp(duration / _duration, _original_rotation, _original_rotation*target);
			pat->setAttitude(rot);
		}
		else
		{
			//if finished, remove itself

			pat->setAttitude(_original_rotation * osg::Quat(_angle, _axis));

			//continue traverse
			traverse(node,nv);
		
			//auto remove itself
			CallbackManager::removeNodeCallback(node, "RotationCallback", true);
			
			return;
		}

	}

	traverse( node, nv);
}