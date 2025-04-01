## yep, straight from a diablo-like game
## yep, I am really bad at giving names sometimes
class_name ResistanceNerfDueToDifficultyLevelBuff 
extends AttributeBuff


func _init():
	stack_size = 3


func _applies_to(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(ResistanceDarkness.ATTRIBUTE_NAME),
		attribute_set.find_by_name(ResistanceFire.ATTRIBUTE_NAME),
		attribute_set.find_by_name(ResistanceLightning.ATTRIBUTE_NAME),
		attribute_set.find_by_name(ResistancePoison.ATTRIBUTE_NAME),
	]


func _operate(values: Array[float], _attribute_set: AttributeSet) -> Array[AttributeOperation]:
	var new_arr: Array[AttributeOperation] = []

	new_arr.resize(values.size())
	new_arr.fill(AttributeOperation.subtract(30))
	
	return new_arr
