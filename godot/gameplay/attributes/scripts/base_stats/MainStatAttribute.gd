class_name MainStatAttribute 
extends Attribute

const ATTRIBUTE_NAME := "MainStatAttribute"


func _init(_attribute_name = ATTRIBUTE_NAME) -> void:
	attribute_name = _attribute_name


func _compute_value(_compute_value: AttributeComputationArgument) -> float:
	assert([0.0, 1.0, 2.0].has(_compute_value.operated_value), "invalid value, accepted are Dexterity (0), Intelligence (1) or Strength (2)" )	
	return _compute_value.operated_value
