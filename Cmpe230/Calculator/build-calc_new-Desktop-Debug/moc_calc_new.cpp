/****************************************************************************
** Meta object code from reading C++ file 'calc_new.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../calc_new/calc_new.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calc_new.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_calc_new_t {
    QByteArrayData data[13];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_calc_new_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_calc_new_t qt_meta_stringdata_calc_new = {
    {
QT_MOC_LITERAL(0, 0, 8), // "calc_new"
QT_MOC_LITERAL(1, 9, 12), // "digitClicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "hexDigitClicked"
QT_MOC_LITERAL(4, 39, 8), // "clearAll"
QT_MOC_LITERAL(5, 48, 21), // "divisionButtonClicked"
QT_MOC_LITERAL(6, 70, 18), // "timesButtonClicked"
QT_MOC_LITERAL(7, 89, 18), // "minusButtonClicked"
QT_MOC_LITERAL(8, 108, 17), // "plusButtonClicked"
QT_MOC_LITERAL(9, 126, 18), // "equalButtonClicked"
QT_MOC_LITERAL(10, 145, 16), // "decButtonClicked"
QT_MOC_LITERAL(11, 162, 16), // "hexButtonClicked"
QT_MOC_LITERAL(12, 179, 19) // "handlePrevOperation"

    },
    "calc_new\0digitClicked\0\0hexDigitClicked\0"
    "clearAll\0divisionButtonClicked\0"
    "timesButtonClicked\0minusButtonClicked\0"
    "plusButtonClicked\0equalButtonClicked\0"
    "decButtonClicked\0hexButtonClicked\0"
    "handlePrevOperation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_calc_new[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void calc_new::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        calc_new *_t = static_cast<calc_new *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->digitClicked(); break;
        case 1: _t->hexDigitClicked(); break;
        case 2: _t->clearAll(); break;
        case 3: _t->divisionButtonClicked(); break;
        case 4: _t->timesButtonClicked(); break;
        case 5: _t->minusButtonClicked(); break;
        case 6: _t->plusButtonClicked(); break;
        case 7: _t->equalButtonClicked(); break;
        case 8: _t->decButtonClicked(); break;
        case 9: _t->hexButtonClicked(); break;
        case 10: _t->handlePrevOperation(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject calc_new::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_calc_new.data,
      qt_meta_data_calc_new,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *calc_new::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *calc_new::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_calc_new.stringdata0))
        return static_cast<void*>(const_cast< calc_new*>(this));
    return QWidget::qt_metacast(_clname);
}

int calc_new::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
