@tool
class_name MinHealthAttribute 
extends Attribute

const ATTRIBUTE_NAME := "MinHealthAttribute"

func _init(_attribute_name = ATTRIBUTE_NAME) -> void:
	self.attribute_name = _attribute_name
