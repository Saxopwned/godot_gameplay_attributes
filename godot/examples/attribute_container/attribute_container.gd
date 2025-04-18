extends VBoxContainer

const ADD_1_PERCENT = preload("res://examples/attribute_container/buffs/add_1_percent.tres")
const ADD_1_PERCENT_FOR_5_SECONDS = preload("res://examples/attribute_container/buffs/add_1_percent_for_5_seconds.tres")
const ADD_5_FOR_5_SECONDS = preload("res://examples/attribute_container/buffs/add_5_for_5_seconds.tres")
const REMOVE_1_PERCENT = preload("res://examples/attribute_container/buffs/remove_1_percent.tres")
const REMOVE_1_PERCENT_FOR_5_SECONDS = preload("res://examples/attribute_container/buffs/remove_1_percent_for_5_seconds.tres")
const REMOVE_5_FOR_5_SECONDS = preload("res://examples/attribute_container/buffs/remove_5_for_5_seconds.tres")
const BUFF_DURATION: PackedScene = preload("res://examples/attribute_container/buff_duration.tscn")

const BUFFS = [
	ADD_1_PERCENT,
	ADD_1_PERCENT_FOR_5_SECONDS,
	ADD_5_FOR_5_SECONDS,
	REMOVE_1_PERCENT,
	REMOVE_1_PERCENT_FOR_5_SECONDS,
	REMOVE_5_FOR_5_SECONDS,
]

# Vars
@onready var attribute_container: AttributeContainer = $AttributeContainer
@onready var attribute_value_display: ProgressBar = $CenterContainer/VBoxContainer/AttributeValueDisplay
@onready var decrease_value: Button = %DecreaseValue
@onready var increase_value: Button = %IncreaseValue
@onready var buffs_selection: MenuButton = %BuffsSelection
@onready var buffs_selection_container: VBoxContainer = %BuffsSelectionContainer


func _on_attribute_buff_added(buff: RuntimeBuff) -> void:
	print("_on_attribute_buff_added", buff)
	draw_attribute()


func _on_attribute_buff_dequeued(buff: RuntimeBuff) -> void:
	print("_on_attribute_buff_dequeued", buff)
	draw_attribute()


func _on_attribute_buff_enqueued(buff: RuntimeBuff) -> void:
	print("_on_attribute_buff_enqueued", buff, buff.buff.buff_name)
	draw_attribute()
	
	var progress = BUFF_DURATION.instantiate()
	buffs_selection_container.add_child(progress)
	progress.set_buff(buff)


func _on_attribute_buff_removed(buff: RuntimeBuff) -> void:
	print("attribute_buff_removed", buff)
	draw_attribute()


func _on_attribute_changed(attribute: RuntimeAttribute, previous_value: float, new_value: float) -> void:
	print("_on_attribute_changed", attribute, previous_value, new_value)
	attribute_value_display.value = attribute.get_constrained_value()


func _ready():
	var popup = buffs_selection.get_popup()
	var timer = Timer.new()
	
	add_child(timer)
	
	timer.timeout.connect(func ():
		print(attribute_container.get_attribute_by_name(TestAttribute000.ATTRIBUTE_NAME).get_buffed_value())
	)
	timer.wait_time = 2.0
	timer.start()

	popup.id_pressed.connect(func (id: int) -> void:
		attribute_container.apply_buff(BUFFS[id])
	)

	for buff in BUFFS:
		popup.add_item(buff.buff_name)

	attribute_container.attribute_changed.connect(_on_attribute_changed)
	attribute_container.buff_applied.connect(_on_attribute_buff_added)
	attribute_container.buff_dequed.connect(_on_attribute_buff_dequeued)
	attribute_container.buff_enqueued.connect(_on_attribute_buff_enqueued)
	attribute_container.buff_removed.connect(_on_attribute_buff_removed)

	for attr in attribute_container.get_attributes():
		attr.attribute_changed.connect(_on_attribute_changed)
	
	decrease_value.pressed.connect(func ():
		attribute_container.apply_buff(make_debuff(1.0))	
	)
	
	increase_value.pressed.connect(func ():
		attribute_container.apply_buff(make_buff(1.0))
	)
	
	draw_attribute()


func make_debuff(value: float) -> AttributeBuff:
	var buff = AttributeBuff.new()

	buff.attribute_name = TestAttribute000.ATTRIBUTE_NAME
	buff.operation = AttributeOperation.subtract(value)
	buff.transient = false

	return buff


func make_buff(value: float) -> AttributeBuff:
	var buff = AttributeBuff.new()

	buff.attribute_name = TestAttribute000.ATTRIBUTE_NAME
	buff.operation = AttributeOperation.add(value)
	buff.transient = false

	return buff


func draw_attribute() -> void:
	var attribute = attribute_container.get_attribute_by_name(TestAttribute000.ATTRIBUTE_NAME)

	if attribute:
		attribute_value_display.value = attribute.get_buffed_value()
		print("buffed value is " + str(attribute.get_buffed_value()))
