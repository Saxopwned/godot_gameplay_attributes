extends Control

var attribute: RuntimeAttribute = null

@onready var attribute_name_label: Label = %AttributeNameLabel
@onready var attribute_value_label: Label = %AttributeValueLabel


func update() -> void:
	if attribute != null and attribute.attribute != null:
		attribute_name_label.text = attribute.attribute.attribute_name
		attribute_value_label.text = String.num(attribute.get_buffed_value(), 2)
