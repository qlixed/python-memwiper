#include <Python.h>

static PyObject *MemWiper_UtilsError;


static PyObject *
memwiper_utils_kind(PyObject *self, PyObject *str)
{
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
        PyErr_SetString(MemWiper_UtilsError, "Unicode object is not Ready!");
        return NULL;
    }

    kind = PyUnicode_KIND(str);
    if (kind == PyUnicode_WCHAR_KIND) return PyUnicode_FromString("Wide Char");
    if (kind == PyUnicode_1BYTE_KIND) return PyUnicode_FromString("1 Byte");
    if (kind == PyUnicode_2BYTE_KIND) return PyUnicode_FromString("2 Byte");
    return PyUnicode_FromString("4 Byte");
}

static PyObject *
memwiper_utils_size(PyObject *self, PyObject *str)
{
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
        PyErr_SetString(MemWiper_UtilsError, "Unicode object is not Ready!");
        return NULL;
    }

    kind = PyUnicode_KIND(str);
    return PyLong_FromLong((long)(kind*PyUnicode_GET_LENGTH(str)));
}


static PyObject *
memwiper_utils_codepoints(PyObject *self, PyObject *str)
{

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
        PyErr_SetString(MemWiper_UtilsError, "Unicode object is not Ready!");
        return NULL;
    }

    return PyLong_FromSsize_t(PyUnicode_GET_LENGTH(str));
}

/*
 * Required stuff to make the python 3 module
 */

/*
 * Methods of the module declaration
 */
static PyMethodDef MemWiper_UtilsMethods[] = {
    {"kind", memwiper_utils_kind, METH_O,
        PyDoc_STR("kind of Unicode string")},
    {"size", memwiper_utils_size, METH_O,
        PyDoc_STR("Size of the string")},
    {"codepoints", memwiper_utils_codepoints, METH_O,
        PyDoc_STR("Code Point of the Unicode String")},
    {NULL, NULL, 0, NULL},
};

/*
 * Module definition
 */
static struct PyModuleDef MemWiper_Utilsmodule = {
   PyModuleDef_HEAD_INIT,
   "memwiper_utils",   /* name of module */
   NULL, /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   MemWiper_UtilsMethods
};

PyMODINIT_FUNC
PyInit_memwiper_utils(void)
{
    PyObject *m;
    MemWiper_UtilsError = PyErr_NewException("memwiper_util.error", NULL, NULL);
    Py_INCREF(MemWiper_UtilsError);
    m = PyModule_Create(&MemWiper_Utilsmodule);
    PyModule_AddObject(m, "error", MemWiper_UtilsError);
    return m;
}
