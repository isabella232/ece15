#ifndef CMDTEXT_H
#define CMDTEXT_H


PyObject *scribus_getfontsize(PyObject *self, PyObject* args);
PyObject *scribus_getfont(PyObject *self, PyObject* args);
PyObject *scribus_gettextsize(PyObject *self, PyObject* args);
PyObject *scribus_getframetext(PyObject *self, PyObject* args);
PyObject *scribus_gettext(PyObject *self, PyObject* args);
PyObject *scribus_getlinespace(PyObject *self, PyObject* args);
PyObject *scribus_getcolumngap(PyObject *self, PyObject* args);
PyObject *scribus_getcolumns(PyObject *self, PyObject* args);
PyObject *scribus_setboxtext(PyObject *self, PyObject* args);
PyObject *scribus_inserttext(PyObject *self, PyObject* args);
PyObject *scribus_setfont(PyObject *self, PyObject* args);
PyObject *scribus_setfontsize(PyObject *self, PyObject* args);
PyObject *scribus_setlinespace(PyObject *self, PyObject* args);
PyObject *scribus_setcolumngap(PyObject *self, PyObject* args);
PyObject *scribus_setcolumns(PyObject *self, PyObject* args);
PyObject *scribus_setalign(PyObject *self, PyObject* args);
PyObject *scribus_selecttext(PyObject *self, PyObject* args);
PyObject *scribus_deletetext(PyObject *self, PyObject* args);
PyObject *scribus_settextfill(PyObject *self, PyObject* args);
PyObject *scribus_settextstroke(PyObject *self, PyObject* args);
PyObject *scribus_settextshade(PyObject *self, PyObject* args);
/**
 (Un)Link text frames via Scripter.
 02/22/04 (petr vanek)
 TODO: PDF bookmarks handling
 */
PyObject *scribus_linktextframes(PyObject *self, PyObject* args);
PyObject *scribus_unlinktextframes(PyObject * self, PyObject* args);

#endif

