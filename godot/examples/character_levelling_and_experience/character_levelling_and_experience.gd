extends Control

@onready var current_level: Label = %CurrentLevel
@onready var next_level: Label = %NextLevel
@onready var attribute_container: AttributeContainer = %AttributeContainer
@onready var increase_experience: Button = %IncreaseExperience
@onready var minimum_value: SpinBox = %MinimumValue
@onready var maximum_value: SpinBox = %MaximumValue
@onready var current_experience: Label = %CurrentExperience
@onready var next_level_experience: Label = %NextLevelExperience


func update_view() -> void:
	current_level.text = "Level: " + _get_attr(LevelAttribute)
	next_level.text = "Next level: " + _get_attr(NextLevelAttribute)
	current_experience.text = "Current experience: " + _get_attr(ExperienceAttribute)
	next_level_experience.text = "Experience needed for next level: " + _get_attr(NextLevelExperienceAttribute)


func _get_attr(attr_class: Variant) -> String:
	return str(int(attribute_container.get_attribute_buffed_value_by_name(attr_class.ATTRIBUTE_NAME)))

func _ready() -> void:
	attribute_container.attribute_changed.connect(_handle_attribute_changed)
	increase_experience.pressed.connect(_handle_increase_experience)
	minimum_value.value = 1.0
	maximum_value.value = 3.0
	update_view()


func _handle_attribute_changed(attribute: RuntimeAttribute, previous_value: float, new_value: float) -> void:
	print("Attribute {0} updated with new value {1}. Older value is {2}".format({
		0: attribute.attribute.attribute_name,
		1: new_value,
		2: previous_value
	}))
	update_view()


func _handle_increase_experience() -> void:
	var the_magic_attribute_buff := ExperienceBuff.new()
	the_magic_attribute_buff.minimum_experience = minimum_value.value
	the_magic_attribute_buff.maximum_experience = maximum_value.value
	attribute_container.apply_buff(the_magic_attribute_buff)
