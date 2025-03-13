/**************************************************************************/
/*  buff_pool_queue.cpp                                                   */
/**************************************************************************/
/*                         This file is part of:                          */
/*                        Godot Gameplay Systems                          */
/*              https://github.com/OctoD/godot-gameplay-systems           */
/**************************************************************************/
/* Read the license file in this repo.						              */
/**************************************************************************/

#include "buff_pool_queue.hpp"
#include "attribute.hpp"

using namespace gga;

void BuffPoolQueue::_bind_methods()
{
	/// adds signals
	ADD_SIGNAL(MethodInfo("attribute_buff_dequeued", PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeBuff")));
	ADD_SIGNAL(MethodInfo("attribute_buff_enqueued", PropertyInfo(Variant::OBJECT, "buff", PROPERTY_HINT_RESOURCE_TYPE, "RuntimeBuff")));
}

BuffPoolQueue::BuffPoolQueue()
{
	tick = 0.0f;
	server_authoritative = false;
}

void BuffPoolQueue::_exit_tree()
{
	clear();
}

void BuffPoolQueue::handle_physics_process(const double p_delta)
{
	tick += p_delta;

	if (Math::is_equal_approx(tick, 1.0)) {
		const double discarded = tick - 1.0;
		tick = discarded;
		process_items(discarded);
	}
}

void BuffPoolQueue::enqueue(const Ref<RuntimeBuff> &p_buff)
{
	if (server_authoritative && !is_multiplayer_authority()) {
		return;
	}

	queue.push_back(p_buff);
	emit_signal("attribute_buff_enqueued", p_buff);
}

bool BuffPoolQueue::get_server_authoritative() const
{
	return server_authoritative;
}

void BuffPoolQueue::clear()
{
	queue.clear();
}

void BuffPoolQueue::process_items(const double &p_discarded)
{
	if (server_authoritative && !is_multiplayer_authority()) {
		return;
	}

	const float discarded_float = static_cast<float>(p_discarded) + 1.0f;

	for (int64_t i = queue.size() - 1; i >= 0; i--) {
		Ref<RuntimeBuff> buff = queue[i];
		buff->set_time_left(buff->get_time_left() - discarded_float);

		if (buff->can_dequeue()) {
			queue.remove_at(i);
			emit_signal("attribute_buff_dequeued", buff);
		}
	}
}

void BuffPoolQueue::set_server_authoritative(const bool &p_server_authoritative)
{
	server_authoritative = p_server_authoritative;
}
