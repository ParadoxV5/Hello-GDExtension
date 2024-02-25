#include <gdextension_interface.h>

#ifndef HELLO_GDEXTENSION_H
#define HELLO_GDEXTENSION_H

/* Godot Engine Internal Types (check sizes with `include/extension_api.json`)
  In GDScript, everything is a Variant;
  but in C/++ lands, “int”, “String” and etc. refer to the internal data which Variants wrap for GDScript convenience.
*/
typedef uint_least32_t GDExtensionString[2], GDExtensionStringName[2], GDExtensionVariant[10];

// GDExtension Variant API
extern GDExtensionInterfaceStringNewWithLatin1Chars string_new_with_latin1_chars;
extern GDExtensionPtrDestructor string_destroy;
extern GDExtensionVariantFromTypeConstructorFunc variant_from_string;
extern GDExtensionInterfaceVariantDestroy variant_destroy;
// Godot Engine Library
extern GDExtensionPtrUtilityFunction global_scope_print;

void gdextension_print(const char* string);

__attribute__((unused)) GDExtensionBool hello_gdextension_main(
  GDExtensionInterfaceGetProcAddress get_proc_address,
  __attribute__((unused)) GDExtensionClassLibraryPtr library,
  GDExtensionInitialization* r_initialization
);

#endif
