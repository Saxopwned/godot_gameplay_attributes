class_name ExperienceBuff
extends AttributeBuff


@export var minimum_experience: float = 1.0
@export var maximum_experience: float = 3.0


func _applies_to(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(LevelAttribute.ATTRIBUTE_NAME) as AttributeBase,
		attribute_set.find_by_name(ExperienceAttribute.ATTRIBUTE_NAME) as AttributeBase,
		attribute_set.find_by_name(NextLevelExperienceAttribute.ATTRIBUTE_NAME) as AttributeBase,
	]


func _operate(values: Array[float], attribute_set: AttributeSet)	-> Array[AttributeOperation]:
	var new_exp									= randf_range(minimum_experience, maximum_experience)
	var operations: Array[AttributeOperation] 	= []
	var current_level 							= values[0]
	var current_experience 						= values[1]
	var next_level_experience					= values[2]
	var level_operation 							= AttributeOperation.add(0)
	var experience_operation 					= AttributeOperation.add(new_exp)

	if experience_operation.operate(current_experience) >= next_level_experience:
		level_operation.value = 1
		## we need to subtract the current value to reset it
		experience_operation = AttributeOperation.forcefully_set_value(0)

	return [
		level_operation,
		experience_operation,
		AttributeOperation.add(0), # we do not care to alter this but we need to return it to make things work
	]
