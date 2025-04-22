@tool
class_name ApplyDamageBuff
extends AttributeBuff

@export_enum("Darkness", "Fire", "Lightning", "Physical", "Poison") var damage_type := 0:
	get:
		match attribute_name:
			DamageDarknessAttribute.ATTRIBUTE_NAME: return 0
			DamageFireAttribute.ATTRIBUTE_NAME: return 1
			DamageLightningAttribute.ATTRIBUTE_NAME: return 2
			DamagePhysicalAttribute.ATTRIBUTE_NAME: return 3
			DamagePoisonAttribute.ATTRIBUTE_NAME: return 4
		assert(false, "Invalid damage type")
		return 0
	set(value):
		match value:
			0: attribute_name = DamageDarknessAttribute.ATTRIBUTE_NAME
			1: attribute_name = DamageFireAttribute.ATTRIBUTE_NAME
			2: attribute_name = DamageLightningAttribute.ATTRIBUTE_NAME
			3: attribute_name = DamagePhysicalAttribute.ATTRIBUTE_NAME
			4: attribute_name = DamagePoisonAttribute.ATTRIBUTE_NAME
			
@export_range(0.0, 1000.0, 0.1) var damage_range: float = 1.0:
	get:
		return operation.value
	set(value):
		operation = AttributeOperation.add(value)
