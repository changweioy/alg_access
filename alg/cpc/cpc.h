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

class CPC_convertor{
    virtual convert_in(void* out, int len, IMP_CPC_Para_S* para)=0; 
}

class CPC_Configer{
    
    
}

//windows
class CPC{
public:
    start();
    stop();
    config();
private:
    
   

}
local_cpc_start();
local_cpc_config();
param_convert_json(char* json, IMP_CPC_Para_S* result);
params_convert_json