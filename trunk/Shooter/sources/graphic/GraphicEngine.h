#ifndef _GRAPHIC_ENGINE_H_
#define _GRAPHIC_ENGINE_H_

#include <manager/Engine.h>

#include <osgViewer/Viewer>

class GraphicEngine : public Engine
{
public:
	GraphicEngine();
	~GraphicEngine();


	void frame();

private:

	osg::ref_ptr<osgViewer::Viewer> _viewer;
};

#endif