/**************************************************************************/
/*  attribute.hpp                                                         */
/**************************************************************************/
/*                         This file is part of:                          */
/*                        Godot Gameplay Systems                          */
/*              https://github.com/OctoD/godot-gameplay-systems           */
/**************************************************************************/
/* Read the license file in this repo.						              */
/**************************************************************************/

// ReSharper disable CppClassCanBeFinal
#ifndef GODOT_GAMEPLAY_ATTRIBUTES_ATTRIBUTE_HPP
#define GODOT_GAMEPLAY_ATTRIBUTES_ATTRIBUTE_HPP

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>

using namespace godot;

namespace gga
{
	class AttributeBase;
	class AttributeContainer;
	class AttributeSet;
	class RuntimeAttribute;

	enum OperationType
	{
		/// @brief Add operation.
		OP_ADD = 0,
		/// @brief Divide operation.
		OP_DIVIDE = 1,
		/// @brief Multiply operation.
		OP_MULTIPLY = 2,
		/// @brief Percentage operation.
		OP_PERCENTAGE = 3,
		/// @brief Subtract operation.
		OP_SUBTRACT = 4,
		/// @brief Sets the value directly. USE THIS WITH CAUTION.
		OP_SET = 5,
	};

	/// @brief Attribute operation.
	class AttributeOperation : public Resource
	{
		GDCLASS(AttributeOperation, Resource);

	protected:
		/// @brief Bind methods to Godot.
		static void _bind_methods();
		/// @brief Create an attribute operation.
		/// @param p_operand The OperationType instance.
		/// @param p_value The operation value.
		/// @return A new instance of AttributeOperation as a Ref.
		static Ref<AttributeOperation> create(OperationType p_operand, float p_value);

		/// @brief Operand.
		OperationType operand = OP_ADD;
		/// @brief Value.
		float value = 0.0f;

	public:
		bool operator==(const Ref<AttributeOperation> &buff) const;

		/// @brief Returns a new instance of AttributeOperation with the add operation.
		/// @param p_value The value to add.
		/// @return The new instance of AttributeOperation.
		static Ref<AttributeOperation> add(float p_value);
		/// @brief Returns a new instance of AttributeOperation with the divide operation.
		/// @param p_value The value to divide.
		/// @return The new instance of AttributeOperation.
		static Ref<AttributeOperation> divide(float p_value);
		/// @brief Returns a new instance of AttributeOperation with the multiply operation.
		/// @param p_value The value to multiply.
		/// @return The new instance of AttributeOperation.
		static Ref<AttributeOperation> multiply(float p_value);
		/// @brief Returns a new instance of AttributeOperation with the percentage operation.
		/// @param p_value The percentage value.
		/// @return The new instance of AttributeOperation.
		static Ref<AttributeOperation> percentage(float p_value);
		/// @brief Returns a new instance of AttributeOperation with the subtract operation.
		/// @param p_value The value to subtract.
		/// @return The new instance of AttributeOperation.
		static Ref<AttributeOperation> subtract(float p_value);
		/// @brief Returns a new instance of AttributeOperation with the set operation.
		/// @param p_value The value to set.
		/// @return The new instance of AttributeOperation.
		static Ref<AttributeOperation> forcefully_set_value(float p_value);

		/// @brief Get the operand.
		/// @return The operand.
		[[nodiscard]] int get_operand() const;
		/// @brief Get the value.
		/// @return The value.
		[[nodiscard]] float get_value() const;
		/// @brief Operate on a base value.
		/// @param p_base_value The base value to operate on.
		[[nodiscard]] float operate(float p_base_value) const;
		/// @brief Set the operand.
		void set_operand(int p_value);
		/// @brief Set the value.
		void set_value(float p_value);
	};

	class AttributeSet : public Resource
	{
		GDCLASS(AttributeSet, Resource);

	protected:
		/// @brief Bind methods to Godot.
		static void _bind_methods();
		/// @brief The attributes in the set.
		TypedArray<AttributeBase> attributes;
		/// @brief The set name.
		String set_name;

	public:
		/// @brief Equal operator overload.
		/// @param set The AttributeSet to compare.
		/// @return True if the AttributeSet is equal, false otherwise.
		bool operator==(const Ref<AttributeSet> &set) const;

		/// @brief Create an attribute set.
		AttributeSet();
		/// @brief Create an attribute set.
		/// @param p_attributes The attributes in the set.
		/// @param p_set_name The set name.
		AttributeSet(const TypedArray<AttributeBase> &p_attributes, const String &p_set_name);

		/// @brief Add an attribute to the set.
		/// @param p_attribute The attribute to add.
		/// @return True if the attribute was added, false otherwise.
		bool add_attribute(const Ref<AttributeBase> &p_attribute);
		/// @brief Add attributes to the set.
		/// @param p_attributes The attributes to add.
		/// @return The number of attributes added.
		uint16_t add_attributes(const TypedArray<AttributeBase> &p_attributes);
		/// @brief Finds the index of an attribute in the set.
		/// @param p_attribute The attribute to find.
		/// @return The index of the attribute.
		[[nodiscard]] int find(const Ref<AttributeBase> &p_attribute) const;
		/// @brief Finds an attribute by its own class_name name in the set.
		/// @param p_classname The class_name name of the attribute.
		/// @return The attribute.
		[[nodiscard]] Ref<AttributeBase> find_by_classname(const String &p_classname) const;
		/// @brief Finds an attribute by its name in the set.
		/// @param p_name The name of the attribute.
		/// @return The attribute.
		[[nodiscard]] Ref<AttributeBase> find_by_name(const String &p_name) const;
		/// @brief Gets all the attributes'
		/// names in the set.
		/// @return The attributes'
		/// name.
		[[nodiscard]] PackedStringArray get_attributes_names() const;
		/// @brief Get the attributes in the set.
		/// @return The attributes.
		[[nodiscard]] TypedArray<AttributeBase> get_attributes() const;
		/// @brief Get an attribute from the set.
		/// @param index The index of the attribute.
		/// @return The attribute.
		[[nodiscard]] Ref<AttributeBase> get_at(int index) const;
		/// @brief Get the set name.
		/// @return The set name.
		[[nodiscard]] String get_set_name() const;
		/// @brief Check if the set has an attribute.
		/// @param p_attribute The attribute to check.
		/// @return True if the set has the attribute, false otherwise.
		[[nodiscard]] bool has_attribute(const Ref<AttributeBase> &p_attribute) const;
		/// @brief Remove an attribute from the set.
		/// @param p_attribute The attribute to remove.
		/// @return True if the attribute was removed, false otherwise.
		bool remove_attribute(const Ref<AttributeBase> &p_attribute);
		/// @brief Remove attributes from the set.
		/// @param p_attributes The attributes to remove.
		/// @return The number of attributes removed.
		int remove_attributes(const TypedArray<AttributeBase> &p_attributes);
		/// @brief Push an attribute to the set.
		/// @param p_attribute The attribute to push.
		void push_back(const Ref<AttributeBase> &p_attribute);
		/// @brief Set the attributes in the set.
		/// @param p_attributes The attributes in the set.
		void set_attributes(const TypedArray<AttributeBase> &p_attributes);
		/// @brief Set the set name. Sorry for the pun.
		/// @param p_value The set name.
		void set_set_name(const String &p_value);
		/// @brief Get the number of attributes in the set.
		/// @return The number of attributes.
		[[nodiscard]] int count() const;
	};

	class AttributeBuffBase : public Resource
	{
		GDCLASS(AttributeBuffBase, Resource);

	public:
		/// @brief Changes which attributes the buff applies to.
		GDVIRTUAL1RC(TypedArray<AttributeBase>, _applies_to, Ref<AttributeSet>); // NOLINT(*-unnecessary-value-param)
		/// @brief Changes the operation to apply. If overridden, an array of AttributeOperation must be returned. This will skip the operation property.
		GDVIRTUAL2RC(TypedArray<AttributeOperation>, _operate, TypedArray<float>, Ref<AttributeSet>); // NOLINT(*-unnecessary-value-param)

	protected:
		/// @brief Bind methods to Godot.
		static void _bind_methods();
	};

	/// @brief Attribute buff.
	class AttributeBuff : public AttributeBuffBase
	{
		GDCLASS(AttributeBuff, AttributeBuffBase);

		friend class RuntimeBuff;

	public:
		enum DurationMerging : uint8_t
		{
			/// the applied buff will stack
			DURATION_MERGE_STACK,
			/// the applied buff will add its duration to the running one if any
			DURATION_MERGE_ADD,
			/// the applied buff will restart the duration
			DURATION_MERGE_RESTART,
		};

		/// @brief Queue execution types
		enum QueueExecution : uint8_t
		{
			// Starts a queued buff as soon
			// as it is added
			QUEUE_EXECUTION_PARALLEL,
			// Starts a queued buff as soon
			// as the previous finished
			QUEUE_EXECUTION_WATERFALL,
		};

		// equal operator overload
		bool operator==(const Ref<AttributeBuff> &buff) const;

		/// @brief Returns the result of the operation on the base value.
		/// @param base_value The base value to operate on. It is the attribute underlying value.
		/// @return The result of the operation.
		[[nodiscard]] float operate(float base_value) const;
		/// @brief Returns the affected attribute name.
		/// @return The affected attribute name.
		[[nodiscard]] String get_attribute_name() const;
		/// @brief Returns the buff name.
		/// @return The buff name.
		[[nodiscard]] String get_buff_name() const;
		/// @brief Returns the buff duration.
		/// @return The buff duration.
		[[nodiscard]] float get_duration() const;
		/// @brief Returns the duration merging.
		/// @return The duration merging.
		[[nodiscard]] int get_duration_merging() const;
		/// @brief Returns the operation to apply as a Ref.
		/// @return The operation to apply.
		[[nodiscard]] Ref<AttributeOperation> get_operation() const;
		/// @brief Returns the maximum number of stacks possible.
		/// @return The maximum number of stacks possible.
		[[nodiscard]] int get_stack_size() const;
		/// @brief Returns the queue execution.
		/// @return The queue execution.
		[[nodiscard]] int get_queue_execution() const;
		/// @brief Returns if the buff is transient.
		/// @return True if the buff is transient, false otherwise.
		[[nodiscard]] bool get_transient() const;
		/// @brief Returns if the buff is unique.
		/// @return True if the buff is unique, false otherwise.
		[[nodiscard]] bool get_unique() const;
		/// @brief Returns if the _operate method is overridden.
		/// @return True if the _operate method is overridden, false otherwise.
		[[nodiscard]] bool is_operate_overridden() const;
		/// @brief Returns if the buff is time-limited.
		/// @return True if the buff is time-limited,
		/// false otherwise.
		[[nodiscard]] bool is_time_limited() const;
		/// @brief Sets the affected attribute name.
		/// @param p_value The affected attribute name.
		void set_attribute_name(const String &p_value);
		/// @brief Sets the buff name.
		/// @param p_value The buff name.
		void set_buff_name(const String &p_value);
		/// @brief Sets the buff duration.
		/// @param p_value The buff duration.
		void set_duration(float p_value);
		/// @brief Sets the duration merging.
		/// @param p_value The duration merging.
		void set_duration_merging(int p_value);
		/// @brief Sets the operation to apply.
		/// @param p_value The operation to apply.
		void set_operation(const Ref<AttributeOperation> &p_value);
		/// @brief Sets the maximum number of stacks possible.
		/// @param p_value The maximum number of stacks possible.
		void set_stack_size(int p_value);
		/// @brief Sets the queue execution.
		/// @param p_value the queue execution.
		void set_queue_execution(int p_value);
		/// @brief Sets if the buff is transient.
		/// @param p_value True if the buff is transient, false otherwise.
		void set_transient(bool p_value);
		/// @brief Sets if the buff is unique.
		/// @param p_value True if the buff is unique, false otherwise.
		void set_unique(bool p_value);

	protected:
		/// @brief Bind methods to Godot.
		static void _bind_methods();

		/// @brief The affected attribute name.
		String attribute_name = "";
		/// @brief The buff name.
		String buff_name = "";
		/// @brief The buff duration.
		float duration = 0.0f;
		/// @brief The duration merging.
		/// Defaults to stack.
		DurationMerging duration_merging = DURATION_MERGE_STACK;
		/// @brief The maximum number of applications possible
		/// (aka stacking).
		/// If 0,
		/// it means infinite.
		int max_stacking = 0;
		/// @brief The operation to apply.
		Ref<AttributeOperation> operation;
		/// @brief The queue execution.
		QueueExecution queue_execution;
		/// @brief The buff is transient and will be not affect the attribute value directly.
		bool transient = false;
		/// @brief If the buff is unique and only one can be applied.
		bool unique = false;
	};

	/// @brief Attribute computation argument.
	class AttributeComputationArgument : public RefCounted
	{
		GDCLASS(AttributeComputationArgument, RefCounted)

	public:
		/// @brief The attribute buff, if any.
		[[nodiscard]] AttributeBuff *get_buff() const;

		/// @brief The operation value.
		[[nodiscard]] float get_operated_value() const;

		/// @brief The runtime attribute.
		[[nodiscard]] RuntimeAttribute *get_runtime_attribute() const;

		/// @brief Set the attribute buff.
		/// @param p_buff The attribute buff.
		void set_buff(AttributeBuff *p_buff);

		/// @brief Set the runtime attribute.
		/// @param p_value The operation value.
		void set_operated_value(const float &p_value);

		/// @brief Set the runtime attribute.
		/// @param p_runtime_attribute The runtime attribute.
		void set_runtime_attribute(RuntimeAttribute *p_runtime_attribute);

	protected:
		/// @brief Bind methods to Godot.
		static void _bind_methods();

		/// @brief The attribute buff.
		AttributeBuff *buff = nullptr;

		/// @brief The runtime attribute operated value. This value is not committed yet.
		float operated_value = 0.0f;

		/// @brief The runtime attribute.
		RuntimeAttribute *runtime_attribute = nullptr;
	};

	/// @brief Base Attribute Class.
	class AttributeBase : public Resource
	{
		GDCLASS(AttributeBase, Resource);

	protected:
		/// @brief Bind methods to Godot.
		static void _bind_methods();
		/// @brief The attribute name.
		String attribute_name;
		/// @brief The buffs affecting the attribute.
		TypedArray<AttributeBuff> buffs;

	public:
		/// @brief Get the attribute name.
		/// @return The attribute name.
		[[nodiscard]] String get_attribute_name() const;

		/// @brief Compute the value of the attribute.
		GDVIRTUAL1RC(float, _compute_value, Ref<AttributeComputationArgument>); // NOLINT(*-unnecessary-value-param)
		/// @brief Subscribes to some attributes
		GDVIRTUAL1RC(TypedArray<AttributeBase>, _derived_from, Ref<AttributeSet>); // NOLINT(*-unnecessary-value-param)

		/// @brief Get the buffs affecting the attribute.
		/// @return The buffs affecting the attribute.
		[[nodiscard]] TypedArray<AttributeBuff> get_buffs() const;
		/// @brief Set the attribute name.
		/// @param p_value The attribute name.
		void set_attribute_name(const String &p_value);
		/// @brief Set the buffs affecting the attribute.
		/// @param p_buffs The buffs affecting the attribute.
		void set_buffs(const TypedArray<AttributeBuff> &p_buffs);
	};

	/// @brief Attribute.
	class Attribute : public AttributeBase
	{
		GDCLASS(Attribute, AttributeBase);

		friend class RuntimeAttribute;

	protected:
		/// @brief Bind methods to Godot.
		static void _bind_methods();

	public:
		/// @brief Create an attribute from some parameters.
		/// @param p_attribute_name The attribute name.
		/// @param p_buffs The buffs affecting the attribute.
		/// @return The new instance of Attribute.
		static Ref<Attribute> create(const String &p_attribute_name, const TypedArray<AttributeBuff> &p_buffs);
	};

	/// @brief Runtime buff.
	class RuntimeBuff : public RefCounted
	{
		GDCLASS(RuntimeBuff, RefCounted);

	protected:
		friend class AttributeContainer;
		friend class RuntimeAttribute;

		static void _bind_methods();
		/// @brief The attribute buff reference.
		Ref<AttributeBuff> buff;
		/// @brief The time the buff was added.
		float time_left = 0.0f;
		/// @brief If the buff is unique.
		bool unique = false;

		/// @brief Returns the attributes the buff applies to.
		/// @param p_attribute_container The attribute container set to check.
		/// @return The attributes the buff applies to.
		Ref<RuntimeAttribute> applies_to(const AttributeContainer *p_attribute_container) const;
		/// @brief Operate on the runtime attributes.
		/// @param p_runtime_attributes The runtime attributes to operate on.
		/// @return The operated runtime values.
		[[nodiscard]] float operate(const Ref<RuntimeAttribute> &p_runtime_attributes) const;

	public:
		static Ref<RuntimeBuff> from_buff(const Ref<AttributeBuff> &p_buff);
		static Ref<AttributeBuff> to_buff(const Ref<RuntimeBuff> &p_buff);
		/// @brief It is the == operator overload.
		/// @param p_attribute The attribute to compare.
		/// @return True if the attribute is equal, false otherwise.
		bool operator==(const Ref<AttributeBuff> &p_attribute) const;
		/// @brief It is the == operator overload.
		/// @param p_attribute The runtime attribute to compare.
		/// @return True if the runtime attribute is equal, false otherwise.
		bool operator==(const Ref<RuntimeBuff> &p_attribute) const;
		/// @brief Returns if the buff can be applied to an attribute.
		/// @param p_attribute The attribute to check.
		/// @return True if the buff can be applied to the attribute, false otherwise.
		[[nodiscard]] bool can_apply_to_attribute(const Ref<RuntimeAttribute> &p_attribute) const;
		/// @brief Returns if the buff can be dequeued from the queue.
		/// @return True,
		// if the buff can be dequeued,
		// false otherwise.
		[[nodiscard]] bool can_dequeue() const;
		/// @brief Returns if the buff equals to another buff.
		/// @param p_buff The buff to compare.
		/// @return True if the buff is equal to the other buff, false otherwise.
		[[nodiscard]] bool equals_to(const Ref<AttributeBuff> &p_buff) const;
		/// @brief Get the attribute name.
		/// @return The attribute name.
		[[nodiscard]] String get_attribute_name() const;
		/// @brief Get the buff name.
		/// @return The buff name.
		[[nodiscard]] String get_buff_name() const;
		/// @brief Get the buff.
		/// @return The buff.
		[[nodiscard]] Ref<AttributeBuff> get_buff() const;
		/// @brief Get the duration of the buff.
		/// @return The duration of the buff.
		[[nodiscard]] float get_duration() const;
		/// @brief Get the time left for the buff to expire.
		/// @return The time left for the buff to expire.
		[[nodiscard]] float get_time_left() const;
		/// @brief Returns if the _operate method is overridden.
		/// @return True if the _operate method is overridden, false otherwise.
		[[nodiscard]] bool is_operate_overridden() const;
		/// @brief Set the buff.
		/// @param p_value The buff.
		void set_buff(const Ref<AttributeBuff> &p_value);
		/// @brief Set the duration of the buff.
		/// @param p_value The duration of the buff.
		void set_time_left(float p_value);
	};

	class RuntimeAttribute : public RefCounted
	{
		GDCLASS(RuntimeAttribute, RefCounted);

	protected:
		friend class AttributeContainer;
		friend class RuntimeBuff;

		static void _bind_methods();
		/// @brief The attribute reference.
		Ref<AttributeBase> attribute;
		/// @brief The attribute set reference.
		Ref<AttributeSet> attribute_set;
		/// @brief The attribute container reference.
		AttributeContainer *attribute_container;
		/// @brief The previous value of the attribute.
		float previous_value = 0.0f;
		/// @brief The attribute value.
		float value = 0.0f;
		/// @brief The attribute buffs.
		TypedArray<RuntimeBuff> buffs;

	public:
		/// @brief Add a buff to the attribute.
		/// @param p_buff The buff to add.
		/// @return True if the buff was added, false otherwise.
		bool add_buff(const Ref<AttributeBuff> &p_buff);
		/// @brief Add buffs to the attribute.
		/// @param p_buffs The buffs to add.
		/// @return The number of buffs added.
		int add_buffs(const TypedArray<AttributeBuff> &p_buffs);
		/// @brief Check if the attribute can receive a buff.
		/// @param p_buff The buff to check.
		/// @return True if the attribute can receive the buff, false otherwise.
		[[nodiscard]] bool can_receive_buff(const Ref<AttributeBuff> &p_buff) const;
		/// @brief Clear the buffs from the attribute.
		void clear_buffs();
		/// @brief Get the parent runtime attributes.
		/// @return An array of runtime attributes.
		[[nodiscard]] TypedArray<RuntimeAttribute> get_parent_runtime_attributes() const;
		/// @brief Check if the attribute has a buff.
		/// @param p_buff The buff to check.
		/// @return True if the attribute has the buff, false otherwise.
		[[nodiscard]] bool has_buff(const Ref<AttributeBuff> &p_buff) const;
		/// @brief Check if the attribute has ongoing buffs.
		/// @return True if the attribute has ongoing buffs, false otherwise.
		[[nodiscard]] bool has_ongoing_buffs() const;
		/// @brief Check if the attribute is computable.
		/// @return True if the attribute _compute_value is overridden.
		[[nodiscard]] bool is_computable() const;
		/// @brief Remove a buff from the attribute.
		/// @param p_buff The buff to remove.
		/// @return True if the buff was removed, false otherwise.
		bool remove_buff(const Ref<AttributeBuff> &p_buff);
		/// @brief Remove buffs from the attribute.
		/// @param p_buffs The buffs to remove.
		/// @return The number of buffs removed.
		int remove_buffs(const TypedArray<AttributeBuff> &p_buffs);
		/// @brief Get the attribute.
		/// @return The attribute.
		[[nodiscard]] Ref<Attribute> get_attribute() const;
		/// @brief Get the attribute set.
		/// @return The attribute set.
		[[nodiscard]] Ref<AttributeSet> get_attribute_set() const;
		/// @brief Get the buffed value of the attribute.
		/// @return The buffed value.
		[[nodiscard]] float get_buffed_value() const;
		/// @brief Get the attributes the attribute derives from.
		/// @return The attributes the attribute derives from.
		[[nodiscard]] TypedArray<AttributeBase> get_derived_from() const;
		/// @brief Get the previous value of the attribute.
		/// @return The previous value of the attribute.
		[[nodiscard]] float get_previous_value() const;
		/// @brief Gets the value of the attribute.
		/// @return The value of the attribute.
		[[nodiscard]] float get_value() const;
		/// @brief Get the buffs affecting the attribute.
		[[nodiscard]] TypedArray<RuntimeBuff> get_buffs() const;
		/// @brief Set the attribute.
		/// @param p_value The attribute.
		void set_attribute(const Ref<AttributeBase> &p_value);
		/// @brief Set the attribute set.w
		/// @param p_value The attribute set.
		void set_attribute_set(const Ref<AttributeSet> &p_value);
		/// @brief Sets the buffs affecting the attribute.
		/// @param p_value The buffs affecting the attribute.
		void set_buffs(const TypedArray<AttributeBuff> &p_value);
		/// @brief Sets the value of the attribute.
		/// @param p_value The value of the attribute.
		void set_value(float p_value);
	};
} //namespace gga

VARIANT_ENUM_CAST(gga::AttributeBuff::QueueExecution);
VARIANT_ENUM_CAST(gga::AttributeBuff::DurationMerging);
VARIANT_ENUM_CAST(gga::OperationType);

#endif
