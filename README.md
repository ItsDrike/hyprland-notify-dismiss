# Hyprland notify-dismiss plugin

This is a simple plugin that adds support for sending `notifydismiss` requests
via the hyprctl socket (`.socket.sock`, not `.socket2.sock`).

You can trigger this notify dismissal request using `hyprctl` utility directly,
however, due to limitations on how plugins work, they can only hook into the
Hyprland binary, not into hyprctl.

This will still work though, because hyprctl only checks a match on command
prefix (i.e. since `hyprctl notify` works, so will `hyprctl notifydismiss`),
however it will expect 2 arguments here, when `notifydismiss` only needs 1.

> [!WARNING]
> This is clearly a very hacky implementation, just to temporarily
> bring in the support for this feature. Don't expect this plugin to be a
> long-term solution, I will remove this repository once
> https://github.com/hyprwm/Hyprland/issues/4787 is merged, bringing this
> support in officially.

## Installation

The recommended way to install this plugin is via the official plugin manager `hyprpm`:

- `hyprpm add https://github.com/ItsDrike/hyprland-notify-dismiss`
- `hyprpm enable notify-dismiss`

To automatically load the plugin when Hyprland starts, add `exec-once = hyprpm
reload -n` to your Hyprland config.

Alternatively, you can also install manually:

- `make all`
- `hyprctl plugin load ${PWD}/notify-dismiss.so` (must be an absolute path)
