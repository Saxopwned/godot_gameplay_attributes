/**************************************************************************/
/*  attribute.cpp                                                         */
/**************************************************************************/
/*                         This file is part of:                          */
/*                        Godot Gameplay Systems                          */
/*              https://github.com/OctoD/godot-gameplay-systems           */
/**************************************************************************/
/* Read the license file in this repo.						              */
/**************************************************************************/

#include "attribute.hpp"
#include "attribute_container.hpp"

using namespace gga;

#pragma region AttributeOperation

void AttributeOperation::_bind_methods()
{
	/// binds methods to godot
	ClassDB::bind_method(D_METHOD("get_operand"), &AttributeOperation::get_operand);
	ClassDB::bind_method(D_METHOD("get_value"), &AttributeOperation::get_value);
	ClassDB::bind_method(D_METHOD("operate", "base_value"), &AttributeOperation::operate);
	ClassDB::bind_method(D_METHOD("set_operand", "p_value"), &AttributeOperation::set_operand);
	ClassDB::bind_method(D_METHOD("set_value", "p_value"), &AttributeOperation::set_value);

	/// binds static methods to godot
	ClassDB::bind_static_method("AttributeOperation", D_METHOD("add", "p_value"), &AttributeOperation::add);
	ClassDB::bind_static_method("AttributeOperation", D_METHOD("divide", "p_value"), &AttributeOperation::divide);
	ClassDB::bind_static_method("AttributeOperation", D_METHOD("multiply", "p_value"), &AttributeOperation::multiply);
	ClassDB::bind_static_method("AttributeOperation", D_METHOD("percentage", "p_value"), &AttributeOperation::percentage);
	ClassDB::bind_static_method("AttributeOperation", D_METHOD("subtract", "p_value"), &AttributeOperation::subtract);
	ClassDB::bind_static_method("AttributeOperation", D_METHOD("forcefully_set_value", "p_value"), &AttributeOperation::forcefully_set_value);

	/// binds properties
	ADD_PROPERTY(PropertyInfo(Variant::INT, "operand", PROPERTY_HINT_ENUM, "Add:0,Divide:1,Multiply:2,Percentage:3,Subtract:4,Set:5"), "set_operand", "get_operand");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "value"), "set_value", "get_value");

	/// binds enum as consts
	BIND_ENUM_CONSTANT(OP_ADD);
	BIND_ENUM_CONSTANT(OP_DIVIDE);
	BIND_ENUM_CONSTANT(OP_MULTIPLY);
	BIND_ENUM_CONSTANT(OP_PERCENTAGE);
	BIND_ENUM_CONSTANT(OP_SUBTRACT);
	BIND_ENUM_CONSTANT(OP_SET);
}

Ref<AttributeOperation> AttributeOperation::create(const OperationType p_operand, const float p_value)
{
	Ref operation = memnew(AttributeOperation);
	operation->set_operand(p_operand);
	operation->set_value(p_value);
	return operation;
}

bool AttributeOperation::operator==(const Ref<AttributeOperation> &buff) const
{
	return operand == buff->operand && value == buff->value;
}

Ref<AttributeOperation> AttributeOperation::add(const float p_value)
{
	return create(OP_ADD, p_value);
}

Ref<AttributeOperation> AttributeOperation::divide(const float p_value)
{
	return create(OP_DIVIDE, p_value);
}

Ref<AttributeOperation> AttributeOperation::multiply(const float p_value)
{
	return create(OP_MULTIPLY, p_value);
}

Ref<AttributeOperation> AttributeOperation::percentage(const float p_value)
{
	return create(OP_PERCENTAGE, p_value);
}

Ref<AttributeOperation> AttributeOperation::subtract(const float p_value)
{
	return create(OP_SUBTRACT, p_value);
}

Ref<AttributeOperation> AttributeOperation::forcefully_set_value(const float p_value)
{
	return create(OP_SET, p_value);
}

int AttributeOperation::get_operand() const
{
	return operand;
}

float AttributeOperation::get_value() const
{
	return value;
}

float AttributeOperation::operate(float p_base_value) const
{
	switch (operand) {
		case OP_ADD:
			return p_base_value + value;
		case OP_DIVIDE:
			return Math::absf(value) < 0.0001f ? 0 : p_base_value / value;
		case OP_MULTIPLY:
			return p_base_value * value;
		case OP_PERCENTAGE:
			return p_base_value + ((p_base_value / 100) * value);
		case OP_SUBTRACT:
			return p_base_value - value;
		case OP_SET:
			return value;
		default:
			return p_base_value;
	}
}

void AttributeOperation::set_operand(const int p_value)
{
	switch (p_value) {
		case 0:
			operand = OP_ADD;
			break;
		case 1:
			operand = OP_DIVIDE;
			break;
		case 2:
			operand = OP_MULTIPLY;
			break;
		case 3:
			operand = OP_PERCENTAGE;
			break;
		case 4:
			operand = OP_SUBTRACT;
			break;
		case 5:
			operand = OP_SET;
			break;
		default:
			operand = OP_ADD;
			break;
	}
}

void AttributeOperation::set_value(const float p_value)
{
	value = p_value;
}

#pragma endregion

#pragma region AttributeBuffBase

void AttributeBuffBase::_bind_methods()
{
	/// binds virtuals to godot
	GDVIRTUAL_BIND(_applies_to, "attribute_set");
	GDVIRTUAL_BIND(_operate, "values", "attribute_set");
}

#pragma endregion

#pragma region AttributeBuff

void AttributeBuff::_bind_methods()
{
	/// binds methods to godot
	ClassDB::bind_method(D_METHOD("get_attribute_name"), &AttributeBuff::get_attribute_name);
	ClassDB::bind_method(D_METHOD("get_buff_name"), &AttributeBuff::get_buff_name);
	ClassDB::bind_method(D_METHOD("get_duration"), &AttributeBuff::get_duration);
	ClassDB::bind_method(D_METHOD("get_operation"), &AttributeBuff::get_operation);
	ClassDB::bind_method(D_METHOD("get_max_applies"), &AttributeBuff::get_max_applies);
	ClassDB::bind_method(D_METHOD("get_transient"), &AttributeBuff::get_transient);
	ClassDB::bind_method(D_METHOD("get_unique"), &AttributeBuff::get_unique);
	ClassDB::bind_method(D_METHOD("operate", "base_value"), &AttributeBuff::operate);
	ClassDB::bind_method(D_METHOD("set_attribute_name", "p_value"), &AttributeBuff::set_attribute_name);
	ClassDB::bind_method(D_METHOD("set_buff_name", "p_value"), &AttributeBuff::set_buff_name);
	ClassDB::bind_method(D_METHOD("set_duration", "p_value"), &AttributeBuff::set_duration);
	ClassDB::bind_method(D_METHOD("set_operation", "p_value"), &AttributeBuff::set_operation);
	ClassDB::bind_method(D_METHOD("set_max_applies", "p_value"), &AttributeBuff::set_max_applies);
	ClassDB::bind_method(D_METHOD("set_transient", "p_value"), &AttributeBuff::set_transient);
	ClassDB::bind_method(D_METHOD("set_unique", "p_value"), &AttributeBuff::set_unique);

	/// binds properties to godot
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "attribute_name"), "set_attribute_name", "get_attribute_name");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "buff_name"), "set_buff_name", "get_buff_name");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "duration"), "set_duration", "get_duration");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "operation", PROPERTY_HINT_RESOURCE_TYPE, "AttributeOperation"), "set_operation", "get_operation");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_applies"), "set_max_applies", "get_max_applies");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "transient"), "set_transient", "get_transient");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "unique"), "set_unique", "get_unique");
}

bool AttributeBuff::operator==(const Ref<AttributeBuff> &buff) const
{
	return buff->attribute_name == attribute_name && buff->buff_name == buff_name && buff->duration == duration && buff->operation == operation;
}

float AttributeBuff::operate(float base_value) const
{
	ERR_FAIL_COND_V_MSG(operation.is_null(), 0.0f, "AttributeBuff operation is null, cannot operate on base value.");
	return operation->operate(base_value);
}

String AttributeBuff::get_attribute_name() const
{
	return attribute_name;
}

String AttributeBuff::get_buff_name() const
{
	return buff_name;
}

float AttributeBuff::get_duration() const
{
	return duration;
}

bool AttributeBuff::get_transient() const
{
	if (Math::is_zero_approx(duration)) {
		return transient;
	}

	return !Math::is_equal_approx(duration, 0.05f);
}

bool AttributeBuff::get_unique() const
{
	return unique;
}

bool AttributeBuff::is_operate_overridden() const
{
	return GDVIRTUAL_IS_OVERRIDDEN_PTR(this, _operate);
}

Ref<AttributeOperation> AttributeBuff::get_operation() const
{
	return operation;
}

int AttributeBuff::get_max_applies() const
{
	return max_applies;
}

bool AttributeBuff::is_time_limited() const
{
	return Math::absf(1.0f - duration) > 0.0001f;
}

void AttributeBuff::set_attribute_name(const String &p_value)
{
	attribute_name = p_value;
}

void AttributeBuff::set_buff_name(const String &p_value)
{
	buff_name = p_value;
}

void AttributeBuff::set_duration(const float p_value)
{
	duration = p_value;
}

void AttributeBuff::set_operation(const Ref<AttributeOperation> &p_value)
{
	operation = p_value;
}

void AttributeBuff::set_max_applies(const int p_value)
{
	max_applies = p_value;
}

void AttributeBuff::set_transient(const bool p_value)
{
	transient = p_value;
}

void AttributeBuff::set_unique(const bool p_value)
{
	unique = p_value;
}

#pragma endregion

#pragma region AttributeBase

void AttributeBase::_bind_methods()
{
	/// binds methods to godot
	ClassDB::bind_method(D_METHOD("get_attribute_name"), &AttributeBase::get_attribute_name);
	ClassDB::bind_method(D_METHOD("get_buffs"), &AttributeBase::get_buffs);
	ClassDB::bind_method(D_METHOD("set_attribute_name", "p_value"), &AttributeBase::set_attribute_name);
	ClassDB::bind_method(D_METHOD("set_buffs", "p_buffs"), &AttributeBase::set_buffs);

	/// binds virtuals to godot
	GDVIRTUAL_BIND(_constrained_by, "attribute_set");
	GDVIRTUAL_BIND(_derived_from, "attribute_set");
	GDVIRTUAL_BIND(_get_buffed_value, "values");
	GDVIRTUAL_BIND(_get_constrained_value, "buffed_value", "buffed_values", "previous_values");
	GDVIRTUAL_BIND(_get_initial_value, "values");

	/// binds properties to godot
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "attribute_name"), "set_attribute_name", "get_attribute_name");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "buffs"), "set_buffs", "get_buffs");
}

String AttributeBase::get_attribute_name() const
{
	if (attribute_name.is_empty()) {
		return get_class_static();
	}

	return attribute_name;
}

float AttributeBase::get_initial_value() const{
	return 0.0f;
}

TypedArray<AttributeBuff> AttributeBase::get_buffs() const
{
	return buffs;
}

void AttributeBase::set_attribute_name(const String &p_value)
{
	attribute_name = p_value;
}

void AttributeBase::set_buffs(const TypedArray<AttributeBuff> &p_buffs)
{
	buffs = p_buffs;
}

#pragma endregion

#pragma region Attribute

void Attribute::_bind_methods()
{
	/// static methods to bind to godot
	ClassDB::bind_static_method("Attribute", D_METHOD("create", "attribute_name", "initial_value"), &Attribute::create);

	/// binds methods to godot
	ClassDB::bind_method(D_METHOD("get_initial_value"), &Attribute::get_initial_value);
	ClassDB::bind_method(D_METHOD("set_initial_value", "p_value"), &Attribute::set_initial_value);

	/// properties to bind to godot
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "initial_value"), "set_initial_value", "get_initial_value");
}

Ref<Attribute> Attribute::create(const String &p_attribute_name, const float p_initial_value)
{
	Ref attribute = memnew(Attribute);
	attribute->set_attribute_name(p_attribute_name);
	attribute->set_initial_value(p_initial_value);
	return attribute;
}

float Attribute::get_initial_value() const
{
	return initial_value;
}

void Attribute::set_initial_value(const float p_value)
{
	initial_value = p_value;
}

#pragma endregion

#pragma region AttributeSet

void AttributeSet::_bind_methods()
{
	/// binds methods to godot
	ClassDB::bind_method(D_METHOD("add_attribute", "p_attribute"), &AttributeSet::add_attribute);
	ClassDB::bind_method(D_METHOD("add_attributes", "p_attributes"), &AttributeSet::add_attributes);
	ClassDB::bind_method(D_METHOD("find_by_classname", "p_classname"), &AttributeSet::find_by_classname);
	ClassDB::bind_method(D_METHOD("find_by_name", "p_name"), &AttributeSet::find_by_name);
	ClassDB::bind_method(D_METHOD("get_attributes_names"), &AttributeSet::get_attributes_names);
	ClassDB::bind_method(D_METHOD("get_attributes"), &AttributeSet::get_attributes);
	ClassDB::bind_method(D_METHOD("get_set_name"), &AttributeSet::get_set_name);
	ClassDB::bind_method(D_METHOD("has_attribute", "p_attribute"), &AttributeSet::has_attribute);
	ClassDB::bind_method(D_METHOD("remove_attribute", "p_attribute"), &AttributeSet::remove_attribute);
	ClassDB::bind_method(D_METHOD("remove_attributes", "p_attributes"), &AttributeSet::remove_attributes);
	ClassDB::bind_method(D_METHOD("set_attributes", "p_attributes"), &AttributeSet::set_attributes);
	ClassDB::bind_method(D_METHOD("set_set_name", "p_value"), &AttributeSet::set_set_name);

	/// binds properties to godot
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes", PROPERTY_HINT_RESOURCE_TYPE, "24/17:AttributeBase"), "set_attributes", "get_attributes");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "set_name"), "set_set_name", "get_set_name");

	/// adds signals to godot
	ADD_SIGNAL(MethodInfo("attribute_added", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "AttributeBase")));
	ADD_SIGNAL(MethodInfo("attribute_removed", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "AttributeBase")));
}

bool AttributeSet::operator==(const Ref<AttributeSet> &set) const
{
	if (attributes.size() != set->attributes.size()) {
		return false;
	}

	if (set_name != set->set_name) {
		return false;
	}

	for (int i = 0; i < attributes.size(); i++) {
		if (attributes[i] != set->attributes[i]) {
			return false;
		}
	}

	return true;
}

AttributeSet::AttributeSet()
{
	attributes = TypedArray<AttributeBase>();
}

AttributeSet::AttributeSet(const TypedArray<AttributeBase> &p_attributes, const String &p_set_name)
{
	attributes = p_attributes.duplicate(true);
	set_name = p_set_name;
}

bool AttributeSet::add_attribute(const Ref<AttributeBase> &p_attribute)
{
	if (!has_attribute(p_attribute)) {
		const Ref<Attribute> d_attribute = p_attribute->duplicate(true);

		attributes.push_back(d_attribute);
		emit_signal("attribute_added", d_attribute);
		emit_changed();
		return true;
	}

	return false;
}

uint16_t AttributeSet::add_attributes(const TypedArray<AttributeBase> &p_attributes)
{
	uint16_t count = 0;

	for (int i = 0; i < p_attributes.size(); i++) {
		if (!has_attribute(p_attributes[i])) {
			Ref<AttributeBase> d_attribute = p_attributes[i];

			d_attribute = d_attribute->duplicate(true);

			attributes.push_back(d_attribute);
			count++;
			emit_signal("attribute_added", d_attribute);
		}
	}

	if (count > 0) {
		emit_changed();
	}

	return count;
}

int AttributeSet::find(const Ref<AttributeBase> &p_attribute) const
{
	return static_cast<int>(attributes.find(p_attribute));
}

Ref<AttributeBase> AttributeSet::find_by_classname(const String &p_classname) const
{
	for (int i = 0; i < attributes.size(); i++) {

		if (const Ref<AttributeBase> attribute = attributes[i]; attribute->get_class() == p_classname) {
			return attributes[i];
		}
	}

	return Ref<Attribute>();
}

Ref<AttributeBase> AttributeSet::find_by_name(const String &p_name) const
{
	for (int i = 0; i < attributes.size(); i++) {

		if (const Ref<AttributeBase> attribute = attributes[i]; attribute->get_attribute_name() == p_name) {
			return attributes[i];
		}
	}

	return {};
}

PackedStringArray AttributeSet::get_attributes_names() const
{
	PackedStringArray names;

	for (int i = 0; i < attributes.size(); i++) {
		const Ref<AttributeBase> attribute = attributes[i];
		names.push_back(attribute->get_attribute_name());
	}

	return names;
}

TypedArray<AttributeBase> AttributeSet::get_attributes() const
{
	return attributes;
}

Ref<AttributeBase> AttributeSet::get_at(int index) const
{
	if (index >= 0 && index < attributes.size()) {
		return attributes[index];
	}

	return Ref<Attribute>();
}

String AttributeSet::get_set_name() const
{
	return set_name;
}

bool AttributeSet::has_attribute(const Ref<AttributeBase> &p_attribute) const
{
	for (int i = 0; i < attributes.size(); i++) {
		if (attributes[i] == p_attribute) {
			return true;
		}
	}

	return false;
}

bool AttributeSet::remove_attribute(const Ref<AttributeBase> &p_attribute)
{

	if (const int64_t index = attributes.find(p_attribute); index != -1) {
		attributes.remove_at(index);
		emit_signal("attribute_removed", p_attribute);
		emit_changed();
		return true;
	}

	return false;
}

int AttributeSet::remove_attributes(const TypedArray<AttributeBase> &p_attributes)
{
	int count = 0;

	for (int i = 0; i < p_attributes.size(); i++) {
		if (const int64_t index = attributes.find(p_attributes[i]);index != -1) {
			attributes.remove_at(index);
			count++;
			emit_signal("attribute_removed", p_attributes[i]);
		}
	}

	if (count > 0) {
		emit_changed();
	}

	return count;
}

void AttributeSet::push_back(const Ref<AttributeBase> &p_attribute)
{
	attributes.push_back(p_attribute);
	emit_signal("attribute_added", p_attribute);
	emit_changed();
}

void AttributeSet::set_attributes(const TypedArray<AttributeBase> &p_attributes)
{
	attributes = p_attributes;
	emit_changed();
}

void AttributeSet::set_set_name(const String &p_value)
{
	set_name = p_value;
	emit_changed();
}

int AttributeSet::count() const
{
	return static_cast<int>(attributes.size());
}

#pragma endregion

#pragma region BuffPoolQueueItem

void RuntimeBuff::_bind_methods()
{
	/// binds methods to godot
	ClassDB::bind_static_method("RuntimeBuff", D_METHOD("from_buff", "p_buff"), &RuntimeBuff::from_buff);
	ClassDB::bind_static_method("RuntimeBuff", D_METHOD("to_buff", "p_buff"), &RuntimeBuff::to_buff);
	ClassDB::bind_method(D_METHOD("get_attribute_name"), &RuntimeBuff::get_attribute_name);
	ClassDB::bind_method(D_METHOD("get_buff_name"), &RuntimeBuff::get_buff_name);
	ClassDB::bind_method(D_METHOD("get_duration"), &RuntimeBuff::get_duration);
	ClassDB::bind_method(D_METHOD("get_time_left"), &RuntimeBuff::get_time_left);
	ClassDB::bind_method(D_METHOD("set_time_left", "p_value"), &RuntimeBuff::set_time_left);
	ClassDB::bind_method(D_METHOD("get_buff"), &RuntimeBuff::get_buff);
	ClassDB::bind_method(D_METHOD("set_buff", "p_value"), &RuntimeBuff::set_buff);

	/// binds properties to godot
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "AttributeBuff"), "set_buff", "get_buff");
}

bool RuntimeBuff::equals_to(const Ref<AttributeBuff> &p_buff) const
{
	return buff == p_buff;
}

Ref<RuntimeAttribute> RuntimeBuff::applies_to(const AttributeContainer *p_attribute_container) const
{
	Ref<RuntimeAttribute> attribute = p_attribute_container->get_attribute_by_name(buff->get_attribute_name());

	ERR_FAIL_COND_V_MSG(attribute.is_null(), attribute, "Attribute not found in attribute set.");
	ERR_FAIL_COND_V_MSG(!attribute.is_valid(), attribute, "Attribute reference is not valid.");

	return attribute;
}

float RuntimeBuff::operate(const Ref<RuntimeAttribute> &p_runtime_attribute) const
{
	ERR_FAIL_COND_V_MSG(!buff.is_valid(), 0.0f, "Buff is not valid, cannot operate on runtime attributes.");
	ERR_FAIL_NULL_V_MSG(p_runtime_attribute, 0.0f, "Runtime attribute is null, cannot operate on it.");

	return buff->operate(p_runtime_attribute->value);
}

Ref<RuntimeBuff> RuntimeBuff::from_buff(const Ref<AttributeBuff> &p_buff)
{
	Ref runtime_buff = memnew(RuntimeBuff);
	runtime_buff->buff = p_buff;
	runtime_buff->time_left = p_buff->get_duration();
	return runtime_buff;
}

Ref<AttributeBuff> RuntimeBuff::to_buff(const Ref<RuntimeBuff> &p_buff)
{
	return p_buff->buff;
}

bool RuntimeBuff::operator==(const Ref<AttributeBuff> &p_attribute_buff) const
{
	return equals_to(p_attribute_buff);
}

bool RuntimeBuff::operator==(const Ref<RuntimeBuff> &p_runtime_buff) const
{
	return buff == p_runtime_buff->buff && time_left == p_runtime_buff->time_left;
}

bool RuntimeBuff::can_apply_to_attribute(const Ref<RuntimeAttribute> &p_attribute) const
{
	Ref<RuntimeAttribute> applied_to = applies_to(p_attribute->attribute_container);

	ERR_FAIL_NULL_V_MSG(applied_to, false, "Attribute not found in attribute set.");
	ERR_FAIL_COND_V_MSG(!applied_to.is_valid(), false, "Attribute reference is not valid.");

	return applied_to->attribute->get_attribute_name() == p_attribute->attribute->get_attribute_name();
}

bool RuntimeBuff::can_dequeue() const
{
	return Math::is_zero_approx(time_left);
}

String RuntimeBuff::get_attribute_name() const
{
	return buff->attribute_name;
}

String RuntimeBuff::get_buff_name() const
{
	return buff->buff_name;
}

Ref<AttributeBuff> RuntimeBuff::get_buff() const
{
	return buff;
}

float RuntimeBuff::get_duration() const
{
	return buff->duration;
}

float RuntimeBuff::get_time_left() const
{
	return time_left;
}

bool RuntimeBuff::is_operate_overridden() const
{
	return GDVIRTUAL_IS_OVERRIDDEN_PTR(buff, _operate);
}

void RuntimeBuff::set_buff(const Ref<AttributeBuff> &p_value)
{
	buff = p_value;
}

void RuntimeBuff::set_time_left(const float p_value)
{
	time_left = p_value;
}

#pragma endregion

#pragma region RuntimeAttributeBase

void RuntimeAttribute::_bind_methods()
{
	/// binds methods to godot
	ClassDB::bind_method(D_METHOD("add_buff", "p_buff"), &RuntimeAttribute::add_buff);
	ClassDB::bind_method(D_METHOD("add_buffs", "p_buffs"), &RuntimeAttribute::add_buffs);
	ClassDB::bind_method(D_METHOD("can_receive_buff", "p_buff"), &RuntimeAttribute::can_receive_buff);
	ClassDB::bind_method(D_METHOD("clear_buffs"), &RuntimeAttribute::clear_buffs);
	ClassDB::bind_method(D_METHOD("get_attribute"), &RuntimeAttribute::get_attribute);
	ClassDB::bind_method(D_METHOD("get_attribute_set"), &RuntimeAttribute::get_attribute_set);
	ClassDB::bind_method(D_METHOD("get_buffed_value"), &RuntimeAttribute::get_buffed_value);
	ClassDB::bind_method(D_METHOD("get_buffs"), &RuntimeAttribute::get_buffs);
	ClassDB::bind_method(D_METHOD("get_constrained_by"), &RuntimeAttribute::get_constrained_by);
	ClassDB::bind_method(D_METHOD("get_constrained_value"), &RuntimeAttribute::get_constrained_value);
	ClassDB::bind_method(D_METHOD("get_derived_from"), &RuntimeAttribute::get_derived_from);
	ClassDB::bind_method(D_METHOD("get_initial_value"), &RuntimeAttribute::get_initial_value);
	ClassDB::bind_method(D_METHOD("get_value"), &RuntimeAttribute::get_value);
	ClassDB::bind_method(D_METHOD("remove_buff", "p_buff"), &RuntimeAttribute::remove_buff);
	ClassDB::bind_method(D_METHOD("remove_buffs", "p_buffs"), &RuntimeAttribute::remove_buffs);
	ClassDB::bind_method(D_METHOD("set_attribute", "p_value"), &RuntimeAttribute::set_attribute);
	ClassDB::bind_method(D_METHOD("set_attribute_set", "p_value"), &RuntimeAttribute::set_attribute_set);
	ClassDB::bind_method(D_METHOD("set_buffs", "p_buffs"), &RuntimeAttribute::set_buffs);
	ClassDB::bind_method(D_METHOD("set_value", "p_value"), &RuntimeAttribute::set_value);

	/// binds properties to godot
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "AttributeBase"), "set_attribute", "get_attribute");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "value"), "set_value", "get_value");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "buffs"), "set_buffs", "get_buffs");

	/// adds signals to godot
	ADD_SIGNAL(MethodInfo("attribute_changed", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeAttributeBase"), PropertyInfo(Variant::FLOAT, "previous_value"), PropertyInfo(Variant::FLOAT, "new_value")));
	ADD_SIGNAL(MethodInfo("buff_added", PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeBuff")));
	ADD_SIGNAL(MethodInfo("buff_removed", PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeBuff")));
	ADD_SIGNAL(MethodInfo("buffs_cleared"));
}

bool RuntimeAttribute::add_buff(const Ref<AttributeBuff> &p_buff)
{
	if (!can_receive_buff(p_buff)) {
		return false;
	}

	const Ref<RuntimeBuff> runtime_buff = RuntimeBuff::from_buff(p_buff);

	ERR_FAIL_COND_V_MSG(runtime_buff.is_null(), false, "Failed to create runtime buff from attribute buff.");

	if (p_buff->get_transient()) {
		buffs.push_back(runtime_buff);
		emit_signal("buff_added", runtime_buff);
	} else {
		previous_value = value;

		if (runtime_buff->can_apply_to_attribute(this)) {
			value = runtime_buff->operate(this);
		}

		if (!Math::is_equal_approx(previous_value, value)) {
			emit_signal("attribute_changed", this, previous_value, value);
		}
	}

	return true;
}

int RuntimeAttribute::add_buffs(const TypedArray<AttributeBuff> &p_buffs)
{
	int count = 0;

	for (int i = 0; i < p_buffs.size(); i++) {
		if (add_buff(p_buffs[i])) {
			count++;
		}
	}

	return count;
}

bool RuntimeAttribute::can_receive_buff(const Ref<AttributeBuff> &p_buff) const
{
	if (p_buff->get_unique() && has_buff(p_buff)) {
		return false;
	}

	int buffs_count = 0;

	for (int i = 0; i < buffs.size(); i++) {
		if (const Ref<RuntimeBuff> buff = buffs[i]; buff->equals_to(p_buff)) {
			buffs_count++;
		}
	}

	if (buffs_count >= p_buff->get_max_applies() && p_buff->get_max_applies() > 0) {
		return false;
	}

	return p_buff->get_attribute_name() == attribute->get_attribute_name();
}

void RuntimeAttribute::clear_buffs()
{
	buffs.clear();
}

bool RuntimeAttribute::has_buff(const Ref<AttributeBuff> &p_buff) const
{
	for (int i = 0; i < buffs.size(); i++) {
		if (const Ref<RuntimeBuff> buff = buffs[i]; buff->equals_to(p_buff)) {
			return true;
		}
	}

	return false;
}

bool RuntimeAttribute::remove_buff(const Ref<AttributeBuff> &p_buff)
{
	for (int i = 0; i < buffs.size(); i++) {
		if (const Ref<RuntimeBuff> buff = buffs[i]; buff->equals_to(p_buff)) {
			buffs.remove_at(i);
			emit_signal("buff_removed", buff);
			return true;
		}
	}

	return false;
}

int RuntimeAttribute::remove_buffs(const TypedArray<AttributeBuff> &p_buffs)
{
	int count = 0;

	for (int64_t i = p_buffs.size() - 1; i >= 0; i--) {
		for (int64_t j = buffs.size() - 1; j >= 0; j--) {
			if (const Ref<RuntimeBuff> buff = buffs[j]; buff->equals_to(p_buffs[i])) {
				buffs.remove_at(j);
				count++;
			}
		}
	}

	if (count > 0) {
		emit_signal("buffs_cleared");
	}

	return count;
}

Ref<Attribute> RuntimeAttribute::get_attribute() const
{
	return attribute;
}

Ref<AttributeSet> RuntimeAttribute::get_attribute_set() const
{
	return attribute_set;
}

float RuntimeAttribute::get_buffed_value() const
{
	float current_value = value;

	if (GDVIRTUAL_IS_OVERRIDDEN_PTR(attribute, _get_buffed_value)) {
		TypedArray<AttributeBase> derived_from = get_derived_from();
		TypedArray<float> values;

		if (derived_from.size() > 0) {
			for (int i = 0; i < derived_from.size(); i++) {
				const Ref<AttributeBase> derived_attribute = derived_from[i];
				values.push_back(attribute_container->get_attribute_buffed_value_by_name(derived_attribute->get_attribute_name()));
			}
		}

		GDVIRTUAL_CALL_PTR(attribute, _get_buffed_value, values, current_value);
	}

	for (int i = 0; i < buffs.size(); i++) {
		const Ref<RuntimeBuff> buff = buffs[i];

		if (Ref<AttributeBuff> attribute_buff = buff->get_buff();attribute_buff.is_valid() && !attribute_buff.is_null()) {
			current_value = attribute_buff->operate(current_value);
		}
	}

	return current_value;
}

TypedArray<AttributeBase> RuntimeAttribute::get_constrained_by() const
{
	if (GDVIRTUAL_IS_OVERRIDDEN_PTR(attribute, _constrained_by)) {
		TypedArray<AttributeBase> constraining_attributes;

		ERR_FAIL_COND_V_MSG(!GDVIRTUAL_CALL_PTR(attribute, _constrained_by, attribute_set, constraining_attributes), constraining_attributes, "_constrained_by errored.");

		return constraining_attributes;
	}

	return {};
}

float RuntimeAttribute::get_constrained_value() const
{
	const float buffed_value = get_buffed_value();
	float returning_value = buffed_value;

	if (GDVIRTUAL_IS_OVERRIDDEN_PTR(attribute, _get_constrained_value)) {
		TypedArray<AttributeBase> constraining_attributes = get_constrained_by();
		TypedArray<float> buffed_values;
		TypedArray<float> previous_values;

		for (int i = 0; i < constraining_attributes.size(); i++) {
			const Ref<AttributeBase> constraining_attribute = constraining_attributes[i];
			buffed_values.push_back(attribute_container->get_attribute_buffed_value_by_name(constraining_attribute->get_attribute_name()));
			previous_values.push_back(attribute_container->get_attribute_previous_value_by_name(constraining_attribute->get_attribute_name()));
		}

		GDVIRTUAL_CALL_PTR(attribute, _get_constrained_value, buffed_value, buffed_values, previous_values, returning_value);
	}

	return returning_value;
}

TypedArray<AttributeBase> RuntimeAttribute::get_derived_from() const
{
	if (GDVIRTUAL_IS_OVERRIDDEN_PTR(attribute, _derived_from)) {
		if (TypedArray<AttributeBase> derived_attributes; GDVIRTUAL_CALL_PTR(attribute, _derived_from, attribute_set, derived_attributes)) {
			return derived_attributes;
		}
	}

	return {};
}

float RuntimeAttribute::get_initial_value() const
{
	if (GDVIRTUAL_IS_OVERRIDDEN_PTR(attribute, _get_initial_value)) {
		TypedArray<AttributeBase> base_attributes = get_derived_from();

		ERR_FAIL_COND_V_MSG(base_attributes.size() == 0, 0, "Attribute set must be set to get initial value. Please override _derived_from method.");

		PackedFloat32Array values;

		for (int i = 0; i < base_attributes.size(); i++) {
			const Ref<AttributeBase> base_attribute = base_attributes[i];
			values.push_back(base_attribute->get_initial_value());
		}

		if (float ret; GDVIRTUAL_CALL_PTR(attribute, _get_initial_value, values, ret)) {
			return ret;
		}
	}

	return attribute->get_initial_value();
}

float RuntimeAttribute::get_previous_value() const
{
	return previous_value;
}

float RuntimeAttribute::get_value() const
{
	return value;
}

TypedArray<RuntimeBuff> RuntimeAttribute::get_buffs() const
{
	return buffs;
}

void RuntimeAttribute::set_attribute(const Ref<AttributeBase> &p_value)
{
	attribute = p_value;
}

void RuntimeAttribute::set_value(const float p_value)
{
	value = p_value;
	previous_value = value;
}

void RuntimeAttribute::set_buffs(const TypedArray<AttributeBuff> &p_value)
{
	buffs.clear();

	for (int i = 0; i < p_value.size(); i++) {
		buffs.push_back(RuntimeBuff::from_buff(p_value[i]));
	}
}

void RuntimeAttribute::set_attribute_set(const Ref<AttributeSet> &p_value)
{
	attribute_set = p_value;
}

#pragma endregion
