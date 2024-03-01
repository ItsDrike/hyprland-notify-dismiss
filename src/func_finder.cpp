#include "func_finder.hpp"
#include <hyprland/src/debug/Log.hpp>
#include <hyprland/src/plugins/PluginAPI.hpp>

void* findHyprlandFunction(const std::string& name)
{
    const auto METHODS = HyprlandAPI::findFunctionsByName(PHANDLE, name);

    if (METHODS.size() == 0) {
        Debug::log(
            ERR, "[notify-dismiss] Function {} wasn't found in Hyprland binary! This function's signature probably changed, report this", name);
        HyprlandAPI::addNotification(PHANDLE, "[notify-dismiss] Initialization failed! " + name + " function wasn't found", s_notifyColor, 10000);
        return nullptr;
    }

    if (METHODS.size() != 1) {
        Debug::log(ERR, "[notify-dismiss] Function {} matched multiple funtcions in Hyprland binary! Report this.", name);
        HyprlandAPI::addNotification(PHANDLE, "[notify-dismiss] Initialization failde! " + name + " function not unique", s_notifyColor, 1000);
        return nullptr;
    }

    return METHODS[0].address;
}
