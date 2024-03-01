#include "plugin.hpp"
#include "globals.hpp"
#include <hyprland/src/debug/HyprNotificationOverlay.hpp>
#include <hyprland/src/helpers/VarList.hpp>

void CHyprNotificationOverlay::dismissNotifications(const int amount)
{
    if (amount == -1)
        m_dNotifications.clear();
    else {
        const int AMT = std::min(amount, static_cast<int>(m_dNotifications.size()));

        for (int i = 0; i < AMT; ++i) {
            m_dNotifications.pop_front();
        }
    }
}

std::string dismissNotify(CVarList vars)
{
    int amount = -1;

    if (vars.size() > 1) {
        auto arg = vars[1];
        arg.erase(std::remove(arg.begin(), arg.end(), '\n'), arg.end()); // remove the newline char at the end

        if (!isNumber(arg))
            return "invalid arg 1 NaN (" + arg + ")";

        try {
            amount = std::stoi(arg);
        }
        catch (std::exception& e) {
            return "invalid arg 1 stoi EXC";
        }
    }

    g_pHyprNotificationOverlay->dismissNotifications(amount);

    return "ok";
}

std::string newDispatchNotify(eHyprCtlOutputFormat format, std::string request)
{
    CVarList vars(request, 0, ' ');

    auto cmd = vars[0];
    cmd.erase(std::remove(cmd.begin(), cmd.end(), '\n'), cmd.end()); // remove the newline char at the end

    if (cmd == "notifydismiss")
        return dismissNotify(vars);

    auto resp = ((dispatchNotifyFuncT)g_pDispatchNotifyHook->m_pOriginal)(format, request);
    return resp;
}
