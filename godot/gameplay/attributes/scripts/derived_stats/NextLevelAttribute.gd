class_name NextLevelAttribute
extends Attribute

const ATTRIBUTE_NAME = "NextLevelAttribute"

func _init(_attribute_name = ATTRIBUTE_NAME) -> void:
	attribute_name = _attribute_name


func _compute_value(_compute_value: AttributeComputationArgument) -> float:
	var parent_attributes = _compute_value.runtime_attribute.get_parent_runtime_attributes()
	var level = parent_attributes[0].get_buffed_value()
	
	### we are setting the max level to 100
	return clampf(level + 1.0, 0.0, 100.0)
	
	
func _derived_from(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(LevelAttribute.ATTRIBUTE_NAME)
	]
