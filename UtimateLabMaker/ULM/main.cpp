#define _CRT_SECURE_NO_WARNINGS

#include "common.h"
#include "menu.h"
#include "Metasfer0us.h"
#include "TheDoctorWhoo.h"

// Metasfer0us

void main() {	
  ua();
  Menu main("Головне меню", "Вихід");
  main.add("Тест", []() {
    for (int toKek = 1; toKek != 0; input("Kek", toKek));
    return 1;
  });
  main.add("Metasfer0us", metasfer0us);
  main.add("TheDoctorWhoo", drWho);
  main.cycle();
}