#ifndef __UVC_SWAPPER_API__
#define __UVC_SWAPPER_API__


#include <stdint.h>
#include "UVCSwapper.h"

#define PLATFOAR_WINDOWS 1
#define PLATFOAR_LINUX 2

#if (defined(WIN32) || defined(_WIN32) || defined(WINCE))

#	define UVC_PALTFORM PLATFOAR_WINDOWS

#  ifdef UVC_SWAPPER_API
#    define UVC_SWAPPER_API __declspec(dllexport)
#  else
#    define UVC_SWAPPER_API __declspec(dllimport)
#  endif

#else

#	define UVC_PALTFORM PLATFOAR_LINUX
#	define UVC_SWAPPER_API

#endif




class  UVC_SWAPPER_API UVC_Swapper
{
public:
	UVC_Swapper();

	~UVC_Swapper();

public:

	//�������ܣ���ʼ��UVC
	//����������
	//[in] width: ͼ��Ŀ�;
	//[in] height: ͼ��ĸ�;
	//[in] imageFormat: ͼ���ʽ (OB_PIXEL_FORMAT_YUV422 ��OB_PIXEL_FORMAT_MJPEG)
	int UvcInit();

	//����ʼ��
	int UvcDeInit(int subdevice_index = 0);

	UVCDeviceInfo* getDeviceInfo();

	//�������ܣ�����UVC��
	//����������
	//[in] subdevice_index: ����Ҫ���ã�ʹ��Ĭ��ֵ��

	int UVCStreamStart(int width, int height, int imageFormat, int fps, int subdevice_index = 0);

	//ֹͣUVC��
	int UVCStreamStop(int subdevice_index = 0);

	//��ȡUVC����
	//����������
	//[in,out] pBuff:����uvc���ݵĻ�����,�ɵ����߷����ڴ�;
	//[out] nSize: uvc ���ݵ�size;
	//[out] imageType :ͼ���������ͣ�(OB_PIXEL_FORMAT_YUV422 ��OB_PIXEL_FORMAT_MJPEG);
	//[in] nTimeout:��ʱʱ��;
	int WaitUvcStream(uint8_t* pBuff, uint32_t &nSize, uint32_t &imageType, uint32_t nTimeout);

private:
	UVCSwapper* uvcSwapper;

};

#endif