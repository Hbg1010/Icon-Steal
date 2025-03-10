#pragma once

#include <Geode/Geode.hpp>
#include <string.h>
#include "CopyUtils.hpp"
using namespace geode::prelude;

class CopyPlusPopup final : public Popup<GJUserScore* const&> {
public:
    static CopyPlusPopup* create(GJUserScore* const& userDat);
    // static int getExplosionID(std::string ID);
protected:
    ~CopyPlusPopup();
    bool setup(GJUserScore* const& userDat);
    CCMenuItemSpriteExtra* createFormatted(const char* x);
    CCMenuItemSpriteExtra* createTextButton(const char *buttonName);
    void lockObject(int index);
    bool isLocked(int btnID);
    //button actions 
    void onSelect(CCObject* sender);
    void setIcons(CCObject* sender);
    void createInfoPopup(CCObject* sender);
    void resetButtons(CCObject* sender);
};