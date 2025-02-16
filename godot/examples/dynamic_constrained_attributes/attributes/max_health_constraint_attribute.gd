class_name MaxHealthConstraintAttribute
extends Attribute

const ATTRIBUTE_NAME := "MaxHealthConstraintAttribute"

func _init(_attribute_name := ATTRIBUTE_NAME):
	attribute_name = _attribute_name


func _constrained_by(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(MinHealthConstraintAttribute.ATTRIBUTE_NAME)
	]
	
	
func _get_constrained_value(buffed_value: float, buffed_values: PackedFloat32Array, previous_values: PackedFloat32Array) -> float:
	return maxf(buffed_value, buffed_values[0])
