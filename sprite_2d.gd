extends Sprite2D

var init_position
var speed
var travel_distance
var direction

func _ready():
	init_position = self.position
	travel_distance = 100
	speed = 1
	direction = 1

func _process(delta):
	self.position += Vector2(direction * speed, 0)
	if self.position.x < init_position.x - travel_distance:
		direction = 1
	elif self.position.x > init_position.x + travel_distance:
		direction = -1
