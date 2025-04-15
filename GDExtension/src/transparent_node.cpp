#include "transparent_node.hpp"

using namespace godot;

void TransparentNode::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_mouse_passthrough", "enabled"), &TransparentNode::set_mouse_passthrough);
    ClassDB::bind_method(D_METHOD("is_mouse_passthrough"), &TransparentNode::is_mouse_passthrough);
}

TransparentNode::TransparentNode() {
    // Constructor
}

TransparentNode::~TransparentNode() {
    // Destructor
}

void TransparentNode::_ready() {
    UtilityFunctions::printerr("transparent_node.cpp:19 ready!!");
    #ifdef _WIN32
        hWnd = (HWND)DisplayServer::get_singleton()->window_get_native_handle(DisplayServer::HandleType::WINDOW_HANDLE);

        if (hWnd) {
            UtilityFunctions::print("Got Window Handle: ");
            UtilityFunctions::print((int64_t)hWnd); // Cast to print the handle
        } else {
            UtilityFunctions::printerr("Failed to get Window Handle. Mouse Pass-Through will not work.");
            return;
        }
    #endif
    // SetForegroundWindow(hWnd); // Might need this.
}

void TransparentNode::set_mouse_passthrough(bool enabled) {
    #ifdef _WIN32
        // _ready();
        if (!hWnd) {
            UtilityFunctions::printerr("Window Handle is invalid. Cannot set mouse pass-through.");
            return;
        }

        if (enabled == mouse_passthrough_enabled)
            return; //prevent unnecessary calls
        
        // below is one time job ???
        // Use GetWindowLongPtr for 64-bit compatibility
        LONG_PTR exStyle = GetWindowLongPtr(hWnd, GWL_EXSTYLE); 

        if (enabled) {
            exStyle |= WS_EX_LAYERED | WS_EX_TRANSPARENT;
            // SetWindowLongPtr(hWnd, GWL_EXSTYLE, exStyle);
            SetWindowLongPtr(hWnd, GWL_EXSTYLE, WS_EX_LAYERED);
            SetLayeredWindowAttributes(hWnd, 0, 0, LWA_COLORKEY); // Important:  Make a color transparent!  Key out color 0.
            // Try to make it top most.
            // SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

            UtilityFunctions::print("Mouse Pass-Through Enabled");
        } else {
            exStyle &= ~(WS_EX_LAYERED | WS_EX_TRANSPARENT);
            SetWindowLongPtr(hWnd, GWL_EXSTYLE, exStyle);
            // Consider removing LWA_COLORKEY here.
            // SetWindowPos(hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
            UtilityFunctions::print("Mouse Pass-Through Disabled");
        }
        mouse_passthrough_enabled = enabled;

    #else
        if (enabled)
        UtilityFunctions::printerr("Mouse pass-through is currently only supported on Windows.");
    #endif
}

bool TransparentNode::is_mouse_passthrough(){
    #ifdef _WIN32
        return mouse_passthrough_enabled;
    #else
        return false;
    #endif
}
