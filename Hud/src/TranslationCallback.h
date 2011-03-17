#ifndef _TRANSLATION_CALLBACK_H_
#define _TRANSLATION_CALLBACK_H_


#include <osg/NodeCallback>
#include <osg/Timer>
#include <osg/Vec3d>

#include <utility/Macros.h>

/** Callback that makes a osg::PositionAttitudeTransform move from its position to a new position
 *	during a fixed duration
 */
class TranslationCallback : public osg::NodeCallback
{
public:

	METADATA(TranslationCallback);

	/** Constructor
	 *	@brief This Callback Have to be set by user, but it removes it itself from the node callback list
	 *	@param[in] goal position to get at the end of the duration
	 *	@param[in] duration of the translation
	 */
	TranslationCallback(osg::Vec3d goal, double duration);

	void operator()(osg::Node* node, osg::NodeVisitor* nv);


protected:
	~TranslationCallback();

private:

	osg::Timer_t _start_tick;
	bool _first_traverse;
	
	/** position at the begin of the translation */
	osg::Vec3d _origin_position;

	/** position to get at the end */
	osg::Vec3d _goal;

	/** duration of the translation */
	double _duration;

};


#endif //_TRANSLATION_CALLBACK_H_
