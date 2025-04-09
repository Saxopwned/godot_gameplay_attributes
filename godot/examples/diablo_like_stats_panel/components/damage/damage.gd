extends Control

@export var damage_type: ApplyDamageBuff = null
@export var attribute_container: AttributeContainer = null


@onready var label: Label = %Label
@onready var button: Button = %Button
@onready var spin_box: SpinBox = %SpinBox


func _ready() -> void:
	button.pressed.connect(handle_button_pressed)
	label.text = damage_type.attribute_name.replace("Damage", "").replace("Attribute", "")
	
	
func handle_button_pressed() -> void:
	assert(damage_type != null, "damage_type is null")
	assert(attribute_container != null, "attribute_container is null")

	damage_type.damage_range = spin_box.value
	attribute_container.apply_buff(damage_type)
