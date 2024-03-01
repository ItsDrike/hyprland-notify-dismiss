#include "globals.hpp"

// Do NOT change this function.
APICALL EXPORT std::string PLUGIN_API_VERSION()
{
    return HYPRLAND_API_VERSION;
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle)
{
    PHANDLE = handle;

    HyprlandAPI::addNotification(PHANDLE, "[notify-dismiss] Initialized successfully!", s_notifyColor, 5000);
    return s_pluginDescription;
}

APICALL EXPORT void PLUGIN_EXIT() {}
