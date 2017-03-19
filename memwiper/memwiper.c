#include <Python.h>

static PyObject *MemWiperError;


static PyObject *
memwiper_wipeit(PyObject *self, PyObject *str)
{
Py_UNICODE *buffer;
long buffer_size;
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
        PyErr_SetString(MemWiperError, "Unicode object is not Ready!");
        return NULL;
    }

    buffer = PyUnicode_DATA(str);
    kind = PyUnicode_KIND(str);
    buffer_size = (long)PyUnicode_GET_LENGTH(str);
    for (long i=0;i<=(buffer_size-1);i++)
    {
        PyUnicode_WRITE(kind, buffer, i, (Py_UCS4)0);
    }
    return PyUnicode_FromString("");
}


static PyObject *
memwiper_kind(PyObject *self, PyObject *str)
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
        PyErr_SetString(MemWiperError, "Unicode object is not Ready!");
        return NULL;
    }

    kind = PyUnicode_KIND(str);
    if (kind == PyUnicode_WCHAR_KIND) return PyUnicode_FromString("Wide Char");
    if (kind == PyUnicode_1BYTE_KIND) return PyUnicode_FromString("1 Byte");
    if (kind == PyUnicode_2BYTE_KIND) return PyUnicode_FromString("2 Byte");
    return PyUnicode_FromString("4 Byte");
}

static PyObject *
memwiper_size(PyObject *self, PyObject *str)
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
        PyErr_SetString(MemWiperError, "Unicode object is not Ready!");
        return NULL;
    }

    kind = PyUnicode_KIND(str);
    return PyLong_FromLong((long)(kind*PyUnicode_GET_LENGTH(str)));
}


static PyObject *
memwiper_codepoints(PyObject *self, PyObject *str)
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
        PyErr_SetString(MemWiperError, "Unicode object is not Ready!");
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
static PyMethodDef MemWiperMethods[] = {
    {"wipeit", memwiper_wipeit, METH_O,
        PyDoc_STR("clear the memory of the string")},
    {"kind", memwiper_kind, METH_O,
        PyDoc_STR("kind of Unicode string")},
    {"size", memwiper_size, METH_O,
        PyDoc_STR("Size of the string")},
    {"codepoints", memwiper_codepoints, METH_O,
        PyDoc_STR("Code Points of the Unicode String")},
    {NULL, NULL, 0, NULL},
};

/*
 * Module definition
 */
static struct PyModuleDef MemWipermodule = {
   PyModuleDef_HEAD_INIT,
   "memwiper",   /* name of module */
   NULL, /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   MemWiperMethods
};

PyMODINIT_FUNC
PyInit_memwiper(void)
{
    PyObject *m;
    MemWiperError = PyErr_NewException("wipeit.error", NULL, NULL);
    Py_INCREF(MemWiperError);
    m = PyModule_Create(&MemWipermodule);
    PyModule_AddObject(m, "error", MemWiperError);
    return m;
}
