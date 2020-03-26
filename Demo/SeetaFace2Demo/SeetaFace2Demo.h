#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SeetaFace2Demo.h"
#include "seetaFace2.h"

class SeetaFace2Demo : public QMainWindow
{
    Q_OBJECT

public:
    SeetaFace2Demo(QWidget *parent = Q_NULLPTR);
public slots:
    void onActionCameraCompare();
    void onActionTwoPicCompare();
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void printInfo(QString & strInfo);
    void detectFaceAndDraw(QString & strPath,QLabel * label);
private:
    Ui::SeetaFace2DemoClass ui;
    seetaFace2  m_faceAlgo;
    bool        m_bLeftSuccess = false;
    bool        m_bRightSuccess = false;
};
