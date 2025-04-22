extends Control

@onready var attribute_container: AttributeContainer = $AttributeContainer
@onready var remove_health_button: Button = %RemoveHealthButton
@onready var add_health_button: Button = %AddHealthButton
@onready var health_progress_bar: ProgressBar = %HealthProgressBar


var inited = false


func _ready() -> void:
	attribute_container.apply_buff(SetInitialAttributesBuff.new())
	add_health_button.pressed.connect(make_buff_handler(5))
	remove_health_button.pressed.connect(make_buff_handler(-5))

	attribute_container.attribute_changed.connect(func (_a, _b, _c):
		render()	
	)
	
	render()


func make_buff_handler(value: float) -> Callable:
	return func apply_buff() -> void:
		attribute_container.apply_buff(ExampleBuff.new(value))


func render() -> void:
	var health 		:= attribute_container.get_attribute_buffed_value_by_name(HealthAttribute.ATTRIBUTE_NAME)
	var max_health 	:= attribute_container.get_attribute_buffed_value_by_name(MaxHealthAttribute.ATTRIBUTE_NAME)
	
	health_progress_bar.min_value 	= 0.0
	health_progress_bar.max_value 	= max_health
	health_progress_bar.value		= health
	


class ExampleBuff extends AttributeBuff:
	func _init(value: float) -> void:
		attribute_name = HealthAttribute.ATTRIBUTE_NAME
		
		if value < 0:
			operation = AttributeOperation.subtract(absf(value))
		else:
			operation = AttributeOperation.add(value)


class SetInitialAttributesBuff extends AttributeBuff:
	func _applies_to(attribute_set: AttributeSet) -> Array[AttributeBase]:
		## remember: base attributes first, derived later
		return [
			attribute_set.find_by_name(MaxHealthAttribute.ATTRIBUTE_NAME),
			attribute_set.find_by_name(HealthAttribute.ATTRIBUTE_NAME),
		]

	func _operate(_values: Array[float], _attribute_set: AttributeSet) -> Array[AttributeOperation]:
		return [
			AttributeOperation.forcefully_set_value(100.0),
			AttributeOperation.forcefully_set_value(50.00),
		]
