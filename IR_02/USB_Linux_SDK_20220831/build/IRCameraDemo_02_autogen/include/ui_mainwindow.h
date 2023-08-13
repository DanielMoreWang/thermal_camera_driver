/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_uvcdevname;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_4;
    QComboBox *comboBox_capture_res;
    QPushButton *pushButton_link;
    QFrame *frame_7;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_distance_get;
    QFrame *frame_15;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *pushButton;
    QLabel *label_preview;
    QTextEdit *textEdit_log;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(927, 915);
        MainWindow->setMinimumSize(QSize(927, 0));
        MainWindow->setMaximumSize(QSize(927, 16777215));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setLayoutDirection(Qt::LeftToRight);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Plain);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 4, 2, 2);
        lineEdit_uvcdevname = new QLineEdit(frame);
        lineEdit_uvcdevname->setObjectName(QString::fromUtf8("lineEdit_uvcdevname"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_uvcdevname->sizePolicy().hasHeightForWidth());
        lineEdit_uvcdevname->setSizePolicy(sizePolicy1);
        lineEdit_uvcdevname->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(lineEdit_uvcdevname);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_2);
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 5, 2, 5);
        comboBox_capture_res = new QComboBox(frame_2);
        comboBox_capture_res->addItem(QString());
        comboBox_capture_res->addItem(QString());
        comboBox_capture_res->addItem(QString());
        comboBox_capture_res->addItem(QString());
        comboBox_capture_res->addItem(QString());
        comboBox_capture_res->setObjectName(QString::fromUtf8("comboBox_capture_res"));
        comboBox_capture_res->setEditable(true);

        verticalLayout_4->addWidget(comboBox_capture_res);


        verticalLayout->addWidget(frame_2);

        pushButton_link = new QPushButton(frame);
        pushButton_link->setObjectName(QString::fromUtf8("pushButton_link"));
        sizePolicy1.setHeightForWidth(pushButton_link->sizePolicy().hasHeightForWidth());
        pushButton_link->setSizePolicy(sizePolicy1);
        pushButton_link->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(pushButton_link);

        frame_7 = new QFrame(frame);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_7);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 2, -1, 2);
        pushButton_distance_get = new QPushButton(frame_7);
        pushButton_distance_get->setObjectName(QString::fromUtf8("pushButton_distance_get"));

        horizontalLayout_6->addWidget(pushButton_distance_get);


        verticalLayout->addWidget(frame_7);

        frame_15 = new QFrame(frame);
        frame_15->setObjectName(QString::fromUtf8("frame_15"));
        frame_15->setFrameShape(QFrame::StyledPanel);
        frame_15->setFrameShadow(QFrame::Raised);
        horizontalLayout_14 = new QHBoxLayout(frame_15);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(2, 2, 2, 2);
        pushButton = new QPushButton(frame_15);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_14->addWidget(pushButton);


        verticalLayout->addWidget(frame_15);


        horizontalLayout->addWidget(frame);

        label_preview = new QLabel(centralWidget);
        label_preview->setObjectName(QString::fromUtf8("label_preview"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_preview->sizePolicy().hasHeightForWidth());
        label_preview->setSizePolicy(sizePolicy2);
        label_preview->setMinimumSize(QSize(768, 576));
        label_preview->setMaximumSize(QSize(768, 576));

        horizontalLayout->addWidget(label_preview);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        textEdit_log = new QTextEdit(centralWidget);
        textEdit_log->setObjectName(QString::fromUtf8("textEdit_log"));
        textEdit_log->setLineWrapMode(QTextEdit::NoWrap);

        verticalLayout_3->addWidget(textEdit_log);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        comboBox_capture_res->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "IRCameraDemo", nullptr));
        lineEdit_uvcdevname->setText(QApplication::translate("MainWindow", "/dev/video0", nullptr));
        comboBox_capture_res->setItemText(0, QApplication::translate("MainWindow", "640x512", nullptr));
        comboBox_capture_res->setItemText(1, QApplication::translate("MainWindow", "1280x1024", nullptr));
        comboBox_capture_res->setItemText(2, QApplication::translate("MainWindow", "M Series", nullptr));
        comboBox_capture_res->setItemText(3, QApplication::translate("MainWindow", "384x288", nullptr));
        comboBox_capture_res->setItemText(4, QApplication::translate("MainWindow", "256x192", nullptr));

        pushButton_link->setText(QApplication::translate("MainWindow", "Link", nullptr));
        pushButton_distance_get->setText(QApplication::translate("MainWindow", "\346\213\215\347\205\247", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\345\275\225\345\203\217", nullptr));
        label_preview->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
