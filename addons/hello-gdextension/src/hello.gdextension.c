#include <stdbool.h>
#include <stdio.h>
#include "hello.gdextension.h"

#define HASH_print 2648703342 // Fetch hash from `include/extension_api.json`

// GDExtension interface pointer
GDExtensionInterfaceGetProcAddress GetProcAddress;
// GDExtension API pointers
GDExtensionPtrConstructor stringName_from_String;
GDExtensionPtrDestructor destroy_StringName;
GDExtensionPtrDestructor destroy_String;
GDExtensionVariantFromTypeConstructorFunc variant_from_String;
// GDExtension pointers
GDExtensionInterfaceStringNewWithLatin1Chars string_new_with_latin1_chars;
GDExtensionInterfaceStringNewWithUtf8Chars string_new_with_utf8_chars;
GDExtensionInterfaceVariantDestroy variant_destroy;
// Library Functions
GDExtensionPtrUtilityFunction global_print;

GDExtensionStringName CString2StringName(const char* cstring) {
  GDExtensionString string;
  string_new_with_latin1_chars(&string, cstring);
  GDExtensionStringName string_name;
  stringName_from_String(&string_name, (GDExtensionConstTypePtr[1]) {&string});
  destroy_String(&string);
  return string_name;
}

void gdextension_print(const char* cstring) {
  GDExtensionString string;
  string_new_with_utf8_chars(&string, cstring);
  GDExtensionVariant variant;
  variant_from_String(&variant, &string);
  global_print(NULL, (GDExtensionConstVariantPtr[1]) {&variant}, 1);
  variant_destroy(&variant);
  destroy_String(&string);
}

void hello_gdextension_initialize(__attribute__((unused)) void *userdata, GDExtensionInitializationLevel p_level) {
  if(p_level == GDEXTENSION_INITIALIZATION_SCENE) {
    // GDExtension API pointers
    stringName_from_String = (
      (GDExtensionInterfaceVariantGetPtrConstructor)GetProcAddress("variant_get_ptr_constructor")
    )(GDEXTENSION_VARIANT_TYPE_STRING_NAME, 2); // Constructor #2
    GDExtensionInterfaceVariantGetPtrDestructor variant_get_ptr_destructor =
      (GDExtensionInterfaceVariantGetPtrDestructor)GetProcAddress("variant_get_ptr_destructor");
    destroy_StringName = variant_get_ptr_destructor(GDEXTENSION_VARIANT_TYPE_STRING_NAME);
    destroy_String = variant_get_ptr_destructor(GDEXTENSION_VARIANT_TYPE_STRING);
    variant_from_String = (
      (GDExtensionInterfaceGetVariantFromTypeConstructor)GetProcAddress("get_variant_from_type_constructor")
    )(GDEXTENSION_VARIANT_TYPE_STRING);
    // GDExtension pointers
    string_new_with_latin1_chars = (GDExtensionInterfaceStringNewWithLatin1Chars)GetProcAddress("string_new_with_latin1_chars");
    string_new_with_utf8_chars = (GDExtensionInterfaceStringNewWithUtf8Chars)GetProcAddress("string_new_with_utf8_chars");
    variant_destroy = (GDExtensionInterfaceVariantDestroy)GetProcAddress("variant_destroy");
    // Fetch GDScript methods
    GDExtensionStringName stringName_print = CString2StringName("print");
    global_print = (
      (GDExtensionInterfaceVariantGetPtrUtilityFunction)GetProcAddress("variant_get_ptr_utility_function")
    )(&stringName_print, HASH_print);
    destroy_StringName(&stringName_print);
    // Hello, World!
    gdextension_print("Hello, GDExtension!");
  }
  
  printf("initialized at level %u\n", p_level);
}
void hello_gdextension_deinitialize(__attribute__((unused)) void *userdata, GDExtensionInitializationLevel p_level) {
  if(p_level == GDEXTENSION_INITIALIZATION_SCENE) {
    // Goodbye, World!
    gdextension_print("Goodbye, GDExtension!");
    // Unset stale pointers
    global_print = NULL;
    stringName_from_String = NULL;
    destroy_StringName = NULL;
    destroy_String = NULL;
    string_new_with_latin1_chars = NULL;
    string_new_with_utf8_chars = NULL;
    variant_destroy = NULL;
  }
  
  printf("deinitialized at level %u\n", p_level);
}

GDExtensionBool hello_gdextension_main(
  GDExtensionInterfaceGetProcAddress p_get_proc_address,
  GDExtensionClassLibraryPtr p_library,
  GDExtensionInitialization* r_initialization
) {
  // Set up de/initialization functions
  r_initialization->initialize = &hello_gdextension_initialize;
  r_initialization->deinitialize = &hello_gdextension_deinitialize;
  // Save the GDExtensionInterface
  GetProcAddress = p_get_proc_address;
  // Success
  return true;
}
