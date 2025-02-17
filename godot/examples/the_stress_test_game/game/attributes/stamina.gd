@tool
class_name StaminaAttribute extends Attribute

const ATTRIBUTE_NAME := "stamina"

func _init(_attribute_name = ATTRIBUTE_NAME) -> void:
	self.attribute_name = _attribute_name
