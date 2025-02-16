class_name TestAttribute000
extends Attribute

const ATTRIBUTE_NAME := "TestAttribute000"

func _init(_attribute_name := ATTRIBUTE_NAME):
	attribute_name = _attribute_name
	

func _constrained_by(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(TestAttribute000ConstraintMin.ATTRIBUTE_NAME),
		attribute_set.find_by_name(TestAttribute000ConstraintMax.ATTRIBUTE_NAME),
	]
	
	
func _get_constrained_value(buffed_value: float, values: PackedFloat32Array) -> float:
	return clampf(buffed_value, values[0], values[1])
