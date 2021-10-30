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





#define MAX_FRAME_NUM   20*30 //保存20秒30fps的数据
#define MAX_PACKET_NUM  60*30 //包含音视频和私有

//URL长度
#define MAX_URL_LENGTH 500


//静态函数只能在声明它的文件当中可见，不能被其他文件所调用，也就是说该静态函数只
//能在其定义的.cpp或.c中调用，在其它.cpp或.c文件的函数里是不能被调用的。”
//需要对static void toggle_pause(VideoState *is)进行封装



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