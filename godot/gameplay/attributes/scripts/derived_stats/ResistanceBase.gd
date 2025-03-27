class_name ResistanceBase
extends Attribute


func _compute_value(attribute_computation: AttributeComputationArgument) -> float:
	return attribute_computation.get_parent_attributes()[0].get_buffed_value() / 20
	

func _derived_from(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(IntelligenceAttribute.ATTRIBUTE_NAME)
	]
