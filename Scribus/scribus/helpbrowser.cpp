/***************************************************************************
*   Copyright (C) 2004 by Craig Bradney                                   *
*   cbradney@zip.com.au                                                   *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#include "helpbrowser.h"
#include "helpbrowser.moc"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qheader.h>
#include <qlistview.h>
#include <qtextbrowser.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qpopupmenu.h>
#include <qfileinfo.h>
#include <qtextcodec.h>
#include <qdom.h>

#ifdef _MSC_VER
 #if (_MSC_VER >= 1200)
  #include "win-config.h"
 #endif
#else
 #include "config.h"
#endif

extern QPixmap loadIcon(QString nam);


HelpBrowser::HelpBrowser( QWidget* parent, QString caption, QString guiLanguage, QString jumpToSection, QString jumpToFile)
	: QWidget( parent, "Help", WType_TopLevel | WDestructiveClose )
{
	QString fileName;
	mHistory.clear();
	struct histd his;

	helpBrowsermainLayout = new QVBoxLayout( this); 

	buttonLayout = new QHBoxLayout;
	buttonLayout->setSpacing( 6 );
	buttonLayout->setMargin( 2 );

	homeButton = new QToolButton( this, "homeButton" );
	homeButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, homeButton->sizePolicy().hasHeightForWidth() ) );
	homeButton->setMinimumSize( QSize( 0, 0 ) );
	homeButton->setMaximumSize( QSize( 32767, 32767 ) );
	homeButton->setText( "" );
	homeButton->setPixmap(loadIcon("gohome.png"));
	buttonLayout->addWidget( homeButton );

	histMenu = new QPopupMenu( this );
	backButton = new QToolButton( this, "backButton" );
	backButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, backButton->sizePolicy().hasHeightForWidth() ) );
	backButton->setMinimumSize( QSize( 0, 0 ) );
	backButton->setMaximumSize( QSize( 32767, 32767 ) );
	backButton->setPixmap(loadIcon("back.png"));
	backButton->setPopup(histMenu);
	backButton->setPopupDelay(0);
	buttonLayout->addWidget( backButton );

	forwButton = new QToolButton( this, "forwButton" );
	forwButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, forwButton->sizePolicy().hasHeightForWidth() ) );
	forwButton->setMinimumSize( QSize( 0, 0 ) );
	forwButton->setMaximumSize( QSize( 32767, 32767 ) );
	forwButton->setPixmap(loadIcon("forward.png"));
	buttonLayout->addWidget( forwButton );
	QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
	buttonLayout->addItem( spacer );
	helpBrowsermainLayout->addLayout( buttonLayout );

	helpBrowserLayout = new QHBoxLayout; 

	tabWidget = new QTabWidget( this, "tabWidget" );
	tabWidget->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 1, 0, tabWidget->sizePolicy().hasHeightForWidth() ) );
	tabContents = new QWidget( tabWidget, "tabContents" );
	tabLayout = new QHBoxLayout( tabContents, 11, 6, "tabLayout"); 

	listView = new QListView( tabContents, "listView" );
	listView->addColumn( tr( "Contents" ) );
	listView->addColumn( tr( "Link" ) , 0 );
	listView->setSorting(-1,-1);
	listView->setRootIsDecorated( true );
	listView->setSelectionMode(QListView::Single);
	listView->setDefaultRenameAction(QListView::Reject);
	listView->clear();
	tabLayout->addWidget( listView );
	
	tabWidget->insertTab( tabContents, QString("Contents") );
	helpBrowserLayout->addWidget( tabWidget );

	textBrowser = new QTextBrowser( this, "textBrowser" );
	textBrowser->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 3, 0, textBrowser->sizePolicy().hasHeightForWidth() ) );
	textBrowser->setFrameShape( QTextBrowser::StyledPanel );
	helpBrowserLayout->addWidget( textBrowser );
	helpBrowsermainLayout->addLayout( helpBrowserLayout );

	languageChange();
	resize( QSize(602, 491).expandedTo(minimumSizeHint()) );
	clearWState( WState_Polished );
	loadMenu();
	listView->header()->hide();
	jumpToHelpSection( guiLanguage, jumpToSection, jumpToFile );

	connect( homeButton, SIGNAL( clicked() ), textBrowser, SLOT( home() ) );
	connect( forwButton, SIGNAL( clicked() ), textBrowser, SLOT( forward() ) );
	connect( backButton, SIGNAL( clicked() ), textBrowser, SLOT( backward() ) );
	connect( histMenu, SIGNAL(activated(int)), this, SLOT(histChosen(int)));
	connect( listView, SIGNAL(clicked( QListViewItem *)), this, SLOT(itemSelected( QListViewItem *)));
}

HelpBrowser::~HelpBrowser()
{
	// no need to delete child widgets, Qt does it all for us
}

void HelpBrowser::languageChange()
{
	setCaption( tr( "Scribus Online Help" ) );
	listView->header()->setLabel( 0, tr( "Contents" ) );
	listView->clear();

	tabWidget->changeTab( tabContents, tr( "Contents" ) );
//    tabWidget->changeTab( tab_2, tr( "Tab 2" ) );
}


void HelpBrowser::sourceChanged(const QString& url)
{
	bool inList = false;
	struct histd his;
	QString title = "";
	title = textBrowser->documentTitle();
	if (title == "")
		title = url;
	QMap<int, histd>::Iterator it;
	for (it = mHistory.begin(); it != mHistory.end(); ++it)
	{
		if (it.data().Title == title)
			inList = true;
	}
	if (!inList)
	{
		his.Title = title;
		his.Url = url;
		mHistory[histMenu->insertItem(title)] = his;
	}
	if (mHistory.count() > 15)
	{
		int itk = histMenu->idAt(0);
		mHistory.remove(itk);
		histMenu->removeItem(itk);
	}
}

void HelpBrowser::histChosen(int i)
{
	if (mHistory.contains(i))
		textBrowser->setSource(mHistory[i].Url);
}

void HelpBrowser::jumpToHelpSection(QString guiLanguage, QString jumpToSection, QString jumpToFile)
{
	QString toLoad;

	if (guiLanguage=="") 
	{
		qDebug("Error: No help language found.");
		guiLanguage="en";
	}
	if (jumpToFile=="") 
	{
		QString pfad = PREL;
		toLoad = pfad + "/share/scribus/doc/";
		toLoad += guiLanguage.left(2) + "/"; //clean this later to handle 5 char locales
		if (jumpToSection=="") 
		{
			toLoad+="index.html";
			listView->setSelected( listView->firstChild(), true );
		}
		else if (jumpToSection=="scripter") 
		{
			toLoad+="scripter1.html";
			QListViewItemIterator it(listView);
			while (it.current()) 
			{
				if (it.current()->text(1)=="scripter1.html")
					listView->setSelected( it.current(), true );
				if (it.current()->text(1)=="developers.html")
					it.current()->setOpen( true );
				++it;
			}
		}
	}
	else
		toLoad=jumpToFile;

	loadHelp(toLoad);
}

void HelpBrowser::loadHelp(QString filename)
{
	struct histd his;
	bool Avail = true;
	QString toLoad;
	QFileInfo fi;
	fi = QFileInfo(filename);
	if (fi.exists())
		toLoad=filename;
	else 
	{
		QString pfad = PREL;
		toLoad = pfad + "/share/scribus/doc/en/index.html";
		fi = QFileInfo(toLoad);
		if (!fi.exists())
		{
			textBrowser->setText("<h2>"+ tr("Sorry, no manual available! Please see: http://docs.scribus.net for updated docs\nand www.scribus.net for downloads.")+"</h2>");
			Avail = false;
		}
	}
	if (Avail) 
	{
		textBrowser->setSource(toLoad);
		his.Title = textBrowser->documentTitle();
		if (his.Title == "")
			his.Title = toLoad;
		his.Url = toLoad;
		mHistory[histMenu->insertItem(his.Title)] = his;
	}
}

void HelpBrowser::loadMenu()
{
	QString pfad = PREL;
	QString pfad2;
	bool Avail = true;
	pfad2 = pfad + "/share/scribus/doc/"+QString(QTextCodec::locale()).left(2)+"/menu.xml";
	pfad2 = pfad + "/share/scribus/doc/en/menu.xml";

	QFileInfo fi = QFileInfo(pfad2);
	if (fi.exists())
	{
		textBrowser->setText("menu found");
		QDomDocument doc( "menuentries" );
		QFile file( pfad2 );
		if ( !file.open( IO_ReadOnly ) )
			return;
		if ( !doc.setContent( &file ) ) 
		{
			file.close();
			return;
		}
		file.close();

		QDomElement docElem = doc.documentElement();
		QDomNode n = docElem.firstChild();
		QListViewItem *qlvi=NULL, *qlvi2=NULL, *qlvi3=NULL, *qlvi4=NULL, *qlvi5=NULL, *qlvi6=NULL;

		while( !n.isNull() ) 
		{
			QDomElement e = n.toElement(); // try to convert the node to an element.
			if( !e.isNull() ) 
			{
				if (e.hasAttribute( "text" ) && e.hasAttribute( "file" )) 
				{
					QDomAttr textAttr = e.attributeNode( "text" );
					QDomAttr fileAttr = e.attributeNode( "file" );
					if (qlvi2==NULL)
						qlvi=new QListViewItem(listView, textAttr.value(), fileAttr.value());
					else 
					{
						qlvi=new QListViewItem(listView, qlvi2);
						if (qlvi!=NULL) 
						{
							qlvi->setText(0, textAttr.value());
							qlvi->setText(1, fileAttr.value());
						}
					}
					if (qlvi!=NULL)
						qlvi2=qlvi;
				}

				QDomNodeList nl=n.childNodes();
				for(uint i=0 ; i<= nl.count() ; i++) 
				{
					QDomNode child=nl.item(i);
					if (child.isElement()) 
					{
						QDomElement ec = child.toElement();	
						if (!ec.isNull()) 
						{
							if (ec.hasAttribute( "text" ) && ec.hasAttribute( "file" )) 
							{
								QDomAttr textAttr = ec.attributeNode( "text" );
								QDomAttr fileAttr = ec.attributeNode( "file" );
								if (qlvi4==NULL)
									qlvi3=new QListViewItem(qlvi, textAttr.value(), fileAttr.value());
								else 
								{
									qlvi3=new QListViewItem(qlvi, qlvi4);
									if (qlvi3!=NULL) 
									{
										qlvi3->setText(0, textAttr.value());
										qlvi3->setText(1, fileAttr.value());
									}
								}
								if (qlvi3!=NULL)
									qlvi4=qlvi3;
							}
							//3rd level
							QDomNodeList nl2=child.childNodes();
							for(uint i=0 ; i<= nl2.count() ; i++) 
							{
								QDomNode childchild=nl2.item(i);
								if (childchild.isElement()) 
								{
									QDomElement ecc = childchild.toElement();	
									if (!ecc.isNull()) 
									{
										if (ecc.hasAttribute( "text" ) && ecc.hasAttribute( "file" )) 
										{
											QDomAttr textAttr = ecc.attributeNode( "text" );
											QDomAttr fileAttr = ecc.attributeNode( "file" );
											if (qlvi6==NULL)
												qlvi5=new QListViewItem(qlvi3, textAttr.value(), fileAttr.value());
											else 
											{
												qlvi5=new QListViewItem(qlvi3, qlvi6);
												if (qlvi5!=NULL) 
												{
													qlvi5->setText(0, textAttr.value());
													qlvi5->setText(1, fileAttr.value());
												}
											}
										}
										if (qlvi5!=NULL)
											qlvi6=qlvi5;
									}
								}
							}
						}
					}
				}
			}
			n = n.nextSibling();
		}
	}
}

void HelpBrowser::itemSelected(QListViewItem *item)
{
	QString pfad = PREL;
	if ( !item )
		return;
	else if (item->text(1)!=QString::null)
		loadHelp(pfad + "/share/scribus/doc/en/"+item->text(1));
}
