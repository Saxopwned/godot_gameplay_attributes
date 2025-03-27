class_name DefensivePowerAttribute
extends Attribute

const ATTRIBUTE_NAME := "DefensivePowerAttribute"

func _init(_attribute_name = ATTRIBUTE_NAME) -> void:
	attribute_name = _attribute_name


func _compute_value(attribute_computation: AttributeComputationArgument) -> float:
	var parent_attributes: Array[RuntimeAttribute] = attribute_computation.get_parent_runtime_attributes()

	return 0


func _derived_from(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(ArmorAttribute.ATTRIBUTE_NAME),
	]
