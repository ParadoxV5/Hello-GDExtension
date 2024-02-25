#include <stdbool.h>
#include <stdio.h>
#include "hello.gdextension.h"

// GDExtension pointers
GDExtensionInterfaceStringNewWithLatin1Chars string_new_with_latin1_chars;
GDExtensionPtrDestructor string_destroy;
GDExtensionVariantFromTypeConstructorFunc variant_from_string;
GDExtensionInterfaceVariantDestroy variant_destroy;
// Godot Library Functions
GDExtensionPtrUtilityFunction global_scope_print;

void gdextension_print(const char* cstring) {
  GDExtensionString string;
  string_new_with_latin1_chars(string, cstring);
  GDExtensionVariant variant;
  variant_from_string(variant, string);
  global_scope_print(NULL, (GDExtensionConstVariantPtr[1]) {variant}, 1);
  variant_destroy(variant);
  string_destroy(string);
}

void hello_gdextension_initialize(void* userdata, GDExtensionInitializationLevel level) {
  if(level == GDEXTENSION_INITIALIZATION_SCENE) {
    GDExtensionInterfaceGetProcAddress get_proc_address = userdata;
    // GDExtension pointers
    string_new_with_latin1_chars =
      (GDExtensionInterfaceStringNewWithLatin1Chars)get_proc_address("string_new_with_latin1_chars");
    variant_from_string = (
      (GDExtensionInterfaceGetVariantFromTypeConstructor)get_proc_address("get_variant_from_type_constructor")
    )(GDEXTENSION_VARIANT_TYPE_STRING);
    string_destroy = (
      (GDExtensionInterfaceVariantGetPtrDestructor)get_proc_address("variant_get_ptr_destructor")
    )(GDEXTENSION_VARIANT_TYPE_STRING);
    variant_destroy = (GDExtensionInterfaceVariantDestroy)get_proc_address("variant_destroy");
    
    // Fetch GDScript `@GlobalScope#print`
    GDExtensionStringName string_name_print;
    (
      (GDExtensionInterfaceStringNameNewWithLatin1Chars)get_proc_address("string_name_new_with_latin1_chars")
    )(string_name_print, "print", true);
    #define HASH_global_scope_print 2648703342 // Fetch hash from `include/extension_api.json`
    global_scope_print = (
      (GDExtensionInterfaceVariantGetPtrUtilityFunction)get_proc_address("variant_get_ptr_utility_function")
    )(string_name_print, HASH_global_scope_print);
    
    // Hello, World!
    gdextension_print("Hello, GDExtension!");
  }
  
  printf("initialized at level %u\n", level);
}
void hello_gdextension_deinitialize(__attribute__((unused)) void* userdata, GDExtensionInitializationLevel level) {
  if(level == GDEXTENSION_INITIALIZATION_SCENE) {
    // Unset stale pointers
    global_scope_print = NULL;
    variant_from_string = NULL;
    string_new_with_latin1_chars = NULL;
    variant_destroy = NULL;
    string_destroy = NULL;
  }
  
  printf("deinitialized at level %u\n", level);
}

__attribute__((used)) GDExtensionBool hello_gdextension_main(
  GDExtensionInterfaceGetProcAddress get_proc_address,
  __attribute__((unused)) GDExtensionClassLibraryPtr library,
  GDExtensionInitialization* r_initialization
) {
  // Set up de/initialization functions
  r_initialization->minimum_initialization_level = GDEXTENSION_INITIALIZATION_SCENE;
  r_initialization->initialize = hello_gdextension_initialize;
  r_initialization->deinitialize = hello_gdextension_deinitialize;
  // Save the GDExtensionInterface as our userdata of choice
  r_initialization->userdata = get_proc_address;
  // Success
  return true;
}
