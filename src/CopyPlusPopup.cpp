#include "CopyPlusPopup.hpp"

bool activeIcons[14] = { true };
CCArray* buttons;
GJUserScore* m_score;
const ccColor3B greyScale = {.r = 90, .g = 90, .b = 90};
const ccColor3B color = {.r = 255, .g = 255, .b = 255};

CopyPlusPopup* CopyPlusPopup::create(GJUserScore* const& userDat) {
    auto temp = new CopyPlusPopup();

    // trys to make node
    if (temp->initAnchored(360, 240, userDat)) {
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
    return CCMenuItemSpriteExtra::create(spr, this, menu_selector(CopyPlusPopup::onSelect));
}

// text buttons
CCMenuItemSpriteExtra* CopyPlusPopup::createTextButton(const char* buttonName) {
    auto spr = ButtonSprite::create(buttonName, "bigFont.fnt", "GJ_button_04.png");
    spr->setScale(0.5f);
    return CCMenuItemSpriteExtra::create(spr, this, menu_selector(CopyPlusPopup::onSelect));
}

bool CopyPlusPopup::setup(GJUserScore* const& userDat) {
    m_score = userDat;
    buttons = CCArray::create();

     this->setTitle("Copy+");

    // top layer of colors + glow
    buttons->addObject(createTextButton("Col1"));
    buttons->addObject(createTextButton("Col2"));
    buttons->addObject(createTextButton("Col3"));
    buttons->addObject(createTextButton("Glow"));

    // Bottom Layer: icons
    buttons->addObject(createFormatted("gj_iconBtn_off_001.png"));
    buttons->addObject(createFormatted("gj_shipBtn_off_001.png"));
    buttons->addObject(createFormatted("gj_jetpackBtn_off_001.png"));
    buttons->addObject(createFormatted("gj_ballBtn_off_001.png"));
    buttons->addObject(createFormatted("gj_birdBtn_off_001.png"));
    buttons->addObject(createFormatted("gj_dartBtn_off_001.png"));
    buttons->addObject(createFormatted("gj_robotBtn_off_001.png"));
    buttons->addObject(createFormatted("gj_spiderBtn_off_001.png"));
    buttons->addObject(createFormatted("gj_swingBtn_off_001.png"));
    buttons->addObject(createFormatted("gj_streakBtn_off_001.png"));


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
            CCNode* x = static_cast<CCNode*>(buttons->objectAtIndex(i));
            x->setTag(i);
            iconMenu->addChild(x);
            activeIcons[i] = true;
        }
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

    return true;
}

// button action whenever an icon related button is clicked
void CopyPlusPopup::onSelect(CCObject* sender) {
    int x = sender->getTag();
    bool enable = !activeIcons[x];
    activeIcons[x] = enable;

    if (auto btn = typeinfo_cast<CCMenuItemSpriteExtra*>(sender)) {
        auto spr = typeinfo_cast<CCRGBAProtocol*>(btn->getNormalImage());
        spr->setCascadeColorEnabled(true);
        // spr->setCascadeOpacityEnabled(true);
        spr->setColor(enable ? color : greyScale);
        spr->setOpacity(enable ? 255 : 200);
    }

    // log::debug("{}", enable);
}

// sets the icons
void CopyPlusPopup::setIcons(CCObject* sender) {
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
    if(activeIcons[13]) gm->setPlayerStreak(m_score->m_playerStreak);

    log::debug("Copy Plus complete");
    this->onClose(sender);
}

// Creates an info layer
void CopyPlusPopup::createInfoPopup(CCObject* sender) {
    auto infoPopup = FLAlertLayer::create("Copy+ Info", "This menu allows to pick and choose which gamemodes you'd like to copy from the user!\nYou can also hide this button in the mods settings!", "Ok");
    infoPopup->show();
    infoPopup->setID("Info-Layer");
}
