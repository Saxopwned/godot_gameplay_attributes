extends ProgressBar

@onready var label: Label = $Label


func _physics_process(delta: float) -> void:
	value += delta
	
	if max_value <= value:
		queue_free()


func set_buff(p_buff: AttributeBuff) -> void:
	max_value = p_buff.duration
	min_value = 0
	label.text = p_buff.buff_name