#ifndef LAYERPALETTE_H
#define LAYERPALETTE_H

#include <qdialog.h>
#include <qpushbutton.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qpixmap.h>
#include <qcheckbox.h>
#include <qheader.h>
#include <qptrlist.h>
#include <qvaluelist.h>
#include <scribusdoc.h>

class LayerTable : public QTable
{
	Q_OBJECT

public:
	LayerTable(QWidget* parent);
	~LayerTable() {};
	void keyPressEvent(QKeyEvent *k);

signals:
	void ToggleAllPalettes();
	void Schliessen();
};

class LayerPalette : public QDialog
{
	Q_OBJECT

public:
	LayerPalette(QWidget* parent);
	~LayerPalette() {};

	QTable* Table;
	QHeader* Header;
	QPushButton* NewLayer;
	QPushButton* DeleteLayer;
	QPushButton* RaiseLayer;
	QPushButton* LowerLayer;
	QValueList<Layer> *layers;
	void closeEvent(QCloseEvent *ce);
	void setLayers(QValueList<Layer> *layin, int *act);
	void rebuildList();
	QPtrList<QCheckBox> FlagsPrint;
	QPtrList<QCheckBox> FlagsSicht;
	int *Activ;

public slots:
	void addLayer();
	void removeLayer();
	void upLayer();
	void downLayer();
	void changeName(int row, int col);
	void visibleLayer();
	void printLayer();
	void setActiveLayer(int row);
	void ClearInhalt();
	void MarkActiveLayer(int l);

signals:
	void LayerRemoved(int, bool);
	void LayerChanged();
	void LayerActivated(int);
	void Schliessen();

protected:
	virtual void windowActivationChange(bool oldActive);
	QVBoxLayout* LayerPaletteLayout;
	QHBoxLayout* Layout1;

protected slots:
	virtual void reject();
};

#endif // LAYERPALETTE_H
