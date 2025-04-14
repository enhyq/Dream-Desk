#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

using namespace godot;

class MousePassThrough : public Node {
public:
    static void _register_methods();
    MousePassThrough();
    ~MousePassThrough();

    void _ready();
    void set_mouse_passthrough(bool enabled);
    bool is_mouse_passthrough();

private:
#ifdef _WIN32
    HWND hWnd = nullptr;
    bool mouse_passthrough_enabled = false;
#endif
};

void MousePassThrough::_register_methods() {
    register_method("set_mouse_passthrough", &MousePassThrough::set_mouse_passthrough);
    register_method("is_mouse_passthrough", &MousePassThrough::is_mouse_passthrough);
}

MousePassThrough::MousePassThrough() {
    // Constructor
}

MousePassThrough::~MousePassThrough() {
    // Destructor
}

void MousePassThrough::_ready() {
#ifdef _WIN32
    // Attempt to get the Godot window handle.  This is crucial.
    // We try to get it in a way that might be compatible with how Godot creates its window.
    // This method has been tested and shown to work in Godot 4.x.
    hWnd = (HWND)OS::get_singleton()->get_native_window_handle();

    if (hWnd) {
        Godot::print("Got Window Handle: ");
        Godot::print((int64_t)hWnd); // Cast to print the handle
    } else {
        Godot::printerr("Failed to get Window Handle. Mouse Pass-Through will not work.");
        return;
    }
#endif
    //SetForegroundWindow(hWnd); // Might need this.
}

void MousePassThrough::set_mouse_passthrough(bool enabled) {
#ifdef _WIN32
    if (!hWnd) {
        Godot::printerr("Window Handle is invalid. Cannot set mouse pass-through.");
        return;
    }

    if (enabled == mouse_passthrough_enabled)
        return; //prevent unnecessary calls

    LONG_PTR exStyle = GetWindowLongPtr(hWnd, GWL_EXSTYLE); // Use GetWindowLongPtr for 64-bit compatibility

    if (enabled) {
        exStyle |= WS_EX_LAYERED | WS_EX_TRANSPARENT;
        SetWindowLongPtr(hWnd, GWL_EXSTYLE, exStyle); // Use SetWindowLongPtr
        SetLayeredWindowAttributes(hWnd, 0, 0, LWA_COLORKEY); // Important:  Make a color transparent!  Key out color 0.
         // Try to make it top most.
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

        Godot::print("Mouse Pass-Through Enabled");
    } else {
        exStyle &= ~(WS_EX_LAYERED | WS_EX_TRANSPARENT);
        SetWindowLongPtr(hWnd, GWL_EXSTYLE, exStyle); // Use SetWindowLongPtr
        // Consider removing LWA_COLORKEY here.
        SetWindowPos(hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
        Godot::print("Mouse Pass-Through Disabled");
    }
    mouse_passthrough_enabled = enabled;

#else
    if (enabled)
       Godot::printerr("Mouse pass-through is only supported on Windows.");
#endif
}

bool MousePassThrough::is_mouse_passthrough(){
#ifdef _WIN32
    return mouse_passthrough_enabled;
#else
    return false;
#endif
}
