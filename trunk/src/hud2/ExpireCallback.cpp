#include <hud2/ExpireCallback.h>



ExpireCallback::ExpireCallback(HudManager::HudTexts *texts, float visible_time) :
	_hudTexts( texts ),
	_visible_time( visible_time )
{

}


ExpireCallback::~ExpireCallback()
{
	//do not delete the hudText instance, it will be done by the HudManager
}


void ExpireCallback::operator ()(osg::Node *node, osg::NodeVisitor *nv)
{

	update();

	//check all date since there is one that won't expire (so the following also won't  expire)
	traverse(node, nv);
}

void ExpireCallback::update()
{
	//check the list from the begin and stop when a non-expired element has been found

	osg::Timer_t actual_time = osg::Timer::instance()->tick();

	unsigned int nb_to_remove = 0;

	for(HudManager::HudTexts::iterator it = _hudTexts->begin() ; it != _hudTexts->end() ; ++it)
	{
		//if difference between actual and registered is greater than the duration expected
		if(osg::Timer::instance()->delta_s(it->second, actual_time) >= _visible_time)
			nb_to_remove++;
		else
			break; //because they are ordered, no need to continue
	}

	//remove the selected ones
	if(nb_to_remove > 0)
		removeText(nb_to_remove);
}

void ExpireCallback::removeText(unsigned int nb_to_remove)
{

	for(unsigned int i = 0 ; i < nb_to_remove ; ++i)
	{
		HudText * ht = _hudTexts->front().first;

		//set the transparency callback
		//un autre pour ne pas écraser la transparence du fond ?

		//remove from the list
		_hudTexts->pop_front();

	//put on retire list. when all callback are removed from it, remove it from list and graph
	//flag de NORMAL, REMOVING, REMOVED ?
	//sinon je le dégage de la liste normale pour le mettre dans une liste d'attente de suppression

	}

	//3. set the transparency callback on it (0 to 1)
		//careful with the bg transparency

	//4. set the transparency callbcak on the one which will be removed (1 to 0)
		//careful with the bg transparency
	//5. set animation callback on each one

	//all callback will be removed by themselves



}
