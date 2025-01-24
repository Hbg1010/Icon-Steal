#include <Geode/Geode.hpp>
using namespace geode::prelude;

class CopyPlusPopup : public Popup<GJUserScore* const&> {
public:
    static CopyPlusPopup* create(GJUserScore* const& userDat);
protected:
    bool setup(GJUserScore* const& userDat);
    void onSelect(CCObject* sender);
    void setIcons(CCObject* sender);
    CCMenuItemSpriteExtra* createFormatted(const char* x);
    CCMenuItemSpriteExtra* createTextButton(const char *buttonName);

    void createInfoPopup(CCObject* sender);
};