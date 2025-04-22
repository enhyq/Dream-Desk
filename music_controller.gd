extends MarginContainer


var music_player: AudioStreamPlayer
var music_player_playlist: AudioStreamPlaylist

var current_track_index: int = 0
var number_of_songs: int
var song_list: Array[AudioStream]

func _ready():
	music_player = $AudioStreamPlayer
	music_player_playlist = music_player.get_stream()
	
	# set loop is not working as expected
	music_player_playlist.set_loop(false)
	music_player_playlist.set_shuffle(false) 
	
	number_of_songs = music_player_playlist.get_stream_count()
	for i in number_of_songs:
		song_list.append(music_player_playlist.get_list_stream(i))
	
	# initialize volume
	music_player.set_volume_linear(0.1)


func _on_play_pause_music_pressed():
	music_player.stream_paused = not music_player.stream_paused
		
func _on_previous_music_pressed():
	current_track_index = current_track_index - 1
	if current_track_index == -1:
		current_track_index = number_of_songs - 1
	music_player.set_stream(song_list[current_track_index])
	music_player.play()
	
func _on_next_music_pressed():
	current_track_index = (current_track_index + 1) % number_of_songs
	music_player.set_stream(song_list[current_track_index])
	music_player.play()
	

func _on_volume_slider_value_changed(value):
	music_player.set_volume_linear(value)


func _on_audio_stream_player_finished():
	#_on_next_music_pressed()
	print('song ended')

func _on_mute_button_pressed():
	$MusicPanel/MarginContainer/VBoxContainer/HBoxContainer/VolumeSlider.value = 0.0

func _on_max_volume_button_pressed():
	$MusicPanel/MarginContainer/VBoxContainer/HBoxContainer/VolumeSlider.value = 1.0

func _on_shuffle_button_toggled(toggled_on):
	music_player_playlist.set_shuffle(toggled_on)
	print("shuffle:", toggled_on)

func _on_loop_button_toggled(toggled_on):
	music_player_playlist.set_loop(toggled_on)
	print("loop:", toggled_on)
