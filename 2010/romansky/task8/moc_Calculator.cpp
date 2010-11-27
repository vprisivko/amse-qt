/****************************************************************************
** Meta object code from reading C++ file 'Calculator.h'
**
** Created: Sat Nov 27 21:18:09 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Calculator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Calculator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Calculator[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      18,   11,   11,   11, 0x0a,
      24,   11,   11,   11, 0x0a,
      30,   11,   11,   11, 0x0a,
      36,   11,   11,   11, 0x0a,
      43,   11,   11,   11, 0x0a,
      50,   11,   11,   11, 0x0a,
      57,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Calculator[] = {
    "Calculator\0\0Add()\0Sub()\0Mul()\0Div()\0"
    "Calc()\0Open()\0Save()\0Revert()\0"
};

const QMetaObject Calculator::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Calculator,
      qt_meta_data_Calculator, 0 }
};

const QMetaObject *Calculator::metaObject() const
{
    return &staticMetaObject;
}

void *Calculator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Calculator))
        return static_cast<void*>(const_cast< Calculator*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Calculator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Add(); break;
        case 1: Sub(); break;
        case 2: Mul(); break;
        case 3: Div(); break;
        case 4: Calc(); break;
        case 5: Open(); break;
        case 6: Save(); break;
        case 7: Revert(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
