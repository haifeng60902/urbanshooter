#ifndef _DISPLAYGEOMETRY_H
#define _DISPLAYGEOMETRY_H

#include <osg/Geode>

/** Create the geomtry as background of the Text 
 *	The method will be called only once for all text instances, the geode will be shared
 */
class DisplayGeometry {
	public:

		/** Implement this method to create your own background geometry */
		virtual osg::Geode * createBackground();

};

#endif
