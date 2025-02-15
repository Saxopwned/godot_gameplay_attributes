class_name LevelAttribute
extends Attribute

const ATTRIBUTE_NAME := "LevelAttribute"


func _init(_attribute_name := ATTRIBUTE_NAME) -> void:
	attribute_name 	= _attribute_name


func _get_max_value(_attribute_set: AttributeSet) -> float:
	return 100.0 # yes, like most of the games outside


func _get_min_value(_attribute_set: AttributeSet) -> float:
	return 1.0
