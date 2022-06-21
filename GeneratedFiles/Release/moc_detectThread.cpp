/****************************************************************************
** Meta object code from reading C++ file 'detectThread.h'
**
** Created: Tue Jun 21 14:23:04 2022
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../detectThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'detectThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DetectThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      48,   14,   13,   13, 0x05,
     120,   92,   13,   13, 0x05,
     170,  159,   13,   13, 0x05,
     205,  200,   13,   13, 0x25,
     231,   13,   13,   13, 0x05,
     273,  265,   13,   13, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DetectThread[] = {
    "DetectThread\0\0nCamNo,nImgNo,dCostTime,tmpResult\0"
    "signals_updateActiveImg(int,int,double,int)\0"
    "nCamSN,nSignalNo,nErrorType\0"
    "signals_AddErrorTableView(int,int,int)\0"
    "nCam,nMode\0signals_upDateCamera(int,int)\0"
    "nCam\0signals_upDateCamera(int)\0"
    "signals_updateCameraFailureRate()\0"
    ",,,,,,,\0"
    "signals_updateImage(QImage*,QString,QString,QString,QString,QString,QL"
    "ist<QRect>,int)\0"
};

void DetectThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DetectThread *_t = static_cast<DetectThread *>(_o);
        switch (_id) {
        case 0: _t->signals_updateActiveImg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->signals_AddErrorTableView((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->signals_upDateCamera((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->signals_upDateCamera((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->signals_updateCameraFailureRate(); break;
        case 5: _t->signals_updateImage((*reinterpret_cast< QImage*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QList<QRect>(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DetectThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DetectThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DetectThread,
      qt_meta_data_DetectThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DetectThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DetectThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DetectThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DetectThread))
        return static_cast<void*>(const_cast< DetectThread*>(this));
    return QThread::qt_metacast(_clname);
}

int DetectThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void DetectThread::signals_updateActiveImg(int _t1, int _t2, double _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DetectThread::signals_AddErrorTableView(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DetectThread::signals_upDateCamera(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void DetectThread::signals_updateCameraFailureRate()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void DetectThread::signals_updateImage(QImage * _t1, QString _t2, QString _t3, QString _t4, QString _t5, QString _t6, QList<QRect> _t7, int _t8)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
