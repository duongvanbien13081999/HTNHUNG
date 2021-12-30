#ifndef Software_H
#define Software_H
#include "systemc.h"
#include "__common.h"
using namespace sc_core;
class Software : public sc_module {
public:
  int const static num_floors=8;
  SC_HAS_PROCESS(Software);
  Software(sc_module_name name);
  sc_in<sc_bv<num_floors>> btns_out_up;
  sc_in<sc_bv<num_floors>> btns_out_dn;
  sc_in<bool> fire_sensor;
  sc_out<bool> fire_alert;
  sc_out<bool> door_open;
  sc_out<bool> cabin_selected;
  void select_cabin();
  void alert();
};
Software::Software(sc_module_name name = sc_gen_unique_name("software")) : sc_module(name) {
  SC_THREAD(alert);
  sc_trace(file, btns_out_up, "btns_out_up");
  sc_trace(file, btns_out_dn, "btns_out_dn");
  sc_trace(file, fire_sensor, "fire_sensor");
  sc_trace(file, fire_alert, "fire_alert");
  sc_trace(file, door_open, "door_open");
  sc_trace(file, cabin_selected, "cabin_selected");
}
void Software::alert() {
  bool fireSensor;
  fireSensor = fire_sensor.read();
  if (fireSensor) {
    fire_alert.write((bool)1);
    door_open.write((bool)1);
  }
}
#endif // Software_H