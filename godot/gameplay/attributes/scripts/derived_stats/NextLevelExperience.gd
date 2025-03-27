class_name NextLevelExperience
extends Attribute


const ATTRIBUTE_NAME 		:= "NextLevelExperienceAttribute"
const EXPERIENCE_PER_LEVEL 	:= 20.0
const SCALE 				:= 1.5


func _init(_attribute_name = ATTRIBUTE_NAME) -> void:
	attribute_name = _attribute_name


func _compute_value(_compute_value: AttributeComputationArgument) -> float:
	var parent_attributes := _compute_value.runtime_attribute.get_parent_runtime_attributes()
	var current_level = parent_attributes[0].get_buffed_value()
	
	return round(((current_level * SCALE) ** 1.5) * EXPERIENCE_PER_LEVEL)


func _derived_from(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(LevelAttribute.ATTRIBUTE_NAME)
	]
