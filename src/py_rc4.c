#include <Python.h>
#include "rc4.h"

static PyObject *
py_generate_key(PyObject *self, PyObject *args);

static PyObject *
py_destroy_key(PyObject *self, PyObject *args);


static PyObject *
py_encrypt(PyObject *self, PyObject *args);

static PyObject *
py_decrypt(PyObject *self, PyObject *args);

static PyMethodDef rc4Methods[] = {
    {"generate_key",  py_generate_key, METH_VARARGS,
     "generate a key"},
    {"destroy_key",  py_destroy_key, METH_VARARGS,
     "destroy a key"},

    {"encrypt",  py_encrypt, METH_VARARGS,
     "encrypt"},
    {"decrypt",  py_decrypt, METH_VARARGS,
     "decrypt"},

    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static PyObject *
py_generate_key(PyObject *self, PyObject *args)
{
    rc4_state *ctx = (rc4_state *)malloc(sizeof(rc4_state));
    
    int keystr_len;
    char *keystr;
    if (!PyArg_ParseTuple(args, "s#", &keystr, &keystr_len)) {
        return NULL;
    }

    rc4_init(ctx, keystr, keystr_len);
    return PyCObject_FromVoidPtr((void *)ctx, NULL);
}

static PyObject *
py_destroy_key(PyObject *self, PyObject *args)
{
    
    PyCObject *key;
    rc4_state *ctx;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        return NULL;
    }
    ctx = (rc4_state *)PyCObject_AsVoidPtr(key);
    free(ctx);
    return PyBool_FromLong(1);

}


PyObject* py_crypt(PyObject *self, PyObject *args) {
    PyCObject *key;
    PyObject *ret;
    char *data;
    int data_len;
    rc4_state ctx;
    rc4_state * ctx_ptr;
    if (!PyArg_ParseTuple(args, "Os#", &key, &data, &data_len)) {
        return NULL;
    }
    //allocate output buffer
    char *data_out = (char *)malloc(data_len);
    ctx_ptr = (rc4_state *)PyCObject_AsVoidPtr(key);
    memcpy(&ctx, ctx_ptr, sizeof(rc4_state));
    
    rc4_crypt(&ctx, data, data_out, data_len);
    
    ret = PyString_FromStringAndSize(data_out, data_len);
    free(data_out);
    return ret;
}

static PyObject *
py_encrypt(PyObject *self, PyObject *args)
{
    PyObject *ret;
    ret = py_crypt(self, args);
    return ret;
}

static PyObject *
py_decrypt(PyObject *self, PyObject *args)
{
    PyObject *ret;
    ret = py_crypt(self, args);
    return ret;
}

/**
 * Python module initialization 
 *
 */
PyMODINIT_FUNC
init_rc4(void)
{
    PyObject *m;

    m = Py_InitModule("_rc4", rc4Methods);
    if (m == NULL)
        return;

}


