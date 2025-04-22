class_name PotionBuff
extends AttributeBuff


func _init() -> void:
	attribute_name = HealthAttribute.ATTRIBUTE_NAME
	operation = AttributeOperation.add(5)
