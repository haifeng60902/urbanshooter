#ifndef _EXPIRE_CALLBACK_H_
#define _EXPIRE_CALLBACK_H_

#include <osg/NodeCallback>
#include <utility/Macros.h>
#include <hud2/HudManager.h>

class ExpireCallback : public osg::NodeCallback
{
public:

	METADATA(ExpireCallback);

	/** constructor */
	ExpireCallback(HudManager::HudTexts * texts, float visible_time);

	void operator()(osg::Node* node, osg::NodeVisitor* nv);
	

protected :
	~ExpireCallback();

private:

	//check the expiration and call remove
	void update();

	void removeText(unsigned int nb_to_remove);


	typedef std::deque< HudText * > WaitingList;

	HudManager::HudTexts * _hudTexts;
	float _visible_time;
};

#endif //_EXPIRE_CALLBACK_H_
