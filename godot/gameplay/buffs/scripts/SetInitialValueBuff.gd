class_name SetInitialValueBuff
extends AttributeBuff


static func create(_attribute_name: String, initial_value: float) -> AttributeBuff:
	var buff := AttributeBuff.new()

	buff.attribute_name = _attribute_name
	buff.operation		= AttributeOperation.forcefully_set_value(initial_value)

	return buff
