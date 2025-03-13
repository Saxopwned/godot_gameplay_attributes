/**************************************************************************/
/*  attribute_container.cpp                                               */
/**************************************************************************/
/*                         This file is part of:                          */
/*                        Godot Gameplay Systems                          */
/*              https://github.com/OctoD/godot-gameplay-systems           */
/**************************************************************************/
/* Copyright (c) 2020-present Paolo "OctoD"      Roth (see AUTHORS.md).   */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "attribute_container.hpp"

#include "attribute.hpp"
#include "buff_pool_queue.hpp"
#include "godot_cpp/classes/wrapped.hpp"

using namespace gga;

void AttributeContainer::_bind_methods()
{
	/// binds methods to godot
	ClassDB::bind_method(D_METHOD("_on_attribute_changed", "p_attribute", "p_previous_value", "p_new_value"), &AttributeContainer::_on_attribute_changed);
	ClassDB::bind_method(D_METHOD("_on_buff_applied", "p_buff"), &AttributeContainer::_on_buff_applied);
	ClassDB::bind_method(D_METHOD("_on_buff_dequeued", "p_buff"), &AttributeContainer::_on_buff_dequeued);
	ClassDB::bind_method(D_METHOD("_on_buff_enqueued", "p_buff"), &AttributeContainer::_on_buff_enqueued);
	ClassDB::bind_method(D_METHOD("_on_buff_removed", "p_buff"), &AttributeContainer::_on_buff_removed);
	ClassDB::bind_method(D_METHOD("add_attribute", "p_attribute"), &AttributeContainer::add_attribute);
	ClassDB::bind_method(D_METHOD("apply_buff", "p_buff"), &AttributeContainer::apply_buff);
	ClassDB::bind_method(D_METHOD("find", "p_predicate"), &AttributeContainer::find);
	ClassDB::bind_method(D_METHOD("find_buffed_value", "p_predicate"), &AttributeContainer::find_buffed_value);
	ClassDB::bind_method(D_METHOD("find_constrained_value", "p_predicate"), &AttributeContainer::find_constrained_value);
	ClassDB::bind_method(D_METHOD("find_initial_value", "p_predicate"), &AttributeContainer::find_initial_value);
	ClassDB::bind_method(D_METHOD("find_value", "p_predicate"), &AttributeContainer::find_value);
	ClassDB::bind_method(D_METHOD("get_attribute_set"), &AttributeContainer::get_attribute_set);
	ClassDB::bind_method(D_METHOD("get_attributes"), &AttributeContainer::get_attributes);
	ClassDB::bind_method(D_METHOD("get_attribute_by_name", "p_name"), &AttributeContainer::get_attribute_by_name);
	ClassDB::bind_method(D_METHOD("get_attribute_buffed_value_by_name", "p_name"), &AttributeContainer::get_attribute_buffed_value_by_name);
	ClassDB::bind_method(D_METHOD("get_attribute_constrained_value_by_name", "p_name"), &AttributeContainer::get_attribute_constrained_value_by_name);
	ClassDB::bind_method(D_METHOD("get_attribute_initial_value_by_name", "p_name"), &AttributeContainer::get_attribute_initial_value_by_name);
	ClassDB::bind_method(D_METHOD("get_attribute_value_by_name", "p_name"), &AttributeContainer::get_attribute_value_by_name);
	ClassDB::bind_method(D_METHOD("get_server_authoritative"), &AttributeContainer::get_server_authoritative);
	ClassDB::bind_method(D_METHOD("remove_attribute", "p_attribute"), &AttributeContainer::remove_attribute);
	ClassDB::bind_method(D_METHOD("remove_buff", "p_buff"), &AttributeContainer::remove_buff);
	ClassDB::bind_method(D_METHOD("set_attribute_set", "p_attribute_set"), &AttributeContainer::set_attribute_set);
	ClassDB::bind_method(D_METHOD("set_server_authoritative", "p_server_authoritative"), &AttributeContainer::set_server_authoritative);
	ClassDB::bind_method(D_METHOD("setup"), &AttributeContainer::setup);

	/// binds properties to godot
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "attribute_set", PROPERTY_HINT_RESOURCE_TYPE, "AttributeSet"), "set_attribute_set", "get_attribute_set");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "server_authoritative"), "set_server_authoritative", "get_server_authoritative");

	/// signals binding
	ADD_SIGNAL(MethodInfo("attribute_changed", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeAttributeBase"), PropertyInfo(Variant::FLOAT, "previous_value"), PropertyInfo(Variant::FLOAT, "new_value")));
	ADD_SIGNAL(MethodInfo("buff_applied", PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeBuff")));
	ADD_SIGNAL(MethodInfo("buff_dequed", PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeBuff")));
	ADD_SIGNAL(MethodInfo("buff_enqueued", PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeBuff")));
	ADD_SIGNAL(MethodInfo("buff_removed", PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeBuff")));
}

void AttributeContainer::_on_attribute_changed(const Ref<RuntimeAttribute> &p_attribute, const float p_previous_value, const float p_new_value)
{
	emit_signal("attribute_changed", p_attribute, p_previous_value, p_new_value);
	notify_derived_attributes(p_attribute);
}

void AttributeContainer::_on_buff_applied(const Ref<RuntimeBuff> &p_buff)
{
	emit_signal("buff_applied", p_buff);
}

void AttributeContainer::_on_buff_dequeued(const Ref<RuntimeBuff> &p_buff)
{
	emit_signal("buff_dequed", p_buff);
	remove_buff(RuntimeBuff::to_buff(p_buff));
}

void AttributeContainer::_on_buff_enqueued(const Ref<RuntimeBuff> &p_buff)
{
	emit_signal("buff_enqueued", p_buff);
}

void AttributeContainer::_on_buff_removed(const Ref<RuntimeBuff> &p_buff)
{
	emit_signal("buff_removed", p_buff);
}

bool AttributeContainer::has_attribute(const Ref<AttributeBase> &p_attribute)const
{
	return attributes.has(p_attribute->get_attribute_name());
}

void AttributeContainer::notify_derived_attributes(const Ref<RuntimeAttribute> &p_runtime_attribute)
{
	if (derived_attributes.has(p_runtime_attribute->get_attribute()->get_attribute_name())) {
		TypedArray<RuntimeAttribute> derived = derived_attributes[p_runtime_attribute->get_attribute()->get_attribute_name()];

		for (int i = 0; i < derived.size(); i++) {
			Ref<RuntimeAttribute> derived_attribute = derived[i];
			float previous_value = derived_attribute->get_value();
			float current_value = derived_attribute->get_buffed_value();

			if (!Math::is_equal_approx(previous_value, current_value)) {
				derived_attribute->emit_signal("attribute_changed", derived_attribute, previous_value, current_value);
			}
		}
	}
}

void AttributeContainer::_physics_process(double p_delta)
{
	if (buff_pool_queue) {
		buff_pool_queue->handle_physics_process(p_delta);
	}
}

void AttributeContainer::_ready()
{
	/// initializes the BuffPoolQueue
	buff_pool_queue = memnew(BuffPoolQueue);
	buff_pool_queue->set_server_authoritative(server_authoritative);
	buff_pool_queue->connect("attribute_buff_dequeued", Callable::create(this, "_on_buff_dequeued"));
	buff_pool_queue->connect("attribute_buff_enqueued", Callable::create(this, "_on_buff_enqueued"));

	add_child(buff_pool_queue);
	setup();
}

void AttributeContainer::add_attribute(const Ref<AttributeBase> &p_attribute)
{
	ERR_FAIL_NULL_MSG(p_attribute, "Attribute cannot be null, it must be an instance of a class inheriting from AttributeBase abstract class.");
	ERR_FAIL_COND_MSG(has_attribute(p_attribute), "Attribute already exists in the container.");

	const Ref runtime_attribute = memnew(RuntimeAttribute);

	runtime_attribute->attribute_container = this;
	runtime_attribute->set_attribute(p_attribute);
	runtime_attribute->set_attribute_set(attribute_set);
	runtime_attribute->set_buffs(p_attribute->get_buffs());
	runtime_attribute->set_value(runtime_attribute->get_initial_value());

	const Callable attribute_changed_callable = Callable::create(this, "_on_attribute_changed");
	const Callable buff_applied_callable = Callable::create(this, "_on_buff_applied");
	const Callable buff_removed_callable = Callable::create(this, "_on_buff_removed");

	runtime_attribute->connect("attribute_changed", attribute_changed_callable);
	runtime_attribute->connect("buff_added", buff_applied_callable);
	runtime_attribute->connect("buff_removed", buff_removed_callable);

	if (TypedArray<AttributeBase> base_attributes = runtime_attribute->get_derived_from(); base_attributes.size() > 0) {
		for (int i = 0; i < base_attributes.size(); i++) {
			const Ref<AttributeBase> base_attribute = base_attributes[i];

			if (derived_attributes.has(base_attribute->get_attribute_name())) {
				Array _derived = {};
				_derived = derived_attributes[base_attribute->get_attribute_name()];
				_derived.push_back(runtime_attribute);
			} else {
				Array _derived = {};
				derived_attributes[base_attribute->get_attribute_name()] = _derived;
				_derived.push_back(runtime_attribute);
			}
		}
	}

	attributes[p_attribute->get_attribute_name()] = runtime_attribute;
}

void AttributeContainer::apply_buff(const Ref<AttributeBuff> &p_buff) const
{
	ERR_FAIL_NULL_MSG(p_buff, "Buff cannot be null, it must be an instance of a class inheriting from AttributeBuff abstract class.");

	if (p_buff->is_operate_overridden()) {
		Ref<RuntimeBuff> runtime_buff = RuntimeBuff::from_buff(p_buff);
		TypedArray<AttributeBase> _attributes;
		TypedArray<RuntimeAttribute> _affected_runtime_attributes;
		TypedArray<float> constrained_values;

		ERR_FAIL_COND_MSG(!GDVIRTUAL_IS_OVERRIDDEN_PTR(p_buff, _applies_to), "Buff must override the _applies_to method to apply to derived attributes.");
		ERR_FAIL_COND_MSG(!GDVIRTUAL_CALL_PTR(p_buff, _applies_to, attribute_set, _attributes), "An error occurred calling the overridden _applies_to method.");

		for (int i = 0; i < _attributes.size(); i++) {
			Ref<AttributeBase> attribute_base = _attributes[i];
			Ref<RuntimeAttribute> attribute = get_attribute_by_name(attribute_base->get_attribute_name());

			ERR_FAIL_NULL_MSG(attribute, "Attribute not found in attribute set.");

			_affected_runtime_attributes.push_back(attribute);
			constrained_values.push_back(attribute->get_buffed_value());
		}

		TypedArray<AttributeOperation> operations;

		const bool applied = GDVIRTUAL_CALL_PTR(p_buff, _operate, constrained_values, attribute_set, operations);

		ERR_FAIL_COND_MSG(!applied, "An error occurred calling the overridden _operate method.");

		/// we are going to create a new AttributeBuff for each derived attribute affected by the buff
		/// we will add this buff to each affected runtime attribute.
		for (int i = 0; i < operations.size(); i++) {
			Ref derived_buff = memnew(AttributeBuff);
			Ref operation = memnew(AttributeOperation);
			const Ref<RuntimeAttribute> runtime_attribute = _affected_runtime_attributes[i];

			derived_buff->set_attribute_name(runtime_attribute->get_attribute()->get_attribute_name());
			derived_buff->set_buff_name(p_buff->get_buff_name());
			derived_buff->set_duration(p_buff->get_duration());
			/// since it's a derived operation, we must multiply the max_applies by the number of derived attributes
			/// affected.
			derived_buff->set_max_applies(static_cast<int>(operations.size()) * p_buff->get_max_applies());
			derived_buff->set_transient(p_buff->get_transient());

			derived_buff->set_operation(operations[i]);

			if (runtime_attribute->add_buff(derived_buff) && !Math::is_zero_approx(p_buff->get_duration())) {
				buff_pool_queue->enqueue(derived_buff);
			}
		}
	} else {
		const Ref<RuntimeAttribute> runtime_attribute = get_attribute_by_name(p_buff->get_attribute_name());

		ERR_FAIL_COND_MSG(!runtime_attribute.is_valid(), "Attribute '" + p_buff->get_attribute_name() + "' not found in the container.");
		ERR_FAIL_COND_MSG(runtime_attribute.is_null(), "Attribute reference is not valid.");

		if (runtime_attribute->add_buff(p_buff) && !Math::is_zero_approx(p_buff->get_duration())) {
			buff_pool_queue->enqueue(RuntimeBuff::from_buff(p_buff));
		}
	}
}

void AttributeContainer::remove_attribute(const Ref<AttributeBase> &p_attribute)
{
	ERR_FAIL_NULL_MSG(p_attribute, "Attribute cannot be null, it must be an instance of a class inheriting from AttributeBase abstract class.");
	ERR_FAIL_COND_MSG(!has_attribute(p_attribute), "Attribute not found in the container.");

	const Ref<RuntimeAttribute> runtime_attribute = get_attribute_by_name(p_attribute->get_name());

	ERR_FAIL_COND_MSG(!runtime_attribute.is_valid(), "Attribute not valid.");

	String attribute_name = runtime_attribute->get_attribute()->get_attribute_name();

	ERR_FAIL_COND_MSG(!attributes.has(attribute_name), "Attribute not found. This is a bug, please open an issue.");

	runtime_attribute->disconnect("attribute_changed", Callable::create(this, "_on_attribute_changed"));
	runtime_attribute->disconnect("buff_added", Callable::create(this, "_on_buff_applied"));
	runtime_attribute->disconnect("buff_removed", Callable::create(this, "_on_buff_removed"));

	ERR_FAIL_COND_MSG(!attributes.erase(attribute_name), "Failed to remove attribute from container.");
}

void AttributeContainer::remove_buff(const Ref<AttributeBuff> &p_buff) const
{
	ERR_FAIL_NULL_MSG(p_buff, "Buff cannot be null, it must be an instance of a class inheriting from AttributeBuff abstract class.");

	Array _attributes = attributes.values();

	for (int i = 0; i < _attributes.size(); i++) {
		const Ref<RuntimeAttribute> attribute = _attributes[i];
		attribute->remove_buff(p_buff);
	}
}

void AttributeContainer::setup()
{
	attributes.clear();

	if (attribute_set.is_valid()) {
		for (int i = 0; i < attribute_set->count(); i++) {
			add_attribute(attribute_set->get_at(i));
		}
	}
}

Ref<RuntimeAttribute> AttributeContainer::find(const Callable &p_predicate) const
{
	Array _attributes = attributes.values();

	for (int i = 0; i < _attributes.size(); i++) {
		if (p_predicate.call(_attributes[i])) {
			return _attributes[i];
		}
	}

	return nullptr;
}

float AttributeContainer::find_buffed_value(const Callable &p_predicate) const
{
	const Ref<RuntimeAttribute> attribute = find(p_predicate);
	return attribute.is_valid() && !attribute.is_null() ? attribute->get_buffed_value() : 0.0f;
}

float AttributeContainer::find_constrained_value(const Callable &p_predicate) const
{
	const Ref<RuntimeAttribute> attribute = find(p_predicate);
	return attribute.is_valid() && !attribute.is_null() ? attribute->get_constrained_value() : 0.0f;
}

float AttributeContainer::find_initial_value(const Callable &p_predicate) const
{
	const Ref<RuntimeAttribute> attribute = find(p_predicate);
	return attribute.is_valid() && !attribute.is_null() ? attribute->get_initial_value() : 0.0f;
}

float AttributeContainer::find_value(const Callable &p_predicate) const
{
	const Ref<RuntimeAttribute> attribute = find(p_predicate);
	return attribute.is_valid() && !attribute.is_null() ? attribute->get_value() : 0.0f;
}

Ref<AttributeSet> AttributeContainer::get_attribute_set() const
{
	return attribute_set;
}

TypedArray<RuntimeAttribute> AttributeContainer::get_attributes() const
{
	return attributes.values();
}

Ref<RuntimeAttribute> AttributeContainer::get_attribute_by_name(const String &p_name) const
{
	if (attributes.has(p_name)) {
		return attributes[p_name];
	}

	return {};
}

float AttributeContainer::get_attribute_buffed_value_by_name(const String &p_name) const
{
	const Ref<RuntimeAttribute> attribute = get_attribute_by_name(p_name);
	return attribute.is_valid() && !attribute.is_null() ? attribute->get_buffed_value() : 0.0f;
}

float AttributeContainer::get_attribute_constrained_value_by_name(const String &p_name) const
{
	const Ref<RuntimeAttribute> attribute = get_attribute_by_name(p_name);
	return attribute.is_valid() && !attribute.is_null() ? attribute->get_constrained_value() : 0.0f;
}

float AttributeContainer::get_attribute_initial_value_by_name(const String &p_name) const
{
	const Ref<RuntimeAttribute> attribute = get_attribute_by_name(p_name);
	return attribute.is_valid() && !attribute.is_null() ? attribute->get_initial_value() : 0.0f;
}

float AttributeContainer::get_attribute_previous_value_by_name(const String &p_name) const
{
	const Ref<RuntimeAttribute> attribute = get_attribute_by_name(p_name);
	return attribute.is_valid() && !attribute.is_null() ? attribute->get_previous_value() : 0.0f;
}

float AttributeContainer::get_attribute_value_by_name(const String &p_name) const
{
	const Ref<RuntimeAttribute> attribute = get_attribute_by_name(p_name);
	return attribute.is_valid() && !attribute.is_null() ? attribute->get_value() : 0.0f;
}

bool AttributeContainer::get_server_authoritative() const
{
	return server_authoritative;
}

void AttributeContainer::set_attribute_set(const Ref<AttributeSet> &p_attribute_set)
{
	attribute_set = p_attribute_set;
	setup();
}

void AttributeContainer::set_server_authoritative(const bool p_server_authoritative)
{
	server_authoritative = p_server_authoritative;

	if (buff_pool_queue != nullptr) {
		buff_pool_queue->set_server_authoritative(server_authoritative);
	}
}
