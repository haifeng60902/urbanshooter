#include <graphic/HudViewFinder.h>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LineWidth>

HudViewFinder::HudViewFinder(double R, double G, double B, double width) :
	_color( osg::Vec3( R, G, B) ),
	_width( width )
{

	// set the projection matrix
    setProjectionMatrix(osg::Matrix::ortho2D(0,1280,0,1024));
	
    // set the view matrix    
    setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    setViewMatrix(osg::Matrix::identity());

    // only clear the depth buffer
    setClearMask(GL_DEPTH_BUFFER_BIT);

    // draw subgraph after main camera view.
    setRenderOrder(osg::Camera::POST_RENDER);

    // we don't want the camera to grab event focus from the viewers main camera(s).
    setAllowEventFocus(false);


	createGeometry();
}

HudViewFinder::~HudViewFinder()
{
}

void HudViewFinder::createGeometry()
{
	osg::Geode * geode = new osg::Geode;

	int size = 20;
	int space = 5;
	int centerX = 1280/2;
	int centerY = 1024/2;

	//create a cross
	osg::Geometry* geom = new osg::Geometry;
	
	osg::Vec3Array* vertices = new osg::Vec3Array();

	//horizontal
	vertices->push_back(osg::Vec3(centerX+size+space,centerY,0));
	vertices->push_back(osg::Vec3(centerX+space,centerY,0));
	vertices->push_back(osg::Vec3(centerX-space,centerY,0));
	vertices->push_back(osg::Vec3(centerX-size-space,centerY,0));

	vertices->push_back(osg::Vec3(centerX,centerY+size+space,0));
	vertices->push_back(osg::Vec3(centerX,centerY+space,0));
	vertices->push_back(osg::Vec3(centerX,centerY-space,0));
	vertices->push_back(osg::Vec3(centerX,centerY-size-space,0));

	geom->setVertexArray(vertices);

	osg::Vec3Array* normals = new osg::Vec3Array;
	normals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
	geom->setNormalArray(normals);
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(_color, 1.0));
	geom->setColorArray(colors);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(GL_LINES,0,vertices->size()));

	//set width
	osg::LineWidth * ln = new osg::LineWidth;
	ln->setWidth(_width);
	geom->getOrCreateStateSet()->setAttributeAndModes(ln, osg::StateAttribute::ON);
	//disable lightning
	geom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	//disable culling
	geode->setCullingActive(false);

	geode->addDrawable(geom);
	addChild(geode);

	geode->setNodeMask(0x1);
	
}
