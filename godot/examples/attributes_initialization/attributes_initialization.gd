extends Control

@onready var attribute_container: AttributeContainer = $AttributeContainer
@onready var label: Label = $CenterContainer/Label


func _ready() -> void:
	label.text = "Health attribute is {0}/{1}".format({
		0: attribute_container.get_attribute_buffed_value_by_name(HealthAttribute.ATTRIBUTE_NAME),
		1: attribute_container.get_attribute_buffed_value_by_name(MaxHealthAttribute.ATTRIBUTE_NAME)
	})
