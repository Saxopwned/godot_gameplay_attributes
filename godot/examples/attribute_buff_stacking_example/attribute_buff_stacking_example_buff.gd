class_name AttributeBuffStackingExample
extends AttributeBuff

enum ExampleBuffType {
	MaxStackCount,
	InfiniteStack,
	TimeReset,
	UniqueBuff
}


const names = {
	ExampleBuffType.MaxStackCount: "MaxStackCount",
	ExampleBuffType.InfiniteStack: "InfiniteStack",
	ExampleBuffType.TimeReset: "TimeReset",
	ExampleBuffType.UniqueBuff: "UniqueBuff",
}


var _buff_type: ExampleBuffType
var buff_type: ExampleBuffType:
	get:
		return buff_type
	set(value):
		buff_type = value
		buff_name = names[buff_type]
		
		match buff_type:
			ExampleBuffType.MaxStackCount: 
				stack_size = 5
			ExampleBuffType.TimeReset: 
				duration = 3.0 # three seconds should be enough
				duration_merging = AttributeBuff.DURATION_MERGE_RESTART
			ExampleBuffType.UniqueBuff:
				unique = true
		


func _init():
	attribute_name = HealthAttribute.ATTRIBUTE_NAME
	transient = true


func _applies_to(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(HealthAttribute.ATTRIBUTE_NAME)
	]
	
	
func _operate(_values: Array[float], _attribute_set: AttributeSet) -> Array[AttributeOperation]:
	return [
		AttributeOperation.add(1.0)	
	]
