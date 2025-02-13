extends GutTest


const ATTRIBUTE_NAME = "my_test_attribute"


var attribute = Attribute.new()
var runtime_attribute = RuntimeAttribute.new()


func before_each() -> void:
	gut.p("before_each is resetting the test attribute")
	attribute = Attribute.new()
	attribute.attribute_name = ATTRIBUTE_NAME
	runtime_attribute = RuntimeAttribute.new()
	runtime_attribute.attribute = attribute


func test_attribute_name() -> void:
	gut.p("Tests if the attribute_name is set and read properly")
	assert_eq(attribute.attribute_name, ATTRIBUTE_NAME)
	attribute.attribute_name = "hello world"
	assert_eq(attribute.attribute_name, "hello world")


func test_attribute_min_max_values() -> void:
	gut.p("Testing initial, min and max values. Each one must not mutate another")
	assert_eq(attribute.min_value, 0.0, "default value for attribute min value is not 0")
	assert_eq(attribute.max_value, 0.0, "default value for attribute max value  is not 0")
	assert_eq(attribute.initial_value, 0.0, "default value for attribute initial value  is not 0")
	attribute.min_value = 10.0
	assert_eq(attribute.min_value, 10.0, "attribute min value is not 10")
	assert_eq(attribute.max_value, 0.0, "attribute min value is not 10")
	attribute.max_value = 20.0
	assert_eq(attribute.min_value, 10.0, "attribute min value is not 10")
	assert_eq(attribute.initial_value, 0.0, "default value for attribute initial value  is not 0")
	assert_eq(attribute.max_value, 20.0, "attribute max value is not 20")


func test_attribute_buff() -> void:
	watch_signals(runtime_attribute)
	gut.p("Testing attribute buff.")

	attribute.attribute_name = ATTRIBUTE_NAME
	attribute.max_value = 100.0
	attribute.min_value = 0.0

	gut.p("Creating attribute buff")
	var buff = AttributeBuff.new()
	buff.attribute_name = ATTRIBUTE_NAME
	buff.operation = AttributeOperation.add(5.0)
	buff.transient = true
	
	runtime_attribute.add_buff(buff)
	assert_ne(runtime_attribute.buffs.size(), 0, "a transient buff must be added to a runtime_attribute buffs array")
	assert_eq(runtime_attribute.get_buffed_value(), 5.0, "the buff have not been applied correctly")


func test_attribute_buff_transient() -> void:
	gut.p("Testing attribute buff (transient).")

	attribute.attribute_name = ATTRIBUTE_NAME
	attribute.max_value = 100.0
	attribute.min_value = 0.0

	var buff = AttributeBuff.new()
	buff.attribute_name = ATTRIBUTE_NAME
	buff.operation = AttributeOperation.add(5.0)

	assert_eq(true, false)
	runtime_attribute.add_buff(buff)
	assert_eq(runtime_attribute.buffs.size(), 1, "the buff is not applied")

	assert_eq(runtime_attribute.get_buffed_value(), 5.0, "runtime attribute value is not 5")


func test_attribute_buff__transient_limited_applications() -> void:
	watch_signals(runtime_attribute)
	gut.p("Testing attribute buff (transient).")

	attribute.attribute_name = ATTRIBUTE_NAME
	attribute.max_value = 100.0
	attribute.min_value = 0.0

	gut.p("Creating attribute buff")
	var buff = AttributeBuff.new()
	buff.attribute_name = ATTRIBUTE_NAME
	buff.operation = AttributeOperation.add(5.0)
	buff.max_applies = 2

	runtime_attribute.add_buff(buff)
	assert_eq(runtime_attribute.buffs.size(), 1, "the first buff is not applied")
	
	assert_signal_emitted(runtime_attribute, "buff_added")
	assert_eq(runtime_attribute.get_buffed_value(), 5.0, "runtime attribute value is not 5")
	
	runtime_attribute.add_buff(buff)
	assert_eq(runtime_attribute.buffs.size(), 2, "the second buff is not applied")
	
	runtime_attribute.add_buff(buff)
	assert_eq(runtime_attribute.buffs.size(), 2, "the third buff have been applied, this should not be done")

	assert_eq(runtime_attribute.get_buffed_value(), 10.0, "runtime attribute value is not 10.0")


func test_attribute_buff__transient_unique() -> void:
	watch_signals(runtime_attribute)
	gut.p("Testing attribute buff (transient).")

	attribute.attribute_name = ATTRIBUTE_NAME
	attribute.max_value = 100.0
	attribute.min_value = 0.0

	gut.p("Creating attribute buff")
	
	var buff = AttributeBuff.new()
	
	buff.attribute_name = ATTRIBUTE_NAME
	buff.operation = AttributeOperation.add(5.0)
	buff.unique = true

	runtime_attribute.add_buff(buff)
	assert_eq(runtime_attribute.buffs.size(), 1, "the first buff is not applied")
	
	assert_signal_emitted(runtime_attribute, "buff_added")
	assert_eq(runtime_attribute.get_buffed_value(), 5.0, "runtime attribute value is not 5")
	
	runtime_attribute.add_buff(buff)
	assert_eq(runtime_attribute.buffs.size(), 1, "the second buff is not applied")
	
	runtime_attribute.add_buff(buff)
	assert_eq(runtime_attribute.buffs.size(), 1, "the third buff have been applied, this should not be done")

	assert_eq(runtime_attribute.get_buffed_value(), 5.0, "runtime attribute value is not 10.0")


func test_attribute_operation() -> void:
	gut.p("Tests the operators")
	var op_add = AttributeOperation.add(5.0)
	var op_sub = AttributeOperation.subtract(5.0)
	var op_mul = AttributeOperation.multiply(5.0)
	var op_div = AttributeOperation.divide(5.0)
	var op_set = AttributeOperation.forcefully_set_value(11.0)

	assert_eq(op_add.operate(5.0), 10.0, "op_add result is wrong")
	assert_eq(op_sub.operate(10.0), 5.0, "op_sub result is wrong")
	assert_eq(op_mul.operate(2.0), 10.0, "op_mul result is wrong")
	assert_eq(op_div.operate(10.0), 2.0, "op_div result is wrong")
	assert_eq(op_set.operate(24.0), 11.0, "op_set is wrong")
