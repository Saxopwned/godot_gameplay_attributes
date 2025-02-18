@tool
class_name ShotsPerSecondAttribute
extends Attribute

const ATTRIBUTE_NAME := "ShotsPerSecondAttribute"
const MAX_WAIT_TIME  := 3.0

func _init(_attribute_name := ATTRIBUTE_NAME) -> void:
	attribute_name = _attribute_name
	
	
func _derived_from(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(FireRateAttribute.ATTRIBUTE_NAME)
	]
	

func _get_buffed_value(values: PackedFloat32Array) -> float:
	## the value is the MAX_WAIT_TIME - (fire_rate% of MAX_WAIT_TIME)
	return MAX_WAIT_TIME - ((MAX_WAIT_TIME / 100.0) * values[0])
	

func _get_constrained_value(buffed_value: float, _buffed_values: PackedFloat32Array, _previous_values: PackedFloat32Array) -> float:
	return maxf(buffed_value, 0.2)
