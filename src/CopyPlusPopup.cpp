#include "CopyPlusPopup.hpp"

bool activeIcons[14] = { false };
CCArray* buttons;

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

CCMenuItemSpriteExtra* CopyPlusPopup::createFormatted() {
    auto spr = CCSprite::createWithSpriteFrameName("gj_iconBtn_off_001.png");
    auto returnBtn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(CopyPlusPopup::onSelect));

    return returnBtn;
}

bool CopyPlusPopup::setup(GJUserScore* const& userDat) {
    buttons = CCArray::create();
    buttons->addObject(createFormatted());
    
    this->setTitle("Copy+");
    CCMenu* iconMenu = CCMenu::create();
    iconMenu->setPosition({m_mainLayer->getContentWidth()/2, m_mainLayer->getPositionY()/2.f});
    m_mainLayer->addChild(iconMenu);

    CCMenu* extrasMenu = CCMenu::create();
    iconMenu->setContentWidth(300.f);

    if (buttons->count() > 0) {
        for (int i = 0; i < buttons->count(); i++) {
            buttons->objectAtIndex(i)->setTag(i);
        }
    }

    CCMenu* confirmMenu = CCMenu::create();
    confirmMenu->setPosition({m_mainLayer->getContentWidth()/2, m_mainLayer->getScaledContentHeight()/4});
    m_mainLayer->addChild(confirmMenu);
    auto setSpr = ButtonSprite::create("Set");
    CCMenuItemSpriteExtra* setBtn = CCMenuItemSpriteExtra::create(setSpr, this, menu_selector(CopyPlusPopup::setIcons));
    confirmMenu->addChild(setBtn);

    return true;
}

	void CopyPlusPopup::onSelect(CCObject* sender) {
		int x = sender->getTag();
		bool enable = !activeIcons[x];
		activeIcons[x] = enable;
	
		if (auto btn = typeinfo_cast<CCMenuItemSpriteExtra*>(sender)) {
			btn->setEnabled(enable);
			auto spr = typeinfo_cast<CCRGBAProtocol*>(btn->getNormalImage());
				spr->setCascadeColorEnabled(true);
				spr->setCascadeOpacityEnabled(true);
				spr->setColor(enable ? color : greyScale);
				spr->setOpacity(enable ? 255 : 200);
		}
	}

	void CopyPlusPopup::setIcons(CCObject* sender) {
		// TODO: implement
        log::debug("Copy Plus complete");
        this->onClose(sender);
	}

