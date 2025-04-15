#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {

class GDExample : public Sprite2D {
	GDCLASS(GDExample, Sprite2D)

private:
	double time_passed;
	Vector2 init_position;

protected:
	static void _bind_methods();

public:
	GDExample();
	~GDExample();

	void _ready() override;
	void _process(double delta) override;
};

}

#endif