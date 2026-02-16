#include <Geode/Geode.hpp>
#include <string.h>

using namespace geode::prelude;
#define TOTAL_CUSTOMIZATIONS 14 // used to define how many customization catagories there are

class CopyPlusPopup final : public Popup {
public:
    static CopyPlusPopup* create(GJUserScore* const& userDat);
    // static int getExplosionID(std::string ID);
protected:
    bool activeIcons[TOTAL_CUSTOMIZATIONS];
    bool lockedArray[TOTAL_CUSTOMIZATIONS];

    // TODO: use CCArrayExt when i redo some ui elements
    CCArray* buttons;

    // player Profile stats
    const GJUserScore* m_score;

    ~CopyPlusPopup();
    bool init(GJUserScore* const& userDat);
    CCMenuItemSpriteExtra* createFormatted(const char* x);
    CCMenuItemSpriteExtra* createTextButton(const char *buttonName);
    void lockObject(int index);
    
    //button actions 
    void onSelect(CCObject* sender);
    void setIcons(CCObject* sender);
    void createInfoPopup(CCObject* sender);
    void resetButtons(CCObject* sender);
};