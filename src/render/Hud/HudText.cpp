#include <Hud/HudText.h>

#include <osg/Geometry>

HudTest::HudText::HudText(int width, int height) : 
	_width( width),
	_height( height)
{

	//build buildBackground
	buildBackground();

	//build text
	_text = new osgText::Text;

	//set text position and size
	_text->setFont("fonts/arial.ttf");
	_text->setPosition(osg::Vec3d(10. ,_height/2.-2 , 0.));
	_text->setCharacterSize(12);
	_text->setText("empty");
	
	this->addDrawable( _text );

	//no lighting
    getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

}

HudTest::HudText::~HudText()
{}

void HudTest::HudText::setText(const std::string &text)
{
	_text->setText(text);
}

void HudTest::HudText::buildBackground()
{

	float depth = -0.1;
	osg::Vec4 bgcolor(0.8f,0.8,1.0f,0.2f);

	//build a simple surface : from 0,0 to width,height

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

	this->addDrawable(geom);

}