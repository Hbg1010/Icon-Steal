#include <Geode/Geode.hpp>
using namespace geode::prelude;

class CopyPlusPopup : public Popup<GJUserScore* const&> {
public:
    static CopyPlusPopup* create(GJUserScore* const& userDat);
    
protected:
    bool setup(GJUserScore* const& userDat);
    CCMenuItemSpriteExtra* createFormatted(const char* x);
    CCMenuItemSpriteExtra* createTextButton(const char *buttonName);

    //button actions 
    void onSelect(CCObject* sender);
    void setIcons(CCObject* sender);
    void createInfoPopup(CCObject* sender);
};