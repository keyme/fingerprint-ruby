#include <stdio.h>

#include "ruby.h"
#include "compare/compare.h"

VALUE verify_user_wrapper(VALUE self, VALUE db_print, VALUE check_print) {
	bool result;
	unsigned char *db, *check;
	unsigned int db_len, check_len;

	Check_Type(db_print, T_ARRAY);
	Check_Type(check_print, T_ARRAY);

	db_len = RARRAY_LEN(db_print);
	check_len = RARRAY_LEN(check_print);

	db = (unsigned char*) malloc(db_len);
	check = (unsigned char*) malloc(check_len);

	for(unsigned int i = 0; i < db_len; i++) {
		db[i] = NUM2UINT(rb_ary_entry(db_print, i));
	}
	for(unsigned int i = 0; i < check_len; i++) {
		check[i] = NUM2UINT(rb_ary_entry(check_print, i));
	}

	result = VerifyUser(db, db_len, check, check_len);

	free(db);
	free(check);

	return result ? Qtrue : Qfalse;
}

VALUE load_print_wrapper(VALUE self, VALUE path) {
	VALUE result;
	unsigned char *print;
	unsigned int printSize;

	Check_Type(path, T_STRING);
	LoadPrint(RSTRING_PTR(path), &print, &printSize);

	result = rb_ary_new();
	for(unsigned int i = 0; i < printSize; i++) {
		rb_ary_push(result, UINT2NUM(print[i]));
	}

	free(print);

	return result;
}

VALUE rb_mKeyMe;
VALUE rb_mFingerprint;

extern "C" {
	void Init_fingerprint() {
		rb_mKeyMe = rb_define_module("KeyMe");
		rb_mFingerprint = rb_define_module_under(
			rb_mKeyMe,
			"Fingerprint"
		);

		rb_define_singleton_method(
			rb_mFingerprint,
			"verify_user",
			RUBY_METHOD_FUNC(verify_user_wrapper),
			2
		);
		rb_define_singleton_method(
			rb_mFingerprint,
			"load_print",
			RUBY_METHOD_FUNC(load_print_wrapper),
			1
		);
	}
}
