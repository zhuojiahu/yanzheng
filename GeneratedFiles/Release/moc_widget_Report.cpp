/****************************************************************************
** Meta object code from reading C++ file 'widget_Report.h'
**
** Created: Wed Jul 20 09:15:18 2022
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../widget_Report.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_Report.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WidgetReport[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      41,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WidgetReport[] = {
    "WidgetReport\0\0slots_ShowPie(QModelIndex)\0"
    "slots_check()\0"
};

void WidgetReport::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WidgetReport *_t = static_cast<WidgetReport *>(_o);
        switch (_id) {
        case 0: _t->slots_ShowPie((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: _t->slots_check(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WidgetReport::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WidgetReport::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WidgetReport,
      qt_meta_data_WidgetReport, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WidgetReport::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WidgetReport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WidgetReport::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetReport))
        return static_cast<void*>(const_cast< WidgetReport*>(this));
    return QWidget::qt_metacast(_clname);
}

int WidgetReport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
