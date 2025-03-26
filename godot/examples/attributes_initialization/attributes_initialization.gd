extends Control

@onready var attribute_container: AttributeContainer = $AttributeContainer
@onready var label: Label = $CenterContainer/Label


func _ready() -> void:
	### IMPORTANT: order matter when you initialize your attributes! 
	### Always buff the "base" attributes first, the derived later.
	### I will find a smart way to overcome this issue in the future releases without creating
	### a memory hungry monster.
	attribute_container.apply_buff(SetInitialValueBuff.create(MaxHealthAttribute.ATTRIBUTE_NAME, 10.0))
	attribute_container.apply_buff(SetInitialValueBuff.create(HealthAttribute.ATTRIBUTE_NAME, 10.0))

	# oh yes, the output
	label.text = "Health attribute is {0}/{1} (health/max health)".format({
		0: attribute_container.get_attribute_value_by_name(HealthAttribute.ATTRIBUTE_NAME),
		1: attribute_container.get_attribute_value_by_name(MaxHealthAttribute.ATTRIBUTE_NAME)
	})
