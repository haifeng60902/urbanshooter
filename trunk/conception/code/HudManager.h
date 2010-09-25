#ifndef _HUDMANAGER_H
#define _HUDMANAGER_H


#include "Mode.h"
#include <string>
using namespace std;
#include <vector>
using namespace std;

class HudText;
class DisplaySetting;

//Definir le comportement : montant ou descendant ? on push en haut de la liste ou en bas ? ou les deux ???
class HudManager {
	private:
    static HudManager * _instance;

    HudManager(Mode mode = INSERT_AT_TOP);


	protected:
    ~HudManager();


	public:
    static void pushText(const string & text);

     addText(const string & text);


	private:
    vector<HudText *> _hudTexts;

    DisplaySetting * _displaySettings;


	public:
    inline const DisplaySetting * get__displaySettings() const;

    void set__displaySettings(DisplaySetting * value);


	private:
    Mode _mode;

};
inline const DisplaySetting * HudManager::get__displaySettings() const {
  return _displaySettings;
}

#endif
