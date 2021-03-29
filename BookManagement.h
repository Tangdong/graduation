#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "DTableWidget.h"
#include "DPageBtn.h"
#include "DLineEdit.h"
#include "DLabel.h"
#include "DLFUNC.h"
#include "DDialog.h"
#include "DialogWidget.h"

class BookManagement : public QWidget
{
    Q_OBJECT

public:
    BookManagement(QWidget *parent = NULL);
    ~BookManagement();
    void BookManageMsg(SocketMsg msg);
private slots:
    void OnOkBtnClienk();
private:
    void InitGui();
    QLabel* m_BookNum;
    QLabel* m_BookName;
    QLabel* m_Author;
    QLabel* m_Category;
    QLabel* m_Publisher;
    QLabel* m_Totalinventory;
    QLabel* m_Totalavailable;
    QLabel* m_Dealpeople;

    DLineEdit* m_BookNumLd;
    DLineEdit* m_BookNameLd;
    DLineEdit* m_AuthorLd;
    DLineEdit* m_CategoryLd;
    DLineEdit* m_PublisherLd;
    DLineEdit* m_TotalinventoryLd;
    DLineEdit* m_TotalavailableLd;
    DLineEdit* m_DealpeopleLd;

    DPageBtn *m_CancelBtn;
    DPageBtn *m_OkBtn;
};
