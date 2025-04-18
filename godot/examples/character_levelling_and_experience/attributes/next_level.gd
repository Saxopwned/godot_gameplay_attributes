class_name NextLevelAttribute
extends Attribute

const ATTRIBUTE_NAME := "NextLevelAttribute"


func _init(_attribute_name := ATTRIBUTE_NAME) -> void:
	attribute_name = _attribute_name


func _derived_from(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(LevelAttribute.ATTRIBUTE_NAME)
	]


func _get_initial_value(subscribed_attributes: PackedFloat32Array) -> float:
	return subscribed_attributes[0] + 1
	
	
func _get_buffed_value(values: PackedFloat32Array) -> float:
	return values[0] + 1
