
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;


#include <iostream.h>
#include <stdlib.h>
#include <qapplication.h>
#include "clienttestdlg.h"

#define BufferSize 1024


int main(int argc, char *argv[])
{
  QApplication app( argc,argv);


  ClientTestDlg  *fenster = new ClientTestDlg();
   app.setMainWidget( fenster );
   fenster->show();

//   fenster.LineEdit8->Text="HALLO";

//   fenster.le_MaxDataLength->setText("SS");

  // alloc memory
	


	
	
	

	



  return app.exec();



}
