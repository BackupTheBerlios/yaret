/****************************************************************************
** ClientTestDlg meta object code from reading C++ file 'clienttestdlg.h'
**
** Created: Mon May 6 10:45:46 2002
**      by: The Qt MOC ($Id: clienttestdlg.moc.cpp,v 1.1 2002/05/06 17:08:56 Tesla2k Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "clienttestdlg.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ClientTestDlg::className() const
{
    return "ClientTestDlg";
}

QMetaObject *ClientTestDlg::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ClientTestDlg;

#ifndef QT_NO_TRANSLATION
QString ClientTestDlg::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ClientTestDlg", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ClientTestDlg::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ClientTestDlg", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ClientTestDlg::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = form_ClientTest::staticMetaObject();
    static const QUMethod slot_0 = {"AddFieldSlot", 0, 0 };
    static const QUMethod slot_1 = {"AddTableSlot", 0, 0 };
    static const QUMethod slot_2 = {"SubTableChangedSlot", 0, 0 };
    static const QUMethod slot_3 = {"FieldTypChangedSlot", 0, 0 };
    static const QUMethod slot_4 = {"SelectionChangedSlot", 0, 0 };
    static const QUMethod slot_5 = {"TestSlot", 0, 0 };
    static const QUMethod slot_6 = {"AddTagSlot", 0, 0 };
    static const QUMethod slot_7 = {"SaveSlot", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "AddFieldSlot()", &slot_0, QMetaData::Public },
	{ "AddTableSlot()", &slot_1, QMetaData::Public },
	{ "SubTableChangedSlot()", &slot_2, QMetaData::Public },
	{ "FieldTypChangedSlot()", &slot_3, QMetaData::Public },
	{ "SelectionChangedSlot()", &slot_4, QMetaData::Public },
	{ "TestSlot()", &slot_5, QMetaData::Public },
	{ "AddTagSlot()", &slot_6, QMetaData::Public },
	{ "SaveSlot()", &slot_7, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"ClientTestDlg", parentObject,
	slot_tbl, 8,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ClientTestDlg.setMetaObject( metaObj );
    return metaObj;
}

void* ClientTestDlg::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ClientTestDlg" ) ) return (ClientTestDlg*)this;
    return form_ClientTest::qt_cast( clname );
}

bool ClientTestDlg::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: AddFieldSlot(); break;
    case 1: AddTableSlot(); break;
    case 2: SubTableChangedSlot(); break;
    case 3: FieldTypChangedSlot(); break;
    case 4: SelectionChangedSlot(); break;
    case 5: TestSlot(); break;
    case 6: AddTagSlot(); break;
    case 7: SaveSlot(); break;
    default:
	return form_ClientTest::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ClientTestDlg::qt_emit( int _id, QUObject* _o )
{
    return form_ClientTest::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool ClientTestDlg::qt_property( int _id, int _f, QVariant* _v)
{
    return form_ClientTest::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
