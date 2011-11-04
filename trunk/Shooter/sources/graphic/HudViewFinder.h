#ifndef _HUD_VIEW_FINDER_H_
#define _HUD_VIEW_FINDER_H_

#include <osg/Camera>

//View finder implementation
class HudViewFinder : public osg::Camera
{
public:
	HudViewFinder(double R, double G, double B, double width);
	~HudViewFinder();

private:

	void createGeometry();

	osg::Vec3 _color;
	double _width;
};

#endif //_HUD_VIEW_FINDER_H_
