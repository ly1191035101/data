/****************************************************************************
** Meta object code from reading C++ file 'set.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../set.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'set.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_set_t {
    QByteArrayData data[19];
    char stringdata[454];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_set_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_set_t qt_meta_stringdata_set = {
    {
QT_MOC_LITERAL(0, 0, 3),
QT_MOC_LITERAL(1, 4, 23),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 19),
QT_MOC_LITERAL(4, 49, 20),
QT_MOC_LITERAL(5, 70, 25),
QT_MOC_LITERAL(6, 96, 24),
QT_MOC_LITERAL(7, 121, 30),
QT_MOC_LITERAL(8, 152, 33),
QT_MOC_LITERAL(9, 186, 28),
QT_MOC_LITERAL(10, 215, 29),
QT_MOC_LITERAL(11, 245, 32),
QT_MOC_LITERAL(12, 278, 33),
QT_MOC_LITERAL(13, 312, 22),
QT_MOC_LITERAL(14, 335, 21),
QT_MOC_LITERAL(15, 357, 21),
QT_MOC_LITERAL(16, 379, 29),
QT_MOC_LITERAL(17, 409, 18),
QT_MOC_LITERAL(18, 428, 24)
    },
    "set\0on_M0contButton_clicked\0\0"
    "on_evButton_clicked\0on_msgButton_clicked\0"
    "on_registerButton_clicked\0"
    "on_M0stateButton_clicked\0"
    "on_M0led_confirmButton_clicked\0"
    "on_M0buzzer_confirmButton_clicked\0"
    "on_fan_confirmButton_clicked\0"
    "on_tube_confirmButton_clicked\0"
    "on_A9led_confirmButton_3_clicked\0"
    "on_A9buzzer_confirmButton_clicked\0"
    "on_logonButton_clicked\0on_exitButton_clicked\0"
    "on_wifiButton_clicked\0"
    "on_connect_pushButton_clicked\0"
    "on_readyRead_slots\0on_setdataButton_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_set[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08,
       3,    0,  100,    2, 0x08,
       4,    0,  101,    2, 0x08,
       5,    0,  102,    2, 0x08,
       6,    0,  103,    2, 0x08,
       7,    0,  104,    2, 0x08,
       8,    0,  105,    2, 0x08,
       9,    0,  106,    2, 0x08,
      10,    0,  107,    2, 0x08,
      11,    0,  108,    2, 0x08,
      12,    0,  109,    2, 0x08,
      13,    0,  110,    2, 0x08,
      14,    0,  111,    2, 0x08,
      15,    0,  112,    2, 0x08,
      16,    0,  113,    2, 0x08,
      17,    0,  114,    2, 0x08,
      18,    0,  115,    2, 0x08,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void set::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        set *_t = static_cast<set *>(_o);
        switch (_id) {
        case 0: _t->on_M0contButton_clicked(); break;
        case 1: _t->on_evButton_clicked(); break;
        case 2: _t->on_msgButton_clicked(); break;
        case 3: _t->on_registerButton_clicked(); break;
        case 4: _t->on_M0stateButton_clicked(); break;
        case 5: _t->on_M0led_confirmButton_clicked(); break;
        case 6: _t->on_M0buzzer_confirmButton_clicked(); break;
        case 7: _t->on_fan_confirmButton_clicked(); break;
        case 8: _t->on_tube_confirmButton_clicked(); break;
        case 9: _t->on_A9led_confirmButton_3_clicked(); break;
        case 10: _t->on_A9buzzer_confirmButton_clicked(); break;
        case 11: _t->on_logonButton_clicked(); break;
        case 12: _t->on_exitButton_clicked(); break;
        case 13: _t->on_wifiButton_clicked(); break;
        case 14: _t->on_connect_pushButton_clicked(); break;
        case 15: _t->on_readyRead_slots(); break;
        case 16: _t->on_setdataButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject set::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_set.data,
      qt_meta_data_set,  qt_static_metacall, 0, 0}
};


const QMetaObject *set::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *set::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_set.stringdata))
        return static_cast<void*>(const_cast< set*>(this));
    return QDialog::qt_metacast(_clname);
}

int set::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
