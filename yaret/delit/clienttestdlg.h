/***************************************************************************
                          clienttestdlg.h  -  description
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

#ifndef CLIENTTESTDLG_H
#define CLIENTTESTDLG_H


#include "database.h"
#include <qwidget.h>
#include "ClientDlg.h"


class QLineEdit;
class QComboBox;


/**
  *@author Jascha Schubert
  */

class ClientTestDlg : public form_ClientTest  {
   Q_OBJECT
public: 
	ClientTestDlg(QWidget *parent=0, const char *name=0);
	~ClientTestDlg();
  /** No descriptions */
  void AddField();
  void AddTable();
  void AddTag();
  void CreateCPPCatalog();
  int GetNumberOfTags(QListViewItem* item);
  QLineEdit *LineEdit;
  QComboBox *FieldTypBox;
  QListViewItem *EditedItem;
  QComboBox *SubTablesBox;
  QListViewItem *ParseList(char,QListViewItem*,QListViewItem* target=NULL,QString name="");
  void CopyTable(QListViewItem* source,QListViewItem* target);
  QListViewItem *GetFieldTyp(QListViewItem *item);
  QListViewItem *FindTable (QString name);
  QListViewItem *tmpGlobalQListView;
  CppCatalog *Catalog;
  void FillCppTable(CppTable &,QListViewItem *);
  void FillCppField(CppField& field,QListViewItem *item);
  void FillCppTag(CppTag& tag,QListViewItem *item);
  int GetNumberOfTables(QListViewItem*);
  int tmpInt;
  int FilledCppTables;
  int GetNumberOfFields(QListViewItem* item);
	
public slots: // Public slots
  /** No descriptions */
  void AddFieldSlot();
  void AddTableSlot();
  void SubTableChangedSlot();
  void FieldTypChangedSlot();


  /** No descriptions */
  void SelectionChangedSlot();
  /** No descriptions */
  void TestSlot();
  /** No descriptions */
  void AddTagSlot();
  /** No descriptions */
  void SaveSlot();
};

#endif
