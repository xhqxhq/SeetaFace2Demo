#pragma once
#include <QRect>
#include <QVector>
#include <QObject>
#include <QVariant>
#include <QSharedPointer>
#include <QSettings>
#include "opencv2/opencv.hpp"
#include "cvmatandqimage.h"
#pragma  comment(lib,"opencv_world320.lib")

typedef unsigned char BYTE;
class IFaceAlgorithm:public QObject
{
    Q_OBJECT
public:
  //************************************************************************
  // Method:    setConfig
  // FullName:  IFaceAlgorithm::setConfig
  // Access:    public 
  // Returns:   void
  // Parameter: QSharedPointer<QSettings> & settings
  // Function:  ���������ļ�
  // Remark: 	1.���������ļ����ֻ��ȡ,���޸�
  //************************************************************************
  void setConfig(QSharedPointer<QSettings> & settings) { m_settings = settings; }


  //************************************************************************
  // Method:    initFaceAlgorithm
  // FullName:  IFaceAlgorithm::initFaceAlgorithm
  // Access:    virtual public 
  // Returns:   bool
  // Function:  ��ʼ������ʶ���㷨
  // Remark: 	ĳЩ����ʶ���㷨��Ҫ��������,����������Կ�ȴ�,���������������
  //************************************************************************
  virtual bool initFaceAlgorithm() = 0;


  //************************************************************************
  // Method:    setSourceFaceData
  // FullName:  IFaceAlgorithm::setSourceFaceData
  // Access:    virtual public 
  // Returns:   bool
  // Parameter: QVariant & data:���ȶԵ�����ͼ��(Դ),������ͼƬ����������,Ҳ������ͼƬ
  //            ·��
  // Parameter: bool bDecode:�Ƿ���Ҫ����:jpg,png,jpeg��ѹ������ͼƬ��Ҫ����,ֱ��
  //                         ����Ƶ���н�ȡ��֡����Ҫ����
  // Parameter: QSize dstSize:���ȶԵ�����ͼ��ߴ�
  // Function:  ���ô��ȶԵ�����ͼ������
  // Remark: 	1.ʹ�ñ��������ú�,����compareFace(QVariant & dstFaceData,QVariant&result) 
  //              ����ʱ����ָ�����ȶԵ�����,ֱ�Ӻ�ͨ�����������õĴ��ȶ��������бȶ�
  //            2.���data��δ�����ͼƬ(jpg,png,jpeg��ѹ������ͼƬ),����Ҫ���н���
  //************************************************************************
  virtual bool setSourceFaceData(const QVariant & data,QSize size, bool bDecode) = 0;
  /*����opencv ��cv::Mat�����ӿ�*/
  virtual bool setSourceFaceData(cv::Mat & imgMat) { return false; }

  //************************************************************************
  // Method:    getSourceFaceInfo
  // FullName:  IFaceAlgorithm::getSourceFaceInfo
  // Access:    virtual public 
  // Returns:   bool
  // Parameter: QVariant & info:��ȡͼƬ��Ϣ(����λ�õ�)
  // Parameter:  bool bSrc: true��ȡ����ԴͼƬ,false��ȡĿ��ͼƬ
  // Function:  ��ȡ���ú��ͼƬ��Ϣ
  // Remark: 	1.��bSrcΪtrueʱ,��������Ҫ�ڵ���setSourceFaceData�����
  //            2.��bSrcΪfalseʱ,��������Ҫ�ڵ���setDestFaceData�����
  //************************************************************************
  virtual bool getFaceInfo(QVariant & info, bool bSrc) = 0;

  //************************************************************************
  // Method:    setDestFaceData
  // FullName:  IFaceAlgorithm::setDestFaceData
  // Access:    virtual public 
  // Returns:   bool
  // Parameter: QVariant & data:���ȶԵ�����ͼ��(Ŀ��),������ͼƬ����������,Ҳ������ͼƬ
  //            ·��
  // Parameter: bool bDecode:�Ƿ���Ҫ����:jpg,png,jpeg��ѹ������ͼƬ��Ҫ����,ֱ��
  //                         ����Ƶ���н�ȡ��֡����Ҫ����
  // Parameter: QSize dstSize:���ȶԵ�����ͼ��ߴ�
  // Function:  ���ô��ȶԵ�Ŀ��ͼƬ
  // Remark: 	 
  //************************************************************************
  virtual bool setDestFaceData(QVariant & data, QSize size, bool dDecode) = 0;

  /*����opencv ��cv::Mat�����ӿ�*/
  virtual bool setDestFaceData(cv::Mat & imgMat) { return false; }

  //************************************************************************
  // Method:    compareFace
  // FullName:  IFaceAlgorithm::compareFace
  // Access:    virtual public 
  // Returns:   bool
  // Parameter: QVariant & result:�ȶԽ��(һ�㷵�ظ���ֵ����,Ҳ���Է����Զ�����)
  // Function:  Դ��Ŀ�������ȶ�
  // Remark: 	
  //************************************************************************
  virtual bool compareFace(QVariant&result) = 0;


  //************************************************************************
  // Method:    clearSourceFaceData
  // FullName:  IFaceAlgorithm::clearSourceFaceData
  // Access:    virtual public 
  // Returns:   bool
  // Function:  ���setSourceFaceData�趨�Ĵ��ȶ�����(Դ)
  // Remark: 	 
  //************************************************************************
  virtual bool clearSourceFaceData() = 0;
  virtual bool clearDestFaceData() = 0;
protected:
  QSharedPointer<QSettings> m_settings;
};


