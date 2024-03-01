#pragma once

#include <hyprland/src/SharedDefs.hpp>
#include <hyprland/src/debug/Log.hpp>
#include <hyprland/src/plugins/HookSystem.hpp>
#include <hyprland/src/plugins/PluginAPI.hpp>

inline HANDLE PHANDLE = nullptr;

const PLUGIN_DESCRIPTION_INFO s_pluginDescription = {"notify-dismiss", "Notify Dismiss", "ItsDrike", "1.0"};

const CColor s_notifyColor = {0x61 / 255.0f, 0xAF / 255.0f, 0xEF / 255.0f, 1.0f}; // RGBA

// Function hooks
typedef std::string (*dispatchNotifyFuncT)(eHyprCtlOutputFormat, std::string);
inline CFunctionHook* g_pDispatchNotifyHook = nullptr;
