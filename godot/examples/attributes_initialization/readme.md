This example is extremely bare boned.

We add an `AttributeContainer` to the scene, 
set the `res://examples/attributes_initialization/attributes_initialization_attribute_set.tres` 
resource to it (it's an instanced `AttributeSet`)

Then in the code we create and set the buffs.

To simplify my life, I created the `res://gameplay/buffs/scripts/SetInitialValueBuff.gd` script,
extending the `AttributeBuff` class. 
