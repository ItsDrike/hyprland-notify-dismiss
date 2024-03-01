# Hyprland notify-dismiss plugin

This is a simple plugin that adds support for sending `notifydismiss` requests
via the hyprctl socket (`.socket.sock`, not `.socket2.sock`).

> [!WARNING]
> This is a hacky implementation, just to temporarily bring in the support for
> this feature. Don't expect this plugin to be a long-term solution, I will
> remove this repository once https://github.com/hyprwm/Hyprland/issues/4787 is
> merged, bringing this support in officially.

## Usage

### Netcat (writing the command directly to socket)

You can either send the `notifydismiss` request directly to the `.socket.sock`:

```bash
echo "notifydismiss" | nc -U "/tmp/hypr/$HYPRLAND_INSTANCE_SIGNATURE/.socket.sock"
```

Which will dismiss all notifications, or you can use:

```bash
echo "notifydismiss 2" | nc -U "/tmp/hypr/$HYPRLAND_INSTANCE_SIGNATURE/.socket.sock"
```

Which will dismiss the 2 oldest notifications. (Passing `-1` will also dismiss
all notifications.)

### Hyprctl

Due to the limitations on how Hyprland plugins work, it is not possible to hook
into `hyprctl` binary and change the inner handling there, hooks only work
within the `Hyprland` binary.

That said, since `hyprctl` already has support for `notify` command, the way
it's implemented will allow you to also use it with any other command, that
also starts with `notify`, so calling `hyprctl notifydismiss` will actually
work.

That said, hyprctl will expect a minimum of 2 arguments here, since that's the
setting for `notify`. This isn't an issue though, as the 2nd argument will
simply be ignored, so you can pass it anything, it just must be there.

Example usage:

```bash
hyprctl notifydismiss -1 foo  # dismiss all notifications
hyprctl notifydismiss 2 bar  # dissmiss 2 oldest notifications
```

## Installation

The recommended way to install this plugin is via the official plugin manager `hyprpm`:

- `hyprpm add https://github.com/ItsDrike/hyprland-notify-dismiss`
- `hyprpm enable notify-dismiss`

To automatically load the plugin when Hyprland starts, add `exec-once = hyprpm
reload -n` to your Hyprland config.

Alternatively, you can also install manually:

- `make all`
- `hyprctl plugin load ${PWD}/notify-dismiss.so` (must be an absolute path)
