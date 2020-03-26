#pragma once
#include "IFaceAlgorithm.h"
#include "FaceDetector.h"
#include "Struct.h"
#include "FaceLandmarker.h"
#include "FaceRecognizer.h"
#include <QScopedPointer>
#include "opencv2/opencv.hpp"
#include <QScopedArrayPointer>
#pragma comment(lib,"SeetaFaceDetector.lib")
#pragma comment(lib,"SeetaFaceLandmarker.lib")
#pragma comment(lib,"SeetaFaceRecognizer.lib")
#pragma comment(lib,"opencv_world320.lib")
class seetaFace2: public IFaceAlgorithm
{
    Q_OBJECT
    typedef struct tagImageInfo
    {
        QImage      m_image;
        cv::Mat     m_mat;
        SeetaPointF m_faceMark[81];
        cv::Rect    m_faceRect;
        bool        m_bSetted = false;
        QScopedArrayPointer<float> m_features;
    }IMAGE_INFO;
public:
    virtual bool initFaceAlgorithm();
    virtual bool setSourceFaceData(const QVariant & data, QSize size, bool bDecode);
    virtual bool setSourceFaceData(cv::Mat & imgMat);
    virtual bool getFaceInfo(QVariant & info, bool bSrc);
    virtual bool setDestFaceData(QVariant & data, QSize size, bool dDecode);
    virtual bool setDestFaceData(cv::Mat & imgMat);
    virtual bool compareFace(QVariant&result);
    virtual bool clearSourceFaceData();
    virtual bool clearDestFaceData();
    seetaFace2();
    virtual ~seetaFace2();
protected:
    bool detectFace(IMAGE_INFO & ii);
private:
    QScopedPointer<seeta::FaceDetector>   m_faceDetector;
    QScopedPointer<seeta::FaceLandmarker> m_faceLandMarker;
    QScopedPointer<seeta::FaceRecognizer> m_faceRecognizer;
    IMAGE_INFO                            m_srcInfo;
    IMAGE_INFO                            m_dstInfo;
};

