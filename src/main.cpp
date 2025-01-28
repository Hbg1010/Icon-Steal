/**
 * Include the Geode headers.
 * TODO: fix compatibility with a mod. add some more settings 
 */
#include <Geode/Geode.hpp>
#include "CopyPlusPopup.hpp"
using namespace geode::prelude;

#include <Geode/modify/ProfilePage.hpp>
class $modify(copyIcons, ProfilePage) {

	// adds buttons to profiles
	void loadPageFromUserInfo(GJUserScore* a2) {
		ProfilePage::loadPageFromUserInfo(a2);
		
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

		if (!Mod::get()->getSettingValue<bool>("unlocked")) {
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
		} else {
			if (gm->isColorUnlocked(m_score->m_color1, UnlockType::Col1)) gm->setPlayerColor(m_score->m_color1);
			if (gm->isColorUnlocked(m_score->m_color2, UnlockType::Col2)) gm->setPlayerColor2(m_score->m_color2);
			if (gm->isColorUnlocked(m_score->m_color3, UnlockType::Col2)) gm->setPlayerColor3(m_score->m_color3);
			if (gm->isIconUnlocked(m_score->m_playerShip, IconType::Ship)) gm->setPlayerShip(m_score->m_playerShip);
			if (gm->isIconUnlocked(m_score->m_playerJetpack, IconType::Jetpack)) gm->setPlayerJetpack(m_score->m_playerJetpack);
			if (gm->isIconUnlocked(m_score->m_playerBall, IconType::Ball)) gm->setPlayerBall(m_score->m_playerBall);
			if (gm->isIconUnlocked(m_score->m_playerUfo, IconType::Ufo)) gm->setPlayerBird(m_score->m_playerUfo);
			if (gm->isIconUnlocked(m_score->m_playerWave, IconType::Wave)) gm->setPlayerDart(m_score->m_playerWave);
			if (gm->isIconUnlocked(m_score->m_playerRobot, IconType::Robot)) gm->setPlayerRobot(m_score->m_playerRobot);
			if (gm->isIconUnlocked(m_score->m_playerSpider, IconType::Spider)) gm->setPlayerSpider(m_score->m_playerSpider);
			if (gm->isIconUnlocked(m_score->m_playerSwing, IconType::Swing)) gm->setPlayerSwing(m_score->m_playerSwing);
			if (gm->isIconUnlocked(m_score->m_playerStreak, IconType::Special)) gm->setPlayerStreak(m_score->m_playerStreak);
			if (gm->isIconUnlocked(m_score->m_playerCube, IconType::Cube)) gm->setPlayerFrame(m_score->m_playerCube);
			log::debug("{}", gm->completedAchievement("geometry.ach.mappacks03"));

			// get binding
			if (gm->completedAchievement("mappacks03")) gm->setPlayerGlow(m_score->m_glowEnabled);
		}

		//TODO: add text to say applied
	}

	// opens up the menu selector popup
	void createCopyPlusLayer(CCObject* sender) {
	CopyPlusPopup* timePopUp = CopyPlusPopup::create(m_score);

	timePopUp->m_noElasticity = CCDirector::get()->getFastMenu();
	timePopUp->show();
	timePopUp->setID("Copy-Plus"_spr);
	}
};