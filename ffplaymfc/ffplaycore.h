/* 
 * FFplay for MFC
 */

#include "ffplaymfc.h"
#include "ffplaymfcDlg.h"
#include "afxdialogex.h"


#include "config.h"
#include <inttypes.h>
#include <math.h>
#include <limits.h>
#include <signal.h>

extern "C"
{
#include "libavutil/avstring.h"
#include "libavutil/colorspace.h"
#include "libavutil/mathematics.h"
#include "libavutil/pixdesc.h"
#include "libavutil/imgutils.h"
#include "libavutil/dict.h"
#include "libavutil/parseutils.h"
#include "libavutil/samplefmt.h"
#include "libavutil/avassert.h"
#include "libavutil/time.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
#include "libavutil/opt.h"
#include "libavcodec/avfft.h"
#include "libswresample/swresample.h"
}

#if CONFIG_AVFILTER
# include "libavfilter/avcodec.h"
# include "libavfilter/avfilter.h"
# include "libavfilter/avfiltergraph.h"
# include "libavfilter/buffersink.h"
# include "libavfilter/buffersrc.h"
#endif

#include "SDL/SDL.h"
#include "SDL/SDL_thread.h"

#include "cmdutils.h"

#include <assert.h>





#define MAX_FRAME_NUM   20*30 //����20��30fps������
#define MAX_PACKET_NUM  60*30 //��������Ƶ��˽��

//URL����
#define MAX_URL_LENGTH 500


//��̬����ֻ�������������ļ����пɼ������ܱ������ļ������ã�Ҳ����˵�þ�̬����ֻ
//�����䶨���.cpp��.c�е��ã�������.cpp��.c�ļ��ĺ������ǲ��ܱ����õġ���
//��Ҫ��static void toggle_pause(VideoState *is)���з�װ



//Send Command "Pause"
void ffmfc_play_pause();

//Send Command "Step"
void ffmfc_seek_step();

//Send Command "FullScreen"
void ffmfc_play_fullcreen();

//Send Command "Seek"
void ffmfc_seek(int time);

//Send Command "AspectRatio"
void ffmfc_aspectratio(int num,int den);

//Send Command "WindowSize"
void ffmfc_size(int percentage);

//Send Command "Audio Display Mode"
void ffmfc_audio_display(int mode);


//Send Command "Quit"
void ffmfc_quit();


//Main function
int ffmfc_play(LPVOID lpParam);


//Reset
int ffmfc_reset_index();


//Seek Bar
void ffmfc_seek_bar(int pos);

//Stretch
void ffmfc_stretch(int stretch);