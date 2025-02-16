extends CenterContainer

@onready var attribute_container: AttributeContainer = $AttributeContainer
@onready var decrement_health: Button = %DecrementHealth
@onready var decrement_max_health: Button = %DecrementMaxHealth
@onready var decrement_min_health: Button = %DecrementMinHealth
@onready var increment_health: Button = %IncrementHealth
@onready var increment_max_health: Button = %IncrementMaxHealth
@onready var increment_min_health: Button = %IncrementMinHealth
@onready var label_health: Label = %LabelHealth
@onready var label_min_health: Label = %LabelMinHealth
@onready var label_max_health: Label = %LabelMaxHealth
@onready var increment_value: SpinBox = $VBoxContainer/IncrementValue/IncrementValue


func format_value(value: float) -> String:
	return String.num(value, 2)


func make_pressed_handle(attribute_name: String, buff_value: float) -> Callable:
	var buff = AttributeBuff.new()
	
	buff.attribute_name = attribute_name
	buff.transient 		= false

	return func pressed_handler() -> void:
		if buff_value < 0.0:
			buff.operation = AttributeOperation.subtract(increment_value.value)
		else:
			buff.operation = AttributeOperation.add(increment_value.value)
		attribute_container.apply_buff(buff)


func update_view() -> void:
	var health = attribute_container.get_attribute_constrained_value_by_name(ConstrainedHealth.ATTRIBUTE_NAME)
	var min_health = attribute_container.get_attribute_constrained_value_by_name(MinHealthConstraintAttribute.ATTRIBUTE_NAME)
	var max_health = attribute_container.get_attribute_constrained_value_by_name(MaxHealthConstraintAttribute.ATTRIBUTE_NAME)
	
	label_health.text 		= format_value(health)
	label_min_health.text 	= format_value(min_health)
	label_max_health.text 	= format_value(max_health)


func _ready() -> void:
	update_view()
	
	attribute_container.attribute_changed.connect(func (_a, _b, _c): # yeah, I am lazy
		update_view()	
	)

	decrement_health.pressed.connect(make_pressed_handle(ConstrainedHealth.ATTRIBUTE_NAME, -1))
	decrement_max_health.pressed.connect(make_pressed_handle(MaxHealthConstraintAttribute.ATTRIBUTE_NAME, -1))
	decrement_min_health.pressed.connect(make_pressed_handle(MinHealthConstraintAttribute.ATTRIBUTE_NAME, -1))

	increment_health.pressed.connect(make_pressed_handle(ConstrainedHealth.ATTRIBUTE_NAME, +1))
	increment_max_health.pressed.connect(make_pressed_handle(MaxHealthConstraintAttribute.ATTRIBUTE_NAME, +1))
	increment_min_health.pressed.connect(make_pressed_handle(MinHealthConstraintAttribute.ATTRIBUTE_NAME, +1))
