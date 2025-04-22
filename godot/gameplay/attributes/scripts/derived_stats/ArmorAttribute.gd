class_name ArmorAttribute 
extends Attribute

const ATTRIBUTE_NAME := "ArmorAttribute"

func _init(_attribute_name = ATTRIBUTE_NAME) -> void:
	attribute_name = _attribute_name


func _compute_value(_compute_value: AttributeComputationArgument) -> float:
	var parent_attributes := _compute_value.runtime_attribute.get_parent_runtime_attributes()
	var armour = parent_attributes[0].get_buffed_value()
	var strength = parent_attributes[1].get_buffed_value()
	
	return armour + (floorf(strength / 10))
	
	
func _derived_from(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(BaseArmourAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(StrengthAttribute.ATTRIBUTE_NAME),
	]
