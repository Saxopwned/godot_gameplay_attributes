class_name CastSpeedAttribute
extends Attribute

const ATTRIBUTE_NAME := "CastSpeedAttribute"


func _init(_attribute_name = ATTRIBUTE_NAME):
	attribute_name = _attribute_name


func _derived_from(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(ActionSpeedAttribute.ATTRIBUTE_NAME)
	]


func _get_initial_value(values: PackedFloat32Array) -> float:
	return 100.0 * (values[0] / 100.0)


func _get_buffed_value(values: PackedFloat32Array) -> float:
	return values[0]
