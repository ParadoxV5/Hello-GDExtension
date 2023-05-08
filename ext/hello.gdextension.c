#include <stdbool.h>
#include "include/godot/gdextension_interface.h"
#include "hello.gdextension.h"

GDExtensionBool hello_gdextension_main(
  const GDExtensionInterface *p_interface,
  GDExtensionClassLibraryPtr p_library,
  GDExtensionInitialization *r_initialization
) {
  return true;
}
