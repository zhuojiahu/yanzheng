/****************************************************************************
** Meta object code from reading C++ file 'widget_title.h'
**
** Created: Fri Jul 8 17:19:12 2022
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../widget_title.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_title.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WidgetTitle[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   13,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WidgetTitle[] = {
    "WidgetTitle\0\0current_page\0turnPage(int)\0"
    "turnPage(QString)\0"
};

void WidgetTitle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WidgetTitle *_t = static_cast<WidgetTitle *>(_o);
        switch (_id) {
        case 0: _t->turnPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->turnPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WidgetTitle::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WidgetTitle::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WidgetTitle,
      qt_meta_data_WidgetTitle, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WidgetTitle::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WidgetTitle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WidgetTitle::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetTitle))
        return static_cast<void*>(const_cast< WidgetTitle*>(this));
    return QWidget::qt_metacast(_clname);
}

int WidgetTitle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void WidgetTitle::turnPage(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
