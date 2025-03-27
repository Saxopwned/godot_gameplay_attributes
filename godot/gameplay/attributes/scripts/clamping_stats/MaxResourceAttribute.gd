class_name MaxResourceAttribute 
extends Attribute

const ATTRIBUTE_NAME := "MaxResourceAttribute"

func _init(_attribute_name = ATTRIBUTE_NAME) -> void:
	attribute_name = _attribute_name


func _compute_value(computed_value: AttributeComputationArgument) -> float:
	var base_value			:= 5.0
	var parent_attributes	:= computed_value.runtime_attribute.get_parent_runtime_attributes()

	## The maximum resource is the base value + 1 for each 5 points of intelligence.
	## Flooring necessary because I am an asshole and I want you to sweat harder.
	return base_value + floorf(parent_attributes[0].get_buffed_value() / 5.0)
	

func _derived_from(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(IntelligenceAttribute.ATTRIBUTE_NAME)
	]
