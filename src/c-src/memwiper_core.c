#include <Python.h>

static PyObject *MemWiper_CoreError;

static PyObject *
memwiper_core_wipeit(PyObject *self, PyObject *str)
{
Py_UNICODE *buffer;
long buffer_size, i;
int kind;

    /* 
     * Checking the type to avoid nasty things.
     */
    if (!PyUnicode_Check(str))
    {
        PyErr_BadArgument();
        return NULL;
    }

    /* 
     * Checking for "readiness"...
     * Whatever that means.
     * If not ready, push up an exception.
     * TODO: Check what "ready" exactly means and the implications
     */
    if (PyUnicode_READY(str)){
        PyErr_SetString(MemWiper_CoreError, "Unicode object is not Ready!");
        return NULL;
    }

    buffer = PyUnicode_DATA(str);
    kind = PyUnicode_KIND(str);
    buffer_size = (long)PyUnicode_GET_LENGTH(str);
    for (i=0;i<=(buffer_size-1);i++)
    {
        PyUnicode_WRITE(kind, buffer, i, (Py_UCS4)0);
    }
    return PyUnicode_FromString("");
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
Also could raise MemWiperError  exception if the string is not in it \
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
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   MemWiper_CoreMethods
};

PyMODINIT_FUNC
PyInit_memwiper_core(void)
{
    PyObject *m;
    MemWiper_CoreError = PyErr_NewException("memwiper_core.error", NULL, NULL);
    Py_INCREF(MemWiper_CoreError);
    m = PyModule_Create(&MemWiper_Coremodule);
    PyModule_AddObject(m, "error", MemWiper_CoreError);
    return m;
}
