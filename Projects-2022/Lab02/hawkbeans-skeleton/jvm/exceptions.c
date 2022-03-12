/* 
 * This file is part of the Hawkbeans JVM developed by
 * the HExSA Lab at Illinois Institute of Technology.
 *
 * Copyright (c) 2019, Kyle C. Hale <khale@cs.iit.edu>
 *
 * All rights reserved.
 *
 * Author: Kyle C. Hale <khale@cs.iit.edu>
 *
 * This is free software.  You are permitted to use,
 * redistribute, and modify it as specified in the 
 * file "LICENSE.txt".
 */
#include <stdlib.h>
#include <string.h>

#include <types.h>
#include <class.h>
#include <stack.h>
#include <mm.h>
#include <thread.h>
#include <exceptions.h>
#include <bc_interp.h>
#include <gc.h>

extern jthread_t * cur_thread;

/* 
 * Maps internal exception identifiers to fully
 * qualified class paths for the exception classes.
 * Note that the ones without fully qualified paths
 * will not be properly raised. 
 *
 * TODO: add the classes for these
 *
 */
static const char * excp_strs[16] __attribute__((used)) =
{
	"java/lang/NullPointerException",
	"java/lang/IndexOutOfBoundsException",
	"java/lang/ArrayIndexOutOfBoundsException",
	"IncompatibleClassChangeError",
	"java/lang/NegativeArraySizeException",
	"java/lang/OutOfMemoryError",
	"java/lang/ClassNotFoundException",
	"java/lang/ArithmeticException",
	"java/lang/NoSuchFieldError",
	"java/lang/NoSuchMethodError",
	"java/lang/RuntimeException",
	"java/io/IOException",
	"FileNotFoundException",
	"java/lang/InterruptedException",
	"java/lang/NumberFormatException",
	"java/lang/StringIndexOutOfBoundsException",
};


// what's the point of this? 
int 
hb_excp_str_to_type (char * str)
{
    for (int i = 0; i < sizeof(excp_strs)/sizeof(char*); i++) {
        if (strstr(excp_strs[i], str))
                return i;
    }
    return -1;
}



/*
 * Throws an exception given an internal ID
 * that refers to an exception type. This is to 
 * be used by the runtime (there is no existing
 * exception object, so we have to create a new one
 * and init it).
 *
 */
void
hb_throw_and_create_excp (u1 type)
{

java_class_t *exception_class = hb_get_or_load_class(excp_strs[type]);

obj_ref_t *object_class = gc_obj_alloc(exception_class);
	
	// Like a function, but calls a constructor
	if(hb_invoke_ctor(object_class)) { 
		HB_ERR("The hb_invoke_ctor failed to invoke"); 
		exit(EXIT_FAILURE); 	
	}

hb_throw_exception(object_class); 
}



/* 
 * gets the exception message from the object 
 * ref referring to the exception object.
 *
 * NOTE: caller must free the string
 *
 */
static char *
get_excp_str (obj_ref_t * eref)
{
	char * ret;
	native_obj_t * obj = (native_obj_t*)eref->heap_ptr;
		
	obj_ref_t * str_ref = obj->fields[0].obj;
	native_obj_t * str_obj;
	obj_ref_t * arr_ref;
	native_obj_t * arr_obj;
	int i;
	
	if (!str_ref) {
		return NULL;
	}

	str_obj = (native_obj_t*)str_ref->heap_ptr;
	
	arr_ref = str_obj->fields[0].obj;

	if (!arr_ref) {
		return NULL;
	}

	arr_obj = (native_obj_t*)arr_ref->heap_ptr;

	ret = malloc(arr_obj->flags.array.length+1);

	for (i = 0; i < arr_obj->flags.array.length; i++) {
		ret[i] = arr_obj->fields[i].char_val;
	}

	ret[i] = 0;

	return ret;
}


/*
 * Throws an exception using an
 * object reference to some exception object (which
 * implements Throwable). To be used with athrow.
 * If we're given a bad reference, we throw a 
 * NullPointerException.
 *
 * @return: none. exits on failure.  
 *
 */
void
hb_throw_exception (obj_ref_t * eref)
{
	if(!eref) { 
		hb_throw_and_create_excp(EXCP_NULL_PTR);  
	} 
	
	// native object and the object class
	native_obj_t *native_object = (native_obj_t *)(eref->heap_ptr); 
	java_class_t *class_object = (native_object -> class); 

	if(!class_object) { 
		HB_ERR("No class object found!"); 
		exit(EXIT_FAILURE);
	}
	
	// Name of the class object
	const char *name_class_object = hb_get_class_name(class_object); 
	
	// Method information and pointing to exception table 
	method_info_t *method_info = cur_thread->cur_frame->minfo; 
	excp_table_t *exception_table = method_info->code_attr->excp_table; 
    
    HB_ERR("Exception raised: %s %s at %s \n", cur_thread->name, name_class_object, hb_get_class_name(cur_thread->class));

	for(int i = 0; i < method_info->code_attr->excp_table_len; i++) { 
		
		u2 catch_type_idx = exception_table[i].catch_type;

		CONSTANT_Class_info_t *exception_caught = (CONSTANT_Class_info_t *)class_object->const_pool[catch_type_idx]; 	
	
        u2 name_idx = exception_caught->name_idx;
		u2 low = exception_table[i].start_pc; 
		u2 high = exception_table[i].end_pc; 
		u2 pc = cur_thread->cur_frame->pc; 

		const char* exception_type = hb_get_const_str(name_idx, class_object);
		
		if(!strcmp(exception_type, name_class_object) && pc <= high && pc >= low) { 
			var_t v; 
			v.obj = eref; 
			op_stack_t *stack = cur_thread->cur_frame->op_stack; 
			stack->oprs[(stack->sp)++] = v; 
			cur_thread->cur_frame->pc = exception_table[i].handler_pc; 
			hb_exec_method(cur_thread);
		       return; 	
		} 
	/*	else { 
			hb_pop_frame(cur_thread); 
			if (!cur_thread->cur_frame) { 
				hb_throw_exception(eref);
			}

        // Don't pop in loop.
		}*/

hb_pop_frame(cur_thread); 
if(!cur_thread->cur_frame) { 

   return;
	}	

hb_throw_exception(eref);

}
