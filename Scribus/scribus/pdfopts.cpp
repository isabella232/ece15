/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "pdfopts.h"
#include "pdfopts.moc"

#include "customfdialog.h"
#include "prefsmanager.h"
#include "prefsfile.h"
#include "units.h"
#include "pdfoptions.h"
#include "util.h"
#include "commonstrings.h"
#include "scconfig.h"

#ifdef HAVE_CMS
extern bool CMSuse;
#endif
extern bool CMSavail;

PDF_Opts::PDF_Opts( QWidget* parent,  QString docFileName, QMap<QString,QFont> DocFonts, ScribusView *currView, PDFOptions *pdfOptions, QValueList<PDFPresentationData> Eff, ProfilesL *PDFXProfiles, SCFonts &AllFonts, double unitRatio, ProfilesL *printerProfiles)
		: QDialog( parent, "pdf", true, 0 )
{
	setCaption( tr( "Save as PDF" ) );
	setIcon(loadIcon("AppIcon.png"));
	EffVal = Eff;
	Opts = pdfOptions;
	docUnitRatio=unitRatio;
	cmsDescriptorName="";
	components=3;
	appPrinterProfiles=printerProfiles;
	PDFOptsLayout = new QVBoxLayout( this );
	PDFOptsLayout->setSpacing( 5 );
	PDFOptsLayout->setMargin( 11 );
	Name = new QLabel( tr( "O&utput to File:" ), this, "Name" );
	Name->setFrameShape( QLabel::NoFrame );
	PDFOptsLayout->addWidget( Name );
	Layout5 = new QHBoxLayout;
	Layout5->setSpacing( 5 );
	Layout5->setMargin( 0 );
	fileNameLineEdit = new QLineEdit( this, "fileNameLineEdit" );
	fileNameLineEdit->setMinimumSize( QSize( 268, 22 ) );
	if (!pdfOptions->Datei.isEmpty())
		fileNameLineEdit->setText(pdfOptions->Datei);
	else
	{
		PrefsContext* dirs = PrefsManager::instance()->prefsFile->getContext("dirs");
		QFileInfo fi = QFileInfo(docFileName);
		QString pdfdir = dirs->get("pdf", fi.dirPath());
		if (pdfdir.right(1) != "/")
			pdfdir += "/";
		fileNameLineEdit->setText(pdfdir+fi.baseName()+".pdf");
	}
	Name->setBuddy(fileNameLineEdit);
	Layout5->addWidget( fileNameLineEdit );
	FileC = new QToolButton( this, "FileC" );
	FileC->setText( tr( "Cha&nge..." ) );
	FileC->setMinimumSize( QSize( 88, 24 ) );
	Layout5->addWidget( FileC );
	PDFOptsLayout->addLayout( Layout5 );
	Options = new TabPDFOptions( this, pdfOptions, AllFonts, PDFXProfiles, DocFonts,
								Eff, currView->Doc->unitIndex(), currView->Doc->pageHeight,
								currView->Doc->pageWidth, currView );
	PDFOptsLayout->addWidget( Options );
	Layout7 = new QHBoxLayout;
	Layout7->setSpacing( 5 );
	Layout7->setMargin( 0 );
	QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
	Layout7->addItem( spacer_2 );
	OK = new QPushButton( tr( "&Save" ), this, "OK" );
	OK->setAutoDefault( true );
	OK->setDefault( true );
	Layout7->addWidget( OK );
	Cancel = new QPushButton( CommonStrings::tr_Cancel, this, "Cancel" );
	Layout7->addWidget( Cancel );
	PDFOptsLayout->addLayout( Layout7 );
	resize(sizeHint());
//	setMaximumSize( sizeHint() );


	// signals and slots connections
	connect( FileC, SIGNAL( clicked() ), this, SLOT( ChangeFile() ) );
	connect( OK, SIGNAL( clicked() ), this, SLOT( DoExport() ) );
	connect( Cancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
	connect( fileNameLineEdit, SIGNAL( lostFocus() ), this, SLOT( fileNameChanged() ) );
	connect( fileNameLineEdit, SIGNAL( returnPressed() ), this, SLOT( fileNameChanged() ) );
}

void PDF_Opts::DoExport()
{
	QString fn = fileNameLineEdit->text();
	if (overwrite(this, fn))
	{
		EffVal = Options->EffVal;
		EffVal[Options->PgSel].pageViewDuration = Options->PageTime->value();
		EffVal[Options->PgSel].pageEffectDuration = Options->EffectTime->value();
		EffVal[Options->PgSel].effectType = Options->EffectType->currentItem();
		EffVal[Options->PgSel].Dm = Options->EDirection->currentItem();
		EffVal[Options->PgSel].M = Options->EDirection_2->currentItem();
		EffVal[Options->PgSel].Di = Options->EDirection_2_2->currentItem();
		Opts->LPISettings[Options->SelLPIcolor].Frequency = Options->LPIfreq->value();
		Opts->LPISettings[Options->SelLPIcolor].Angle = Options->LPIangle->value();
		Opts->LPISettings[Options->SelLPIcolor].SpotFunc = Options->LPIfunc->currentItem();
		accept();
	}
	else
		return;
}

void PDF_Opts::ChangeFile()
{
	QString fn;
	PrefsContext* dirs = PrefsManager::instance()->prefsFile->getContext("dirs");
	QString wdir = dirs->get("pdf", ".");
	CustomFDialog dia(this, wdir, tr("Save as"), tr("PDF Files (*.pdf);;All Files (*)"), false, false);
	if (!fileNameLineEdit->text().isEmpty())
		dia.setSelection(fileNameLineEdit->text());
	if (dia.exec() == QDialog::Accepted)
	{
		fn = dia.selectedFile();
		dirs->set("pdf", fn.left(fn.findRev("/")));
	}
	else
		return;
	fileNameLineEdit->setText(fn);
}

void PDF_Opts::fileNameChanged()
{
	fileNameLineEdit->setText(checkFileExtension(fileNameLineEdit->text(),"pdf"));
}

void PDF_Opts::updateDocOptions()
{
	Opts->Datei = fileNameLineEdit->text();
	Opts->Thumbnails = Options->CheckBox1->isChecked();
	Opts->Compress = Options->Compression->isChecked();
	Opts->CompressMethod = Options->CMethod->currentItem();
	Opts->Quality = Options->CQuality->currentItem();
	Opts->Resolution = Options->Resolution->value();
	Opts->EmbedList = Options->FontsToEmbed;
	Opts->SubsetList = Options->FontsToSubset;
	Opts->RecalcPic = Options->DSColor->isChecked();
	Opts->PicRes = Options->ValC->value();
	Opts->Bookmarks = Options->CheckBM->isChecked();
	Opts->Binding = Options->ComboBind->currentItem();
	Opts->MirrorH = Options->MirrorH->isOn();
	Opts->MirrorV = Options->MirrorV->isOn();
	Opts->RotateDeg = Options->RotateDeg->currentItem() * 90;
	Opts->PresentMode = Options->CheckBox10->isChecked();
	Opts->PresentVals = EffVal;
	Opts->Articles = Options->Article->isChecked();
	Opts->Encrypt = Options->Encry->isChecked();
	Opts->UseLPI = Options->UseLPI->isChecked();
	Opts->useLayers = Options->useLayers->isChecked();
	if (Options->Encry->isChecked())
	{
		int Perm = -64;
		if (Options->PDFVersionCombo->currentItem() == 1)
			Perm &= ~0x00240000;
		if (Options->PrintSec->isChecked())
			Perm += 4;
		if (Options->ModifySec->isChecked())
			Perm += 8;
		if (Options->CopySec->isChecked())
			Perm += 16;
		if (Options->AddSec->isChecked())
			Perm += 32;
		Opts->Permissions = Perm;
		Opts->PassOwner = Options->PassOwner->text();
		Opts->PassUser = Options->PassUser->text();
	}
	if (Options->PDFVersionCombo->currentItem() == 0)
		Opts->Version = PDFOptions::PDFVersion_13;
	if (Options->PDFVersionCombo->currentItem() == 1)
		Opts->Version = PDFOptions::PDFVersion_14;
	if (Options->PDFVersionCombo->currentItem() == 2)
		Opts->Version = PDFOptions::PDFVersion_15;
	if (Options->PDFVersionCombo->currentItem() == 3)
		Opts->Version = PDFOptions::PDFVersion_X3;
	if (Options->OutCombo->currentItem() == 0)
	{
		Opts->UseRGB = true;
		Opts->isGrayscale = false;
		Opts->UseProfiles = false;
		Opts->UseProfiles2 = false;
	}
	else
	{
		if (Options->OutCombo->currentItem() == 2)
		{
			Opts->isGrayscale = true;
			Opts->UseRGB = false;
			Opts->UseProfiles = false;
			Opts->UseProfiles2 = false;
		}
		else
		{
			Opts->isGrayscale = false;
			Opts->UseRGB = false;
#ifdef HAVE_CMS
			if (CMSuse)
			{
				Opts->UseProfiles = Options->EmbedProfs->isChecked();
				Opts->UseProfiles2 = Options->EmbedProfs2->isChecked();
				Opts->Intent = Options->IntendS->currentItem();
				Opts->Intent2 = Options->IntendI->currentItem();
				Opts->EmbeddedI = Options->NoEmbedded->isChecked();
				Opts->SolidProf = Options->SolidPr->currentText();
				Opts->ImageProf = Options->ImageP->currentText();
				Opts->PrintProf = Options->PrintProfC->currentText();
				if (Opts->Version == PDFOptions::PDFVersion_X3)
				{
					cmsHPROFILE hIn;
					hIn = cmsOpenProfileFromFile((*appPrinterProfiles)[Opts->PrintProf], "r");
					const char *Descriptor = cmsTakeProductDesc(hIn);
					cmsDescriptorName = QString(Descriptor);
					if (static_cast<int>(cmsGetColorSpace(hIn)) == icSigRgbData)
						components = 3;
					if (static_cast<int>(cmsGetColorSpace(hIn)) == icSigCmykData)
						components = 4;
					if (static_cast<int>(cmsGetColorSpace(hIn)) == icSigCmyData)
						components = 3;
					cmsCloseProfile(hIn);
					Opts->Info = Options->InfoString->text();
					Opts->BleedTop = Options->BleedTop->value()/docUnitRatio;
					Opts->BleedLeft = Options->BleedLeft->value()/docUnitRatio;
					Opts->BleedRight = Options->BleedRight->value()/docUnitRatio;
					Opts->BleedBottom = Options->BleedBottom->value()/docUnitRatio;
					Opts->Encrypt = false;
					Opts->MirrorH = false;
					Opts->MirrorV = false;
					Opts->RotateDeg = 0;
					Opts->PresentMode = false;
					Opts->Encrypt = false;
				}
			}
			else
			{
				Opts->UseProfiles = false;
				Opts->UseProfiles2 = false;
			}
#else
			Opts->UseProfiles = false;
			Opts->UseProfiles2 = false;
#endif
		}
	}
}

const QString PDF_Opts::cmsDescriptor()
{
	return cmsDescriptorName;
}

const int PDF_Opts::colorSpaceComponents()
{
	return components;
}
