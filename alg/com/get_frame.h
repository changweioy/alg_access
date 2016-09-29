/**
 * Get video/audio frame on IPC
 * 
 * @file get_frame.h
 * @author Wei Chang (cw@impower-tech.com)
 * @date 2016-09
 * @copyright  Beijing Impower Technologies Co. Ltd. All rights reserved.
 */
#ifndef _IMPOWER_GET_FRAME_INCLUDED_
#define _IMPOWER_GET_FRAME_INCLUDED_


#ifdef __cplusplus
extern "C"{
#endif

typedef struct _VideoChannel{
    int id;
    int width;
    int height;
    int rate;
}VideoChannelInfo;

typedef struct _VideoChannels{
    int num;  //channels number
    VideoChannelInfo info[8]; //max channels num 8
}VideoChannels;

/**
 *params:
 *  chns- The Channels Info
 *return:
 *  0- success
 *  1- error
 */
int get_video_channels(VideoChannels* chns);

/**
 *params:
 *  data- The buffer to store the gray image
 *  width- The image width
 *  height- The image height
 *  channel_id- The Video CHannel ID of IPC
 *return:
 *  0- success
 *  1- error
 */
int get_video_frame_gray(char* data, int* width, int* height, int* timeref, int channel_id);

/**
 *params:
 *  y- The Y component of YUV data
 *  u- The V component of YUV data
 *  v- The V component of YUV data
 *  width- The image width
 *  height- The image height
 *  channel_id- The Video CHannel ID of IPC
 *return:
 *  0- success
 *  1- error
 */
int get_video_frame_yuv(char* y, char* u, char* v, int* width, int* height, int* timeref, int channel_id);

/**
 *params:
 *  pcm- The audio data(format pcm)
 *  rate- The rate of the pcm
 *  bits- The bits of the pcm
 *  channel- The channel num of the pcm
 *return:
 *  0- success
 *  1- error
 */
int get_audio_frame_pcm(char* pcm, int* rate, int* bits, int* channel);


#ifdef __cplusplus
}
#endif

#endif