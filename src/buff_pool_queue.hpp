/**************************************************************************/
/*  buff_pool_queue.hpp                                                   */
/**************************************************************************/
/*                         This file is part of:                          */
/*                        Godot Gameplay Systems                          */
/*              https://github.com/OctoD/godot-gameplay-systems           */
/**************************************************************************/
/* Read the license file in this repo.						              */
/**************************************************************************/

#ifndef GGA_BUFF_POOL_QUEUE_HPP
#define GGA_BUFF_POOL_QUEUE_HPP

#include <godot_cpp/classes/node.hpp>

using namespace godot;

namespace octod::gameplay::attributes
{
	class AttributeBuff;
	class RuntimeBuff;

	class BuffPoolQueue : public Node
	{
		GDCLASS(BuffPoolQueue, Node);

	public:
		BuffPoolQueue();

		/// @brief Overridden _exit_tree method.
		void _exit_tree() override;
		/// @brief Overridden _physics_process method.
		void _physics_process(double p_delta) override;
		/// @brief Adds a buff to the queue.
		void enqueue(const Ref<RuntimeBuff> &p_buff);
		/// @brief Clears the queue.
		void clear();
		/// @brief Processes the items in the queue.
		void process_items(const double &p_discarded);

	protected:
		/// @brief Binds methods to Godot.
		static void _bind_methods();
		/// @brief The current tick.
		double tick;
		/// @brief The queue of buffs.
		TypedArray<RuntimeBuff> queue;
	};
} //namespace gga

#endif