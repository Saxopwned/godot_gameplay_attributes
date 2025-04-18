class_name Player extends CharacterBody2D


signal died()
signal projectile_fired(starting_position: Vector2, target_position: Vector2)


@onready var attribute_container: AttributeContainer = $AttributeContainer
@onready var progress_bar: ProgressBar = $ProgressBar
@onready var camera_2d: Camera2D = $Camera2D


var health: RuntimeAttribute
var min_health: RuntimeAttribute
var max_health: RuntimeAttribute
var fire_rate: RuntimeAttribute
var fire_timer_time: RuntimeAttribute
var fire_timer: Timer
var is_dead: bool = false
var movement_speed: RuntimeAttribute
var pickup_radius: RuntimeAttribute
var target: Node2D


func _ready() -> void:
	fire_timer = Timer.new()
	add_child(fire_timer)
	health = attribute_container.get_attribute_by_name(HealthAttribute.ATTRIBUTE_NAME)
	min_health = attribute_container.get_attribute_by_name(MinHealthAttribute.ATTRIBUTE_NAME)
	max_health = attribute_container.get_attribute_by_name(MaxHealthAttribute.ATTRIBUTE_NAME)
	movement_speed = attribute_container.get_attribute_by_name(MovementSpeedAttribute.ATTRIBUTE_NAME)
	fire_rate = attribute_container.get_attribute_by_name(FireRateAttribute.ATTRIBUTE_NAME)
	fire_timer_time = attribute_container.get_attribute_by_name(ShotsPerSecondAttribute.ATTRIBUTE_NAME)
	pickup_radius = attribute_container.get_attribute_by_name(PickupRadiusAttribute.ATTRIBUTE_NAME)

	if health:
		progress_bar.min_value = min_health.get_constrained_value()
		progress_bar.max_value = max_health.get_constrained_value()
		progress_bar.value = health.get_constrained_value()
	
	attribute_container.attribute_changed.connect(func (attribute, _old, new_value):
		if attribute is HealthAttribute:
			progress_bar.value = new_value
			if new_value <= 0.01:
				is_dead = true
				died.emit()	
		elif attribute is ShotsPerSecondAttribute:
			fire_timer.stop()
			fire_timer.wait_time = fire_timer_time.get_buffed_value()
			fire_timer.start()
	)
	
	fire_timer.timeout.connect(fire_projectile)
	fire_timer.wait_time = fire_timer_time.get_buffed_value()
	fire_timer.start()


func _input(event: InputEvent) -> void:
	if event.is_action_pressed("die_immediately"):
		print("uh oh")
		var instantdeath = AttributeBuff.new()
		instantdeath.attribute_name = HealthAttribute.ATTRIBUTE_NAME
		instantdeath.transient = false
		instantdeath.operation = AttributeOperation.subtract(99999999)
		attribute_container.apply_buff(instantdeath)


func _physics_process(delta: float) -> void:
	if is_dead:
		progress_bar.modulate.a = lerp(progress_bar.modulate.a, 0.0, 1.0 * delta)
		return
	
	var current_speed = movement_speed.get_buffed_value()
	var move_vector = Input.get_vector("move_left", "move_right", "move_up", "move_down").normalized()

	velocity =  (move_vector * current_speed)
	
	move_and_slide()


func fire_projectile() -> void:
	if is_dead: 
		return

	var next: Node2D = null

	for child in get_tree().get_nodes_in_group("mobs"):
		if next == null:
			next = child
		elif child.global_position.distance_to(global_position) < next.global_position.distance_to(global_position):
			next = child
	
	if next:
		projectile_fired.emit(global_position, next.global_position, attribute_container.get_attribute_by_name(DamageAttribute.ATTRIBUTE_NAME).get_buffed_value())
