#include "SeetaFace2Demo.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMimeDatabase>
#include <QDebug>
#include <QPainter>
#include "cvmatandqimage.h"
#include <QTime>
SeetaFace2Demo::SeetaFace2Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.mainToolBar->addAction(ui.actionCameraCompare);
    ui.mainToolBar->addAction(ui.actionTwoPicCompare);
    ui.mainToolBar->insertSeparator(ui.actionTwoPicCompare);
    ui.textEdit->setReadOnly(true);
    ui.actionTwoPicCompare->setChecked(true);

    connect(ui.actionCameraCompare, SIGNAL(triggered()),this,SLOT(onActionCameraCompare()));
    connect(ui.actionTwoPicCompare, SIGNAL(triggered()), this, SLOT(onActionTwoPicCompare()));
    m_faceAlgo.initFaceAlgorithm();

}


void SeetaFace2Demo::onActionCameraCompare()
{
    ui.actionTwoPicCompare->setChecked(false);
    ui.label1->setAcceptDrops(false);
}


void SeetaFace2Demo::onActionTwoPicCompare()
{
    ui.actionCameraCompare->setChecked(false);
}


void SeetaFace2Demo::dragEnterEvent(QDragEnterEvent *event)
{
    QList<QUrl> urlst = event->mimeData()->urls();
    QMimeDatabase db;
    QMimeType fileType = db.mimeTypeForUrl(urlst.first());
    if (!fileType.isValid())
    {
        event->ignore();
        return;
    }

    if (!fileType.name().contains("image", Qt::CaseInsensitive))
    {
        event->ignore();
        return;
    }
    event->acceptProposedAction();
}


void SeetaFace2Demo::dropEvent(QDropEvent *event)
{

    QList<QUrl> urlst = event->mimeData()->urls();
    QString path = urlst.first().toLocalFile();
    QPoint mousePos = event->pos();
    QRect areaRect1 = ui.label1->geometry();
    QRect areaRect2 = ui.label2->geometry();
    if (ui.actionTwoPicCompare->isChecked())
    {
        if (areaRect1.contains(mousePos))
        {
            detectFaceAndDraw(path, ui.label1);
        }
        else if (areaRect2.contains(mousePos))
        {
            detectFaceAndDraw(path, ui.label2);
        }
    }

}

void SeetaFace2Demo::printInfo(QString & strInfo)
{
    QString strWithTime = QTime::currentTime().toString("hh:mm:ss.zzz  ");
    strWithTime += strInfo;
    strWithTime += "\n";
    ui.textEdit->append(strWithTime);
}

void SeetaFace2Demo::detectFaceAndDraw(QString & strPath, QLabel * label)
{
    SeetaImageData imagData;
    QVariant result;
    QImage qRectImage;
    cv::Mat m_mat = cv::imread(strPath.toLocal8Bit().data());
    if (label == ui.label1)
    {
        /*左侧QLabel*/
        if (!m_faceAlgo.setSourceFaceData(m_mat))
        {
            printInfo(QStringLiteral("左侧图像识别失败"));
            m_bLeftSuccess = false;
            return;
        }

        m_faceAlgo.getFaceInfo(result, true);
        QRect qRect = result.toRect();
        cv::Rect cvRect(qRect.x(), qRect.y(), qRect.width(), qRect.height());
        cv::rectangle(m_mat, cvRect, cv::Scalar(0, 0, 255), 2, 1);
        qRectImage = QtOcv::mat2Image_shared(m_mat, QImage::Format::Format_RGB888).rgbSwapped();
        m_bLeftSuccess = true;
        printInfo(QStringLiteral("左侧图像识别成功"));

        if (m_bRightSuccess)
        {
            m_faceAlgo.compareFace(result);
            printInfo(QStringLiteral("左右两张图片比对分数:%1").arg(result.toFloat()));
        }
    }
    else
    {
        /*右侧QLabel*/
        if (!m_faceAlgo.setDestFaceData(m_mat))
        {
            printInfo(QStringLiteral("右侧图像识别失败"));
            m_bRightSuccess = false;
            return;
        }

        m_faceAlgo.getFaceInfo(result, false);
        QRect qRect = result.toRect();
        cv::Rect cvRect(qRect.x(), qRect.y(), qRect.width(), qRect.height());
        cv::rectangle(m_mat, cvRect, cv::Scalar(0, 0, 255), 2, 1);
        qRectImage = QtOcv::mat2Image_shared(m_mat, QImage::Format::Format_RGB888).rgbSwapped();


        m_bRightSuccess = true;
        printInfo(QStringLiteral("右侧图像识别成功"));

        if (m_bLeftSuccess)
        {
            QVariant result;
            m_faceAlgo.compareFace(result);
            printInfo(QStringLiteral("左右两张图片比对分数:%1").arg(result.toFloat()));
        }
    }

    label->setPixmap(QPixmap::fromImage(qRectImage.scaled(label->size(), Qt::KeepAspectRatio)));
}


