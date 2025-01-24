/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
using namespace geode::prelude;

#include <Geode/modify/ProfilePage.hpp>
class $modify(copyIcons, ProfilePage) {

	// adds a copy button
	void loadPageFromUserInfo(GJUserScore* a2) {
		ProfilePage::loadPageFromUserInfo(a2);

		log::debug("x");

		if (m_ownProfile) return;

		if(auto leftMenu = m_mainLayer->getChildByID("left-menu")) {
			auto spr = ButtonSprite::create("Copy");
			spr->setScale(0.5f);
			auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(copyIcons::setIcons));
            
            btn->setID("Copy-icons"_spr);
            leftMenu->addChild(btn);
			
            this->m_buttons->addObject(btn);

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
};