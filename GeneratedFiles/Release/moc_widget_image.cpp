/****************************************************************************
** Meta object code from reading C++ file 'widget_image.h'
**
** Created: Tue Jun 21 14:23:03 2022
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../widget_image.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_image.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      33,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      61,   53,   12,   12, 0x0a,
     131,   12,   12,   12, 0x0a,
     191,  163,   12,   12, 0x0a,
     219,   12,   12,   12, 0x0a,
     237,   12,   12,   12, 0x0a,
     253,   12,   12,   12, 0x0a,
     269,   12,   12,   12, 0x0a,
     305,  297,   12,   12, 0x0a,
     326,  297,   12,   12, 0x0a,
     347,   12,   12,   12, 0x0a,
     374,  297,   12,   12, 0x0a,
     396,  297,   12,   12, 0x0a,
     417,  297,   12,   12, 0x0a,
     437,   12,   12,   12, 0x0a,
     467,  458,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ImageWidget[] = {
    "ImageWidget\0\0signals_showCarve()\0"
    "signals_hideCarve()\0,,,,,,,\0"
    "slots_showErrorImage(QImage*,int,int,double,int,int,QList<QRect>,int)\0"
    "slots_imageItemDoubleClick(int)\0"
    "nCamSN,nSignalNo,nErrorType\0"
    "slots_addError(int,int,int)\0"
    "slots_turnImage()\0slots_setPama()\0"
    "slot_PameSure()\0slots_showStartRefresh(int)\0"
    "nItemID\0slots_showCheck(int)\0"
    "slots_stopCheck(int)\0slots_stopAllStressCheck()\0"
    "slots_startCheck(int)\0slots_startShow(int)\0"
    "slots_stopShow(int)\0slots_startShowAll()\0"
    "cameraId\0slots_showOnlyCamera(int)\0"
};

void ImageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImageWidget *_t = static_cast<ImageWidget *>(_o);
        switch (_id) {
        case 0: _t->signals_showCarve(); break;
        case 1: _t->signals_hideCarve(); break;
        case 2: _t->slots_showErrorImage((*reinterpret_cast< QImage*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< QList<QRect>(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8]))); break;
        case 3: _t->slots_imageItemDoubleClick((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slots_addError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->slots_turnImage(); break;
        case 6: _t->slots_setPama(); break;
        case 7: _t->slot_PameSure(); break;
        case 8: _t->slots_showStartRefresh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slots_showCheck((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slots_stopCheck((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slots_stopAllStressCheck(); break;
        case 12: _t->slots_startCheck((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->slots_startShow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->slots_stopShow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->slots_startShowAll(); break;
        case 16: _t->slots_showOnlyCamera((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ImageWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImageWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImageWidget,
      qt_meta_data_ImageWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImageWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageWidget))
        return static_cast<void*>(const_cast< ImageWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void ImageWidget::signals_showCarve()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ImageWidget::signals_hideCarve()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
