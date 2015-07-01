/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../NetworkTesterGUI/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata[552];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 27), // "on_progressBar_valueChanged"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 5), // "value"
QT_MOC_LITERAL(4, 46, 28), // "on_RequestSlider_sliderMoved"
QT_MOC_LITERAL(5, 75, 8), // "position"
QT_MOC_LITERAL(6, 84, 30), // "on_RequestSlider_sliderPressed"
QT_MOC_LITERAL(7, 115, 28), // "on_TimeoutSlider_sliderMoved"
QT_MOC_LITERAL(8, 144, 30), // "on_TimeoutSlider_sliderPressed"
QT_MOC_LITERAL(9, 175, 30), // "on_RequestTimeBox_valueChanged"
QT_MOC_LITERAL(10, 206, 4), // "arg1"
QT_MOC_LITERAL(11, 211, 30), // "on_TimeoutTimeBox_valueChanged"
QT_MOC_LITERAL(12, 242, 28), // "on_StopLoggingButton_clicked"
QT_MOC_LITERAL(13, 271, 29), // "on_ApplyChangesButton_clicked"
QT_MOC_LITERAL(14, 301, 27), // "on_DisplayLogsCheck_clicked"
QT_MOC_LITERAL(15, 329, 7), // "checked"
QT_MOC_LITERAL(16, 337, 31), // "on_AlertIfErrorCheckBox_clicked"
QT_MOC_LITERAL(17, 369, 25), // "on_DomainEdit_textChanged"
QT_MOC_LITERAL(18, 395, 23), // "on_NameEdit_textChanged"
QT_MOC_LITERAL(19, 419, 23), // "on_HostEdit_textChanged"
QT_MOC_LITERAL(20, 443, 27), // "on_UsernameEdit_textChanged"
QT_MOC_LITERAL(21, 471, 27), // "on_DatabaseEdit_textChanged"
QT_MOC_LITERAL(22, 499, 27), // "on_PasswordEdit_textChanged"
QT_MOC_LITERAL(23, 527, 24) // "on_EmailEdit_textChanged"

    },
    "MainWindow\0on_progressBar_valueChanged\0"
    "\0value\0on_RequestSlider_sliderMoved\0"
    "position\0on_RequestSlider_sliderPressed\0"
    "on_TimeoutSlider_sliderMoved\0"
    "on_TimeoutSlider_sliderPressed\0"
    "on_RequestTimeBox_valueChanged\0arg1\0"
    "on_TimeoutTimeBox_valueChanged\0"
    "on_StopLoggingButton_clicked\0"
    "on_ApplyChangesButton_clicked\0"
    "on_DisplayLogsCheck_clicked\0checked\0"
    "on_AlertIfErrorCheckBox_clicked\0"
    "on_DomainEdit_textChanged\0"
    "on_NameEdit_textChanged\0on_HostEdit_textChanged\0"
    "on_UsernameEdit_textChanged\0"
    "on_DatabaseEdit_textChanged\0"
    "on_PasswordEdit_textChanged\0"
    "on_EmailEdit_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x08 /* Private */,
       4,    1,  107,    2, 0x08 /* Private */,
       6,    0,  110,    2, 0x08 /* Private */,
       7,    1,  111,    2, 0x08 /* Private */,
       8,    0,  114,    2, 0x08 /* Private */,
       9,    1,  115,    2, 0x08 /* Private */,
      11,    1,  118,    2, 0x08 /* Private */,
      12,    0,  121,    2, 0x08 /* Private */,
      13,    0,  122,    2, 0x08 /* Private */,
      14,    1,  123,    2, 0x08 /* Private */,
      16,    0,  126,    2, 0x08 /* Private */,
      17,    1,  127,    2, 0x08 /* Private */,
      18,    1,  130,    2, 0x08 /* Private */,
      19,    1,  133,    2, 0x08 /* Private */,
      20,    1,  136,    2, 0x08 /* Private */,
      21,    1,  139,    2, 0x08 /* Private */,
      22,    1,  142,    2, 0x08 /* Private */,
      23,    1,  145,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_progressBar_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_RequestSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_RequestSlider_sliderPressed(); break;
        case 3: _t->on_TimeoutSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_TimeoutSlider_sliderPressed(); break;
        case 5: _t->on_RequestTimeBox_valueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_TimeoutTimeBox_valueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_StopLoggingButton_clicked(); break;
        case 8: _t->on_ApplyChangesButton_clicked(); break;
        case 9: _t->on_DisplayLogsCheck_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_AlertIfErrorCheckBox_clicked(); break;
        case 11: _t->on_DomainEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->on_NameEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->on_HostEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->on_UsernameEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->on_DatabaseEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->on_PasswordEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->on_EmailEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
