/****************************************************************************
** Form interface generated from reading ui file 'ClientDlg.ui'
**
** Created: Son Apr 28 22:34:27 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FORM_CLIENTTEST_H
#define FORM_CLIENTTEST_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QFrame;
class QListView;
class QListViewItem;
class QPushButton;

class form_ClientTest : public QDialog
{ 
    Q_OBJECT

public:
    form_ClientTest( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~form_ClientTest();

    QPushButton* pb_test;
    QFrame* frameEditValue;
    QListView* lvCatalogDesign;
    QPushButton* Add_Field;
    QPushButton* Add_Tag;
    QPushButton* Add_Table;
    QPushButton* Save;


public slots:
    virtual void AddFieldSlot();
    virtual void AddTableSlot();
    virtual void AddTagSlot();
    virtual void SelectionChangedSlot();
    virtual void TestSlot();
    virtual void SaveSlot();

};

#endif // FORM_CLIENTTEST_H
