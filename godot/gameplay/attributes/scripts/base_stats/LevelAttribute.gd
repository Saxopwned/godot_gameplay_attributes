class_name LevelAttribute
extends Attribute

const ATTRIBUTE_NAME = "LevelAttribute"

func _init(_attribute_name = ATTRIBUTE_NAME) -> void:
	attribute_name = _attribute_name


func _compute_value(attribute_computation: AttributeComputationArgument) -> float:
	return clampf(attribute_computation.operated_value, 1.0, 100.0)
