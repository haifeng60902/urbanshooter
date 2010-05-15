#ifndef _PROGRESSIVE_TRANSPARENCY_CALLBACK_H_
#define _PROGRESSIVE_TRANSPARENCY_CALLBACK_H_



#include <osg/NodeCallback>
#include <osg/Timer>
#include <osg/Material>


class ProgressiveTransparencyCallback : public osg::NodeCallback
{
public:

	ProgressiveTransparencyCallback(double durationVisible = 2.0, double duration_blur = 2.0);
	~ProgressiveTransparencyCallback();


	void operator()(osg::Node* node, osg::NodeVisitor* nv);

private:

	osg::Timer_t _start_tick;
	bool _first_traverse;

	double _duration_visible;
	double _duration_blur;

	osg::ref_ptr<osg::Material> _material;
};


#endif //_PROGRESSIVE_TRANSPARENCY_CALLBACK_H_

