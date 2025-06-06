/**************************************************************************/
/*  attribute_container.cpp                                               */
/**************************************************************************/
/*                         This file is part of:                          */
/*                        Godot Gameplay Systems                          */
/*              https://github.com/OctoD/godot-gameplay-systems           */
/**************************************************************************/
/* Read the license file in this repo.						              */
/**************************************************************************/

#include "attribute_container.hpp"

#include "attribute.hpp"
#include "godot_cpp/classes/wrapped.hpp"

using namespace octod::gameplay::attributes;

void AttributeContainer::_bind_methods()
{
	/// binds methods to godot
	ClassDB::bind_method(D_METHOD("_on_attribute_changed", "p_attribute", "p_previous_value", "p_new_value"), &AttributeContainer::_on_attribute_changed);
	ClassDB::bind_method(D_METHOD("_on_buff_applied", "p_buff"), &AttributeContainer::_on_buff_applied);
	ClassDB::bind_method(D_METHOD("_on_buff_dequeued", "p_buff"), &AttributeContainer::_on_buff_dequeued);
	ClassDB::bind_method(D_METHOD("_on_buff_enqueued", "p_buff"), &AttributeContainer::_on_buff_enqueued);
	ClassDB::bind_method(D_METHOD("_on_buff_removed", "p_buff"), &AttributeContainer::_on_buff_removed);
	ClassDB::bind_method(D_METHOD("_on_buff_time_updated", "p_buff"), &AttributeContainer::_on_buff_time_updated);
	ClassDB::bind_method(D_METHOD("add_attribute", "p_attribute"), &AttributeContainer::add_attribute);
	ClassDB::bind_method(D_METHOD("apply_buff", "p_buff"), &AttributeContainer::apply_buff);
	ClassDB::bind_method(D_METHOD("find", "p_predicate"), &AttributeContainer::find);
	ClassDB::bind_method(D_METHOD("find_buffed_value", "p_predicate"), &AttributeContainer::find_buffed_value);
	ClassDB::bind_method(D_METHOD("find_value", "p_predicate"), &AttributeContainer::find_value);
	ClassDB::bind_method(D_METHOD("get_attribute_set"), &AttributeContainer::get_attribute_set);
	ClassDB::bind_method(D_METHOD("get_attributes"), &AttributeContainer::get_runtime_attributes);
	ClassDB::bind_method(D_METHOD("get_attribute_by_name", "p_name"), &AttributeContainer::get_runtime_attribute_by_name);
	ClassDB::bind_method(D_METHOD("get_attribute_buffed_value_by_name", "p_name"), &AttributeContainer::get_attribute_buffed_value_by_name);
	ClassDB::bind_method(D_METHOD("get_attribute_value_by_name", "p_name"), &AttributeContainer::get_attribute_value_by_name);
	ClassDB::bind_method(D_METHOD("remove_attribute", "p_attribute"), &AttributeContainer::remove_attribute);
	ClassDB::bind_method(D_METHOD("remove_buff", "p_buff"), &AttributeContainer::remove_buff);
	ClassDB::bind_method(D_METHOD("set_attribute_set", "p_attribute_set"), &AttributeContainer::set_attribute_set);
	ClassDB::bind_method(D_METHOD("setup"), &AttributeContainer::setup);

	/// binds properties to godot
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "attribute_set", PROPERTY_HINT_RESOURCE_TYPE, "AttributeSet"), "set_attribute_set", "get_attribute_set");

	/// signals binding
	ADD_SIGNAL(MethodInfo("attribute_changed", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeAttributeBase"), PropertyInfo(Variant::FLOAT, "previous_value"), PropertyInfo(Variant::FLOAT, "new_value")));
	ADD_SIGNAL(MethodInfo("buff_applied", PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeBuff")));
	ADD_SIGNAL(MethodInfo("buff_dequed", PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeBuff")));
	ADD_SIGNAL(MethodInfo("buff_enqueued", PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeBuff")));
	ADD_SIGNAL(MethodInfo("buff_removed", PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeBuff")));
	ADD_SIGNAL(MethodInfo("buff_time_elapsed", PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeBuff")));
	ADD_SIGNAL(MethodInfo("buff_time_updated", PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeBuff")));
}

void AttributeContainer::_notification(const int p_what)
{
	if (p_what == NOTIFICATION_READY) {
		setup();
		set_physics_process(true);
	} else if (p_what == NOTIFICATION_PHYSICS_PROCESS) {
		const TypedArray<RuntimeAttribute> &runtime_attributes = attributes.values();
		const float phy_time = static_cast<float>(get_physics_process_delta_time());

		for (int64_t i = 0; i < runtime_attributes.size(); i++) {
			const Ref<RuntimeAttribute> &attribute = runtime_attributes[i];

			if (!attribute.is_valid()) {
				continue;
			}

			TypedArray<RuntimeBuff> buffs = attribute->get_buffs();

			for (int64_t j = buffs.size() - 1; j >= 0; j--) {
				Ref<RuntimeBuff> buff = buffs[j];

				if (!buff.is_valid() || buff.is_null()) {
					continue;
				}

				if (buff->is_transient() && buff->has_duration()) {
					buff->set_time_left(buff->get_time_left() - phy_time);

					emit_signal("buff_time_elapsed", buff);

					if (buff->can_dequeue()) {
						emit_signal("buff_dequed", buff);
						attribute->remove_buff(buff);
						buffs.remove_at(j);
					}
				}
			}
		}
	}
}

void AttributeContainer::_on_attribute_changed(const Ref<RuntimeAttribute> &p_attribute, const float p_previous_value, const float p_new_value)
{
	emit_signal("attribute_changed", p_attribute, p_previous_value, p_new_value);
	notify_derived_attributes(p_attribute);
}

void AttributeContainer::_on_buff_applied(const Ref<RuntimeBuff> &p_buff)
{
	emit_signal("buff_applied", p_buff);

	if (const auto attribute = get_runtime_attribute_by_name(p_buff->get_attribute_name()); attribute.is_valid() && !attribute.is_null()) {
		notify_derived_attributes(attribute);
	}
}

void AttributeContainer::_on_buff_dequeued(const Ref<RuntimeBuff> &p_buff)
{
	emit_signal("buff_dequed", p_buff);
	remove_buff(p_buff->buff);
}

void AttributeContainer::_on_buff_enqueued(const Ref<RuntimeBuff> &p_buff)
{
	emit_signal("buff_enqueued", p_buff);
}

void AttributeContainer::_on_buff_removed(const Ref<RuntimeBuff> &p_buff)
{
	emit_signal("buff_removed", p_buff);

	if (const auto attribute = get_runtime_attribute_by_name(p_buff->get_attribute_name()); attribute.is_valid() && !attribute.is_null()) {
		notify_derived_attributes(attribute);
	}
}

void AttributeContainer::_on_buff_time_updated(const Ref<RuntimeBuff> &p_buff)
{
	emit_signal("buff_time_updated", p_buff);
}

bool AttributeContainer::has_attribute(const Ref<AttributeBase> &p_attribute) const
{
	return attributes.has(p_attribute->get_attribute_name());
}

void AttributeContainer::notify_derived_attributes(const Ref<RuntimeAttribute> &p_base_runtime_attribute)
{
	if (derived_attributes.has(p_base_runtime_attribute->get_attribute()->get_attribute_name())) {
		TypedArray<RuntimeAttribute> derived = derived_attributes[p_base_runtime_attribute->get_attribute()->get_attribute_name()];

		for (int i = 0; i < derived.size(); i++) {
			const Ref<RuntimeAttribute> derived_attribute = derived[i];
			derived_attribute->compute_value();
		}
	}
}

void AttributeContainer::add_attribute(const Ref<AttributeBase> &p_attribute)
{
	ERR_FAIL_NULL_MSG(p_attribute, "Attribute cannot be null, it must be an instance of a class inheriting from AttributeBase abstract class.");
	ERR_FAIL_COND_MSG(has_attribute(p_attribute), "Attribute already exists in the container.");

	RuntimeAttribute *runtime_attribute = memnew(RuntimeAttribute);

	if (attribute_set.is_null() || !attribute_set.is_valid()) {
		attribute_set.instantiate();
	}

	if (!attribute_set->has_attribute(p_attribute)) {
		attribute_set->add_attribute(p_attribute);
	}

	runtime_attribute->attribute_container = this;
	runtime_attribute->set_attribute(p_attribute);
	runtime_attribute->set_attribute_set(attribute_set);

	if (TypedArray<AttributeBase> base_attributes = runtime_attribute->get_derived_from(); base_attributes.size() > 0) {
		for (int i = 0; i < base_attributes.size(); i++) {
			const Ref<AttributeBase> base_attribute = base_attributes[i];

			ERR_FAIL_COND_MSG(!base_attribute.is_valid() || base_attribute.is_null(), "Required base attribute " + p_attribute->get_attribute_name() + " does not exist into the AttributeSet.");

			if (derived_attributes.has(base_attribute->get_attribute_name())) {
				Array _derived = derived_attributes[base_attribute->get_attribute_name()];
				_derived.push_back(runtime_attribute);
			} else {
				Array _derived;
				derived_attributes[base_attribute->get_attribute_name()] = _derived;
				_derived.push_back(runtime_attribute);
			}
		}
	}

	const Callable attribute_changed_callable = Callable::create(this, "_on_attribute_changed");
	const Callable buff_applied_callable = Callable::create(this, "_on_buff_applied");
	const Callable buff_removed_callable = Callable::create(this, "_on_buff_removed");
	const Callable buff_time_updated_callable = Callable::create(this, "_on_buff_time_updated");

	runtime_attribute->connect("attribute_changed", attribute_changed_callable);
	runtime_attribute->connect("buff_added", buff_applied_callable);
	runtime_attribute->connect("buff_removed", buff_removed_callable);
	runtime_attribute->connect("buff_time_updated", buff_time_updated_callable);

	attributes[p_attribute->get_attribute_name()] = runtime_attribute;
}

void AttributeContainer::apply_buff(const Ref<AttributeBuff> &p_buff) const
{
	ERR_FAIL_NULL_MSG(p_buff, "Buff cannot be null, it must be an instance of a class inheriting from AttributeBuff abstract class.");

	if (p_buff->is_operate_overridden()) {
		TypedArray<AttributeBase> _attributes;
		TypedArray<RuntimeAttribute> _affected_runtime_attributes;
		TypedArray<float> buffed_values;

		ERR_FAIL_COND_MSG(!GDVIRTUAL_IS_OVERRIDDEN_PTR(p_buff, _applies_to), "Buff must override the _applies_to method to apply to derived attributes.");
		ERR_FAIL_COND_MSG(!GDVIRTUAL_CALL_PTR(p_buff, _applies_to, attribute_set, _attributes), "An error occurred calling the overridden _applies_to method.");

		for (int i = 0; i < _attributes.size(); i++) {
			const Ref<AttributeBase> attribute_base = _attributes[i];
			Ref<RuntimeAttribute> attribute = get_runtime_attribute_by_name(attribute_base->get_attribute_name());

			ERR_FAIL_NULL_MSG(attribute, "Attribute not found in attribute set.");

			_affected_runtime_attributes.push_back(attribute);
			buffed_values.push_back(attribute->get_buffed_value());
		}

		TypedArray<AttributeOperation> operations;

		const bool applied = GDVIRTUAL_CALL_PTR(p_buff, _operate, buffed_values, attribute_set, operations);

		ERR_FAIL_COND_MSG(!applied, "An error occurred calling the overridden _operate method.");

		/// we are going to create a new AttributeBuff for each derived attribute affected by the buff
		/// we will add this buff to each affected runtime attribute.
		for (int i = 0; i < operations.size(); i++) {
			Ref derived_buff = memnew(AttributeBuff);

			const Ref<RuntimeAttribute> runtime_attribute = _affected_runtime_attributes[i];

			derived_buff->set_attribute_name(runtime_attribute->get_attribute()->get_attribute_name());
			derived_buff->set_buff_name(p_buff->get_buff_name());
			derived_buff->set_duration(p_buff->get_duration());
			derived_buff->set_duration_merging(p_buff->get_duration_merging());
			derived_buff->set_queue_execution(p_buff->get_queue_execution());
			derived_buff->set_unique(p_buff->get_unique());
			derived_buff->set_stack_size(p_buff->get_stack_size());
			derived_buff->set_transient(p_buff->get_transient());
			derived_buff->set_operation(operations[i]);

			runtime_attribute->add_buff(derived_buff);
		}
	} else {
		const Ref<RuntimeAttribute> runtime_attribute = get_runtime_attribute_by_name(p_buff->get_attribute_name());

		ERR_FAIL_COND_MSG(!runtime_attribute.is_valid(), "Attribute '" + p_buff->get_attribute_name() + "' not found in the container.");
		ERR_FAIL_COND_MSG(runtime_attribute.is_null(), "Attribute reference is not valid.");

		runtime_attribute->add_buff(p_buff);
	}
}

void AttributeContainer::remove_attribute(const Ref<AttributeBase> &p_attribute)
{
	ERR_FAIL_NULL_MSG(p_attribute, "Attribute cannot be null, it must be an instance of a class inheriting from AttributeBase abstract class.");
	ERR_FAIL_COND_MSG(!has_attribute(p_attribute), "Attribute not found in the container.");

	const Ref<RuntimeAttribute> runtime_attribute = get_runtime_attribute_by_name(p_attribute->get_name());

	ERR_FAIL_COND_MSG(!runtime_attribute.is_valid(), "Attribute not valid.");

	const String attribute_name = runtime_attribute->get_attribute()->get_attribute_name();

	ERR_FAIL_COND_MSG(!attributes.has(attribute_name), "Attribute not found. This is a bug, please open an issue.");

	runtime_attribute->disconnect("attribute_changed", Callable::create(this, "_on_attribute_changed"));
	runtime_attribute->disconnect("buff_added", Callable::create(this, "_on_buff_applied"));
	runtime_attribute->disconnect("buff_removed", Callable::create(this, "_on_buff_removed"));

	ERR_FAIL_COND_MSG(!attributes.erase(attribute_name), "Failed to remove attribute from container.");
}

void AttributeContainer::remove_buff(const Ref<AttributeBuff> &p_buff) const
{
	ERR_FAIL_NULL_MSG(p_buff, "Buff cannot be null, it must be an instance of a class inheriting from AttributeBuff abstract class.");
	ERR_FAIL_COND_MSG(p_buff.is_null(), "Buff cannot be null, it must be an instance of a class inheriting from AttributeBuff abstract class.");
	ERR_FAIL_COND_MSG(!p_buff.is_valid(), "Buff reference not valid.");

	if (p_buff->is_operate_overridden()) {
		TypedArray<AttributeBase> _attributes;

		ERR_FAIL_COND_MSG(!GDVIRTUAL_IS_OVERRIDDEN_PTR(p_buff, _applies_to), "Buff must override the _applies_to method to apply to derived attributes.");
		ERR_FAIL_COND_MSG(!GDVIRTUAL_CALL_PTR(p_buff, _applies_to, attribute_set, _attributes), "An error occurred calling the overridden _applies_to method.");

		for (int i = 0; i < _attributes.size(); i++) {
			Ref<AttributeBuff> buff_copy = p_buff->duplicate();
			Ref<RuntimeAttribute> runtime_attribute = get_runtime_attribute_by_name(cast_to<Attribute>(_attributes[i])->get_attribute_name());

			buff_copy->set_attribute_name(runtime_attribute->attribute->get_attribute_name());

			runtime_attribute->remove_buff(buff_copy);
		}
	} else {
		Array _attributes = attributes.values();

		for (int i = 0; i < _attributes.size(); i++) {
			cast_to<RuntimeAttribute>(_attributes[i])->remove_buff(p_buff);
		}
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

float AttributeContainer::find_value(const Callable &p_predicate) const
{
	const Ref<RuntimeAttribute> attribute = find(p_predicate);
	return attribute.is_valid() && !attribute.is_null() ? attribute->get_value() : 0.0f;
}

Ref<AttributeSet> AttributeContainer::get_attribute_set() const
{
	return attribute_set;
}

TypedArray<RuntimeAttribute> AttributeContainer::get_runtime_attributes() const
{
	return attributes.values();
}

Ref<RuntimeAttribute> AttributeContainer::get_runtime_attribute_by_name(const String &p_name) const
{
	if (attributes.has(p_name)) {
		return attributes[p_name];
	}

	return {};
}

float AttributeContainer::get_attribute_buffed_value_by_name(const String &p_name) const
{
	const Ref<RuntimeAttribute> attribute = get_runtime_attribute_by_name(p_name);
	return attribute.is_valid() && !attribute.is_null() ? attribute->get_buffed_value() : 0.0f;
}

float AttributeContainer::get_attribute_previous_value_by_name(const String &p_name) const
{
	const Ref<RuntimeAttribute> attribute = get_runtime_attribute_by_name(p_name);
	return attribute.is_valid() && !attribute.is_null() ? attribute->get_previous_value() : 0.0f;
}

float AttributeContainer::get_attribute_value_by_name(const String &p_name) const
{
	const Ref<RuntimeAttribute> attribute = get_runtime_attribute_by_name(p_name);
	return attribute.is_valid() && !attribute.is_null() ? attribute->get_value() : 0.0f;
}

void AttributeContainer::set_attribute_set(const Ref<AttributeSet> &p_attribute_set)
{
	attribute_set = p_attribute_set;
	setup();
}
