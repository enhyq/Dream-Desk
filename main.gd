extends Control

func _ready():
	if DisplayServer.is_window_transparency_available():
		get_window().transparent = true
		get_viewport().transparent_bg = true
	else:
		printerr("Window transparency is not available on this system.")
		# Optionally handle the case where transparency isn't supported
