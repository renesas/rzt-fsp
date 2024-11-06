/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <string.h>
#include "r_rsip_wrapper.h"
#include "r_rsip_primitive.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/*
 * Maximum retry count of RSA key generation derived from FIPS186-4 B.3.3. 4.7 and 5.8 (1024, 2048, 3072)
 * Maximum retry count of RSA key generation derived from FIPS186-5 A.1.3. 4.7 and 5.8 (4096)
 */
#define RSIP_PRV_MAX_RETRY_COUNT_KEY_GEN_RSA_1024    (2 * (5 * 1024 / 2))
#define RSIP_PRV_MAX_RETRY_COUNT_KEY_GEN_RSA_2048    (2 * (5 * 2048 / 2))
#define RSIP_PRV_MAX_RETRY_COUNT_KEY_GEN_RSA_3072    (2 * (5 * 3072 / 2))
#define RSIP_PRV_MAX_RETRY_COUNT_KEY_GEN_RSA_4096    (5 * 4096 + 10 * 4096)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_cmd
{
    CMD_AES_MODE_ECB_ENCRYPT = 0,
    CMD_AES_MODE_ECB_DECRYPT = 1,
    CMD_AES_MODE_CBC_ENCRYPT = 2,
    CMD_AES_MODE_CBC_DECRYPT = 3,
    CMD_AES_MODE_CTR_CRYPT   = 4,

    CMD_AES_IV_TYPE_PLAIN   = 0,
    CMD_AES_IV_TYPE_WRAPPED = 1,

    CMD_AES_CMAC_GENERATE_WITHOUT_REMAINDER = 0,
    CMD_AES_CMAC_GENERATE_WITH_REMAINDER    = 1,
    CMD_AES_CMAC_VERIFY_WITHOUT_REMAINDER   = 2,
    CMD_AES_CMAC_VERIFY_WITH_REMAINDER      = 3,

    CMD_ECC_TYPE_NIST      = 0,
    CMD_ECC_TYPE_BRAINPOOL = 1,

    CMD_ECC_KEY_LENGTH_256 = 0,

    CMD_ECDH_PUBKEY_TYPE_PLAIN   = 0,
    CMD_ECDH_PUBKEY_TYPE_WRAPPED = 1,

    CMD_HMAC_HASH_TYPE_SHA1   = 0,
    CMD_HMAC_HASH_TYPE_SHA224 = 1,
    CMD_HMAC_HASH_TYPE_SHA256 = 2,

    CMD_PKI_KEY_TYPE_RSA_2048      = 0,
    CMD_PKI_KEY_TYPE_ECC_SECP256R1 = 3,

    CMD_KDF_HASH_TYPE_SHA256 = 0,

    CMD_KDF_OUTDATA_TYPE_AES128      = 0,
    CMD_KDF_OUTDATA_TYPE_AES256      = 1,
    CMD_KDF_OUTDATA_TYPE_IV_AES      = 2,
    CMD_KDF_OUTDATA_TYPE_IV_TLS12    = 3,
    CMD_KDF_OUTDATA_TYPE_HMAC_SHA1   = 5,
    CMD_KDF_OUTDATA_TYPE_HMAC_SHA256 = 6,

    CMD_KDF_TLS12_PRF_VERIFY_DATA_CLIENT = 0,
    CMD_KDF_TLS12_PRF_VERIFY_DATA_SERVER = 1,

    CMD_OTF_CHANNEL_0 = 0,
    CMD_OTF_CHANNEL_1 = 1,

    CMD_AUTH_HASH_TYPE_JTAG_DEBUG_LEVEL1 = 0,
    CMD_AUTH_HASH_TYPE_JTAG_DEBUG_LEVEL2 = 1,
    CMD_AUTH_HASH_TYPE_SCI_USB_BOOT      = 2,
} cmd_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

static const uint32_t gs_cmd[7] =
{
    BSWAP_32BIG_C(0U), BSWAP_32BIG_C(1U), BSWAP_32BIG_C(2U), BSWAP_32BIG_C(3U), BSWAP_32BIG_C(4U), BSWAP_32BIG_C(5U),
    BSWAP_32BIG_C(6U)
};

static const uint32_t gs_cmd_no_swap[4] =
{
    0, 1, 2, 3
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

rsip_ret_t r_rsip_wrapper_pf4_secp256r1 (uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[])
{
    return r_rsip_pf4(&gs_cmd[CMD_ECC_TYPE_NIST],
                      &gs_cmd[CMD_ECC_KEY_LENGTH_256],
                      OutData_PubKeyIndex,
                      OutData_PrivKeyIndex);
}

rsip_ret_t r_rsip_wrapper_pf4_brainpoolp256r1 (uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[])
{
    return r_rsip_pf4(&gs_cmd[CMD_ECC_TYPE_BRAINPOOL],
                      &gs_cmd[CMD_ECC_KEY_LENGTH_256],
                      OutData_PubKeyIndex,
                      OutData_PrivKeyIndex);
}

rsip_ret_t r_rsip_wrapper_p2a (uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[])
{
    return r_rsip_p2a(RSIP_PRV_MAX_RETRY_COUNT_KEY_GEN_RSA_1024, OutData_PubKeyIndex, OutData_PrivKeyIndex);
}

rsip_ret_t r_rsip_wrapper_p2b (uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[])
{
    return r_rsip_p2b(RSIP_PRV_MAX_RETRY_COUNT_KEY_GEN_RSA_2048, OutData_PubKeyIndex, OutData_PrivKeyIndex);
}

rsip_ret_t r_rsip_wrapper_p3a (uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[])
{
    return r_rsip_p3a(RSIP_PRV_MAX_RETRY_COUNT_KEY_GEN_RSA_3072, OutData_PubKeyIndex, OutData_PrivKeyIndex);
}

rsip_ret_t r_rsip_wrapper_p3b (uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[])
{
    return r_rsip_p3b(RSIP_PRV_MAX_RETRY_COUNT_KEY_GEN_RSA_4096, OutData_PubKeyIndex, OutData_PrivKeyIndex);
}

rsip_ret_t r_rsip_wrapper_p2c_secp256r1 (uint32_t const InData_IV[],
                                         uint32_t const InData_InstData[],
                                         uint32_t       OutData_KeyIndex[])
{
    return r_rsip_p2c(&gs_cmd[CMD_ECC_TYPE_NIST],
                      &gs_cmd[CMD_ECC_KEY_LENGTH_256],
                      InData_IV,
                      InData_InstData,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p1e_secp256r1 (uint32_t const InData_IV[],
                                         uint32_t const InData_InstData[],
                                         uint32_t       OutData_KeyIndex[])
{
    return r_rsip_p1e(&gs_cmd[CMD_ECC_TYPE_NIST],
                      &gs_cmd[CMD_ECC_KEY_LENGTH_256],
                      InData_IV,
                      InData_InstData,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p2c_brainpoolp256r1 (uint32_t const InData_IV[],
                                               uint32_t const InData_InstData[],
                                               uint32_t       OutData_KeyIndex[])
{
    return r_rsip_p2c(&gs_cmd[CMD_ECC_TYPE_BRAINPOOL],
                      &gs_cmd[CMD_ECC_KEY_LENGTH_256],
                      InData_IV,
                      InData_InstData,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p1e_brainpoolp256r1 (uint32_t const InData_IV[],
                                               uint32_t const InData_InstData[],
                                               uint32_t       OutData_KeyIndex[])
{
    return r_rsip_p1e(&gs_cmd[CMD_ECC_TYPE_BRAINPOOL],
                      &gs_cmd[CMD_ECC_KEY_LENGTH_256],
                      InData_IV,
                      InData_InstData,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p0f_hmac_sha1 (const uint32_t InData_IV[],
                                         const uint32_t InData_InstData[],
                                         uint32_t       OutData_KeyIndex[])
{
    return r_rsip_p0f(&gs_cmd[CMD_HMAC_HASH_TYPE_SHA1], InData_IV, InData_InstData, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p0f_hmac_sha224 (const uint32_t InData_IV[],
                                           const uint32_t InData_InstData[],
                                           uint32_t       OutData_KeyIndex[])
{
    return r_rsip_p0f(&gs_cmd[CMD_HMAC_HASH_TYPE_SHA224], InData_IV, InData_InstData, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p0f_hmac_sha256 (const uint32_t InData_IV[],
                                           const uint32_t InData_InstData[],
                                           uint32_t       OutData_KeyIndex[])
{
    return r_rsip_p0f(&gs_cmd[CMD_HMAC_HASH_TYPE_SHA256], InData_IV, InData_InstData, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p48i_ecb_enc (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p48i(&gs_cmd[CMD_AES_MODE_ECB_ENCRYPT], InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p48i_ecb_dec (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p48i(&gs_cmd[CMD_AES_MODE_ECB_DECRYPT], InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p48i_cbc_enc (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p48i(&gs_cmd[CMD_AES_MODE_CBC_ENCRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p48i_cbc_dec (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p48i(&gs_cmd[CMD_AES_MODE_CBC_DECRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p48i_cbc_enc_wrapped_iv (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p48i(&gs_cmd[CMD_AES_MODE_CBC_ENCRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p48i_cbc_dec_wrapped_iv (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p48i(&gs_cmd[CMD_AES_MODE_CBC_DECRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p48i_ctr (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p48i(&gs_cmd[CMD_AES_MODE_CTR_CRYPT], InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_ecb_enc (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p50i(&gs_cmd[CMD_AES_MODE_ECB_ENCRYPT], InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_ecb_dec (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p50i(&gs_cmd[CMD_AES_MODE_ECB_DECRYPT], InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_cbc_enc (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p50i(&gs_cmd[CMD_AES_MODE_CBC_ENCRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_cbc_dec (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p50i(&gs_cmd[CMD_AES_MODE_CBC_DECRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_cbc_enc_wrapped_iv (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p50i(&gs_cmd[CMD_AES_MODE_CBC_ENCRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_cbc_dec_wrapped_iv (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p50i(&gs_cmd[CMD_AES_MODE_CBC_DECRYPT], InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_ctr (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    return r_rsip_p50i(&gs_cmd[CMD_AES_MODE_CTR_CRYPT], InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p29i_plain_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p29i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p29i_wrapped_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p29i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p32i_plain_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p32i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p32i_wrapped_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p32i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p34i_plain_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p34i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p34i_wrapped_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p34i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p36i_plain_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p36i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_PLAIN], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p36i_wrapped_iv (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    return r_rsip_p36i(InData_KeyIndex, &gs_cmd[CMD_AES_IV_TYPE_WRAPPED], InData_IV);
}

rsip_ret_t r_rsip_wrapper_p41f_gen (const uint32_t InData_Text[], uint32_t OutData_DataT[], const uint32_t all_msg_len)
{
    cmd_t cmd = ((0 == (all_msg_len % 16)) && (0 != all_msg_len)) ?
                CMD_AES_CMAC_GENERATE_WITHOUT_REMAINDER : CMD_AES_CMAC_GENERATE_WITH_REMAINDER;

    return r_rsip_p41f(&gs_cmd_no_swap[cmd], InData_Text, NULL, NULL, OutData_DataT);
}

rsip_ret_t r_rsip_wrapper_p44f_gen (const uint32_t InData_Text[], uint32_t OutData_DataT[], const uint32_t all_msg_len)
{
    cmd_t cmd = ((0 == (all_msg_len % 16)) && (0 != all_msg_len)) ?
                CMD_AES_CMAC_GENERATE_WITHOUT_REMAINDER : CMD_AES_CMAC_GENERATE_WITH_REMAINDER;

    return r_rsip_p44f(&gs_cmd_no_swap[cmd], InData_Text, NULL, NULL, OutData_DataT);
}

rsip_ret_t r_rsip_wrapper_p41f_veri (const uint32_t InData_Text[],
                                     const uint32_t InData_DataT[],
                                     const uint32_t InData_DataTLen[],
                                     const uint32_t all_msg_len)
{
    cmd_t cmd = ((0 == (all_msg_len % 16)) && (0 != all_msg_len)) ?
                CMD_AES_CMAC_VERIFY_WITHOUT_REMAINDER : CMD_AES_CMAC_VERIFY_WITH_REMAINDER;

    return r_rsip_p41f(&gs_cmd_no_swap[cmd], InData_Text, InData_DataT, InData_DataTLen, NULL);
}

rsip_ret_t r_rsip_wrapper_p44f_veri (const uint32_t InData_Text[],
                                     const uint32_t InData_DataT[],
                                     const uint32_t InData_DataTLen[],
                                     const uint32_t all_msg_len)
{
    cmd_t cmd = ((0 == (all_msg_len % 16)) && (0 != all_msg_len)) ?
                CMD_AES_CMAC_VERIFY_WITHOUT_REMAINDER : CMD_AES_CMAC_VERIFY_WITH_REMAINDER;

    return r_rsip_p44f(&gs_cmd_no_swap[cmd], InData_Text, InData_DataT, InData_DataTLen, NULL);
}

rsip_ret_t r_rsip_wrapper_pf0_secp256r1 (const uint32_t InData_KeyIndex[],
                                         const uint32_t InData_MsgDgst[],
                                         uint32_t       OutData_Signature[])
{
    return r_rsip_pf0(&gs_cmd[CMD_ECC_TYPE_NIST],
                      &gs_cmd[CMD_ECC_KEY_LENGTH_256],
                      InData_KeyIndex,
                      InData_MsgDgst,
                      OutData_Signature);
}

rsip_ret_t r_rsip_wrapper_pf1_secp256r1 (const uint32_t InData_KeyIndex[],
                                         const uint32_t InData_MsgDgst[],
                                         const uint32_t InData_Signature[])
{
    return r_rsip_pf1(&gs_cmd[CMD_ECC_TYPE_NIST],
                      &gs_cmd[CMD_ECC_KEY_LENGTH_256],
                      InData_KeyIndex,
                      InData_MsgDgst,
                      InData_Signature);
}

rsip_ret_t r_rsip_wrapper_pf0_brainpoolp256r1 (const uint32_t InData_KeyIndex[],
                                               const uint32_t InData_MsgDgst[],
                                               uint32_t       OutData_Signature[])
{
    return r_rsip_pf0(&gs_cmd[CMD_ECC_TYPE_BRAINPOOL],
                      &gs_cmd[CMD_ECC_KEY_LENGTH_256],
                      InData_KeyIndex,
                      InData_MsgDgst,
                      OutData_Signature);
}

rsip_ret_t r_rsip_wrapper_pf1_brainpoolp256r1 (const uint32_t InData_KeyIndex[],
                                               const uint32_t InData_MsgDgst[],
                                               const uint32_t InData_Signature[])
{
    return r_rsip_pf1(&gs_cmd[CMD_ECC_TYPE_BRAINPOOL],
                      &gs_cmd[CMD_ECC_KEY_LENGTH_256],
                      InData_KeyIndex,
                      InData_MsgDgst,
                      InData_Signature);
}

rsip_ret_t r_rsip_wrapper_pfa_secp256r1 (const uint32_t InData_SharedKeyNum[],
                                         const uint32_t InData_SharedKeyIndex[],
                                         const uint32_t InData_SessionKey[],
                                         const uint32_t InData_IV[],
                                         const uint32_t InData_InstData[],
                                         uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pfa(InData_SharedKeyNum,
                      InData_SharedKeyIndex,
                      InData_SessionKey,
                      &gs_cmd[CMD_ECC_TYPE_NIST],
                      &gs_cmd[CMD_ECC_KEY_LENGTH_256],
                      InData_IV,
                      InData_InstData,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_pf3_secp256r1 (const uint32_t InData_SharedKeyNum[],
                                         const uint32_t InData_SharedKeyIndex[],
                                         const uint32_t InData_SessionKey[],
                                         const uint32_t InData_IV[],
                                         const uint32_t InData_InstData[],
                                         uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pf3(InData_SharedKeyNum,
                      InData_SharedKeyIndex,
                      InData_SessionKey,
                      &gs_cmd[CMD_ECC_TYPE_NIST],
                      &gs_cmd[CMD_ECC_KEY_LENGTH_256],
                      InData_IV,
                      InData_InstData,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_pfa_brainpoolp256r1 (const uint32_t InData_SharedKeyNum[],
                                               const uint32_t InData_SharedKeyIndex[],
                                               const uint32_t InData_SessionKey[],
                                               const uint32_t InData_IV[],
                                               const uint32_t InData_InstData[],
                                               uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pfa(InData_SharedKeyNum,
                      InData_SharedKeyIndex,
                      InData_SessionKey,
                      &gs_cmd[CMD_ECC_TYPE_BRAINPOOL],
                      &gs_cmd[CMD_ECC_KEY_LENGTH_256],
                      InData_IV,
                      InData_InstData,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_pf3_brainpoolp256r1 (const uint32_t InData_SharedKeyNum[],
                                               const uint32_t InData_SharedKeyIndex[],
                                               const uint32_t InData_SessionKey[],
                                               const uint32_t InData_IV[],
                                               const uint32_t InData_InstData[],
                                               uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pf3(InData_SharedKeyNum,
                      InData_SharedKeyIndex,
                      InData_SessionKey,
                      &gs_cmd[CMD_ECC_TYPE_BRAINPOOL],
                      &gs_cmd[CMD_ECC_KEY_LENGTH_256],
                      InData_IV,
                      InData_InstData,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p80_hmac_sha1 (const uint32_t InData_SharedKeyNum[],
                                         const uint32_t InData_SharedKeyIndex[],
                                         const uint32_t InData_SessionKey[],
                                         const uint32_t InData_IV[],
                                         const uint32_t InData_InstData[],
                                         uint32_t       OutData_KeyIndex[])
{
    return r_rsip_p80(InData_SharedKeyNum,
                      InData_SharedKeyIndex,
                      InData_SessionKey,
                      &gs_cmd[CMD_HMAC_HASH_TYPE_SHA1],
                      InData_IV,
                      InData_InstData,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p80_hmac_sha224 (const uint32_t InData_SharedKeyNum[],
                                           const uint32_t InData_SharedKeyIndex[],
                                           const uint32_t InData_SessionKey[],
                                           const uint32_t InData_IV[],
                                           const uint32_t InData_InstData[],
                                           uint32_t       OutData_KeyIndex[])
{
    return r_rsip_p80(InData_SharedKeyNum,
                      InData_SharedKeyIndex,
                      InData_SessionKey,
                      &gs_cmd[CMD_HMAC_HASH_TYPE_SHA224],
                      InData_IV,
                      InData_InstData,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p80_hmac_sha256 (const uint32_t InData_SharedKeyNum[],
                                           const uint32_t InData_SharedKeyIndex[],
                                           const uint32_t InData_SessionKey[],
                                           const uint32_t InData_IV[],
                                           const uint32_t InData_InstData[],
                                           uint32_t       OutData_KeyIndex[])
{
    return r_rsip_p80(InData_SharedKeyNum,
                      InData_SharedKeyIndex,
                      InData_SessionKey,
                      &gs_cmd[CMD_HMAC_HASH_TYPE_SHA256],
                      InData_IV,
                      InData_InstData,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_pe2_wrapped (const uint32_t InData_PubKey[],
                                       const uint32_t InData_KeyIndex[],
                                       uint32_t       OutData_EncSecret[])
{
    return r_rsip_pe2(&gs_cmd[CMD_ECDH_PUBKEY_TYPE_WRAPPED], InData_PubKey, InData_KeyIndex, OutData_EncSecret);
}

rsip_ret_t r_rsip_wrapper_pe2_plain (const uint32_t InData_PubKey[],
                                     const uint32_t InData_KeyIndex[],
                                     uint32_t       OutData_EncSecret[])
{
    return r_rsip_pe2(&gs_cmd[CMD_ECDH_PUBKEY_TYPE_PLAIN], InData_PubKey, InData_KeyIndex, OutData_EncSecret);
}

rsip_ret_t r_rsip_wrapper_pe0_secp256r1 (const uint32_t InData_RootCertificate[],
                                         const uint32_t InData_RootCertificateInfo[],
                                         const uint32_t InData_RootCertificatePubKey[],
                                         uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pe0(&gs_cmd[CMD_PKI_KEY_TYPE_ECC_SECP256R1],
                      InData_RootCertificate,
                      InData_RootCertificateInfo,
                      InData_RootCertificatePubKey,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_pe0_rsa2048 (const uint32_t InData_RootCertificate[],
                                       const uint32_t InData_RootCertificateInfo[],
                                       const uint32_t InData_RootCertificatePubKey[],
                                       uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pe0(&gs_cmd[CMD_PKI_KEY_TYPE_RSA_2048],
                      InData_RootCertificate,
                      InData_RootCertificateInfo,
                      InData_RootCertificatePubKey,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_pe1_secp256r1 (const uint32_t InData_HashType[],
                                         const uint32_t InData_Certificate[],
                                         const uint32_t InData_CertificateLength[],
                                         const uint32_t InData_CertificatePubKey[],
                                         const uint32_t InData_EncCertificateInfo[],
                                         uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pe1(&gs_cmd[CMD_PKI_KEY_TYPE_ECC_SECP256R1],
                      InData_HashType,
                      InData_Certificate,
                      InData_CertificateLength,
                      InData_CertificatePubKey,
                      InData_EncCertificateInfo,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_pe1_rsa2048 (const uint32_t InData_HashType[],
                                       const uint32_t InData_Certificate[],
                                       const uint32_t InData_CertificateLength[],
                                       const uint32_t InData_CertificatePubKey[],
                                       const uint32_t InData_EncCertificateInfo[],
                                       uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pe1(&gs_cmd[CMD_PKI_KEY_TYPE_RSA_2048],
                      InData_HashType,
                      InData_Certificate,
                      InData_CertificateLength,
                      InData_CertificatePubKey,
                      InData_EncCertificateInfo,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_pe3_sha256 (const uint32_t InData_EncSecret[], uint32_t OutData_EncMsg[])
{
    return r_rsip_pe3(&gs_cmd[CMD_KDF_HASH_TYPE_SHA256], InData_EncSecret, OutData_EncMsg);
}

rsip_ret_t r_rsip_wrapper_pe4_sha256 (const uint32_t InData_EncSecret[], uint32_t OutData_KeyIndex[])
{
    return r_rsip_pe4(&gs_cmd[CMD_KDF_HASH_TYPE_SHA256], InData_EncSecret, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_pe6_sha256 (const uint32_t InData_KDFInfo[],
                                      const uint32_t InData_KDFInfo_Count[],
                                      const uint32_t InData_OutDataLength[],
                                      uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pe6(&gs_cmd[CMD_KDF_HASH_TYPE_SHA256],
                      InData_KDFInfo,
                      InData_KDFInfo_Count,
                      InData_OutDataLength,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_pe7_sha256_aes128 (const uint32_t InData_KDFInfo[],
                                             const uint32_t InData_KDFInfo_Count[],
                                             const uint32_t InData_OutDataLocation[],
                                             uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pe7(&gs_cmd[CMD_KDF_HASH_TYPE_SHA256], InData_KDFInfo, InData_KDFInfo_Count,
                      &gs_cmd[CMD_KDF_OUTDATA_TYPE_AES128], InData_OutDataLocation, NULL, NULL, OutData_KeyIndex, NULL);
}

rsip_ret_t r_rsip_wrapper_pe7_sha256_aes256 (const uint32_t InData_KDFInfo[],
                                             const uint32_t InData_KDFInfo_Count[],
                                             const uint32_t InData_OutDataLocation[],
                                             uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pe7(&gs_cmd[CMD_KDF_HASH_TYPE_SHA256], InData_KDFInfo, InData_KDFInfo_Count,
                      &gs_cmd[CMD_KDF_OUTDATA_TYPE_AES256], InData_OutDataLocation, NULL, NULL, OutData_KeyIndex, NULL);
}

rsip_ret_t r_rsip_wrapper_pe7_sha256_hmac_sha1 (const uint32_t InData_KDFInfo[],
                                                const uint32_t InData_KDFInfo_Count[],
                                                const uint32_t InData_OutDataLocation[],
                                                uint32_t       OutData_HMACKeyIndex[])
{
    return r_rsip_pe7(&gs_cmd[CMD_KDF_HASH_TYPE_SHA256],
                      InData_KDFInfo,
                      InData_KDFInfo_Count,
                      &gs_cmd[CMD_KDF_OUTDATA_TYPE_HMAC_SHA1],
                      InData_OutDataLocation,
                      NULL,
                      OutData_HMACKeyIndex,
                      NULL,
                      NULL);
}

rsip_ret_t r_rsip_wrapper_pe7_sha256_hmac_sha256 (const uint32_t InData_KDFInfo[],
                                                  const uint32_t InData_KDFInfo_Count[],
                                                  const uint32_t InData_OutDataLocation[],
                                                  uint32_t       OutData_HMACKeyIndex[])
{
    return r_rsip_pe7(&gs_cmd[CMD_KDF_HASH_TYPE_SHA256],
                      InData_KDFInfo,
                      InData_KDFInfo_Count,
                      &gs_cmd[CMD_KDF_OUTDATA_TYPE_HMAC_SHA256],
                      InData_OutDataLocation,
                      NULL,
                      OutData_HMACKeyIndex,
                      NULL,
                      NULL);
}

rsip_ret_t r_rsip_wrapper_pe7_sha256_iv_aes (const uint32_t InData_KDFInfo[],
                                             const uint32_t InData_KDFInfo_Count[],
                                             const uint32_t InData_OutDataLocation[],
                                             const uint32_t InData_SeqNum[],
                                             uint32_t       OutData_EncIV[])
{
    return r_rsip_pe7(&gs_cmd[CMD_KDF_HASH_TYPE_SHA256],
                      InData_KDFInfo,
                      InData_KDFInfo_Count,
                      &gs_cmd[CMD_KDF_OUTDATA_TYPE_IV_AES],
                      InData_OutDataLocation,
                      InData_SeqNum,
                      NULL,
                      NULL,
                      OutData_EncIV);
}

rsip_ret_t r_rsip_wrapper_pe7_sha256_iv_tls12 (const uint32_t InData_KDFInfo[],
                                               const uint32_t InData_KDFInfo_Count[],
                                               const uint32_t InData_OutDataLocation[],
                                               const uint32_t InData_SeqNum[],
                                               uint32_t       OutData_EncIV[])
{
    return r_rsip_pe7(&gs_cmd[CMD_KDF_HASH_TYPE_SHA256],
                      InData_KDFInfo,
                      InData_KDFInfo_Count,
                      &gs_cmd[CMD_KDF_OUTDATA_TYPE_IV_TLS12],
                      InData_OutDataLocation,
                      InData_SeqNum,
                      NULL,
                      NULL,
                      OutData_EncIV);
}

rsip_ret_t r_rsip_wrapper_pe9_sha256_client (const uint32_t InData_Hash[],
                                             const uint32_t InData_KeyIndex[],
                                             uint32_t       OutData_Verify_data[])
{
    return r_rsip_pe9(&gs_cmd[CMD_KDF_HASH_TYPE_SHA256], InData_Hash, InData_KeyIndex,
                      &gs_cmd[CMD_KDF_TLS12_PRF_VERIFY_DATA_CLIENT], OutData_Verify_data);
};

rsip_ret_t r_rsip_wrapper_pe9_sha256_server (const uint32_t InData_Hash[],
                                             const uint32_t InData_KeyIndex[],
                                             uint32_t       OutData_Verify_data[])
{
    return r_rsip_pe9(&gs_cmd[CMD_KDF_HASH_TYPE_SHA256], InData_Hash, InData_KeyIndex,
                      &gs_cmd[CMD_KDF_TLS12_PRF_VERIFY_DATA_SERVER], OutData_Verify_data);
};

rsip_ret_t r_rsip_wrapper_p15_jtag_level1 (const uint32_t InData_SharedKeyNum[],
                                           const uint32_t InData_SharedKeyIndex[],
                                           const uint32_t InData_SessionKey[],
                                           const uint32_t InData_IV[],
                                           const uint32_t InData_EncAuthData[],
                                           uint32_t       OutData_Hash[])
{
    return r_rsip_p15(InData_SharedKeyNum,
                      InData_SharedKeyIndex,
                      InData_SessionKey,
                      InData_IV,
                      InData_EncAuthData,
                      &gs_cmd[CMD_AUTH_HASH_TYPE_JTAG_DEBUG_LEVEL1],
                      OutData_Hash);
}

rsip_ret_t r_rsip_wrapper_p15_jtag_level2 (const uint32_t InData_SharedKeyNum[],
                                           const uint32_t InData_SharedKeyIndex[],
                                           const uint32_t InData_SessionKey[],
                                           const uint32_t InData_IV[],
                                           const uint32_t InData_EncAuthData[],
                                           uint32_t       OutData_Hash[])
{
    return r_rsip_p15(InData_SharedKeyNum,
                      InData_SharedKeyIndex,
                      InData_SessionKey,
                      InData_IV,
                      InData_EncAuthData,
                      &gs_cmd[CMD_AUTH_HASH_TYPE_JTAG_DEBUG_LEVEL2],
                      OutData_Hash);
}

rsip_ret_t r_rsip_wrapper_p15_sci_usb (const uint32_t InData_SharedKeyNum[],
                                       const uint32_t InData_SharedKeyIndex[],
                                       const uint32_t InData_SessionKey[],
                                       const uint32_t InData_IV[],
                                       const uint32_t InData_EncAuthData[],
                                       uint32_t       OutData_Hash[])
{
    return r_rsip_p15(InData_SharedKeyNum,
                      InData_SharedKeyIndex,
                      InData_SessionKey,
                      InData_IV,
                      InData_EncAuthData,
                      &gs_cmd[CMD_AUTH_HASH_TYPE_SCI_USB_BOOT],
                      OutData_Hash);
}

rsip_ret_t r_rsip_wrapper_pba_ch0 (const uint32_t InData_KeyIndex[], const uint32_t InData_DOTFSEED[])
{
    return r_rsip_pba(&gs_cmd[CMD_OTF_CHANNEL_0], InData_KeyIndex, InData_DOTFSEED);
};

rsip_ret_t r_rsip_wrapper_pba_ch1 (const uint32_t InData_KeyIndex[], const uint32_t InData_DOTFSEED[])
{
    return r_rsip_pba(&gs_cmd[CMD_OTF_CHANNEL_1], InData_KeyIndex, InData_DOTFSEED);
};

rsip_ret_t r_rsip_wrapper_pbc_ch0 (const uint32_t InData_KeyIndex[], const uint32_t InData_DOTFSEED[])
{
    return r_rsip_pbc(&gs_cmd[CMD_OTF_CHANNEL_0], InData_KeyIndex, InData_DOTFSEED);
};

rsip_ret_t r_rsip_wrapper_pbc_ch1 (const uint32_t InData_KeyIndex[], const uint32_t InData_DOTFSEED[])
{
    return r_rsip_pbc(&gs_cmd[CMD_OTF_CHANNEL_1], InData_KeyIndex, InData_DOTFSEED);
};

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
