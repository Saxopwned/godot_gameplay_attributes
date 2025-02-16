class_name ConstrainedHealth
extends Attribute

const ATTRIBUTE_NAME := "ConstrainedHealth"

func _init(_attribute_name := ATTRIBUTE_NAME):
	attribute_name = _attribute_name
	
	
func _constrained_by(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(MinHealthConstraintAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(MaxHealthConstraintAttribute.ATTRIBUTE_NAME),
	]
	
	
func _get_constrained_value(buffed_value: float, values_constraints: PackedFloat32Array) -> float:
	return clampf(buffed_value, values_constraints[0], values_constraints[1])
