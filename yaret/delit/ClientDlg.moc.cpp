/****************************************************************************
** form_ClientTest meta object code from reading C++ file 'ClientDlg.h'
**
** Created: Sun Apr 28 22:35:43 2002
**      by: The Qt MOC ($Id: ClientDlg.moc.cpp,v 1.2 2002/05/08 22:03:57 Tesla2k Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "ClientDlg.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *form_ClientTest::className() const
{
    return "form_ClientTest";
}

QMetaObject *form_ClientTest::metaObj = 0;
static QMetaObjectCleanUp cleanUp_form_ClientTest;

#ifndef QT_NO_TRANSLATION
QString form_ClientTest::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "form_ClientTest", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString form_ClientTest::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "form_ClientTest", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* form_ClientTest::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"AddFieldSlot", 0, 0 };
    static const QUMethod slot_1 = {"AddTableSlot", 0, 0 };
    static const QUMethod slot_2 = {"AddTagSlot", 0, 0 };
    static const QUMethod slot_3 = {"SelectionChangedSlot", 0, 0 };
    static const QUMethod slot_4 = {"TestSlot", 0, 0 };
    static const QUMethod slot_5 = {"SaveSlot", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "AddFieldSlot()", &slot_0, QMetaData::Public },
	{ "AddTableSlot()", &slot_1, QMetaData::Public },
	{ "AddTagSlot()", &slot_2, QMetaData::Public },
	{ "SelectionChangedSlot()", &slot_3, QMetaData::Public },
	{ "TestSlot()", &slot_4, QMetaData::Public },
	{ "SaveSlot()", &slot_5, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"form_ClientTest", parentObject,
	slot_tbl, 6,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_form_ClientTest.setMetaObject( metaObj );
    return metaObj;
}

void* form_ClientTest::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "form_ClientTest" ) ) return (form_ClientTest*)this;
    return QDialog::qt_cast( clname );
}

bool form_ClientTest::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: AddFieldSlot(); break;
    case 1: AddTableSlot(); break;
    case 2: AddTagSlot(); break;
    case 3: SelectionChangedSlot(); break;
    case 4: TestSlot(); break;
    case 5: SaveSlot(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool form_ClientTest::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool form_ClientTest::qt_property( int _id, int _f, QVariant* _v)
{
    return QDialog::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
