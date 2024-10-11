#ifndef __UVC_SWAPPER_H__
#define __UVC_SWAPPER_H__

#include <stdint.h>

typedef struct UVCDeviceInfo
{
	int devicePid;
	int deviceVid;
} UVCDeviceInfo;



class  UVCSwapper
{
public:
	UVCSwapper();
	virtual ~UVCSwapper();

public:

	//�������ܣ���ʼ��UVC
	//����������
	//[in] width: ͼ��Ŀ�;
	//[in] height: ͼ��ĸ�;
	//[in] imageFormat: ͼ���ʽ (OB_PIXEL_FORMAT_YUV422 ��OB_PIXEL_FORMAT_MJPEG)
	virtual int UvcInit();

	virtual UVCDeviceInfo* getDeviceInfo();

	//����ʼ��
	virtual int UvcDeInit(int subdevice_index = 0);

	//�������ܣ�����UVC��
	//����������
	//[in] subdevice_index: ����Ҫ���ã�ʹ��Ĭ��ֵ��
	virtual int UVCStreamStart(int width, int height, int imageFormat, int fps, int subdevice_index = 0);

	//ֹͣUVC��
	virtual int UVCStreamStop(int subdevice_index = 0);

	//��ȡUVC����
	//����������
	//[in,out] pBuff:����uvc���ݵĻ�����,�ɵ����߷����ڴ�;
	//[out] nSize: uvc ���ݵ�size;
	//[out] imageType :ͼ���������ͣ�(OB_PIXEL_FORMAT_YUV422 ��OB_PIXEL_FORMAT_MJPEG);
	//[in] nTimeout:��ʱʱ��;
	virtual int WaitUvcStream(uint8_t* pBuff, uint32_t &nSize, uint32_t &imageType, uint32_t nTimeout);

protected:
	UVCDeviceInfo uvcDeviceInfo;

};

#endif