class_name WeaponDamageBuff
extends AttributeBuff

var damage_array 	:= [0.0, 5.0, 10.0, 20.0]
var speed_array 	:= [2.0, 1.4, 1.2, 0.9]
var weapon_type 	:= 0.0

func _init(_weapon_type: float) -> void:
	attribute_name = WeaponDamageAttribute.ATTRIBUTE_NAME
	buff_name = "WeaponDamageBuff"
	weapon_type = _weapon_type
	
	
func _applies_to(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(WeaponDamageAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(WeaponSpeedAttribute.ATTRIBUTE_NAME)
	]
	
	
func _operate(_values: Array[float], _attribute_set: AttributeSet) -> Array[AttributeOperation]:
	var weapon_damage	:float = damage_array[weapon_type]
	var weapon_speed	:float = speed_array[weapon_type]
	
	return [
		AttributeOperation.forcefully_set_value(weapon_damage),
		AttributeOperation.forcefully_set_value(weapon_speed)
	]
