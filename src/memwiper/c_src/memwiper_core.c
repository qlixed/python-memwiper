#include <Python.h>


static PyObject *MemWiper_CoreError;


/*
 * TODO: Rehash the string someway.
 */
static PyObject *
memwiper_core_wipeit(PyObject *self, PyObject *str)
{
Py_UCS4 null_codepoint;
Py_UNICODE *buffer;
PyGILState_STATE gilstate;
long buffer_size, i;
int kind, refc;

	/*
	 * Ensure the gil is hold to avoid multiple thread
	 * broke this string manipulation.
	 */
	gilstate = PyGILState_Ensure();

	/* 
	 * Checking the type to avoid nasty things.
	 */
	if (!PyUnicode_Check(str))
	{
		PyGILState_Release(gilstate);
		PyErr_BadArgument();
		Py_RETURN_NONE;
	}

	/* 
	 * Checking for "readiness"...
	 * Whatever that means.
	 * If not ready, push up an exception.
	 */
	if (PyUnicode_READY(str)){
		PyErr_SetString(MemWiper_CoreError, "Precheck: Unicode object is not Ready!");
		PyGILState_Release(gilstate);
		Py_RETURN_NONE;
	}

	buffer = PyUnicode_DATA(str);
	kind = PyUnicode_KIND(str);
	refc = Py_REFCNT(str);
	buffer_size = (long)PyUnicode_GET_LENGTH(str);
	null_codepoint = (Py_UCS4)0;
#ifdef MEMWIPER_DEBUG
	PySys_WriteStderr("kind: %d - refc: %d - buffer size: %ld\n", kind, refc, buffer_size);
#endif
	/*
	 *
	 * If refcount is 1 is OK to use PyUnicode_Fill()
	 */
	if (refc == 1) {
#ifdef MEMWIPER_DEBUG
		PySys_WriteStderr("REFCNT=1 - Using PyUnicode_Fill");
#endif
		int finalsize;
		finalsize = PyUnicode_Fill(str, 0, buffer_size-1, null_codepoint);
#ifdef MEMWIPER_DEBUG
		PySys_WriteStderr("buffer_size: %ld - finalsize: %d\n", buffer_size, finalsize);
#endif
	}else{
	/*
	 * Overwirte the current str buffer "manually"
	*/
#ifdef MEMWIPER_DEBUG
		PySys_WriteStderr("REFCNT!=1 - Using for+PyUnicode_WRITE\n");
#endif
		for (i=0;i<buffer_size;i++)
		{
#ifdef MEMWIPER_DEBUG
	        	PySys_WriteStderr("Writing %ld of %ld\n", i, (buffer_size-1));
#endif
			PyUnicode_WRITE(kind, buffer, i, null_codepoint);
#ifdef MEMWIPER_DEBUG
                        PySys_WriteStderr("It was written %ld of %ld\n", i, (buffer_size-1));
#endif
		}
	}
#ifdef MEMWIPER_DEBUG
        PySys_WriteStderr("All Written! goint to ready test\n");
#endif
	if (PyUnicode_READY(str)){
		PyErr_SetString(MemWiper_CoreError, "Postcheck: Unicode object is not Ready!");
		PyGILState_Release(gilstate);
		Py_RETURN_NONE;
	}
#ifdef MEMWIPER_DEBUG
        PySys_WriteStderr("Post Ready check was OK!\n");
#endif
	/*
	 * Releasing the gil ASAP
	 */
	PyGILState_Release(gilstate);
#ifdef MEMWIPER_DEBUG
        PySys_WriteStderr("GIL Released! - Returning!\n");
#endif
	Py_RETURN_NONE;
}


/*
 * Required stuff to make the python 3 module
 */

/*
 * Methods of the module declaration
 */
static PyMethodDef MemWiper_CoreMethods[] = {
	{"wipeit", memwiper_core_wipeit, METH_O, 
		PyDoc_STR("wipeit(s) -> str(\"\")\n\n\
Clear the memory of the string passed as \
parameter.\n\
Could raise TypeError if you use a parameter that is not a string.\n\
Also could raise MemWiperError exception if the string is not in it \
canonical representation, this usually never happen, but it MAY happen \
under weird circumstances.\n\
  :param s: The string you want to overwrite.\n\
  :return: An empty string.")},
	{NULL, NULL, 0, NULL}
};

/*
 * Module definition
 */
static struct PyModuleDef MemWiper_Coremodule = {
   PyModuleDef_HEAD_INIT,
   "memwiper_core",   /* name of module */
   NULL, /* module documentation, may be NULL */
   -1,   /* size of per-interpreter state of the module,
	or -1 if the module keeps state in global variables. */
   MemWiper_CoreMethods
};

PyMODINIT_FUNC
PyInit_memwiper_core(void)
{
	PyObject *m;
	m = PyModule_Create(&MemWiper_Coremodule);
	if (m == NULL)
	        return NULL;
	MemWiper_CoreError = PyErr_NewException("memwiper_core.error", NULL, NULL);
	Py_INCREF(MemWiper_CoreError);
	PyModule_AddObject(m, "error", MemWiper_CoreError);
	return m;
}
