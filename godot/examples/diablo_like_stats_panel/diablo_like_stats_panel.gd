extends HBoxContainer


@onready var attribute_container: AttributeContainer = $AttributeContainer


func _ready() -> void:
	attribute_container.apply_buff(SetInitialValueBuff.create(DexterityAttribute.ATTRIBUTE_NAME, 5.0))
	attribute_container.apply_buff(SetInitialValueBuff.create(IntelligenceAttribute.ATTRIBUTE_NAME, 5.0))
	attribute_container.apply_buff(SetInitialValueBuff.create(StrengthAttribute.ATTRIBUTE_NAME, 5.0))
	attribute_container.apply_buff(SetInitialValueBuff.create(WillpowerAttribute.ATTRIBUTE_NAME, 5.0))
