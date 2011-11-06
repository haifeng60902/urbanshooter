#ifndef _ROTATION_CALLBACK_H_
#define _ROTATION_CALLBACK_H_


#include <osg/NodeCallback>
#include <osg/Timer>
#include <osg/Quat>

#include <animation/Macros.h>

/** Callback that makes a osg::PositionAttitudeTransform rotate during a fixed duration
 */
class RotationCallback : public osg::NodeCallback
{
public:

	METADATA(RotationCallback);

	RotationCallback(osg::Vec3d axis, double angle, double duration);

	void operator()(osg::Node* node, osg::NodeVisitor* nv);


protected:
	~RotationCallback();

private:

	osg::Timer_t _start_tick;
	bool _first_traverse;
	
	/** rotation axis */
	osg::Vec3d _axis;

	/** rotation angle (in radians) */
	double _angle;

	/** duration of the translation */
	double _duration;

	osg::Quat _original_rotation;

};


#endif //_ROTATION_CALLBACK_H_
