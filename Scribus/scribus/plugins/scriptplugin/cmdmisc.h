#ifndef CMDMISC_H
#define CMDMISC_H


/** Other Commands */
PyObject *scribus_setredraw(PyObject *self, PyObject* args);
PyObject *scribus_fontnames(PyObject *self, PyObject* args);
 /**
 return a list of the tuples with
 Scribus name, Family, Real name, subset (1|0), embed PS (1|0), font file
 */
PyObject *scribus_xfontnames(PyObject *self, PyObject* args);
PyObject *scribus_renderfont(PyObject *self, PyObject* args);
PyObject *scribus_getlayers(PyObject *self, PyObject* args);
PyObject *scribus_setactlayer(PyObject *self, PyObject* args);
PyObject *scribus_getactlayer(PyObject *self, PyObject* args);
PyObject *scribus_senttolayer(PyObject *self, PyObject* args);
PyObject *scribus_layervisible(PyObject *self, PyObject* args);
PyObject *scribus_layerprint(PyObject *self, PyObject* args);
PyObject *scribus_glayervisib(PyObject *self, PyObject* args);
PyObject *scribus_glayerprint(PyObject *self, PyObject* args);
PyObject *scribus_removelayer(PyObject *self, PyObject* args);
PyObject *scribus_createlayer(PyObject *self, PyObject* args);

#endif

