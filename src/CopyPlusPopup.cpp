#include "CopyPlusPopup.hpp"
#include <numeric> 

// Button related variables
bool activeIcons[15] = { true };
bool lockedArray[15] = { false };

CCArray* buttons;

// player Profile stats
GJUserScore* m_score;

// colors for updating stuff
const ccColor3B greyScale = {.r = 90, .g = 90, .b = 90};
const ccColor3B color = {.r = 255, .g = 255, .b = 255};

CopyPlusPopup* CopyPlusPopup::create(GJUserScore* const& userDat) {
    auto temp = new CopyPlusPopup();

    // trys to make node
    if (temp->initAnchored(360, 180, userDat)) {
        temp->autorelease();
        return temp;

    } else {
        CC_SAFE_DELETE(temp);

        return nullptr;
    }
}

//Button creators:
// buttons with images
CCMenuItemSpriteExtra* CopyPlusPopup::createFormatted(const char* x) {
    auto spr = CCSprite::createWithSpriteFrameName(x);
    std::string tagID = std::string(x).substr(3,sizeof(x));
    tagID = std::string(tagID).substr(0,std::string(tagID).find('B'));

    // im too lazy to use a lib :(
    auto returnBtn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(CopyPlusPopup::onSelect));
    returnBtn->setID(tagID);

    return returnBtn;
}

// text buttons
CCMenuItemSpriteExtra* CopyPlusPopup::createTextButton(const char* buttonName) {
    auto spr = ButtonSprite::create(buttonName, "bigFont.fnt", "GJ_button_02.png");
    spr->setScale(0.5f);
    auto x = CCMenuItemSpriteExtra::create(spr, this, menu_selector(CopyPlusPopup::onSelect));
    x->setID(buttonName);
    return x;
}

CopyPlusPopup::~CopyPlusPopup() {
    CC_SAFE_DELETE(buttons);
}

bool CopyPlusPopup::setup(GJUserScore* const& userDat) {
    m_score = userDat;
    buttons = CCArray::createWithCapacity(20);
    this->setTitle("Copy+");
    // top layer of colors + glow
    buttons->addObject(createTextButton("Col1"));
    buttons->addObject(createTextButton("Col2"));
    buttons->addObject(createTextButton("Col3"));
    buttons->addObject(createTextButton("Glow"));

    // Bottom Layer: icons
    buttons->addObject(createFormatted("gj_iconBtn_on_001.png"));
    buttons->addObject(createFormatted("gj_shipBtn_on_001.png"));
    buttons->addObject(createFormatted("gj_jetpackBtn_on_001.png"));
    buttons->addObject(createFormatted("gj_ballBtn_on_001.png"));
    buttons->addObject(createFormatted("gj_birdBtn_on_001.png"));
    buttons->addObject(createFormatted("gj_dartBtn_on_001.png"));
    buttons->addObject(createFormatted("gj_robotBtn_on_001.png"));
    buttons->addObject(createFormatted("gj_spiderBtn_on_001.png"));
    buttons->addObject(createFormatted("gj_swingBtn_on_001.png"));
    buttons->addObject(createFormatted("gj_explosionBtn_on_001.png"));

    // this wont be added if it's not added
    if (m_score->m_special) {buttons->addObject(createFormatted("gj_streakBtn_on_001.png"));
    } else {
        activeIcons[13] = false;
        lockedArray[13] = true;
    }



    // top menu for colors and glow
    CCMenu* extrasMenu = CCMenu::create();
    extrasMenu->setPosition({m_mainLayer->getContentWidth()/2, m_mainLayer->getContentHeight()*3/4.f});
    extrasMenu->setContentWidth(300.f);
    extrasMenu->setLayout(
        RowLayout::create()
        ->setAxisAlignment(AxisAlignment::Even)
    );

    // icon menus
    CCMenu* iconMenu = CCMenu::create();
    iconMenu->setPosition({m_mainLayer->getContentWidth()/2, m_mainLayer->getContentHeight()/2.f});
    iconMenu->setContentWidth(300.f);
    iconMenu->setLayout(
        RowLayout::create()
        ->setAxisAlignment(AxisAlignment::Even)
    );

    m_mainLayer->addChild(extrasMenu);
    m_mainLayer->addChild(iconMenu);

    // tags and children are added in these for loop
    if (buttons->count() > 0) {
        for (int i = 0; i < 4; i++) {
            CCNode* x = static_cast<CCNode*>(buttons->objectAtIndex(i));
            x->setTag(i);
            extrasMenu->addChild(x);
            activeIcons[i] = true;
        }

        for (int i = 4; i < buttons->count(); i++) {
            if (CCNode* x = static_cast<CCNode*>(buttons->objectAtIndex(i))) {
                x->setTag(i);
                iconMenu->addChild(x);
                activeIcons[i] = true;
            }
        }
    }

    // this locks icons if settings are enabled
    if (Mod::get()->getSettingValue<bool>("unlocked")) {
        auto gm = GameManager::sharedState();
    
        if (!gm->isColorUnlocked(m_score->m_color1, UnlockType::Col1)) lockObject(0);
        if (!gm->isColorUnlocked(m_score->m_color2, UnlockType::Col2)) lockObject(1);
        if (!gm->isIconUnlocked(2, IconType::Special)) {
            lockObject(2);
            lockObject(3);
        } else if (!gm->isColorUnlocked(m_score->m_color3, UnlockType::Col2)) lockObject(2);
        if (!gm->isIconUnlocked(m_score->m_playerCube, IconType::Cube)) lockObject(4);
        if (!gm->isIconUnlocked(m_score->m_playerShip, IconType::Ship)) lockObject(5);
        if (!gm->isIconUnlocked(m_score->m_playerJetpack, IconType::Jetpack)) lockObject(6);
        if (!gm->isIconUnlocked(m_score->m_playerBall, IconType::Ball)) lockObject(7);
        if (!gm->isIconUnlocked(m_score->m_playerUfo, IconType::Ufo)) lockObject(8);
        if (!gm->isIconUnlocked(m_score->m_playerWave, IconType::Wave)) lockObject(9);
        if (!gm->isIconUnlocked(m_score->m_playerRobot, IconType::Robot)) lockObject(10);
        if (!gm->isIconUnlocked(m_score->m_playerSpider, IconType::Spider)) lockObject(11);
        if (!gm->isIconUnlocked(m_score->m_playerSwing, IconType::Swing)) lockObject(12);
        if (!gm->isIconUnlocked(m_score->m_playerExplosion, IconType::DeathEffect)) lockObject(13);
        if (!lockedArray[13] && !gm->isIconUnlocked(m_score->m_playerStreak, IconType::Special)) lockObject(14);

    }
    extrasMenu->updateLayout();
    iconMenu->updateLayout();

    // set button
    CCMenu* confirmMenu = CCMenu::create();
    confirmMenu->setPosition({m_mainLayer->getContentWidth()/2, m_mainLayer->getScaledContentHeight()/8});
    m_mainLayer->addChild(confirmMenu);
    auto setSpr = ButtonSprite::create("Set");
    CCMenuItemSpriteExtra* setBtn = CCMenuItemSpriteExtra::create(setSpr, this, menu_selector(CopyPlusPopup::setIcons));
    confirmMenu->addChild(setBtn);

    // creates the menu where the info button is placed
    auto infoMenu = CCMenu::create();
    infoMenu->setPosition({m_mainLayer->getContentWidth(), m_mainLayer->getContentHeight()});
    m_mainLayer->addChild(infoMenu);
    infoMenu->setID("info-menu"_spr);

    // creates the info button
    auto infoSpr = cocos2d::CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
    CCMenuItemSpriteExtra* infoButton = CCMenuItemSpriteExtra::create(infoSpr, this, menu_selector(CopyPlusPopup::createInfoPopup));
    infoMenu->addChild(infoButton);
    infoButton->setID("info-btn"_spr);

    // does not work right now 

    // creates the menu where the info button is placed
    auto refreshMenu = CCMenu::create(); 
    refreshMenu->setPosition({0,0});
    m_mainLayer->addChild(refreshMenu);
    refreshMenu->setID("refresh-menu"_spr);

    // creates the refresh button
    auto refreshSpr = cocos2d::CCSprite::createWithSpriteFrameName("GJ_updateBtn_001.png");
    refreshSpr->setScale(.8f);
    CCMenuItemSpriteExtra* resfreshBtn = CCMenuItemSpriteExtra::create(refreshSpr, this, menu_selector(CopyPlusPopup::resetButtons));
    refreshMenu->addChild(resfreshBtn);
    infoButton->setID("refresh-btn"_spr);

    CC_SAFE_RETAIN(buttons);

    return true;
}

// button action whenever an icon related button is clicked
void CopyPlusPopup::onSelect(CCObject* sender) {
    int x = sender->getTag();
    bool enable = !activeIcons[x];
    activeIcons[x] = enable;

    if (CCMenuItemSpriteExtra* btn = typeinfo_cast<CCMenuItemSpriteExtra*>(sender)) {
        if (x > 3) {
            auto stringID = "gj_" + btn->getID() + (13 == btn->getTag() ? "n" : "") + "Btn_" + (enable ? "on" : "off") + "_001.png";
            btn->setSprite(CCSprite::createWithSpriteFrameName(stringID.c_str()));
        } else {
            auto x = ButtonSprite::create(btn->getID().c_str(), "bigFont.fnt", enable ? "GJ_button_02.png" : "GJ_button_04.png");
            x->setScale(0.5f);
            btn->setSprite(x);
        }
    }
}

// sets the icons
void CopyPlusPopup::setIcons(CCObject* sender) {
//"exMark_001.png"

    int copiedIcons = std::accumulate(activeIcons, activeIcons + 15, 0);

    // checks if the popup should close
    if (copiedIcons == 0) {
        Notification::create(
            " Nothing selected!",
            CCSprite::createWithSpriteFrameName("exMark_001.png")
        )->show();
        return;
    }

    // THERE HAS TO BE A BETTER WAY
    auto gm = GameManager::sharedState();
    if(activeIcons[0]) gm->setPlayerColor(m_score->m_color1);
    if(activeIcons[1]) gm->setPlayerColor2(m_score->m_color2);
    if(activeIcons[2]) gm->setPlayerColor3(m_score->m_color3);
    if(activeIcons[3]) gm->setPlayerGlow(m_score->m_glowEnabled);
    if(activeIcons[4]) gm->setPlayerFrame(m_score->m_playerCube);
    if(activeIcons[5]) gm->setPlayerShip(m_score->m_playerShip);
    if(activeIcons[6]) gm->setPlayerJetpack(m_score->m_playerJetpack);
    if(activeIcons[7]) gm->setPlayerBall(m_score->m_playerBall);
    if(activeIcons[8]) gm->setPlayerBird(m_score->m_playerUfo);
    if(activeIcons[9]) gm->setPlayerDart(m_score->m_playerWave);
    if(activeIcons[10]) gm->setPlayerRobot(m_score->m_playerRobot);
    if(activeIcons[11]) gm->setPlayerSpider(m_score->m_playerSpider);
    if(activeIcons[12]) gm->setPlayerSwing(m_score->m_playerSwing);
    if(activeIcons[13]) gm->setPlayerDeathEffect(m_score->m_playerExplosion);
    if(activeIcons[14] && m_score->m_playerStreak) gm->setPlayerStreak(m_score->m_playerStreak);

    // updates user profiles 
    if (Mod::get()->getSettingValue<bool>("updateProfile")) {
        auto jeff = GameLevelManager::get();
        jeff->updateUserScore();
    }

    Notification::create(
        fmt::format("Copied {} Icon{}!", copiedIcons, copiedIcons == 1 ? "" : "s"),
        CCSprite::createWithSpriteFrameName("GJ_completesIcon_001.png")
    )->show();

    this->onClose(sender);
}

// Creates an info layer
void CopyPlusPopup::createInfoPopup(CCObject* sender) {
    auto infoPopup = FLAlertLayer::create("Copy+ Info", "This menu allows you to pick and choose which game modes you'd like to copy from the user!\n<cb>You can also hide this button in the mods settings!</c>", "Ok");
    infoPopup->show();
    infoPopup->setID("Info-Layer");
}

// Locks an object when enabled
void CopyPlusPopup::lockObject(int index) {
    if (auto btn = typeinfo_cast<CCMenuItemSpriteExtra*>(buttons->objectAtIndex(index))) {
        onSelect(btn);
        lockedArray[index] = true;
        auto spr = typeinfo_cast<CCRGBAProtocol*>(btn->getNormalImage());
        spr->setCascadeColorEnabled(true);
        spr->setColor(greyScale);
        spr->setOpacity(200);

        // adds a lock to the sprite
        auto lockSprite = CCSprite::createWithSpriteFrameName("GJ_lock_001.png");
        auto position = static_cast<CCSprite*>(btn->getChildren()->objectAtIndex(0))->getPosition();

        lockSprite->setPosition(position);
        lockSprite->setScale(btn->getTag() > 3 ? .8f : .5f);
        btn->addChild(lockSprite);
        lockSprite->setID("lock"_spr);
        btn->setEnabled(false);
    }
}
/*
TODO: figure out why I get null pointer errors here
*/
// resets all the buttons
void CopyPlusPopup::resetButtons(CCObject* sender) {
    for (int i = 0; i < sizeof(activeIcons); i++) {
        if (!lockedArray[i] && !activeIcons[i]) {
            if (auto btn = typeinfo_cast<CCMenuItemSpriteExtra*>(buttons->objectAtIndex(i))) onSelect(btn);
        }
    }
}