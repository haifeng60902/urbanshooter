#ifndef _HUDMANAGER_H
#define _HUDMANAGER_H


#include <string>
using namespace std;

class DisplaySetting;

class HudManager {
  private:
    static HudManager * _instance;

    HudManager();


  protected:
    ~HudManager();


  public:
    static void pushText(const string & text);

     addText(const string & text);


  private:
    DisplaySetting * _displaySettings;


  public:
    inline const DisplaySetting * get__displaySettings() const;

    void set__displaySettings(DisplaySetting * value);

};
inline const DisplaySetting * HudManager::get__displaySettings() const {
  return _displaySettings;
}

#endif
