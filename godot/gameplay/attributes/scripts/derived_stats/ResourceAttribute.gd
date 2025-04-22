class_name ResourceAttribute 
extends Attribute

const ATTRIBUTE_NAME := "ResourceAttribute"

func _init(_attribute_name = ATTRIBUTE_NAME) -> void:
	attribute_name = _attribute_name


func _compute_value(compute_value: AttributeComputationArgument) -> float:
	var parent_attributes 	= compute_value.runtime_attribute.get_parent_runtime_attributes()

	# here we are clamping the health value to a minimum of 0.0 and to the maximum of max health's buffed value
	return clampf(compute_value.operated_value, 0.0, parent_attributes[0].get_buffed_value())


func _derived_from(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(MaxResourceAttribute.ATTRIBUTE_NAME),
	]
