/****************************************************************************
** Meta object code from reading C++ file 'Widget_CountPlot.h'
**
** Created: Tue Jun 21 14:23:03 2022
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Widget_CountPlot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Widget_CountPlot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Widget_CountPlot[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   18,   17,   17, 0x08,
      52,   18,   17,   17, 0x08,
      76,   17,   17,   17, 0x08,
      95,   17,   17,   17, 0x08,
     113,   17,   17,   17, 0x08,
     133,   17,   17,   17, 0x08,
     153,  151,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Widget_CountPlot[] = {
    "Widget_CountPlot\0\0isChecked\0"
    "Table1CheckedSlot(bool)\0Table2CheckedSlot(bool)\0"
    "SearchButtonSlot()\0PushBtnSaveSlot()\0"
    "PushBtnCancelSlot()\0slots_saveTable()\0"
    "e\0Slots_Show_ContextMenu(QMouseEvent*)\0"
};

void Widget_CountPlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Widget_CountPlot *_t = static_cast<Widget_CountPlot *>(_o);
        switch (_id) {
        case 0: _t->Table1CheckedSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->Table2CheckedSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->SearchButtonSlot(); break;
        case 3: _t->PushBtnSaveSlot(); break;
        case 4: _t->PushBtnCancelSlot(); break;
        case 5: _t->slots_saveTable(); break;
        case 6: _t->Slots_Show_ContextMenu((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Widget_CountPlot::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Widget_CountPlot::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget_CountPlot,
      qt_meta_data_Widget_CountPlot, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Widget_CountPlot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Widget_CountPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Widget_CountPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Widget_CountPlot))
        return static_cast<void*>(const_cast< Widget_CountPlot*>(this));
    return QWidget::qt_metacast(_clname);
}

int Widget_CountPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
