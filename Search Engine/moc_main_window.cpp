/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "main_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      21,   11,   11,   11, 0x08,
      35,   11,   11,   11, 0x08,
      46,   11,   11,   11, 0x08,
      56,   11,   11,   11, 0x08,
      68,   11,   11,   11, 0x08,
      84,   11,   11,   11, 0x08,
     100,   11,   11,   11, 0x08,
     116,   11,   11,   11, 0x08,
     133,   11,   11,   11, 0x08,
     150,   11,   11,   11, 0x08,
     167,   11,   11,   11, 0x08,
     187,   11,   11,   11, 0x08,
     214,  208,   11,   11, 0x08,
     230,  208,   11,   11, 0x08,
     248,  208,   11,   11, 0x08,
     266,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0search()\0clickSingle()\0"
    "clickAND()\0clickOR()\0clickRank()\0"
    "clickFilename()\0clickOutgoing()\0"
    "clickIncoming()\0clickFilename2()\0"
    "clickOutgoing2()\0clickIncoming2()\0"
    "mainButtonClicked()\0otherButtonClicked()\0"
    "index\0showWindow(int)\0showOutgoing(int)\0"
    "showIncoming(int)\0hideWindow()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->search(); break;
        case 1: _t->clickSingle(); break;
        case 2: _t->clickAND(); break;
        case 3: _t->clickOR(); break;
        case 4: _t->clickRank(); break;
        case 5: _t->clickFilename(); break;
        case 6: _t->clickOutgoing(); break;
        case 7: _t->clickIncoming(); break;
        case 8: _t->clickFilename2(); break;
        case 9: _t->clickOutgoing2(); break;
        case 10: _t->clickIncoming2(); break;
        case 11: _t->mainButtonClicked(); break;
        case 12: _t->otherButtonClicked(); break;
        case 13: _t->showWindow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->showOutgoing((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->showIncoming((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->hideWindow(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
