#include <stdio.h>
#include <stdbool.h>
#include "include/godot/gdextension_interface.h"
#include "hello.gdextension.h"

void hello_gdextension_initialize(void *userdata, GDExtensionInitializationLevel p_level) {
  printf("initialized at level %u\n", p_level);
}
void hello_gdextension_deinitialize(void *userdata, GDExtensionInitializationLevel p_level){
  printf("deinitialized at level %u\n", p_level);
}


GDExtensionBool hello_gdextension_main(
  const GDExtensionInterface *p_interface,
  GDExtensionClassLibraryPtr p_library,
  GDExtensionInitialization *r_initialization
) {
  // Set up de/initialization functions
  r_initialization->initialize = &hello_gdextension_initialize;
  r_initialization->deinitialize = &hello_gdextension_deinitialize;
  return true;
}
