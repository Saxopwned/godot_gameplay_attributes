class_name InitializeAttributes
extends AttributeBuff


func _applies_to(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(LevelAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(DexterityAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(IntelligenceAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(StrengthAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(WillpowerAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(MaxHealthAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(ResourceAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(MaxResourceAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(HealthAttribute.ATTRIBUTE_NAME),
	]


func _operate(_values: Array[float], _attribute_set: AttributeSet) -> Array[AttributeOperation]:
	### Since we are going to set them directly, we should not overthink with calculations
	### Bear in mind that you should always set base attributes first, derived later
	
	return [
		AttributeOperation.forcefully_set_value(1.0),
		AttributeOperation.forcefully_set_value(5.0),
		AttributeOperation.forcefully_set_value(5.0),
		AttributeOperation.forcefully_set_value(5.0),
		AttributeOperation.forcefully_set_value(5.0),
		AttributeOperation.forcefully_set_value(10.0),
		AttributeOperation.forcefully_set_value(5.0),
		AttributeOperation.forcefully_set_value(10.0),
		AttributeOperation.forcefully_set_value(5.0),
	]
