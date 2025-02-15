class_name ExperienceBuff
extends AttributeBuff


@export var minimum_experience: float = 1.0
@export var maximum_experience: float = 3.0


func _applies_to(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(LevelAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(ExperienceAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(NextLevelExperienceAttribute.ATTRIBUTE_NAME),
	]


func _operate(values: Array[float], _attribute_set: AttributeSet)	-> Array[AttributeOperation]:
	var new_exp					= round(randf_range(minimum_experience, maximum_experience))
	var current_level 			= values[0]
	var current_experience 		= values[1]
	var next_level_experience	= values[2]
	var experience_operation 	= AttributeOperation.add(new_exp)
	var boosted_experience		= experience_operation.operate(current_experience)

	print("Got values (LevelAttribute, ExperienceAttribute, NextLevelExperienceAttribute)", values)
	print("""
			New experience:			{0} 
			Next level experience: 	{1} 
			Current level is: 		{2}
			Should reset exp to 0: 	{3}
	""".format({
		0: boosted_experience,
		1: next_level_experience,
		2: current_level,
		3: boosted_experience >= next_level_experience
	}))

	if boosted_experience >= next_level_experience:
		return [
			AttributeOperation.add(1),
			AttributeOperation.forcefully_set_value(0),
			AttributeOperation.add(0),
		]

	return [
		AttributeOperation.add(0),
		experience_operation,
		AttributeOperation.add(0), # we do not care to alter this but we need to return it to make things work
	]
