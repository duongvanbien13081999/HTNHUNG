#ifndef Elevator_H
#define Elevator_H
#include "systemc.h"
#include "__common.h"
using namespace sc_core;
class Elevator : public sc_module {
public:
  int const static num_floors=8;
  SC_HAS_PROCESS(Elevator);
  Elevator(sc_module_name name);
  sc_in<sc_bv<num_floors>> btns_select_floor;
  sc_in<sc_bv<num_floors>> current_floor;
  sc_in<bool> door_open;
  sc_in<sc_bv<num_floors>> floor_sensor;
  sc_in<bool> btn_close;
  sc_in<bool> btn_open;
  sc_in<bool> cabin_selected;
  sc_in<sc_bv<num_floors>> btns_out_up;
  sc_in<sc_bv<num_floors>> btns_out_dn;
  sc_in<bool> over_weight_sensor;
  sc_out<bool> overload_alert;
  sc_out<bool> dir_up;
  sc_out<bool> dir_dn;
  sc_out<bool> motor_up;
  sc_out<bool> motor_dn;
  sc_out<sc_bv<num_floors>> doors_opened;
  sc_out<sc_bv<num_floors>> led_select_floor;
  sc_out<bool> led_up;
  sc_out<bool> led_down;
  void elevator_system();
};
Elevator::Elevator(sc_module_name name = sc_gen_unique_name("elevator")) : sc_module(name) {
  SC_THREAD(elevator_system);
  sc_trace(file, btns_select_floor, "btns_select_floor");
  sc_trace(file, current_floor, "current_floor");
  sc_trace(file, door_open, "door_open");
  sc_trace(file, floor_sensor, "floor_sensor");
  sc_trace(file, btn_close, "btn_close");
  sc_trace(file, btn_open, "btn_open");
  sc_trace(file, cabin_selected, "cabin_selected");
  sc_trace(file, btns_out_up, "btns_out_up");
  sc_trace(file, btns_out_dn, "btns_out_dn");
  sc_trace(file, over_weight_sensor, "over_weight_sensor");
  sc_trace(file, overload_alert, "overload_alert");
  sc_trace(file, dir_up, "dir_up");
  sc_trace(file, dir_dn, "dir_dn");
  sc_trace(file, motor_up, "motor_up");
  sc_trace(file, motor_dn, "motor_dn");
  sc_trace(file, doors_opened, "doors_opened");
  sc_trace(file, led_select_floor, "led_select_floor");
  sc_trace(file, led_up, "led_up");
  sc_trace(file, led_down, "led_down");
}

void Elevator::elevator_system() {
  int s_floor, cr_floor;
  bool weight_sensor;
  bool fire_alert;
  sc_bv<8> cur_floor;
  sc_bv<8> select_floor;

  weight_sensor = over_weight_sensor.read();
  fire_alert = door_open.read();
  cur_floor = current_floor.read();
  select_floor = btns_select_floor.read();

  for(int i = 0; i < 8; i++) {
    if (select_floor[i]==1) {
      s_floor = i;
    }
    if (cur_floor[i] == 1) {
      cr_floor = i + 1;
    }
  }
  if (fire_alert) {
    doors_opened.write(cur_floor);
  }
  else if (weight_sensor) {
    overload_alert.write((bool)1);
    doors_opened.write(cur_floor);
  }
  else {
    led_select_floor.write(select_floor);
    if (s_floor > cr_floor) {
      dir_up.write((bool)1);
      led_up.write((bool)1);
      motor_up.write((bool)1);
      doors_opened.write(select_floor);
    }
    else {
      dir_dn.write((bool)1);
      led_down.write((bool)1);
      motor_dn.write((bool)1);
      doors_opened.write(select_floor);
    }
  }
}
#endif // Elevator_H