@tool
extends MarginContainer

var tween

@export var texture: Texture2D:
	set(new_value):
		var child = get_node_or_null("DecorButton/TextureButton")
		if is_instance_valid(child):
			child.texture = new_value
	get():
		var child = get_node_or_null("DecorButton/TextureButton")
		if is_instance_valid(child):
			return child.texture
		return null

@export var child_variable: String:
	set(new_value):
		var child = get_node_or_null("DecorButton/Label")
		if is_instance_valid(child):
			child.text = new_value
	get():
		var child = get_node_or_null("DecorButton/Label")
		if is_instance_valid(child):
			return child.text
		return ""



func _on_mouse_entered():
	tween = create_tween()
	tween.tween_property(self, "scale", Vector2(1.2, 1.2), 0.1)
	#self.set_scale(Vector2(2,2))


func _on_mouse_exited():
	if tween:
		tween.kill()
	tween = create_tween()
	tween.tween_property(self, "scale", Vector2(1, 1), 0.1)
