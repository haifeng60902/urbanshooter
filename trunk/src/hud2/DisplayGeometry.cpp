#include <hud2/DisplayGeometry.h>

#include <osg/Geometry>
#include <osg/Geode>


DisplayGeometry::DisplayGeometry(float w, float h) : 
_width( w ),
_height( h )
{
}

osg::Geode * DisplayGeometry::createBackground() {
  
	osg::Geode * geode = new osg::Geode();

	float depth = -0.1f;
	osg::Vec4 bgcolor(0.8f,0.8f,1.0f,1.0);


	//build a simple surface : from 5,5 to width,height

	osg::Geometry* geom = new osg::Geometry;
	
	osg::Vec3Array* vertices = new osg::Vec3Array();

	vertices->push_back(osg::Vec3(5,5,depth));
	vertices->push_back(osg::Vec3(_width+5,5,depth));
	vertices->push_back(osg::Vec3(_width+5,_height+5,depth));
	vertices->push_back(osg::Vec3(5,_height+5,depth));
	geom->setVertexArray(vertices);

	osg::Vec3Array* normals = new osg::Vec3Array;
	normals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
	geom->setNormalArray(normals);
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(bgcolor);
	geom->setColorArray(colors);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));

	osg::StateSet* stateset = geom->getOrCreateStateSet();
	stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
	stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	geode->addDrawable(geom);

	return geode;
}

