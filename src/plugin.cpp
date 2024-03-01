#include "plugin.hpp"
#include "globals.hpp"
#include <hyprland/src/debug/HyprNotificationOverlay.hpp>
#include <hyprland/src/helpers/VarList.hpp>

// HACK: This structure has the same members as the CHyprNotificationOverlay class, but declared as public
// This allows us to recast the g_pHyprNotificationOverlay as a pointer to this structure, and access it's
// private variables. This is incredibly hacky, and I'm not sure it will work if hyprland was compiled with
// a different compiler (or different settings) than the plugin, but it's the only way I could think of to
// be able to access the private variables.
struct DummyHyprNotificationOverlay {
    CBox m_bLastDamage;
    std::deque<std::unique_ptr<SNotification>> m_dNotifications;
    cairo_surface_t* m_pCairoSurface = nullptr;
    cairo_t* m_pCairo = nullptr;
    CMonitor* m_pLastMonitor = nullptr;
    CTexture m_tTexture;
    eIconBackend m_eIconBackend = ICONS_BACKEND_NONE;
    std::string m_szIconFontName = "Sans";
};

void dismissNotifications(const int amount)
{
    // HACK: This is horrendous
    DummyHyprNotificationOverlay* dummyOverlay = reinterpret_cast<DummyHyprNotificationOverlay*>(g_pHyprNotificationOverlay.get());

    if (amount == -1)
        dummyOverlay->m_dNotifications.clear();
    else {
        const int AMT = std::min(amount, static_cast<int>(dummyOverlay->m_dNotifications.size()));

        for (int i = 0; i < AMT; ++i) {
            dummyOverlay->m_dNotifications.pop_front();
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

    dismissNotifications(amount);

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
