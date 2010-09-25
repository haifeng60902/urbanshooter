
#include "HudManager.h"
#include "HudText.h"
#include "DisplaySetting.h"

HudManager * HudManager::_instance;

HudManager::HudManager(Mode mode) {
  // Bouml preserved body begin 0001F402
  // Bouml preserved body end 0001F402
}

HudManager::~HudManager() {
  // Bouml preserved body begin 0001F482
  // Bouml preserved body end 0001F482
}

void HudManager::pushText(const string & text)
{
  // Bouml preserved body begin 0001F502
  getInstance()->addText(text);
  // Bouml preserved body end 0001F502
}

 HudManager::addText(const string & text) {
  // Bouml preserved body begin 0001F582
  // Bouml preserved body end 0001F582
}

void HudManager::set__displaySettings(DisplaySetting * value) {
  _displaySettings = value;
}

