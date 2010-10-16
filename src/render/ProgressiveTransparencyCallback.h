#ifndef _PROGRESSIVE_TRANSPARENCY_CALLBACK_H_
#define _PROGRESSIVE_TRANSPARENCY_CALLBACK_H_



#include <osg/NodeCallback>
#include <osg/Timer>
#include <osg/Material>

#include <Hud/Macros.h>

/** This callback implements a simple way to turn a node in transparent */
class ProgressiveTransparencyCallback : public osg::NodeCallback
{
public:


	METADATA(ProgressiveTransparencyCallback);

	/** Constructor
	 *	@brief This Callback Have to be set by user, but it removes it itself from the node callback list
	 *	@param[in] alphaFrom transparency begin level
	 *	@param[in] alphaTo transparency end level
	 *	@param[in] durationVisible delay before starting to make it transparent (in second)
	 *	@param[in] durationBlur duration to make the transparency go from alphaFrom to alphaTo
	 */
	ProgressiveTransparencyCallback(double alphaFrom = 1., double alphaTo = 0., double durationVisible = 2.0, double durationBlur = 2.0);

	void operator()(osg::Node* node, osg::NodeVisitor* nv);

protected :
	/** destructor */
	~ProgressiveTransparencyCallback();


private:

	osg::Timer_t _start_tick;
	bool _first_traverse;

	/** visible time in second */
	double _duration_visible;
	/** blur time in second */
	double _duration_blur;
	/** transparency begin value */
	double _alpha_from;
	/** transparency end value */
	double _alpha_to;

	osg::ref_ptr<osg::Material> _material;
};


#endif //_PROGRESSIVE_TRANSPARENCY_CALLBACK_H_

