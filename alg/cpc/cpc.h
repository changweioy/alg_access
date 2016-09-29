/**
 * The Algorithm CPC ACCESS
 * 
 * @file cpc.h
 * @author Wei Chang (cw@impower-tech.com)
 * @date 2016-09
 * @copyright  Beijing Impower Technologies Co. Ltd. All rights reserved.
 */
 
typedef void (* FUNC_GET_ALG_RESULT)(char* alg_result, int len, void* user_data);

int cpc_start(FUNC_GET_ALG_RESULT func);
int cpc_stop();
int cpc_set_params(void* params, int len);