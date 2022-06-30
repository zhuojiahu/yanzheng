/****************************************************************************
** Meta object code from reading C++ file 'MyImageshowItem.h'
**
** Created: Fri Jun 24 17:22:40 2022
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyImageshowItem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyImageshowItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyImageShowItem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      51,   16,   16,   16, 0x05,
      81,   16,   16,   16, 0x05,
     104,   16,   16,   16, 0x05,
     127,   16,   16,   16, 0x05,
     150,   16,   16,   16, 0x05,
     179,   16,   16,   16, 0x05,
     203,   16,   16,   16, 0x05,
     226,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     256,  248,   16,   16, 0x0a,
     340,   16,   16,   16, 0x0a,
     355,   16,   16,   16, 0x0a,
     373,   16,   16,   16, 0x0a,
     391,   16,   16,   16, 0x0a,
     409,   16,   16,   16, 0x0a,
     436,   16,   16,   16, 0x0a,
     455,   16,   16,   16, 0x0a,
     483,   16,   16,   16, 0x0a,
     501,   16,   16,   16, 0x0a,
     518,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyImageShowItem[] = {
    "MyImageShowItem\0\0signals_imageItemDoubleClick(int)\0"
    "signals_showStartRefresh(int)\0"
    "signals_startShowAll()\0signals_showCheck(int)\0"
    "signals_stopCheck(int)\0"
    "signals_stopAllStressCheck()\0"
    "signals_startCheck(int)\0signals_startShow(int)\0"
    "signals_stopShow(int)\0,,,,,,,\0"
    "slots_updateImage(QImage*,QString,QString,QString,QString,QString,QLis"
    "t<QRect>,int)\0"
    "slots_update()\0slots_saveImage()\0"
    "slots_showCheck()\0slots_stopCheck()\0"
    "slots_stopAllStressCheck()\0"
    "slots_startCheck()\0slots_startAllStressCheck()\0"
    "slots_startShow()\0slots_stopShow()\0"
    "slots_startShowAll()\0"
};

void MyImageShowItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyImageShowItem *_t = static_cast<MyImageShowItem *>(_o);
        switch (_id) {
        case 0: _t->signals_imageItemDoubleClick((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signals_showStartRefresh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signals_startShowAll(); break;
        case 3: _t->signals_showCheck((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->signals_stopCheck((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->signals_stopAllStressCheck(); break;
        case 6: _t->signals_startCheck((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->signals_startShow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->signals_stopShow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slots_updateImage((*reinterpret_cast< QImage*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QList<QRect>(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8]))); break;
        case 10: _t->slots_update(); break;
        case 11: _t->slots_saveImage(); break;
        case 12: _t->slots_showCheck(); break;
        case 13: _t->slots_stopCheck(); break;
        case 14: _t->slots_stopAllStressCheck(); break;
        case 15: _t->slots_startCheck(); break;
        case 16: _t->slots_startAllStressCheck(); break;
        case 17: _t->slots_startShow(); break;
        case 18: _t->slots_stopShow(); break;
        case 19: _t->slots_startShowAll(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyImageShowItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyImageShowItem::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyImageShowItem,
      qt_meta_data_MyImageShowItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyImageShowItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyImageShowItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyImageShowItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyImageShowItem))
        return static_cast<void*>(const_cast< MyImageShowItem*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyImageShowItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void MyImageShowItem::signals_imageItemDoubleClick(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyImageShowItem::signals_showStartRefresh(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyImageShowItem::signals_startShowAll()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MyImageShowItem::signals_showCheck(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MyImageShowItem::signals_stopCheck(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MyImageShowItem::signals_stopAllStressCheck()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void MyImageShowItem::signals_startCheck(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MyImageShowItem::signals_startShow(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MyImageShowItem::signals_stopShow(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
