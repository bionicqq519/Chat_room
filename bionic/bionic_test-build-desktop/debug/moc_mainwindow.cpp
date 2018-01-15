/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Fri Dec 24 02:34:25 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      26,   11,   11,   11, 0x08,
      35,   11,   11,   11, 0x08,
      47,   11,   11,   11, 0x08,
      59,   11,   11,   11, 0x08,
      72,   11,   11,   11, 0x08,
      85,   11,   11,   11, 0x08,
     103,   11,   11,   11, 0x08,
     121,   11,   11,   11, 0x08,
     133,   11,   11,   11, 0x08,
     142,   11,   11,   11, 0x08,
     151,   11,   11,   11, 0x08,
     170,   11,   11,   11, 0x08,
     191,   11,   11,   11, 0x08,
     201,   11,   11,   11, 0x08,
     218,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0exitprogram()\0helphw()\0"
    "helpautor()\0loginfunc()\0logoutfunc()\0"
    "submit_btn()\0timecheck_click()\0"
    "simulate_window()\0set_radio()\0accept()\0"
    "reject()\0search_chat_func()\0"
    "set_search_default()\0set_btn()\0"
    "search_allname()\0set_friend_ip()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
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
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: exitprogram(); break;
        case 1: helphw(); break;
        case 2: helpautor(); break;
        case 3: loginfunc(); break;
        case 4: logoutfunc(); break;
        case 5: submit_btn(); break;
        case 6: timecheck_click(); break;
        case 7: simulate_window(); break;
        case 8: set_radio(); break;
        case 9: accept(); break;
        case 10: reject(); break;
        case 11: search_chat_func(); break;
        case 12: set_search_default(); break;
        case 13: set_btn(); break;
        case 14: search_allname(); break;
        case 15: set_friend_ip(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
