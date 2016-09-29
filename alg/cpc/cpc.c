/**
 * The Algorithm CPC ACCESS
 * 
 * @file cpc.h
 * @author Wei Chang (cw@impower-tech.com)
 * @date 2016-09
 * @copyright  Beijing Impower Technologies Co. Ltd. All rights reserved.
 */
#include <stdlib.h>
#include <stdio.h>

#include "get_frame.h"

#include "imp_algo_type.h"
#include "imp_cpc_para.h"
#include "imp_cpc_api.h"

void _cpc_default_config(IMP_CPC_Para_S *para){
    printf("_cpc_default_config enter\n");
    #define UNUSED_X 5
    #define UNUSED_Y (ALGO_HEIGHT/5)
    para->stROIRect.s16X1 = UNUSED_X;
    para->stROIRect.s16Y1 = UNUSED_Y;
    para->stROIRect.s16X2 = ALGO_WIDTH - UNUSED_X;
    para->stROIRect.s16Y2 = ALGO_HEIGHT - UNUSED_Y;
    para->stDirection.stPe.s16X = 0;
    para->stDirection.stPe.s16Y = 10;
    para->stDirection.stPs.s16X = 0;
    para->stDirection.stPs.s16Y = 100;
    para->enSensity = IMP_CPC_SENS_NORMAL;

    /* advanced para */
    para->s32Valid = 1;
    para->stCPCAdvPara.s32ScanStep = -1;
    para->stCPCAdvPara.s32StartScale = -1;
    para->stCPCAdvPara.s32ScaleNum = -1;
    para->stCPCAdvPara.s32UsedClsN = -1;
    para->stCPCAdvPara.fScaleChange = -1;
    para->stCPCAdvPara.s32MinTrackLen = -1;
    para->stCPCAdvPara.s32MinDis2RuleLine = -1;
    para->stCPCAdvPara.s32Reserved = -1;
    return;
}

void* cpc_loop(void* user_data)
{
    int i = 0;
    int ret;
    int alg_width;
    int alg_height;
    IMP_HANDLE alg_handle;
    IMP_CPC_Para_S alg_param;
    IMP_CPC_Result_S alg_result;
    IMAGE3_S alg_image;
    
    int channel_id;
    VideoChannelInfo alg_use_channel;
    VideoChannels chns;
    
    if(get_video_channels(&chns)){
        perror("get_video_channels error!");
        return NULL;
    }
    alg_use_channel.width = 0;
    for(i = 0; i <= chns.num; i++){
        printf("id:%d, w:%d, h:%d\n",
            chns.info[i].id,
            chns.info[i].width,
            chns.info[i].height);
            
        if(alg_use_channel.width > chns.info[i].width
            || alg_use_channel.width == 0){
            alg_use_channel.id = chns.info[i].id;
            alg_use_channel.width = chns.info[i].width;
            alg_use_channel.height = chns.info[i].height;
        }
    }
    channel_id = alg_use_channel.id;
    alg_width = alg_use_channel.width;
    alg_height = alg_use_channel.alg_height;
    printf("alg use channel id:%d, w:%d, h:%d\n",
        channel_id,
        alg_width,
        alg_height);
    
    memset(&alg_image, 0, sizeof(alg_image));
    alg_image.s32W = alg_width;
    alg_image.s32H = alg_height;
    alg_image.pu8D1 = (IMP_U8*)malloc(alg_image.s32W * alg_image.s32H);
    if(NULL == alg_image.pu8D1){
        perror("malloc alg image error!");
        return NULL;
    }
    
    if(IMP_FAILURE == IMP_CPC_Create(alg_width, alg_height, &alg_handle)){
        perror("IMP_CPC_Create error!");
        return NULL;
    }
    
    _cpc_default_config(&alg_param);
    if(IMP_FAILURE == IMP_CPC_Config(alg_handle, &alg_param)){
        perror("IMP_CPC_Config error!");
        return NULL;
    }

    while(1){
        if(get_video_frame_gray(
                (char*)alg_image.pu8D1, 
                &alg_image.s32W, 
                &alg_image.s32H,
                &alg_image.u32Time,
                channel_id)){
            perror("get_video_frame_gray error, continue.");
            continue;
        }
        
        IMP_CPC_Process(alg_handle, &alg_image, &alg_result);
        
        printf("cpc detect num:%d\n", alg_result.u32TgtNum);
    } //while(1)
      
    IMP_CPC_Release(alg_handle);
    free(alg_image.pu8D1);
    
    return NULL;
}