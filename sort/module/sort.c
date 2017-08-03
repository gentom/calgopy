#include <Python.h>

static PyObject *bubble_sort(PyObject *self, PyObject *args)
{
    Py_ssize_t i, j, n;
    PyObject *a, *b, *list;
    PyObject *seq;
    int cmp;

    /*
    int PyArg_ParseTuple(PyObject *args, const char *format, ...)
        Parse the parameters of a function that takes only positional parameters into local variables. 
        Returns true on success; 
        on failure, it returns false and raises the appropriate exception.
    */

    /*
    O (object) [PyObject *]
        Store a Python object (without any conversion) in a C object pointer. 
        The C program thus receives the actual object that was passed. 
        The object’s reference count is not increased. 
        The pointer stored is not NULL.
    */

    if (!PyArg_ParseTuple(args, "O", &seq))
        return NULL;

    /*
    void Py_INCREF(PyObject *o)
        Increment the reference count for object o. 
        The object must not be NULL; 
        if you aren’t sure that it isn’t NULL, use Py_XINCREF().
    */
    Py_INCREF(seq);

    /*
    PyObject* PySequence_List(PyObject *o)
        Return value: New reference.
        Return a list object with the same contents as the sequence or iterable o, or NULL on failure. 
        The returned list is guaranteed to be new. 
        This is equivalent to the Python expression list(o).
    */
    list = PySequence_List(seq);

    /*
    void Py_DECREF(PyObject *o)
        Decrement the reference count for object o. 
        The object must not be NULL; 
        if you aren’t sure that it isn’t NULL, use Py_XDECREF(). 
        If the reference count reaches zero, 
        the object’s type’s deallocation function (which must not be NULL) is invoked.
    */
    Py_DECREF(seq);

    /*
    Py_ssize_t PyObject_Size(PyObject *o)
        Return the length of object o. 
        If the object o provides either the sequence and mapping protocols, 
        the sequence length is returned. 
        On error, -1 is returned. 
        This is the equivalent to the Python expression len(o).
    */
    n = PyObject_Size(list);

    if (n < 0)
        return NULL;

    for (i = 1; i < n; ++i)
        for (j = 1; j < n - i + 1; ++j)
        {
            /*
            PyObject* PyList_GetItem(PyObject *list, Py_ssize_t index)
                Return value: Borrowed reference.
                Return the object at position index in the list pointed to by list. 
                The position must be positive, indexing from the end of the list is not supported. 
                If index is out of bounds, return NULL and set an IndexError exception.
            */
            a = PyList_GetItem(list, j);

            Py_INCREF(a);

            b = PyList_GetItem(list, j - 1);

            Py_INCREF(b);

            /*
            int PyObject_RichCompareBool(PyObject *o1, PyObject *o2, int opid)
                Compare the values of o1 and o2 using the operation specified by opid, 
                which must be one of Py_LT, Py_LE, Py_EQ, Py_NE, Py_GT, or Py_GE, 
                corresponding to <, <=, ==, !=, >, or >= respectively. 
                Returns -1 on error, 0 if the result is false, 1 otherwise. 
                This is the equivalent of the Python expression o1 op o2, 
                where op is the operator corresponding to opid.
            */
            cmp = PyObject_RichCompareBool(a, b, Py_LT);

            if (cmp == -1)
            {
                Py_DECREF(a);
                Py_DECREF(b);
                return NULL;
            }

            if (cmp == 1)
            {
                /*
                int PyList_SetItem(PyObject *list, Py_ssize_t index, PyObject *item)
                    Set the item at index index in list to item. 
                    Return 0 on success or -1 on failure.
                    ＊Note:
                        This function “steals” a reference to item and 
                        discards a reference to an item already in the list 
                        at the affected position.
                */
                PyList_SetItem(list, j, b);
                PyList_SetItem(list, j - 1, a);
            }
            else
            {
                Py_DECREF(a);
                Py_DECREF(b);
            }
        }

    return list;
}

static char bubblesort_doc[] = "Apply bubble sort to given list.";

static PyMethodDef GMSortMethods[] = {
    {"bubble_sort", bubble_sort, METH_VARARGS, bubblesort_doc},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef gmsortmodule = {
    PyModuleDef_HEAD_INIT,
    "gmsort",
    NULL,
    -1,
    GMSortMethods};

PyMODINIT_FUNC PyInit_gmsort(void)
{
    return PyModule_Create(&gmsortmodule);
}