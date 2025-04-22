extends Control

func _ready():
	if DisplayServer.is_window_transparency_available():
		get_window().transparent = true
		get_viewport().transparent_bg = true
		
		$TransparentNode.set_mouse_passthrough(true)
		get_tree().get_root().size_changed.connect(_on_window_resized) 
	else:
		printerr("Window transparency is not available on this system.")
		# Optionally handle the case where transparency isn't supported
#
	for btn in self.get_tree().get_nodes_in_group("ui_button"):
		pass


func _on_exit_button_pressed():
	get_tree().quit(0)


func _on_minimize_button_pressed():
	get_tree().root.mode = Window.MODE_MINIMIZED

func _on_window_resized():
	print(get_tree().root.get_mode())
	#if get_tree().root.get_mode() == Window.MODE_FULLSCREEN:
		#get_tree().root.mode = Window.MODE_EXCLUSIVE_FULLSCREEN
	if get_tree().root.get_mode() == Window.MODE_FULLSCREEN:
		print("full screen")
		$TransparentNode.set_mouse_passthrough(true)
