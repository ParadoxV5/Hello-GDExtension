#include <stdio.h>
#include <stdbool.h>
#include "include/godot/gdextension_interface.h"
#include "hello.gdextension.h"

#define gdextension_hash_print 2648703342 // fetch from `include/extension_api.json`

// GDExtension interface pointer
const GDExtensionInterface* INTERFACE;
// GDExtension API pointers
GDExtensionPtrConstructor StringName_from_String;
GDExtensionPtrDestructor destroy_StringName;
GDExtensionPtrDestructor destroy_String;
// Library StringNames
GDExtensionStringName stringName_print;

GDExtensionStringName CString2StringName(const char* cstring) {
  void* string;
  INTERFACE->string_new_with_latin1_chars(&string, cstring);
  GDExtensionStringName string_name;
  StringName_from_String(&string_name, (GDExtensionConstTypePtr[1]) {&string});
  destroy_String(string);
  return string_name;
}

void hello_gdextension_initialize(void *userdata, GDExtensionInitializationLevel p_level) {
  if(p_level == GDEXTENSION_INITIALIZATION_SCENE) {
    // Save used pointers
    StringName_from_String = INTERFACE->variant_get_ptr_constructor(GDEXTENSION_VARIANT_TYPE_STRING_NAME, 2); // Constructor #2
    destroy_StringName = INTERFACE->variant_get_ptr_destructor(GDEXTENSION_VARIANT_TYPE_STRING_NAME);
    destroy_String = INTERFACE->variant_get_ptr_destructor(GDEXTENSION_VARIANT_TYPE_STRING);
    // Build StringNames
    stringName_print = CString2StringName("print");
  }
  
  printf("initialized at level %u\n", p_level);
}
void hello_gdextension_deinitialize(void *userdata, GDExtensionInitializationLevel p_level) {
  if(p_level == GDEXTENSION_INITIALIZATION_SCENE) {
    // Destroy StringNames
    destroy_StringName(&stringName_print);
    // Unset stale pointers
    StringName_from_String = NULL;
    destroy_StringName = NULL;
    destroy_String = NULL;
  }
  
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
  // Save the GDExtensionInterface
  INTERFACE = p_interface;
  // Success
  return true;
}
