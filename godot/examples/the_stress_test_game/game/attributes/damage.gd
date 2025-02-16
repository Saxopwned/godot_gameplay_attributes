@tool
class_name DamageAttribute 
extends Attribute


const ATTRIBUTE_NAME := "damage"


func _init(_attribute_name := ATTRIBUTE_NAME) -> void:
	self.attribute_name = _attribute_name
