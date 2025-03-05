extends Control

const ACTION_SPEED_ADD_1 = preload("res://examples/complex_cases/attribute_buffs/action_speed_+1.tres")
const ACTION_SPEED_SUB_1 = preload("res://examples/complex_cases/attribute_buffs/action_speed_-1.tres")
const CAST_SPEED_1_5_X = preload("res://examples/complex_cases/attribute_buffs/cast_speed_1_5_x.tres")

@onready var derived_attribute_apply_buff_button: Button = $DerivedAttributeHBoxContainer/ApplyBuffButton
@onready var attribute_container: AttributeContainer = %AttributeContainer
@onready var base_attribute_display: Control = %BaseAttributeDisplay
@onready var derived_attribute_display: Control = %DerivedAttributeDisplay
@onready var derived_attribute_remove_buff_button: Button = $DerivedAttributeHBoxContainer/RemoveBuffButton
@onready var base_attribute_apply_buff_button: Button = $BaseAttributeHBoxContainer/ApplyBuffButton
@onready var base_attribute_remove_buff_button: Button = $BaseAttributeHBoxContainer/RemoveBuffButton


func _ready() -> void:
	attribute_container.attribute_changed.connect(func (_a, _b, _c):
		print(_a, _b, _c)
		update()	
	)
	attribute_container.buff_applied.connect(func (_a):
		update()	
	)
	attribute_container.buff_removed.connect(func (_a):
		update()	
	)
	base_attribute_apply_buff_button.pressed.connect(handle_base_attribute_apply_buff_button_pressed)
	base_attribute_remove_buff_button.pressed.connect(handle_base_attribute_remove_buff_button_pressed)
	derived_attribute_apply_buff_button.pressed.connect(handle_derived_attribute_apply_buff_button_pressed)
	derived_attribute_remove_buff_button.pressed.connect(handle_derived_attribute_remove_buff_button_pressed)
	
	update()


func handle_base_attribute_apply_buff_button_pressed() -> void:
	attribute_container.apply_buff(ACTION_SPEED_ADD_1)


func handle_base_attribute_remove_buff_button_pressed() -> void:
	attribute_container.apply_buff(ACTION_SPEED_SUB_1)


func handle_derived_attribute_apply_buff_button_pressed() -> void:
	attribute_container.apply_buff(CAST_SPEED_1_5_X)


func handle_derived_attribute_remove_buff_button_pressed() -> void:
	attribute_container.remove_buff(CAST_SPEED_1_5_X)


func update() -> void:
	base_attribute_display.attribute = attribute_container.get_attribute_by_name(ActionSpeedAttribute.ATTRIBUTE_NAME)
	derived_attribute_display.attribute = attribute_container.get_attribute_by_name(CastSpeedAttribute.ATTRIBUTE_NAME)
	base_attribute_display.update()
	derived_attribute_display.update()
