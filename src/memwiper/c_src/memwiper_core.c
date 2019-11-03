#include <Python.h>
#include <pyhash.h>


static PyObject *MemWiper_CoreError;


static PyObject *
memwiper_core_wipeit(PyObject *self, PyObject *str)
{
Py_UNICODE *buffer;
PyGILState_STATE gilstate;
PyASCIIObject *str_obj;
long buffer_size, i;
int kind, refc;

	/*
	 * Checking the type to avoid nasty things.
	 */
	if (!PyUnicode_Check(str))
	{
		PyErr_BadArgument();
		Py_RETURN_NONE;
	}

	/*
	 * Checking for "readiness"...
	 * If not ready, push up an exception.
	 */
	if (PyUnicode_READY(str)){
		PyErr_SetString(MemWiper_CoreError, "Precheck: Unicode object is not Ready!");
		Py_RETURN_NONE;
	}
	/*
	 * Get the low level info of the string
	 */
	str_obj = (PyASCIIObject *)(str);
	buffer = PyUnicode_DATA(str);
	kind = PyUnicode_KIND(str);
	refc = Py_REFCNT(str);
	buffer_size = (long)PyUnicode_GET_LENGTH(str);

	/*
	 * Setup the filler character for the string
	 *  based on the 'kind' (UCS width) we set
	 *  the 'filler' of the same size
	 */
	PyObject *filler;
	Py_UCS4 *filler_codepoint;
	const char *filler_char[3] = {"\U000000ff", "\U0000ffff", "\U000fffff"};
	switch (kind){
		/* 4 byte filler, the value is between the unicode range in python */
		case 4:
			filler = PyUnicode_FromString(filler_char[2]);
			break;
		/* 2 byte filler */
		case 2:
			filler = PyUnicode_FromString(filler_char[1]);
			break;
		/* 1 byte filler */
		default:
			filler = PyUnicode_FromString(filler_char[0]);
			break;
	}
	filler_codepoint = PyUnicode_AsUCS4Copy(filler);

	#ifdef MEMWIPER_DEBUG
	PySys_WriteStderr("kind: %d - refc: %d - buffer size: %ld\n", kind, refc, buffer_size);
        PySys_WriteStderr("Pre hash: %ld\n", str_obj->hash);
	#endif

	/*
	 * Ensure the gil is hold to avoid multiple thread
	 * broke this string manipulation.
	 */
	gilstate = PyGILState_Ensure();
	#ifdef MEMWIPER_DEBUG
        PySys_WriteStderr("GIL Taked!\n");
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
		finalsize = PyUnicode_Fill(str, 0, buffer_size-1, *filler_codepoint);
		if (finalsize != buffer_size){
			PySys_WriteStderr("Using PyUnicode_fill and the spected size is diferent:\n");
			PySys_WriteStderr("buffer_size: %ld - finalsize: %d\n", buffer_size, finalsize);
			PyErr_SetString(MemWiper_CoreError, "Using PyUnicode_fill and the resulting size is diferent.\n");
			PyGILState_Release(gilstate);
			Py_RETURN_NONE;
		}
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
			PyUnicode_WRITE(kind, buffer, i, *filler_codepoint);
		}
	}

	/*
	 * Releasing the gil ASAP
	 */
	Py_DECREF(filler_codepoint);
	Py_DECREF(filler);
	PyGILState_Release(gilstate);

	#ifdef MEMWIPER_DEBUG
        PySys_WriteStderr("GIL Released! - Returning!\n");
	#endif

	if (PyUnicode_READY(str)){
		PyErr_SetString(MemWiper_CoreError, "Postcheck: Unicode object is not Ready!");
		PyGILState_Release(gilstate);
		Py_RETURN_NONE;
	}

	#ifdef MEMWIPER_DEBUG
        PySys_WriteStderr("Post Ready check was OK!\n");
	PySys_WriteStderr("Current hash: %ld\n", str_obj->hash);
	#endif

	if (str_obj->hash != -1)
		str_obj->hash = _Py_HashBytes(buffer, buffer_size*kind);

	#ifdef MEMWIPER_DEBUG
        PySys_WriteStderr("New hash: %ld\n", str_obj->hash);
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
