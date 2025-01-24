/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
#include "CopyPlusPopup.hpp"
using namespace geode::prelude;

#include <Geode/modify/ProfilePage.hpp>
class $modify(copyIcons, ProfilePage) {

	// adds a copy button
	void loadPageFromUserInfo(GJUserScore* a2) {
		ProfilePage::loadPageFromUserInfo(a2);

		log::debug("x");

		if (m_ownProfile) return;

		if(auto leftMenu = m_mainLayer->getChildByID("left-menu")) {
			// copy button
			auto cSprite = ButtonSprite::create("Copy");
			cSprite->setScale(0.5f);
			auto btn = CCMenuItemSpriteExtra::create(cSprite, this, menu_selector(copyIcons::setIcons));
            btn->setID("Copy-icons"_spr);
            leftMenu->addChild(btn);
            this->m_buttons->addObject(btn);

			// copy+ button
			if (Mod::get()->getSettingValue<bool>("CopyPlus")) {
				auto copyPlusSprite = ButtonSprite::create("Copy+", "goldFont.fnt", "GJ_button_03.png");
				copyPlusSprite->setScale(0.45f);
				auto copyPlus = CCMenuItemSpriteExtra::create(copyPlusSprite, this, menu_selector(copyIcons::createCopyPlusLayer));

				// adds them to left menu
				copyPlus->setID("CopyPlus-icons"_spr);
				leftMenu->addChild(copyPlus);

				this->m_buttons->addObject(copyPlus);
			}
			

            leftMenu->updateLayout();
        }
	}

	// sets icons in CCGameManager from whatever is possible to obtain from m_score. 
	// dont think its possible to do death effect + shipstreek rn. damn 
	void setIcons(CCObject* sender) {
		auto gm = GameManager::sharedState();
		gm->setPlayerColor(m_score->m_color1);
		gm->setPlayerColor2(m_score->m_color2);
		gm->setPlayerColor3(m_score->m_color3);
		gm->setPlayerShip(m_score->m_playerShip);
		gm->setPlayerJetpack(m_score->m_playerJetpack);
		gm->setPlayerBall(m_score->m_playerBall);
		gm->setPlayerBird(m_score->m_playerUfo);
		gm->setPlayerDart(m_score->m_playerWave);
		gm->setPlayerRobot(m_score->m_playerRobot);
		gm->setPlayerSpider(m_score->m_playerSpider);
		gm->setPlayerSwing(m_score->m_playerSwing);
		gm->setPlayerStreak(m_score->m_playerStreak);
		gm->setPlayerFrame(m_score->m_playerCube);
		gm->setPlayerGlow(m_score->m_glowEnabled);
	}

	// opens up the menu selector popup
	void createCopyPlusLayer(CCObject* sender) {
	CopyPlusPopup* timePopUp = CopyPlusPopup::create(m_score);

	timePopUp->m_noElasticity = CCDirector::get()->getFastMenu();
	timePopUp->show();
	timePopUp->setID("Copy-Plus"_spr);
	}

};


// CUSTOM LAYER CLASS


// class CopyPlusPopup : public Popup<GJUserScore* const&> {

// 	bool activeIcons[14] = { false };
// 	const ccColor3B greyScale = {.r = 90, .g = 90, .b = 90};
//     const ccColor3B color = {.r = 255, .g = 255, .b = 255};
// 	public:
// 	static CopyPlusPopup* create(GJUserScore* const& userDat) {
// 		auto temp = new CopyPlusPopup();

// 		// trys to make node
// 		if (temp->initAnchored(300, 150, userDat)) {
// 			temp->autorelease();
// 			return temp;

// 		} else {
// 			CC_SAFE_DELETE(temp);

// 			return nullptr;
// 		}
// 	}

// 	protected:
// 	bool setup(GJUserScore* const& userDat) {
// 		this->setTitle("Copy+");
// 		// CCMenu* iconMenu = CCMenu::create();
// 		// iconMenu->setPosition({m_mainLayer->getContentWidth()/2, m_mainLayer->getPositionY()/2.f});
// 		// m_mainLayer->addChild(iconMenu);

// 		// CCMenu* extrasMenu = CCMenu::create();
//     	// iconMenu->setContentWidth(300.f);

// 		// CCMenu* confirmMenu = CCMenu::create();
// 		// auto setSpr = ButtonSprite::create("Set");
// 		// CCMenuItemSpriteExtra* setBtn = CCMenuItemSpriteExtra::create(setSpr, this, menu_selector(setIcons));

// 		return true;
// 	}

// 	void onSelect(CCObject* sender) {
// 		int x = sender->getTag();
// 		bool enable = !activeIcons[x];
// 		activeIcons[x] = enable;
	
// 		if (auto btn = typeinfo_cast<CCMenuItemSpriteExtra*>(sender)) {
// 			btn->setEnabled(enable);
// 			auto spr = typeinfo_cast<CCRGBAProtocol*>(btn->getNormalImage());
// 				spr->setCascadeColorEnabled(true);
// 				spr->setCascadeOpacityEnabled(true);
// 				spr->setColor(enable ? color : greyScale);
// 				spr->setOpacity(enable ? 255 : 200);
// 		}
// 	}

// 	void setIcons(CCObject* sender) {
// 		// TODO: implement
// 	}
// };
