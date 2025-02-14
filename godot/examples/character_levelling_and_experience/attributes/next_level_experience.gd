class_name NextLevelExperienceAttribute
extends Attribute

const ATTRIBUTE_NAME 		:= "NextLevelExperienceAttribute"
const EXPERIENCE_PER_LEVEL 	:= 20.0
const SCALE 				:= 1.5


func calculate_next(current_level: float) -> float:
	return round(((current_level * SCALE) ** 1.5) * EXPERIENCE_PER_LEVEL)


func _init(_attribute_name := ATTRIBUTE_NAME) -> void:
	attribute_name = _attribute_name


func _derived_from(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(LevelAttribute.ATTRIBUTE_NAME),
	]


func _get_buffed_value(values: PackedFloat32Array) -> float:
	return calculate_next(values[0])


func _get_initial_value(values: PackedFloat32Array) -> float:
	return calculate_next(values[0])


func _get_min_value(_attribute_set: AttributeSet) -> float:
	return 0.0
