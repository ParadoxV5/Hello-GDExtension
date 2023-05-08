#include <stdio.h>
#include <stdbool.h>
#include "include/godot/gdextension_interface.h"
#include "hello.gdextension.h"

#define HASH_print 2648703342 // fetch from `include/extension_api.json`

GDExtensionStringName CString2StringName(const char* cstring) {
  GDExtensionString string;
  INTERFACE->string_new_with_latin1_chars(&string, cstring);
  GDExtensionStringName string_name;
  stringName_from_String(&string_name, (GDExtensionConstTypePtr[1]) {&string});
  destroy_String(string);
  return string_name;
}

void gdextension_print(const char* cstring) {
  GDExtensionString string;
  INTERFACE->string_new_with_utf8_chars(&string, cstring);
  GDExtensionVariant variant;
  variant_from_String(&variant, &string);
  global_print(NULL, (GDExtensionConstVariantPtr[1]) { &variant }, 1);
  INTERFACE->variant_destroy(&variant);
  destroy_String(&string);
}

void hello_gdextension_initialize(void *userdata, GDExtensionInitializationLevel p_level) {
  if(p_level == GDEXTENSION_INITIALIZATION_SCENE) {
    // Save API pointers
    stringName_from_String = INTERFACE->variant_get_ptr_constructor(GDEXTENSION_VARIANT_TYPE_STRING_NAME, 2); // Constructor #2
    destroy_StringName = INTERFACE->variant_get_ptr_destructor(GDEXTENSION_VARIANT_TYPE_STRING_NAME);
    destroy_String = INTERFACE->variant_get_ptr_destructor(GDEXTENSION_VARIANT_TYPE_STRING);
    variant_from_String = INTERFACE->get_variant_from_type_constructor(GDEXTENSION_VARIANT_TYPE_STRING);
    // Fetch GDScript methods
    GDExtensionStringName stringName_print = CString2StringName("print");
    global_print = INTERFACE->variant_get_ptr_utility_function(&stringName_print, HASH_print);
    destroy_StringName(&stringName_print);
  }
  
  printf("initialized at level %u\n", p_level);
}
void hello_gdextension_deinitialize(void *userdata, GDExtensionInitializationLevel p_level) {
  if(p_level == GDEXTENSION_INITIALIZATION_SCENE) {
    // Unset stale pointers
    stringName_from_String = NULL;
    destroy_StringName = NULL;
    destroy_String = NULL;
    global_print = NULL;
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
