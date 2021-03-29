/****************************************************************************
** Meta object code from reading C++ file 'ViewInformation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ViewInformation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ViewInformation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ViewInformation_t {
    QByteArrayData data[13];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ViewInformation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ViewInformation_t qt_meta_stringdata_ViewInformation = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ViewInformation"
QT_MOC_LITERAL(1, 16, 10), // "ViewDetail"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(4, 46, 14), // "CheckBoxChange"
QT_MOC_LITERAL(5, 61, 14), // "ChangeBtnState"
QT_MOC_LITERAL(6, 76, 16), // "OnDeleteBtnClick"
QT_MOC_LITERAL(7, 93, 16), // "OnSearchBtnClick"
QT_MOC_LITERAL(8, 110, 14), // "OnMenuBtnClick"
QT_MOC_LITERAL(9, 125, 18), // "OnSearchBooknumAct"
QT_MOC_LITERAL(10, 144, 19), // "OnSearchBooknaemAct"
QT_MOC_LITERAL(11, 164, 19), // "OnSearchCatagoryAct"
QT_MOC_LITERAL(12, 184, 17) // "OnSearchAuthorAct"

    },
    "ViewInformation\0ViewDetail\0\0"
    "QTableWidgetItem*\0CheckBoxChange\0"
    "ChangeBtnState\0OnDeleteBtnClick\0"
    "OnSearchBtnClick\0OnMenuBtnClick\0"
    "OnSearchBooknumAct\0OnSearchBooknaemAct\0"
    "OnSearchCatagoryAct\0OnSearchAuthorAct"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ViewInformation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x08 /* Private */,
       4,    2,   67,    2, 0x08 /* Private */,
       5,    1,   72,    2, 0x08 /* Private */,
       6,    0,   75,    2, 0x08 /* Private */,
       7,    0,   76,    2, 0x08 /* Private */,
       8,    0,   77,    2, 0x08 /* Private */,
       9,    0,   78,    2, 0x08 /* Private */,
      10,    0,   79,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    0,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ViewInformation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ViewInformation *_t = static_cast<ViewInformation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ViewDetail((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->CheckBoxChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->ChangeBtnState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->OnDeleteBtnClick(); break;
        case 4: _t->OnSearchBtnClick(); break;
        case 5: _t->OnMenuBtnClick(); break;
        case 6: _t->OnSearchBooknumAct(); break;
        case 7: _t->OnSearchBooknaemAct(); break;
        case 8: _t->OnSearchCatagoryAct(); break;
        case 9: _t->OnSearchAuthorAct(); break;
        default: ;
        }
    }
}

const QMetaObject ViewInformation::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ViewInformation.data,
      qt_meta_data_ViewInformation,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ViewInformation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ViewInformation::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ViewInformation.stringdata0))
        return static_cast<void*>(const_cast< ViewInformation*>(this));
    return QWidget::qt_metacast(_clname);
}

int ViewInformation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
