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
  // Function:  设置配置文件
  // Remark: 	1.对于配置文件最好只读取,不修改
  //************************************************************************
  void setConfig(QSharedPointer<QSettings> & settings) { m_settings = settings; }


  //************************************************************************
  // Method:    initFaceAlgorithm
  // FullName:  IFaceAlgorithm::initFaceAlgorithm
  // Access:    virtual public 
  // Returns:   bool
  // Function:  初始化人脸识别算法
  // Remark: 	某些人脸识别算法需要进行配置,例如设置密钥等待,都可以在这里完成
  //************************************************************************
  virtual bool initFaceAlgorithm() = 0;


  //************************************************************************
  // Method:    setSourceFaceData
  // FullName:  IFaceAlgorithm::setSourceFaceData
  // Access:    virtual public 
  // Returns:   bool
  // Parameter: QVariant & data:待比对的人脸图像(源),可以是图片二进制数据,也可以是图片
  //            路径
  // Parameter: bool bDecode:是否需要解码:jpg,png,jpeg等压缩过的图片需要解码,直接
  //                         从视频流中截取的帧不需要解码
  // Parameter: QSize dstSize:待比对的人脸图像尺寸
  // Function:  设置待比对的人脸图像数据
  // Remark: 	1.使用本函数设置后,调用compareFace(QVariant & dstFaceData,QVariant&result) 
  //              函数时无需指定待比对的人脸,直接和通过本函数设置的带比对人脸进行比对
  //            2.如果data是未解码的图片(jpg,png,jpeg等压缩过的图片),则需要进行解码
  //************************************************************************
  virtual bool setSourceFaceData(const QVariant & data,QSize size, bool bDecode) = 0;
  /*增加opencv 的cv::Mat参数接口*/
  virtual bool setSourceFaceData(cv::Mat & imgMat) { return false; }

  //************************************************************************
  // Method:    getSourceFaceInfo
  // FullName:  IFaceAlgorithm::getSourceFaceInfo
  // Access:    virtual public 
  // Returns:   bool
  // Parameter: QVariant & info:获取图片信息(人脸位置等)
  // Parameter:  bool bSrc: true获取的是源图片,false获取目标图片
  // Function:  获取设置后的图片信息
  // Remark: 	1.当bSrc为true时,本函数需要在调用setSourceFaceData后调用
  //            2.当bSrc为false时,本函数需要在调用setDestFaceData后调用
  //************************************************************************
  virtual bool getFaceInfo(QVariant & info, bool bSrc) = 0;

  //************************************************************************
  // Method:    setDestFaceData
  // FullName:  IFaceAlgorithm::setDestFaceData
  // Access:    virtual public 
  // Returns:   bool
  // Parameter: QVariant & data:待比对的人脸图像(目标),可以是图片二进制数据,也可以是图片
  //            路径
  // Parameter: bool bDecode:是否需要解码:jpg,png,jpeg等压缩过的图片需要解码,直接
  //                         从视频流中截取的帧不需要解码
  // Parameter: QSize dstSize:待比对的人脸图像尺寸
  // Function:  设置待比对的目标图片
  // Remark: 	 
  //************************************************************************
  virtual bool setDestFaceData(QVariant & data, QSize size, bool dDecode) = 0;

  /*增加opencv 的cv::Mat参数接口*/
  virtual bool setDestFaceData(cv::Mat & imgMat) { return false; }

  //************************************************************************
  // Method:    compareFace
  // FullName:  IFaceAlgorithm::compareFace
  // Access:    virtual public 
  // Returns:   bool
  // Parameter: QVariant & result:比对结果(一般返回浮点值即可,也可以返回自定义结果)
  // Function:  源和目标人脸比对
  // Remark: 	
  //************************************************************************
  virtual bool compareFace(QVariant&result) = 0;


  //************************************************************************
  // Method:    clearSourceFaceData
  // FullName:  IFaceAlgorithm::clearSourceFaceData
  // Access:    virtual public 
  // Returns:   bool
  // Function:  清除setSourceFaceData设定的待比对人脸(源)
  // Remark: 	 
  //************************************************************************
  virtual bool clearSourceFaceData() = 0;
  virtual bool clearDestFaceData() = 0;
protected:
  QSharedPointer<QSettings> m_settings;
};


