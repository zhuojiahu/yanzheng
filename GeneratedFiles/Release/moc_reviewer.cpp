/****************************************************************************
** Meta object code from reading C++ file 'reviewer.h'
**
** Created: Tue Jun 21 14:38:20 2022
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../reviewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reviewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Reviewer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   10,    9,    9, 0x0a,
      66,   53,    9,    9, 0x2a,
      88,   86,    9,    9, 0x0a,
     113,    9,    9,    9, 0x0a,
     131,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Reviewer[] = {
    "Reviewer\0\0current_page,iPara\0"
    "slots_turnPage(int,int)\0current_page\0"
    "slots_turnPage(int)\0e\0closeEvent(QCloseEvent*)\0"
    "slots_OnBtnStar()\0slots_Clear()\0"
};

void Reviewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Reviewer *_t = static_cast<Reviewer *>(_o);
        switch (_id) {
        case 0: _t->slots_turnPage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slots_turnPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 3: _t->slots_OnBtnStar(); break;
        case 4: _t->slots_Clear(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Reviewer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Reviewer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Reviewer,
      qt_meta_data_Reviewer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Reviewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Reviewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Reviewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Reviewer))
        return static_cast<void*>(const_cast< Reviewer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Reviewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
