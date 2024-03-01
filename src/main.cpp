#include "func_finder.hpp"
#include "globals.hpp"
#include "plugin.hpp"

// Do NOT change this function.
APICALL EXPORT std::string PLUGIN_API_VERSION()
{
    return HYPRLAND_API_VERSION;
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle)
{
    PHANDLE = handle;

    Debug::log(LOG, "[notify-dismiss] Finding Hyprland functions");

    auto pDispatchNotifyFunc = findHyprlandFunction("dispatchNotify");

    // Return immediately if the function wasn't found
    // (the error message has already been logged from findHyprlandFunction, this just quits)
    if (!pDispatchNotifyFunc) {
        return s_pluginDescription;
    }

    Debug::log(LOG, "[notify-dismiss] Registering function hooks");

    // Register function hooks for overriding the original funcs
    g_pDispatchNotifyHook = HyprlandAPI::createFunctionHook(PHANDLE, pDispatchNotifyFunc, (void*)&newDispatchNotify);

    // Initialize the hooks, from now on, the original functions will be overridden
    g_pDispatchNotifyHook->hook();

    Debug::log(LOG, "[notify-dismiss] Plugin loaded successfully");
    HyprlandAPI::addNotification(PHANDLE, "[notify-dismiss] Initialized successfully!", s_notifyColor, 5000);

    return s_pluginDescription;
}

APICALL EXPORT void PLUGIN_EXIT()
{
    if (!g_pDispatchNotifyHook) {
        g_pDispatchNotifyHook->unhook();
        HyprlandAPI::removeFunctionHook(PHANDLE, g_pDispatchNotifyHook);
        g_pDispatchNotifyHook = nullptr;
    }

    HyprlandAPI::addNotification(PHANDLE, "[notify-dismiss] Unloaded successfully!!", s_notifyColor, 5000);
}
