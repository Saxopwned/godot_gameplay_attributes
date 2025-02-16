# note, it's not the best practice

extends Area2D

var direction: Vector2
var damage: float

func _ready() -> void:
	body_entered.connect(_on_body_entered)


func _physics_process(delta: float) -> void:
	global_position += (direction * delta) * 100.0
	look_at(direction)


func _on_body_entered(body: Node2D) -> void:
	if body.is_in_group("mobs"):
		var debuff = AttributeBuff.new()
		debuff.attribute_name = HealthAttribute.ATTRIBUTE_NAME
		debuff.operation = AttributeOperation.subtract(absf(damage))
		debuff.transient = false
		body.attribute_container.apply_buff(debuff)
		queue_free()
