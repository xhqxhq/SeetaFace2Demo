/********************************************************************************
** Form generated from reading UI file 'SeetaFace2Demo.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEETAFACE2DEMO_H
#define UI_SEETAFACE2DEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SeetaFace2DemoClass
{
public:
    QAction *actionCameraCompare;
    QAction *actionTwoPicCompare;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label1;
    QVBoxLayout *verticalLayout;
    QLabel *label2;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SeetaFace2DemoClass)
    {
        if (SeetaFace2DemoClass->objectName().isEmpty())
            SeetaFace2DemoClass->setObjectName(QStringLiteral("SeetaFace2DemoClass"));
        SeetaFace2DemoClass->setWindowModality(Qt::ApplicationModal);
        SeetaFace2DemoClass->resize(1048, 724);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SeetaFace2DemoClass->sizePolicy().hasHeightForWidth());
        SeetaFace2DemoClass->setSizePolicy(sizePolicy);
        SeetaFace2DemoClass->setMinimumSize(QSize(1048, 724));
        SeetaFace2DemoClass->setMaximumSize(QSize(1048, 724));
        SeetaFace2DemoClass->setAcceptDrops(true);
        actionCameraCompare = new QAction(SeetaFace2DemoClass);
        actionCameraCompare->setObjectName(QStringLiteral("actionCameraCompare"));
        actionCameraCompare->setCheckable(true);
        actionTwoPicCompare = new QAction(SeetaFace2DemoClass);
        actionTwoPicCompare->setObjectName(QStringLiteral("actionTwoPicCompare"));
        actionTwoPicCompare->setCheckable(true);
        centralWidget = new QWidget(SeetaFace2DemoClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setAcceptDrops(true);
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label1 = new QLabel(centralWidget);
        label1->setObjectName(QStringLiteral("label1"));
        label1->setStyleSheet(QLatin1String("font-size:20px;\n"
"border:2px dashed black;\n"
"border-radius:10px;\n"
"background:rgba(0,255,0,100)"));
        label1->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label2 = new QLabel(centralWidget);
        label2->setObjectName(QStringLiteral("label2"));
        label2->setLayoutDirection(Qt::RightToLeft);
        label2->setStyleSheet(QLatin1String("font-size:20px;\n"
"border:2px dashed black;\n"
"border-radius:10px;\n"
"background:rgba(0,255,0,100)"));
        label2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label2);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);

        verticalLayout->setStretch(0, 7);
        verticalLayout->setStretch(1, 3);

        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 6);
        horizontalLayout->setStretch(1, 4);

        verticalLayout_2->addLayout(horizontalLayout);

        SeetaFace2DemoClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SeetaFace2DemoClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1048, 23));
        SeetaFace2DemoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SeetaFace2DemoClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SeetaFace2DemoClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SeetaFace2DemoClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SeetaFace2DemoClass->setStatusBar(statusBar);

        retranslateUi(SeetaFace2DemoClass);

        QMetaObject::connectSlotsByName(SeetaFace2DemoClass);
    } // setupUi

    void retranslateUi(QMainWindow *SeetaFace2DemoClass)
    {
        SeetaFace2DemoClass->setWindowTitle(QApplication::translate("SeetaFace2DemoClass", "SeetaFace2Demo", Q_NULLPTR));
        actionCameraCompare->setText(QApplication::translate("SeetaFace2DemoClass", "\346\221\204\345\203\217\345\244\264\345\256\236\346\227\266\346\257\224\345\257\271\346\250\241\345\274\217", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCameraCompare->setToolTip(QApplication::translate("SeetaFace2DemoClass", "\346\272\220\345\233\276\347\211\207\345\222\214\346\221\204\345\203\217\345\244\264\351\207\207\351\233\206\345\210\260\347\232\204\350\247\206\351\242\221\345\270\247\350\277\233\350\241\214\346\257\224\345\257\271", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionTwoPicCompare->setText(QApplication::translate("SeetaFace2DemoClass", "\344\270\244\345\274\240\345\233\276\347\211\207\346\257\224\345\257\271\346\250\241\345\274\217", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionTwoPicCompare->setToolTip(QApplication::translate("SeetaFace2DemoClass", "\344\273\216\346\234\254\345\234\260\346\226\207\344\273\266\345\244\271\344\270\255\345\212\240\350\275\275\344\270\244\345\274\240\345\233\276\347\211\207\350\277\233\350\241\214\346\257\224\345\257\271", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label1->setText(QApplication::translate("SeetaFace2DemoClass", "\346\213\226\346\213\275\345\233\276\347\211\207\345\210\260\350\277\231\351\207\214", Q_NULLPTR));
        label2->setText(QApplication::translate("SeetaFace2DemoClass", "\346\213\226\346\213\275\345\233\276\347\211\207\345\210\260\350\277\231\351\207\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SeetaFace2DemoClass: public Ui_SeetaFace2DemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEETAFACE2DEMO_H
