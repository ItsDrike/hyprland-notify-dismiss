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
        const auto AMOUNT = vars[1];
        if (!isNumber(AMOUNT))
            return "invalid arg 1";
        try {
            amount = std::stoi(AMOUNT);
        }
        catch (std::exception& e) {
            return "invalid arg 1";
        }
    }

    g_pHyprNotificationOverlay->dismissNotifications(amount);

    return "ok";
}

std::string newDispatchNotify(eHyprCtlOutputFormat format, std::string request)
{
    CVarList vars(request, 0, ' ');

    if (vars[0] == "notifydismiss") {
        return dismissNotify(vars);
    }

    auto resp = ((dispatchNotifyFuncT)g_pDispatchNotifyHook->m_pOriginal)(format, request);
    return resp;
}