#pragma once

#include <Geode/Geode.hpp>
#include <string.h>
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>
using namespace geode::prelude;

class CopyUtils {
public:
    // static void disableCustomIcon(std::string iconType, Mod* moreIcons = getMoreIconsMod()) {
    //     if (moreIcons != nullptr && iconType != "") MoreIcons::setIcon("",)
    // }

    static void disableCustomIcon(IconType iconType, Mod* moreIcons = getMoreIconsMod()) {
        if (moreIcons != nullptr) MoreIcons::setIcon("", iconType);
    }

    static void disableAllCustomIcons() {
        if (auto mi = getMoreIconsMod()) {
            for (int i = 0; i < 9; i++) {
                MoreIcons::setIcon("", static_cast<IconType>(i));
            }
            MoreIcons::setIcon("", IconType::Special);
        }
    };

    static void setCopiedIcon(IconType icon, int id) {

    }

    static std::string ittos(IconType type) {
        switch (type) {
            case IconType::Cube: return "icon";
            case IconType::Ship: return "ship";
            case IconType::Ball: return "ball";
            case IconType::Ufo: return "ufo";
            case IconType::Wave: return "wave";
            case IconType::Robot: return "robot";
            case IconType::Spider: return "spider";
            case IconType::Swing: return "swing";
            case IconType::Jetpack: return "jetpack";
            case IconType::Special: return "trail";
            default: return "";
        }
    }

    /*Icon Type to string*/

protected:
    static Mod* getMoreIconsMod() {
        if (Loader::get()->isModLoaded("hiimjustin000.more_icons")) {
            if (auto MoreIcons = Loader::get()->getLoadedMod("hiimjustin000.more_icons"))
            return MoreIcons;
        } 
        return nullptr;
    }
};

