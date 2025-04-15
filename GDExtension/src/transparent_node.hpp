#ifndef TRANSPARENTNODE_H
#define TRANSPARENTNODE_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {

class TransparentNode : public Node {
	GDCLASS(TransparentNode, Node)

private:
	#ifdef _WIN32
    HWND hWnd = nullptr;
    bool mouse_passthrough_enabled = false;
	#endif

protected:
	static void _bind_methods();

public:
	TransparentNode();
	~TransparentNode();

	void _ready() override;
	void set_mouse_passthrough(bool enabled);
    bool is_mouse_passthrough();
};

}

#endif