/****************************************************************************
** Form implementation generated from reading ui file 'ClientDlg.ui'
**
** Created: Son Apr 28 22:34:27 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "ClientDlg.h"

#include <qvariant.h>
#include <qframe.h>
#include <qheader.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>


/* 
 *  Constructs a form_ClientTest which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
form_ClientTest::form_ClientTest( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "form_ClientTest" );
    resize( 802, 731 ); 
    setCaption( trUtf8( "Form1" ) );

    pb_test = new QPushButton( this, "pb_test" );
    pb_test->setGeometry( QRect( 410, 420, 51, 51 ) ); 
    pb_test->setText( trUtf8( "Test" ) );

    frameEditValue = new QFrame( this, "frameEditValue" );
    frameEditValue->setGeometry( QRect( 410, 30, 240, 160 ) ); 
    frameEditValue->setFrameShape( QFrame::StyledPanel );
    frameEditValue->setFrameShadow( QFrame::Raised );

    lvCatalogDesign = new QListView( this, "lvCatalogDesign" );
    lvCatalogDesign->addColumn( trUtf8( "Catalog" ) );
    lvCatalogDesign->addColumn( trUtf8( "Value" ) );
    lvCatalogDesign->addColumn( trUtf8( "id" ) );
    QListViewItem * item_2 = new QListViewItem( lvCatalogDesign, 0 );
    item_2->setOpen( TRUE );
    QListViewItem * item_3 = new QListViewItem( item_2, 0 );
    item_3->setOpen( TRUE );
    QListViewItem * item = new QListViewItem( item_3, 0 );
    item->setText( 0, trUtf8( "Name" ) );
    item->setText( 1, trUtf8( "Table0" ) );
    item_3->setText( 0, trUtf8( "Table" ) );
    item_2->setOpen( TRUE );
    item = new QListViewItem( item_2, item_3 );
    item->setText( 0, trUtf8( "Name" ) );
    item_2->setText( 0, trUtf8( "Catalog" ) );

    lvCatalogDesign->setGeometry( QRect( 30, 30, 360, 450 ) ); 

    Add_Field = new QPushButton( this, "Add_Field" );
    Add_Field->setGeometry( QRect( 410, 290, 161, 41 ) ); 
    Add_Field->setText( trUtf8( "Add Field" ) );

    Add_Tag = new QPushButton( this, "Add_Tag" );
    Add_Tag->setGeometry( QRect( 410, 350, 161, 41 ) ); 
    Add_Tag->setText( trUtf8( "Add Tag" ) );

    Add_Table = new QPushButton( this, "Add_Table" );
    Add_Table->setGeometry( QRect( 410, 230, 161, 41 ) ); 
    Add_Table->setText( trUtf8( "Add Table" ) );

    Save = new QPushButton( this, "Save" );
    Save->setGeometry( QRect( 590, 230, 111, 41 ) ); 
    Save->setText( trUtf8( "Save" ) );

    // signals and slots connections
    connect( Add_Field, SIGNAL( pressed() ), this, SLOT( AddFieldSlot() ) );
    connect( lvCatalogDesign, SIGNAL( selectionChanged() ), this, SLOT( SelectionChangedSlot() ) );
    connect( Add_Table, SIGNAL( pressed() ), this, SLOT( AddTableSlot() ) );
    connect( pb_test, SIGNAL( pressed() ), this, SLOT( TestSlot() ) );
    connect( Add_Tag, SIGNAL( pressed() ), this, SLOT( AddTagSlot() ) );
    connect( Save, SIGNAL( pressed() ), this, SLOT( SaveSlot() ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
form_ClientTest::~form_ClientTest()
{
    // no need to delete child widgets, Qt does it all for us
}

void form_ClientTest::AddFieldSlot()
{
    qWarning( "form_ClientTest::AddFieldSlot(): Not implemented yet!" );
}

void form_ClientTest::AddTableSlot()
{
    qWarning( "form_ClientTest::AddTableSlot(): Not implemented yet!" );
}

void form_ClientTest::AddTagSlot()
{
    qWarning( "form_ClientTest::AddTagSlot(): Not implemented yet!" );
}

void form_ClientTest::SelectionChangedSlot()
{
    qWarning( "form_ClientTest::SelectionChangedSlot(): Not implemented yet!" );
}

void form_ClientTest::TestSlot()
{
    qWarning( "form_ClientTest::TestSlot(): Not implemented yet!" );
}

void form_ClientTest::SaveSlot()
{
    qWarning( "form_ClientTest::SaveSlot(): Not implemented yet!" );
}

