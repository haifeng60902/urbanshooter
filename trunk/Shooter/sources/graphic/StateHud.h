#ifndef _STATE_HUD_H_
#define _STATE_HUD_H_

#include <osg/Camera>
#include <osg/Switch>
#include <osgText/Text>

#include <sstream>

class Weapon;

//class for amo hud and scores
class StateHud : public osg::Camera
{

public:
	StateHud();
	~StateHud();

	void setScore(int score){ *_scoreI = score; }
	void setchrono(int chrono){ *_chronoI = chrono; }
	void setTotalBullet(int bullet){ *_bulletI = bullet; }

	void setCurrentBulletCountInLoader( int bullet );

	void setBulletCountInLoader( int bullet );

	void displayEnd();

	void buildManual();
	void hideManual();

private:

	osg::Geode * _manual;

	void createAmoGeometry();

//	Weapon * _weapon; //use a setter that will rebuild/refresh the 

	osg::ref_ptr<osgText::Text> _totalBullet;
	osg::ref_ptr<osgText::Text> _chrono;
	osg::ref_ptr<osgText::Text> _score;

	int * _scoreI;
	int * _chronoI;
	int * _bulletI;
	


	//private update text callback to avoid crashes
	class StateHudDrawCallback : public virtual osg::Drawable::DrawCallback
	{
	private :
	      
		osg::ref_ptr<osgText::Text> _totalBullet;
		osg::ref_ptr<osgText::Text> _chrono;
		osg::ref_ptr<osgText::Text> _score;

		int * _scoreI;
		int * _chronoI;
		int * _bulletI;
	
	public :
		StateHudDrawCallback(osgText::Text* tbullet, osgText::Text* tscore, osgText::Text* tchrono, int * ibullet, int * iscore, int * ichrono):
		   _totalBullet( tbullet ),
		   _chrono( tchrono ),
		   _score( tscore ),
		   _bulletI( ibullet ),
		   _scoreI( iscore ),
		   _chronoI( ichrono )
	        {
	        }
	
	private :
	        virtual void drawImplementation(osg::RenderInfo& renderInfo,const osg::Drawable* drawable) const
	        {
	            //osg::ref_ptr<osgText::Text> text = (osgText::Text*)drawable;
				_totalBullet->setText( "Amo: " + to_string( *_bulletI ) );
				_chrono->setText( "Remaining Time: " + to_string( *_chronoI ) );
				_score->setText( "Score: " + to_string( *_scoreI ) );
		
				_totalBullet->drawImplementation(renderInfo);
				_chrono->drawImplementation(renderInfo);
				_score->drawImplementation(renderInfo);
	        }

			static std::string to_string( int i)
			{
				 // créer un flux de sortie
				std::ostringstream oss;
				// écrire un nombre dans le flux
				oss << i;
				// récupérer une chaîne de caractères
				std::string result = oss.str();
				return result;
			}
	}; 


	int _numBulletPerLoader;
	//keep a reference to ba able to create the amo square in the good size
	osg::BoundingBox _loaderBB;

	osg::ref_ptr<osg::Switch> _loaderSwitch;

	void createLoader();


	
};

#endif //_STATE_HUD_H_
