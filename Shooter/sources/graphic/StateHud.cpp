#include <graphic/StateHud.h>

#include <game/Weapon.h>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LineWidth>


StateHud::StateHud()
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


	createAmoGeometry();
}

StateHud::~StateHud()
{
}

void StateHud::createAmoGeometry()
{
	osg::Geode * geode = new osg::Geode;

	int maxX = 1280;
	int maxY = 1024;

	//BG settings
	int margin = 10;
	int width = 150;//on 1280
	int height = 600;//on 1024

	osg::Vec3d bgcolor(0.65,0.85,0.85);
	osg::Vec3d linecolor(1.0,1.0,1.0);
	osg::Vec3d textcolor(0.0,0.0,0.0);

	double lineWidth = 2.0;

	//(all z are negative due to culling)

	//create the background
	osg::Geometry* geomBG = new osg::Geometry;
	{
		osg::Vec3Array* vertices = new osg::Vec3Array();
		
		//horizontal square
		vertices->push_back(osg::Vec3(maxX-width-height,maxY,-1.0));
		vertices->push_back(osg::Vec3(maxX-width,maxY,-1.0));
		vertices->push_back(osg::Vec3(maxX-width,maxY-width,-1.0));
		vertices->push_back(osg::Vec3(maxX-width-height,maxY-width,-1.0));

		//vertical square
		vertices->push_back(osg::Vec3(maxX-width,maxY,-1.0));
		vertices->push_back(osg::Vec3(maxX,maxY,-1.0));
		vertices->push_back(osg::Vec3(maxX,maxY-height,-1.0));
		vertices->push_back(osg::Vec3(maxX-width,maxY-height,-1.0));

		geomBG->setVertexArray(vertices);

		osg::Vec3Array* normals = new osg::Vec3Array;
		normals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
		geomBG->setNormalArray(normals);
		geomBG->setNormalBinding(osg::Geometry::BIND_OVERALL);

		osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back(osg::Vec4(bgcolor, 1.0));
		geomBG->setColorArray(colors);
		geomBG->setColorBinding(osg::Geometry::BIND_OVERALL);

		geomBG->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,vertices->size()));
	}


	//create the total amo text zone

	_totalBullet = new osgText::Text();
	_totalBullet->setPosition(osg::Vec3(maxX-width+margin,maxY-margin*10,-0.5)); //4th point
	_totalBullet->setAutoRotateToScreen(false);
	_totalBullet->setCharacterSizeMode(osgText::TextBase::SCREEN_COORDS);
	_totalBullet->setCharacterSize(120);
	_totalBullet->setText("Amo: 15");
	_totalBullet->setColor(osg::Vec4(textcolor, 1.0));


	osg::Geometry* geomText = new osg::Geometry;
	{
		osg::Vec3Array* vertices = new osg::Vec3Array();
		
		//horizontal square
		vertices->push_back(osg::Vec3(maxX-width+margin,maxY-margin*5,-0.5));
		vertices->push_back(osg::Vec3(maxX-margin,maxY-margin*5,-0.5));
		vertices->push_back(osg::Vec3(maxX-margin,maxY-margin*10,-0.5));
		vertices->push_back(osg::Vec3(maxX-width+margin,maxY-margin*10,-0.5));

		geomText->setVertexArray(vertices);

		osg::Vec3Array* normals = new osg::Vec3Array;
		normals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
		geomText->setNormalArray(normals);
		geomText->setNormalBinding(osg::Geometry::BIND_OVERALL);

		osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back(osg::Vec4(linecolor, 1.0));
		geomText->setColorArray(colors);
		geomText->setColorBinding(osg::Geometry::BIND_OVERALL);

		geomText->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP,0,vertices->size()));
		//set width
		osg::LineWidth * ln = new osg::LineWidth;
		ln->setWidth(lineWidth);
		geomText->getOrCreateStateSet()->setAttributeAndModes(ln, osg::StateAttribute::ON);
	}


	//disable culling
	geode->setCullingActive(false);
	//disable picking
	geode->setNodeMask(0x1);
	//disable lightning
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	//add background
	geode->addDrawable(geomBG);
	//add textLines
	geode->addDrawable(geomText);
	geode->addDrawable(_totalBullet);

	//attach to the camera
	addChild(geode);

}