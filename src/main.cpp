#include <Geode/utils/Keyboard.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

bool canTrigger() {
    auto mod = Mod::get();
    
    if (!mod->getSettingValue<bool>("enabled")) return false;

    bool isGameplay = PlayLayer::get() != nullptr;
    bool isEditor = LevelEditorLayer::get() != nullptr;

    bool allowGameplay = mod->getSettingValue<bool>("allow-in-gameplay");
    bool allowEditor = mod->getSettingValue<bool>("allow-in-editor");

    if (isGameplay && !allowGameplay) return false;
    if (isEditor && !allowEditor) return false;

    return true;
}

$on_mod(Loaded) {
    struct Shortcut {
        std::string setting;
        std::string url;
    };

    std::vector<Shortcut> shortcuts = {
        {"linkedin-shortcut", "https://www.linkedin.com"},
        {"word-shortcut", "https://www.office.com/launch/word"},
        {"teams-shortcut", "https://www.teams.microsoft.com"},
        {"excel-shortcut", "https://www.office.com/launch/excel"},
        {"powerpoint-shortcut", "https://www.office.com/launch/powerpoint"},
        {"outlook-shortcut", "https://outlook.office.com"},
        {"onenote-shortcut", "https://www.onenote.com"}
    };

    for (auto const& sc : shortcuts) {
        listenForKeybindSettingPresses(sc.setting, [sc](Keybind const& keybind, bool down, bool repeat, double timestamp) {
            if (down && !repeat && canTrigger()) {
                geode::utils::web::openLinkInBrowser(sc.url);
            }
        });
    }
}