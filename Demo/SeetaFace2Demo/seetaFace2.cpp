#include "seetaFace2.h"
#include <QByteArray>


bool seetaFace2::initFaceAlgorithm()
{
    seeta::ModelSetting::Device device = seeta::ModelSetting::GPU;
    seeta::ModelSetting faceDetectorModel("model/fd_2_00.dat", device, 0);
    /*����ֻʹ��5�㶨λģ��,81�㲻֧�������ȶ�*/
    seeta::ModelSetting faceLandMarkModel("model/pd_2_00_pts5.dat", device, 0);
    seeta::ModelSetting faceRecognizModel("model/fr_2_10.dat", device, 0);

    try
    {
        /*�������๹��ʱ����Ҳ���ģ���ļ������쳣*/
        m_faceDetector.reset(new seeta::FaceDetector(faceDetectorModel));
        m_faceLandMarker.reset(new seeta::FaceLandmarker(faceLandMarkModel));
        m_faceRecognizer.reset(new seeta::FaceRecognizer(faceRecognizModel));
    }

    catch (...)
    {
        return false;
    }
 

    m_faceDetector->set(seeta::FaceDetector::PROPERTY_MIN_FACE_SIZE, 80);
    int nFeatureSize = m_faceRecognizer->GetExtractFeatureSize();
    m_srcInfo.m_features.reset(new float[nFeatureSize]);
    m_dstInfo.m_features.reset(new float[nFeatureSize]);

    return true;
}

bool seetaFace2::setSourceFaceData(const QVariant & data, QSize size, bool bDecode)
{
    if (!data.canConvert<QByteArray>())
    {
        /*�����֧��ͨ��QByteArrayװ���ͼ������*/
        return false;
    }

    QByteArray buff = data.value<QByteArray>();
    cv::Mat tmp(size.height(), size.width(), CV_8UC3);
    m_srcInfo.m_mat = tmp;

    return detectFace(m_srcInfo);
}



bool seetaFace2::setSourceFaceData(cv::Mat & imgMat)
{
    m_srcInfo.m_mat = imgMat;
    return detectFace(m_srcInfo);
}

bool seetaFace2::getFaceInfo(QVariant & info, bool bSrc)
{
    /*����ֻ������������λ��,���������Ҫ������Ϣ��������չ*/
    QRect faceRect;
    if (bSrc)
    {
        if (!m_srcInfo.m_bSetted)
        {
            return false;
        }

        faceRect = QRect(m_srcInfo.m_faceRect.x, m_srcInfo.m_faceRect.y,
                         m_srcInfo.m_faceRect.width, m_srcInfo.m_faceRect.height);
    }
    else
    {
        if (!m_dstInfo.m_bSetted)
        {
            return false;
        }
        faceRect = QRect(m_dstInfo.m_faceRect.x, m_dstInfo.m_faceRect.y,
                         m_dstInfo.m_faceRect.width, m_dstInfo.m_faceRect.height);
    }

    info.setValue<QRect>(faceRect);
    return true;
}



bool seetaFace2::setDestFaceData(QVariant & data, QSize size, bool dDecode)
{
    if (!data.canConvert<QByteArray>())
    {
        /*�����֧��ͨ��QByteArrayװ���ͼ������*/
        return false;
    }

    QByteArray buff = data.value<QByteArray>();
    cv::Mat tmp(size.height(), size.width(), CV_8UC3);
    m_dstInfo.m_mat = tmp;
    return detectFace(m_srcInfo);
}


bool seetaFace2::setDestFaceData(cv::Mat & imgMat)
{
    m_dstInfo.m_mat = imgMat;
    return detectFace(m_dstInfo);
}

bool seetaFace2::compareFace(QVariant&result)
{
    if (!m_srcInfo.m_bSetted || !m_dstInfo.m_bSetted)
    {
        return false;
    }

    float fResult = m_faceRecognizer->CalculateSimilarity(m_srcInfo.m_features.data(), m_dstInfo.m_features.data());
    result.setValue(fResult);
    return true;
}


bool seetaFace2::clearSourceFaceData()
{
    /*ֻ���ñ�Ǽ���*/
    m_srcInfo.m_bSetted = false;
    return true;
}

bool seetaFace2::clearDestFaceData()
{
    /*ֻ���ñ�Ǽ���*/
    m_dstInfo.m_bSetted = false;
    return true;
}

//************************************************************************
// Method:    detectFace
// FullName:  seetaFace2::detectFace
// Access:    protected 
// Returns:   bool
// Parameter: IMAGE_INFO & ii
// Function:  ���ͼƬ�е�����λ�ò���ȡ����ֵ
// Remark: 	 
//************************************************************************
bool seetaFace2::detectFace(IMAGE_INFO & ii)
{
    ii.m_bSetted = false;
    if (ii.m_mat.empty())
    {
        return false;
    }

    SeetaImageData imagData;
    imagData.height = ii.m_mat.rows;
    imagData.width = ii.m_mat.cols;
    imagData.channels = ii.m_mat.channels();
    imagData.data = ii.m_mat.data;
    SeetaFaceInfoArray faceInfo = m_faceDetector->detect(imagData);

    if (faceInfo.size <= 0)
    {
        /*ͼƬ��δ��⵽����*/
        return false;
    }

    /*�����ͼ���м�⵽�������,��ֻʹ�������ߴ�(���)��������*/
    int nMaxWidthIndex = 0;
    for (int iIndex = 0; iIndex < faceInfo.size; iIndex++)
    {
        if (faceInfo.data[nMaxWidthIndex].pos.width < faceInfo.data[iIndex].pos.width)
        {
            nMaxWidthIndex = iIndex;
        }
    }

    /*��¼����λ��*/
    SeetaRect seetaRect = faceInfo.data[nMaxWidthIndex].pos;
    ii.m_faceRect.x = seetaRect.x;
    ii.m_faceRect.y = seetaRect.y;
    ii.m_faceRect.width = seetaRect.width;
    ii.m_faceRect.height = seetaRect.width;

    /*��ȡ����������*/
    m_faceLandMarker->mark(imagData, faceInfo.data[nMaxWidthIndex].pos, ii.m_faceMark);
    int nLenOfMark = m_faceLandMarker->number();
    if (nLenOfMark < 5)
    {
        /*seetaface2��Ȼ��81��������λ,���ǲ������������Ƚ�,����ֻ��ʹ��5�㶨λ,��λ����5������Ϊʶ��ʧ��*/
        return false;
    }

    /*��ȡ��������ֵ*/
    bool bRet = m_faceRecognizer->Extract(imagData, ii.m_faceMark, ii.m_features.data());
    if (!bRet)
    {
        return false;
    }
    ii.m_bSetted = true;
    return true;
}


seetaFace2::seetaFace2()
{
}


seetaFace2::~seetaFace2()
{
}
