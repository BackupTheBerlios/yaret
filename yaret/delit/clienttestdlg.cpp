/***************************************************************************
                          clienttestdlg.cpp  -  description
                             -------------------
    begin                : Sun Nov 25 2001
    copyright            : (C) 2001 by Jascha Schubert
    email                : Jascha.Schubert@web.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "clienttestdlg.h"
#include <qcombobox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qmultilineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qmessagebox.h>
#include <stdio.h>
#include <qlistview.h>
#include <stdlib.h>
#include <qdom.h>
#include <qfile.h>
#include "database.h"

// #include "ClientDlg.h"



ClientTestDlg::ClientTestDlg(QWidget *parent, const char *name ) : form_ClientTest(parent,name)
{
EditedItem=lvCatalogDesign->firstChild();
LineEdit = new QLineEdit(frameEditValue,"LineEdit");
		LineEdit->setGeometry( QRect( 10, 10, 91, 51 ) );

  FieldTypBox = new QComboBox(frameEditValue,"FieldTypBox");
FieldTypBox->setGeometry( QRect( 10, 10, 91, 51 ) );

   	 	FieldTypBox->insertItem( trUtf8( "direkt" ) );
	    FieldTypBox->insertItem( trUtf8( "file" ) );
     FieldTypBox->insertItem( trUtf8( "id" ) );
     FieldTypBox->insertItem( trUtf8( "multi id" ) );
     FieldTypBox->insertItem( trUtf8( "reverse id" ) );
FieldTypBox->hide();
LineEdit->hide();

SubTablesBox = new QComboBox(frameEditValue,"SubTablesBox");
SubTablesBox->setGeometry( QRect( 10, 10, 91, 51 ) );
SubTablesBox->hide();

connect( SubTablesBox, SIGNAL( activated(int) ), this, SLOT( SubTableChangedSlot() ) );
connect( FieldTypBox, SIGNAL( activated(int) ), this, SLOT( FieldTypChangedSlot() ) );
Catalog=NULL;
}

ClientTestDlg::~ClientTestDlg(){
}

void ClientTestDlg::SubTableChangedSlot()
{
   if (lvCatalogDesign->currentItem()->text(1) == SubTablesBox->currentText())
   	return;

   QListViewItem *t,*d;
    t=EditedItem->firstChild();
    while (t!=NULL)
    {
   	 d=t;
   	 t=t->nextSibling();
     delete d;
    }



    t=FindTable(SubTablesBox->currentText());
    if (t==lvCatalogDesign->currentItem()->parent()->parent())
{
    QMessageBox::warning( this, "Recursive",
    "This would create an infinite Recursive Loop" );
 }
 else
 {

	CopyTable(t->firstChild(),lvCatalogDesign->currentItem());
    lvCatalogDesign->currentItem()->setText(1,SubTablesBox->currentText());
 	
	}
 	

 //SubTablesBox->clear();
//	ParseList(1,lvCatalogDesign->firstChild());

}


void ClientTestDlg::FieldTypChangedSlot()
{

lvCatalogDesign->selectedItem()->setText(1,FieldTypBox->text(FieldTypBox->currentItem()));
 	
 char str2[20];
    sprintf(str2,"%d",FieldTypBox->currentItem());

 	lvCatalogDesign->selectedItem()->setText(2,str2);


  QListViewItem *d,*t=lvCatalogDesign->selectedItem()->parent()->firstChild();

  if (FieldTypBox->currentItem()<=1)
  {
    while (t->text(0)!="datatyp")
    	t=t->nextSibling();


    if (t->firstChild()!=NULL)
    {
      t->setText(1,"");
    t=t->firstChild();
    while (t!=NULL)
    {
   	 d=t;
   	 t=t->nextSibling();
     delete d;
    }

     }

	
  }
}


void ClientTestDlg::SelectionChangedSlot()
 {
QString str;
LineEdit->hide();
FieldTypBox->hide();
SubTablesBox->hide();

str=EditedItem->text(0);
if ((str == "Name") || (str=="Typ"))
{
	
	if ((EditedItem->parent()->text(0) == "Field") || (EditedItem->text(1)==LineEdit->text()) || (FindTable(LineEdit->text())==NULL))
 {
	EditedItem->setText(1,LineEdit->text());

 	if ((EditedItem->parent()->parent()!=NULL) &&(EditedItem->parent()->parent()->text(0)=="datatyp"))
  {
    EditedItem->parent()->parent()->setText(1,LineEdit->text());
    }
 }
 else
   QMessageBox::warning( this, "Table exists",
    "A table with this name already exists" );

}

if (str == "datatyp")
{
	if (GetFieldTyp(EditedItem)->text(2).toInt() <= 1)
 		EditedItem->setText(1,LineEdit->text());
}



if (lvCatalogDesign->selectedItem())
{

EditedItem=lvCatalogDesign->selectedItem();

str=lvCatalogDesign->selectedItem()->text(0);
    if ((str == "Name") || (str=="Typ"))
    {
		LineEdit->show();
		LineEdit->setText(lvCatalogDesign->selectedItem()->text(1));
	}

	if (str == "datatyp")
	{

		if (GetFieldTyp(lvCatalogDesign->selectedItem())->text(2).toInt() <= 1)
		{
    		LineEdit->show();
			LineEdit->setText(lvCatalogDesign->selectedItem()->text(1));
		}
  		else
    	{
    		SubTablesBox->clear();
			ParseList(1,lvCatalogDesign->firstChild());
    		SubTablesBox->show();
      }
	}

    if (str == "Fieldtyp")
    {
  		FieldTypBox->show();
    	FieldTypBox->setCurrentItem(lvCatalogDesign->selectedItem()->text(2).toInt());
	}

   }


}
/** No descriptions */
void ClientTestDlg::AddFieldSlot()
  {

if (lvCatalogDesign->selectedItem())
{
QString str;
str=lvCatalogDesign->selectedItem()->text(0);
    if (str == "Table")
	    AddField();
     }







}
/** No descriptions */
void ClientTestDlg::AddField()
{
QListViewItem * field = new QListViewItem( lvCatalogDesign->selectedItem(), 0 );
field->setText( 0, trUtf8( "Field" ) );

QListViewItem * fname = new QListViewItem( field, 0 );
fname->setText( 0, trUtf8( "Name" ) );


QListViewItem * fftyp = new QListViewItem( field, 0 );
fftyp->setText( 0, trUtf8( "Fieldtyp" ) );

QListViewItem * fdtyp = new QListViewItem( field, 0 );
fdtyp->setText( 0, trUtf8( "datatyp" ) );






}

void ClientTestDlg::AddTableSlot()
{
if (lvCatalogDesign->selectedItem())
{
QString str;
str=lvCatalogDesign->selectedItem()->text(0);
    if ( ((str=="datatyp") && (lvCatalogDesign->selectedItem()->firstChild()==NULL) && (GetFieldTyp(lvCatalogDesign->selectedItem())->text(2).toInt()>1)))
	    AddTable();
     }



}

void ClientTestDlg::AddTable()
{
QListViewItem * table = new QListViewItem( lvCatalogDesign->selectedItem(), 0 );
table->setText( 0, trUtf8( "Table" ) );
QListViewItem * tname = new QListViewItem( table, 0 );
tname->setText( 0, trUtf8( "Name" ) );

int i=0;
char str[20];
QString str2;
do
{
sprintf(str,"%d",i);
i++;
str2=(QString)"Table"+str;
}
while (FindTable(str2)!=NULL);

tname->setText(1,(QString)"Table"+(QString)str);

if (lvCatalogDesign->selectedItem()->text(0)=="datatyp")
  {
    lvCatalogDesign->selectedItem()->setText(1,tname->text(1));
    }

}

void ClientTestDlg::CopyTable(QListViewItem* source,QListViewItem* target)
{

 QListViewItem * tname = new QListViewItem( target, "Table");

ParseList(2,source,tname);

}



QListViewItem *ClientTestDlg::GetFieldTyp(QListViewItem *item)
{
QListViewItem *ti;
ti=item;
ti=ti->parent();
if (ti->text(0) != "Field") return NULL;
ti=ti->firstChild();
while (ti->text(0) != "Fieldtyp")
{
ti=ti->nextSibling();
}

return ti;

}


QListViewItem *ClientTestDlg::ParseList(char mode, QListViewItem *item,QListViewItem *target=NULL,QString name="")
{
QListViewItem *savetarget=target;

	if (mode==1)
	{
		
		if ((item->parent()!=NULL) && (item->parent()->text(0)=="Table") && (item->text(0)=="Name"))
			SubTablesBox->insertItem( item->text(1) );
	}
	if (mode==4)
 	{
    	if (item->text(0)=="Table")
			tmpInt++;
    }


if (mode==2)
{
QListViewItem * tname = new QListViewItem( target, item->text(0),item->text(1),item->text(2));
if (item->firstChild()!=NULL)
	target=tname;
}

if (mode==3)
{
	if ((item->parent()!=NULL) && (item->parent()->text(0)=="Table") && (item->text(0)=="Name") && (item->text(1)==name))
	{
	 	tmpGlobalQListView=item;
	  	return NULL;
    }
}




if (item->firstChild()!=NULL)
	ParseList(mode,item->firstChild(),target,name);

if (mode==2)
{
target=savetarget;
}



if (item->nextSibling()!=NULL)
	ParseList(mode,item->nextSibling(),target,name);

return NULL;


}

	
void ClientTestDlg::TestSlot()
{
}


QListViewItem *ClientTestDlg::FindTable (QString name)
{
tmpGlobalQListView=NULL;
ParseList(3,lvCatalogDesign->firstChild(),NULL,name);
if (tmpGlobalQListView!=NULL)
	return tmpGlobalQListView->parent();
return NULL;
}


void ClientTestDlg::AddTagSlot()
{
if (lvCatalogDesign->selectedItem())
{
QString str;
str=lvCatalogDesign->selectedItem()->text(0);
    if ( str=="Field" )
	    AddTag();
     }


}

void ClientTestDlg::AddTag()
{
QListViewItem * table = new QListViewItem( lvCatalogDesign->selectedItem(), 0 );
table->setText( 0, trUtf8( "Tag" ) );
QListViewItem * tname = new QListViewItem( table, 0 );
tname->setText( 0, trUtf8( "Typ" ) );
QListViewItem * name = new QListViewItem( table, 0 );
name->setText( 0, trUtf8( "Name" ) );
}



void ClientTestDlg::SaveSlot()
{

CreateCPPCatalog();
if (Catalog->name=="")
{

	QMessageBox::warning(this,"No Catalog Name","You must give the Catalog a name before you can save it","OK");
 	Save->setDown(false);
	return;
}

QDomDocument doc( "Catalog" );

doc.appendChild(Catalog->ToXML(doc));

QString xml = doc.toString();

QFile f(Catalog->name+".xml");
f.open(IO_WriteOnly);
f.writeBlock( xml, qstrlen(xml) );
f.close();


}

int ClientTestDlg::GetNumberOfTables(QListViewItem* item)
{
	tmpInt=0;
	ParseList(4,item);
	return tmpInt;
}

// item: first child of the tree to parse
int ClientTestDlg::GetNumberOfFields(QListViewItem* item)
{
	int nb_of_fields=0;
	do
 	{
    	if (item->text(0)=="Field")
     		nb_of_fields++;
    } while ((item=item->nextSibling())!=NULL);

    return nb_of_fields;
}

int ClientTestDlg::GetNumberOfTags(QListViewItem* item)
{
	int nb_of_tags=0;
	do
 	{
    	if (item->text(0)=="Tag")
     		nb_of_tags++;
    } while ((item=item->nextSibling())!=NULL);

    return nb_of_tags;
}



void ClientTestDlg::CreateCPPCatalog()
{
QListViewItem *item;


FilledCppTables=0;
item=lvCatalogDesign->firstChild()->firstChild();
if (Catalog!=NULL) delete Catalog;
Catalog = new CppCatalog();
Catalog->nb_tables=GetNumberOfTables(item);
if (Catalog->nb_tables>0)
	Catalog->tables=new CppTable[Catalog->nb_tables];

do
{
	if (item->text(0)=="Name")
		Catalog->name=item->text(1);

	if (item->text(0)=="Table")
 	{
		FilledCppTables++;
		FillCppTable(Catalog->tables[FilledCppTables-1],item);
		

	}


}
while ((item->nextSibling()) && (item=item->nextSibling()));


}

void ClientTestDlg::FillCppTable(CppTable& table,QListViewItem *item)
{
int FilledCppFields=0;
item=item->firstChild();
table.nb_fields=GetNumberOfFields(item);
if (table.nb_fields>0)
	table.fields=new CppField[table.nb_fields];


do
{
	if (item->text(0)=="Field")
	{
   		FilledCppFields++;
		FillCppField(table.fields[FilledCppFields-1],item);
  		
	}

	if (item->text(0)=="Name")
		table.name=item->text(1);
	

}
while ((item->nextSibling()) && (item=item->nextSibling()));


}

void ClientTestDlg::FillCppField(CppField& field,QListViewItem *item)
{
int FilledCppTags=0;
item=item->firstChild();
field.nb_tags=GetNumberOfTags(item);
if (field.nb_tags>0)
	field.tags=new CppTag[field.nb_tags];
do
{
	if (item->text(0)=="Tag")
	{
   		FilledCppTags++;
		FillCppTag(field.tags[FilledCppTags-1],item);
		
    }

	if (item->text(0)=="Name")
		field.name=item->text(1);
	if (item->text(0)=="datatyp")
		field.datatyp=item->text(1);
	if (item->text(0)=="Fieldtyp")
		field.fieldtyp=item->text(2).toInt();
} while ((item->nextSibling()) && (item=item->nextSibling()));

	
	if (field.fieldtyp>1)
	{
		item=item->parent()->firstChild();
  		while ((item->nextSibling()) && item->text(0)!="datatyp")
    	{
			item=item->nextSibling();
 		}
   		FilledCppTables++;
	   	FillCppTable(Catalog->tables[FilledCppTables-1],item->firstChild());
		
	}


}

void ClientTestDlg::FillCppTag(CppTag& tag,QListViewItem *item)
{

item=item->firstChild();
do
{

	if (item->text(0)=="Typ")
		tag.typ=item->text(1);
	if (item->text(0)=="Name")
		tag.name=item->text(1);

} while ((item->nextSibling()) && (item=item->nextSibling()));
}
