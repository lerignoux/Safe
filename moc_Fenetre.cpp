/****************************************************************************
** Meta object code from reading C++ file 'Fenetre.h'
**
** Created: Wed Jul 28 22:15:56 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Fenetre.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Fenetre.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Fenetre[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      20,    8,    8,    8, 0x0a,
      29,    8,    8,    8, 0x0a,
      50,    8,    8,    8, 0x0a,
      67,    8,    8,    8, 0x0a,
      79,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Fenetre[] = {
    "Fenetre\0\0findPass()\0copier()\0"
    "setPasswordsWidget()\0setFilesWidget()\0"
    "cryptFile()\0activate()\0"
};

const QMetaObject Fenetre::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Fenetre,
      qt_meta_data_Fenetre, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Fenetre::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Fenetre::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Fenetre::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Fenetre))
        return static_cast<void*>(const_cast< Fenetre*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Fenetre::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: findPass(); break;
        case 1: copier(); break;
        case 2: setPasswordsWidget(); break;
        case 3: setFilesWidget(); break;
        case 4: cryptFile(); break;
        case 5: activate(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
