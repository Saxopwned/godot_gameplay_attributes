class_name ToNextLevelPercentageAttribute
extends Attribute

const ATTRIBUTE_NAME := "ToNextLevelPercentageAttribute"

func _init(_attribute_name = ATTRIBUTE_NAME) -> void:
	attribute_name = _attribute_name


func _compute_value(attribute_computation: AttributeComputationArgument) -> float:
	var parent_attributes := attribute_computation.runtime_attribute.get_parent_runtime_attributes()
	var experience				:= parent_attributes[0].get_buffed_value()
	var next_level_experience	:= parent_attributes[1].get_buffed_value()

	return (experience / next_level_experience) * 100.0


func _derived_from(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(ExperienceAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(NextLevelExperience.ATTRIBUTE_NAME),
	]
