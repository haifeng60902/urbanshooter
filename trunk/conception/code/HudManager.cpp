
#include "HudManager.h"
#include "DisplaySetting.h"

HudManager * HudManager::_instance;

HudManager::HudManager() {
}

HudManager::~HudManager() {
}

void HudManager::pushText(const string & text)
{
  getInstance()->addText(text);
}

 HudManager::addText(const string & text) {
}

void HudManager::set__displaySettings(DisplaySetting * value) {
  _displaySettings = value;
}

