#include <graphic/StateHud.h>

#include <game/Weapon.h>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LineWidth>


StateHud::StateHud()
{

	_scoreI = new int();
	_chronoI = new int();
	_bulletI = new int();

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


	//add the draw callback for multi-htread rendering issue
	_totalBullet->setDrawCallback(new StateHudDrawCallback(_totalBullet, _score, _chrono, _bulletI, _scoreI, _chronoI));
}


void StateHud::setBulletCountInLoader( int bullet )
{
	_numBulletPerLoader = bullet;
	createLoader();

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
	_totalBullet->setPosition(osg::Vec3(maxX-width+margin,maxY-margin*9,-0.5)); //4th point
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



	//create the chrono text

	_chrono = new osgText::Text();
	_chrono->setPosition(osg::Vec3(maxX-width-height+margin,maxY-margin*9, -0.5)); //4th point
	_chrono->setAutoRotateToScreen(false);
	_chrono->setCharacterSizeMode(osgText::TextBase::SCREEN_COORDS);
	_chrono->setCharacterSize(100);
	_chrono->setText("Remaining Time: 920");
	_chrono->setColor(osg::Vec4(textcolor, 1.0));


	osg::Geometry* geomchrono = new osg::Geometry;
	{
		osg::Vec3Array* vertices = new osg::Vec3Array();
		
		//horizontal square
		vertices->push_back(osg::Vec3(maxX-width-height+margin,maxY-margin*5,-0.5));
		vertices->push_back(osg::Vec3(maxX-width-height+margin*30,maxY-margin*5,-0.5));
		vertices->push_back(osg::Vec3(maxX-width-height+margin*30,maxY-margin*10,-0.5));
		vertices->push_back(osg::Vec3(maxX-width-height+margin,maxY-margin*10,-0.5));

		geomchrono->setVertexArray(vertices);

		osg::Vec3Array* normals = new osg::Vec3Array;
		normals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
		geomchrono->setNormalArray(normals);
		geomchrono->setNormalBinding(osg::Geometry::BIND_OVERALL);

		osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back(osg::Vec4(linecolor, 1.0));
		geomchrono->setColorArray(colors);
		geomchrono->setColorBinding(osg::Geometry::BIND_OVERALL);

		geomchrono->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP,0,vertices->size()));
		//set width
		osg::LineWidth * ln = new osg::LineWidth;
		ln->setWidth(lineWidth);
		geomchrono->getOrCreateStateSet()->setAttributeAndModes(ln, osg::StateAttribute::ON);
	}



	_score = new osgText::Text();
	_score->setPosition(osg::Vec3(maxX-width-height+margin*35,maxY-margin*9,-0.5)); //4th point
	_score->setAutoRotateToScreen(false);
	_score->setCharacterSizeMode(osgText::TextBase::SCREEN_COORDS);
	_score->setCharacterSize(100);
	_score->setText("Score: 1535454");
	_score->setColor(osg::Vec4(textcolor, 1.0));

	osg::Geometry* geomscore = new osg::Geometry;
	{
		osg::Vec3Array* vertices = new osg::Vec3Array();
		
		//horizontal square
		vertices->push_back(osg::Vec3(maxX-width-height+margin*35,maxY-margin*5,-0.5));
		vertices->push_back(osg::Vec3(maxX-width-height+margin*55,maxY-margin*5,-0.5));
		vertices->push_back(osg::Vec3(maxX-width-height+margin*55,maxY-margin*10,-0.5));
		vertices->push_back(osg::Vec3(maxX-width-height+margin*35,maxY-margin*10,-0.5));

		geomscore->setVertexArray(vertices);

		osg::Vec3Array* normals = new osg::Vec3Array;
		normals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
		geomscore->setNormalArray(normals);
		geomscore->setNormalBinding(osg::Geometry::BIND_OVERALL);

		osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back(osg::Vec4(linecolor, 1.0));
		geomscore->setColorArray(colors);
		geomscore->setColorBinding(osg::Geometry::BIND_OVERALL);

		geomscore->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP,0,vertices->size()));
		//set width
		osg::LineWidth * ln = new osg::LineWidth;
		ln->setWidth(lineWidth);
		geomscore->getOrCreateStateSet()->setAttributeAndModes(ln, osg::StateAttribute::ON);
	}


	//loader

	osg::Geometry* geomloader = new osg::Geometry;
	{
		osg::Vec3Array* vertices = new osg::Vec3Array();
		
		//horizontal square
		vertices->push_back(osg::Vec3(maxX-width+margin*3,maxY-margin*15,-0.5));
		vertices->push_back(osg::Vec3(maxX-margin*3,maxY-margin*15,-0.5));
		vertices->push_back(osg::Vec3(maxX-margin*3,maxY-height+margin*10,-0.5));
		vertices->push_back(osg::Vec3(maxX-width+margin*3,maxY-height+margin*10,-0.5));

		geomloader->setVertexArray(vertices);

		osg::Vec3Array* normals = new osg::Vec3Array;
		normals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
		geomloader->setNormalArray(normals);
		geomloader->setNormalBinding(osg::Geometry::BIND_OVERALL);

		osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back(osg::Vec4(linecolor, 1.0));
		geomloader->setColorArray(colors);
		geomloader->setColorBinding(osg::Geometry::BIND_OVERALL);

		geomloader->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP,0,vertices->size()));
		//set width
		osg::LineWidth * ln = new osg::LineWidth;
		ln->setWidth(lineWidth);
		geomloader->getOrCreateStateSet()->setAttributeAndModes(ln, osg::StateAttribute::ON);


		//copy vertices in BB
		_loaderBB.set(vertices->at(3), vertices->at(1));
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
	geode->addDrawable(geomchrono);
	geode->addDrawable(geomscore);
	geode->addDrawable(geomloader);
	geode->addDrawable(_totalBullet);
	geode->addDrawable(_chrono);
	geode->addDrawable(_score);

	//attach to the camera
	addChild(geode);

}



void StateHud::createLoader()
{
	_loaderSwitch = new osg::Switch;

	osg::Vec3d linecolor(1.0,1.0,1.0);

	//attach to the camera
	addChild(_loaderSwitch);

	osg::Vec2 size(_loaderBB.xMax() - _loaderBB.xMin(), _loaderBB.yMax() - _loaderBB.yMin());
	osg::Vec2 oneSize(size.x(), size.y() / _numBulletPerLoader);
	int margin = 10;

	//up to down
	for(int i = 0 ; i < _numBulletPerLoader ; ++i)
	{

		osg::Geode* geode = new osg::Geode;
		osg::Geometry* geomBullet = new osg::Geometry;
	
		osg::Vec3Array* vertices = new osg::Vec3Array();
		
		//horizontal square
		vertices->push_back(osg::Vec3(_loaderBB.xMin()+margin,_loaderBB.yMax()-margin-oneSize.y()*i,-0.5));
		vertices->push_back(osg::Vec3(_loaderBB.xMax()-margin,_loaderBB.yMax()-margin-oneSize.y()*i,-0.5));
		vertices->push_back(osg::Vec3(_loaderBB.xMax()-margin,_loaderBB.yMax()+margin-oneSize.y()-oneSize.y()*i,-0.5));
		vertices->push_back(osg::Vec3(_loaderBB.xMin()+margin,_loaderBB.yMax()+margin-oneSize.y()-oneSize.y()*i,-0.5));

		geomBullet->setVertexArray(vertices);

		osg::Vec3Array* normals = new osg::Vec3Array;
		normals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
		geomBullet->setNormalArray(normals);
		geomBullet->setNormalBinding(osg::Geometry::BIND_OVERALL);

		osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back(osg::Vec4(linecolor, 1.0));
		geomBullet->setColorArray(colors);
		geomBullet->setColorBinding(osg::Geometry::BIND_OVERALL);

		geomBullet->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));

		geode->addDrawable(geomBullet);

		_loaderSwitch->addChild(geode);
	}
}


void StateHud::setCurrentBulletCountInLoader( int bullet )
{
	if(!_loaderSwitch.valid())
		return;

	for(int i = _numBulletPerLoader-1 ; i >= 0 ; --i)
	{
		if(i > _numBulletPerLoader-bullet-1)
			_loaderSwitch->setValue(i, true);
		else
			_loaderSwitch->setValue(i, false);
	}
}
