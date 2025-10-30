/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RSIP_PRIVATE_H
#define R_RSIP_PRIVATE_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip.h"
#include "r_rsip_err.h"
#include "r_rsip_util.h"
#include "r_rsip_addr.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/*
 * Private/Primitive functions
 */

/* Random number generation */
typedef rsip_ret_t (* rsip_func_rng_t)(uint32_t OutData_Text[]);

/* Key generation */
typedef rsip_ret_t (* rsip_func_key_generate_t)(uint32_t OutData_KeyIndex[]);

/* Key pair generation */
typedef rsip_ret_t (* rsip_func_key_pair_generate_t)(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);

/* Encrypted key wrap */
typedef rsip_ret_t (* rsip_func_encrypted_key_wrap_t)(const uint32_t InData_IV[], const uint32_t InData_InstData[],
                                                      uint32_t OutData_KeyIndex[]);

/* RFC3394 Key Wrap */
typedef rsip_ret_t (* rsip_func_rfc3394_key_wrap_t)(const uint32_t InData_KeyIndex[],
                                                    const uint32_t InData_WrappedKeyType[],
                                                    const uint32_t InData_WrappedKeyIndex[], uint32_t OutData_Text[],
                                                    uint32_t KEY_INDEX_SIZE, uint32_t WRAPPED_KEY_SIZE);

/* RFC3394 Key Unwrap */
typedef rsip_ret_t (* rsip_func_rfc3394_key_unwrap_t)(const uint32_t InData_KeyIndex[],
                                                      const uint32_t InData_WrappedKeyType[],
                                                      const uint32_t InData_Text[], uint32_t OutData_KeyIndex[],
                                                      uint32_t WRAPPED_KEY_SIZE, uint32_t KEY_INDEX_SIZE);

/* AES-ECB/CBC/CTR */
typedef rsip_ret_t (* rsip_func_aes_cipher_init_t)(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);

/* AES-GCM */
typedef rsip_ret_t (* rsip_func_aes_gcm_init_t)(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
typedef rsip_ret_t (* rsip_func_ghash_t)(const uint32_t InData_HV[], const uint32_t InData_IV[],
                                         const uint32_t InData_Text[], uint32_t OutData_DataT[], uint32_t MAX_CNT);

/* ChaCha20-Poly1305 */
typedef rsip_ret_t (* rsip_func_chacha_poly_init_t)(const uint32_t * InData_KeyIndex, const uint32_t * InData_Nonce,
                                                    const uint32_t * InData_TextLen, const uint32_t * InData_DataALen);
typedef rsip_ret_t (* rsip_func_chacha_poly_resume_t)(const uint32_t * InData_KeyIndex, const uint32_t * InData_Nonce,
                                                      const uint32_t * InData_State);

/* ECDSA */
typedef rsip_ret_t (* rsip_func_ecdsa_sign_t)(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[],
                                              uint32_t OutData_Signature[]);
typedef rsip_ret_t (* rsip_func_ecdsa_verify_t)(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[],
                                                const uint32_t InData_Signature[]);

/* EdDSA */
typedef rsip_ret_t (* rsip_func_eddsa_sign_t)(const uint32_t InData_PrivKeyIndex[], const uint32_t InData_PubKeyIndex[],
                                              const uint32_t InData_Msg[], const uint64_t InData_MsgLen,
                                              uint32_t OutData_Signature[]);

typedef rsip_ret_t (* rsip_func_eddsa_verify_t)(const uint32_t InData_KeyIndex[], const uint32_t InData_Msg[],
                                                const uint64_t InData_MsgLen, const uint32_t InData_Signature[]);

/* ECDH */
typedef rsip_ret_t (* rsip_func_ecdh_t)(const uint32_t InData_PubKey[], const uint32_t InData_KeyIndex[],
                                        uint32_t OutData_EncSecret[]);

/* RSA */
typedef rsip_ret_t (* rsip_func_rsa_t)(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[],
                                       uint32_t OutData_Text[]);

/* PKI */
typedef rsip_ret_t (* rsip_func_pki_cert_key_import_t)(const uint32_t InData_HashType[],
                                                       const uint32_t InData_Certificate[],
                                                       const uint32_t InData_CertificateLength[],
                                                       const uint32_t InData_CertificatePubKey[],
                                                       const uint32_t InData_EncCertificateInfo[],
                                                       uint32_t       OutData_KeyIndex[]);

/* KDF */
typedef rsip_ret_t (* rsip_func_kdf_ecdh_secret_key_import_t)(const uint32_t InData_EncSecret[],
                                                              uint32_t       OutData_KeyIndex[]);
typedef rsip_ret_t (* rsip_func_kdf_ecdh_secret_msg_wrap_t)(const uint32_t InData_EncSecret[],
                                                            uint32_t       OutData_EncMsg[]);
typedef rsip_ret_t (* rsip_func_kdf_dkm_key_import_t)(const uint32_t InData_KDFInfo[],
                                                      const uint32_t InData_KDFInfo_Count[],
                                                      const uint32_t InData_OutDataLength[],
                                                      uint32_t       OutData_KeyIndex[]);
typedef rsip_ret_t (* rsip_func_kdf_derived_key_import_t)(const uint32_t InData_KDFInfo[],
                                                          const uint32_t InData_KDFInfo_Count[],
                                                          const uint32_t InData_OutDataLocation[],
                                                          uint32_t       OutData_KeyIndex[]);
typedef rsip_ret_t (* rsip_func_kdf_derived_iv_wrap_t)(const uint32_t InData_KDFInfo[],
                                                       const uint32_t InData_KDFInfo_Count[],
                                                       const uint32_t InData_OutDataLocation[],
                                                       const uint32_t InData_SeqNum[],
                                                       uint32_t       OutData_EncIV[]);

/* OTF */
typedef rsip_ret_t (* rsip_func_otf_t)(const uint32_t InData_KeyIndex[], const uint32_t InData_DOTFSEED[]);

/*
 * Private/Primitive function subsets
 */

/* AES-ECB/CBC/CTR */
typedef struct st_rsip_func_subset_aes_cipher
{
    rsip_func_aes_cipher_init_t p_init_ecb_enc;
    rsip_func_aes_cipher_init_t p_init_ecb_dec;
    rsip_func_aes_cipher_init_t p_init_cbc_enc;
    rsip_func_aes_cipher_init_t p_init_cbc_dec;
    rsip_func_aes_cipher_init_t p_init_cbc_enc_wrapped_iv;
    rsip_func_aes_cipher_init_t p_init_cbc_dec_wrapped_iv;
    rsip_func_aes_cipher_init_t p_init_ctr;
    void (* p_update)(const uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
    rsip_ret_t (* p_final)();
} rsip_func_subset_aes_cipher_t;

/* AES-XTS */
typedef struct st_rsip_func_subset_aes_xts
{
    rsip_ret_t (* p_init)(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
    void (* p_update)(const uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
    rsip_ret_t (* p_final)(const uint32_t * InData_TextBitLen, const uint32_t * InData_Text, uint32_t * OutData_Text);
} rsip_func_subset_aes_xts_t;

/* AES-GCM */
typedef struct st_rsip_func_subset_aes_gcm
{
    rsip_func_aes_gcm_init_t p_init;
    rsip_func_aes_gcm_init_t p_init_wrapped_iv;
    void (* p_updateAad)(const uint32_t * InData_DataA, uint32_t MAX_CNT);
    void (* p_updateTransition)();
    void (* p_update)(const uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
    rsip_ret_t (* p_encryptFinal)(const uint32_t * InData_Text, const uint32_t * InData_DataALen,
                                  const uint32_t * InData_TextLen, uint32_t * OutData_Text, uint32_t * OutData_DataT);
    rsip_ret_t (* p_decryptFinal)(const uint32_t * InData_Text, const uint32_t * InData_DataT,
                                  const uint32_t * InData_DataALen, const uint32_t * InData_TextLen,
                                  const uint32_t * InData_DataTLen,
                                  uint32_t * OutData_Text);
} rsip_func_subset_aes_gcm_t;

/* AES-CCM */
typedef struct st_rsip_func_subset_aes_ccm
{
    rsip_ret_t (* p_encryptInit)(const uint32_t * InData_KeyIndex, const uint32_t * InData_TextLen,
                                 const uint32_t * InData_IV, const uint32_t * InData_Header, uint32_t Header_Len);
    rsip_ret_t (* p_decryptInit)(const uint32_t * InData_KeyIndex, const uint32_t * InData_TextLen,
                                 const uint32_t * InData_MACLength, const uint32_t * InData_IV,
                                 const uint32_t * InData_Header, uint32_t Header_Len);
    void (* p_update)(const uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
    rsip_ret_t (* p_encryptFinal)(const uint32_t * InData_Text, const uint32_t * InData_TextLen,
                                  uint32_t * OutData_Text, uint32_t * OutData_MAC);
    rsip_ret_t (* p_decryptFinal)(const uint32_t * InData_Text, const uint32_t * InData_TextLen,
                                  const uint32_t * InData_MAC, const uint32_t * InData_MACLength,
                                  uint32_t * OutData_Text);
} rsip_func_subset_aes_ccm_t;

/* AES-CMAC */
typedef struct st_rsip_func_subset_aes_cmac
{
    rsip_ret_t (* p_init)(const uint32_t * InData_KeyIndex);
    void (* p_update)(const uint32_t * InData_Text, uint32_t MAX_CNT);
    rsip_ret_t (* p_generateFinal)(const uint32_t * InData_Text, uint32_t * OutData_DataT, const uint32_t all_msg_len);
    rsip_ret_t (* p_verifyFinal)(const uint32_t * InData_Text, const uint32_t * InData_DataT,
                                 const uint32_t * InData_DataTLen, const uint32_t all_msg_len);
} rsip_func_subset_aes_cmac_t;

/* ChaCha20 */
typedef struct st_rsip_func_subset_chacha20
{
    rsip_ret_t (* p_init)(const uint32_t * InData_KeyIndex, const uint32_t * InData_Ctr, const uint32_t * InData_Nonce,
                          const uint32_t * InData_TextLen);
    void (* p_update)(const uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
    rsip_ret_t (* p_final)(const uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
    rsip_ret_t (* p_suspend)(uint32_t * OutData_State);
    rsip_ret_t (* p_resume)(const uint32_t * InData_KeyIndex, const uint32_t * InData_Nonce,
                            const uint32_t * InData_State);
} rsip_func_subset_chacha20_t;

/* ChaCha20-Poly1305 */
typedef struct st_rsip_func_subset_chacha20_poly1305
{
    rsip_func_chacha_poly_init_t p_init_enc;
    rsip_func_chacha_poly_init_t p_init_dec;
    void (* p_updateAad)(const uint32_t * InData_DataA, uint32_t MAX_CNT);
    void (* p_updateTransition)();
    void (* p_update)(const uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
    rsip_ret_t (* p_final)(const uint32_t * InData_Text, const uint32_t * InData_DataT, uint32_t * OutData_Text,
                           uint32_t * OutData_DataT, uint32_t MAX_CNT);
    rsip_ret_t (* p_suspend)(uint32_t * OutData_State);
    rsip_func_chacha_poly_resume_t p_resume_enc;
    rsip_func_chacha_poly_resume_t p_resume_dec;
} rsip_func_subset_chacha20_poly1305_t;

/* SHA */
#if 1U == RSIP_PRV_HASH_IP_TYPE
typedef rsip_ret_t (* rsip_func_subset_sha_t)(const uint32_t InData_InitVal[], const uint32_t InData_PaddedMsg[],
                                              uint32_t MAX_CNT, uint32_t OutData_MsgDigest[]);
#elif (3U == RSIP_PRV_HASH_IP_TYPE) || (5U == RSIP_PRV_HASH_IP_TYPE)
typedef struct st_rsip_func_subset_sha
{
    rsip_ret_t (* p_init)(const uint32_t InData_HashType[], const uint32_t InData_MsgLen[]);
    rsip_ret_t (* p_resume)(const uint32_t InData_HashType[], const uint32_t InData_State[]);
    rsip_ret_t (* p_update)(const uint32_t InData_Msg[], uint32_t MAX_CNT);
    rsip_ret_t (* p_suspend)(uint32_t OutData_State[]);
    rsip_ret_t (* p_final)(const uint32_t InData_Msg[], uint32_t MAX_CNT, uint32_t OutData_MsgDigest[]);
} rsip_func_subset_sha_t;
#endif

/* HMAC */
#if 1U == RSIP_PRV_HASH_IP_TYPE
typedef struct st_rsip_func_subset_hmac
{
    rsip_ret_t (* p_init)(const uint32_t InData_KeyIndex[]);
    rsip_ret_t (* p_resume)(const uint32_t InData_KeyIndex[], const uint32_t InData_State[]);
    rsip_ret_t (* p_update)(const uint32_t InData_PaddedMsg[], uint32_t MAX_CNT);
    rsip_ret_t (* p_suspend)(uint32_t OutData_State[]);
    rsip_ret_t (* p_final)(const uint32_t InData_Cmd[], const uint32_t InData_MAC[], const uint32_t InData_length[],
                           uint32_t OutData_MAC[]);
} rsip_func_subset_hmac_t[RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256 + 1];
#elif (3U == RSIP_PRV_HASH_IP_TYPE) || (5U == RSIP_PRV_HASH_IP_TYPE)
typedef struct st_rsip_func_subset_hmac
{
    rsip_ret_t (* p_init)(const uint32_t InData_KeyIndex[], const uint32_t InData_HashType[],
                          const uint32_t InData_MsgLen[], uint32_t KEY_INDEX_SIZE);
    rsip_ret_t (* p_resume)(const uint32_t InData_KeyIndex[], const uint32_t InData_HashType[],
                            const uint32_t InData_State[], uint32_t KEY_INDEX_SIZE);
    rsip_ret_t (* p_update)(const uint32_t InData_Msg[], uint32_t MAX_CNT);
    rsip_ret_t (* p_suspend)(uint32_t OutData_State[]);
    rsip_ret_t (* p_final)(const uint32_t InData_Cmd[], const uint32_t InData_Msg[], const uint32_t InData_MAC[],
                           const uint32_t InData_length[], uint32_t MAX_CNT, uint32_t OutData_MAC[]);
} rsip_func_subset_hmac_t;
#endif

/* KDF SHA */
#if 1U == RSIP_PRV_HASH_IP_TYPE
typedef rsip_ret_t (* rsip_func_subset_kdf_sha_t)(const uint32_t InData_Msg1[], const uint32_t InData_Msg1Length[],
                                                  const uint32_t InData_EncMsg[], const uint32_t InData_EncMsgLength[],
                                                  const uint32_t InData_Msg2[],
                                                  const uint32_t InData_Msg2Length[], uint32_t OutData_KDFInfo[]);
#elif (3U == RSIP_PRV_HASH_IP_TYPE) || (5U == RSIP_PRV_HASH_IP_TYPE)
typedef struct st_rsip_func_subset_kdf_sha
{
    rsip_ret_t (* p_init)(const uint32_t InData_HashType[], const uint32_t InData_MsgLen[]);
    rsip_ret_t (* p_resume)(const uint32_t InData_HashType[], const uint32_t InData_State[]);
    rsip_ret_t (* p_update)(const uint32_t InData_Msg1[], const uint32_t InData_Msg1Length[],
                            const uint32_t InData_EncMsg[], const uint32_t InData_EncMsgLength[],
                            const uint32_t InData_Msg2[],
                            const uint32_t InData_Msg2Length[]);
    rsip_ret_t (* p_suspend)(uint32_t OutData_State[]);
    rsip_ret_t (* p_final)(const uint32_t InData_Msg1[], const uint32_t InData_Msg1Length[],
                           const uint32_t InData_EncMsg[], const uint32_t InData_EncMsgLength[],
                           const uint32_t InData_Msg2[],
                           const uint32_t InData_Msg2Length[], uint32_t OutData_KDFInfo[]);
} rsip_func_subset_kdf_sha_t;
#endif

/* KDF HMAC */
typedef struct st_rsip_func_subset_kdf_hmac
{
    rsip_ret_t (* p_init)(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[],
                          const uint32_t InData_HashType[], const uint32_t InData_MsgLen[]);
    rsip_ret_t (* p_resume)(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[],
                            const uint32_t InData_HashType[], const uint32_t InData_State[]);
    rsip_ret_t (* p_enc_update)(const uint32_t InData_EncMsg[], uint32_t MAX_CNT2);
    rsip_ret_t (* p_update)(const uint32_t InData_Msg[], uint32_t MAX_CNT);
    rsip_ret_t (* p_suspend)(uint32_t OutData_State[]);
    rsip_ret_t (* p_final)(const uint32_t InData_Msg[], const uint32_t InData_EncMsg[], uint32_t OutData_KDFInfo[],
                           uint32_t MAX_CNT, uint32_t MAX_CNT2);
} rsip_func_subset_kdf_hmac_t;

/* PKI */
typedef struct st_rsip_func_subset_pki_ecdsa_verify
{
    rsip_ret_t (* p_init)(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[],
                          const uint32_t InData_Signature[]);
    rsip_ret_t (* p_final)(uint32_t OutData_EncCertificateInfo[]);
} rsip_func_subset_pki_ecdsa_verify_t;

typedef struct st_rsip_func_subsetpki_rsa_verify
{
    rsip_ret_t (* p_init)(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
    rsip_ret_t (* p_final)(const uint32_t InData_SignatureType[], const uint32_t InData_HashType[],
                           const uint32_t InData_MsgDgst[], const uint32_t InData_Salt[],
                           const uint32_t InData_SaltLength[],
                           uint32_t OutData_EncCertificateInfo[]);
} rsip_func_subset_pki_rsa_verify_t;

/** Parsed key type */
typedef struct st_rsip_key_type_extend
{
    uint8_t alg;                       ///< Key algorithm
    uint8_t subtype;                   ///< Key subtype
} rsip_key_type_extend_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

extern const bool g_sha_enabled[RSIP_HASH_TYPE_NUM];
extern const bool g_hmac_enabled[RSIP_PRV_KEY_SUBTYPE_HMAC_NUM];
extern const bool g_kdf_sha_enabled[RSIP_HASH_TYPE_NUM];
extern const bool g_kdf_hmac_enabled[RSIP_PRV_KEY_SUBTYPE_HMAC_NUM];

extern const uint32_t g_pki_hash_type[RSIP_HASH_TYPE_NUM];

extern const rsip_func_key_generate_t gp_func_key_generate_aes[RSIP_PRV_KEY_SUBTYPE_AES_NUM];
extern const rsip_func_key_generate_t gp_func_key_generate_xts_aes[RSIP_PRV_KEY_SUBTYPE_AES_NUM];
extern const rsip_func_key_generate_t gp_func_key_generate_chacha[RSIP_PRV_KEY_SUBTYPE_CHACHA_NUM];
extern const rsip_func_key_generate_t gp_func_key_generate_hmac[RSIP_PRV_KEY_SUBTYPE_HMAC_NUM];

extern const rsip_func_key_pair_generate_t gp_func_key_pair_generate_ecc[RSIP_PRV_KEY_SUBTYPE_ECC_NUM];
extern const rsip_func_key_pair_generate_t gp_func_key_pair_generate_rsa[RSIP_PRV_KEY_SUBTYPE_RSA_NUM];

extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_aes[RSIP_PRV_KEY_SUBTYPE_AES_NUM];
extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_xts_aes[RSIP_PRV_KEY_SUBTYPE_AES_NUM];
extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_chacha[RSIP_PRV_KEY_SUBTYPE_CHACHA_NUM];
extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_ecc_pub[RSIP_PRV_KEY_SUBTYPE_ECC_NUM];
extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_ecc_priv[RSIP_PRV_KEY_SUBTYPE_ECC_NUM];
extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_rsa_pub[RSIP_PRV_KEY_SUBTYPE_RSA_NUM];
extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_rsa_priv[RSIP_PRV_KEY_SUBTYPE_RSA_NUM];
extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_hmac[RSIP_PRV_KEY_SUBTYPE_HMAC_NUM];

extern const rsip_func_rfc3394_key_wrap_t   gp_func_rfc3394_key_wrap[RSIP_PRV_KEY_SUBTYPE_AES_NUM];
extern const rsip_func_rfc3394_key_unwrap_t gp_func_rfc3394_key_unwrap[RSIP_PRV_KEY_SUBTYPE_AES_NUM];

extern const rsip_func_subset_aes_cipher_t gp_func_aes_cipher[RSIP_PRV_KEY_SUBTYPE_AES_NUM];
extern const rsip_func_subset_aes_xts_t    gp_func_aes_xts_enc[RSIP_PRV_KEY_SUBTYPE_AES_NUM];
extern const rsip_func_subset_aes_xts_t    gp_func_aes_xts_dec[RSIP_PRV_KEY_SUBTYPE_AES_NUM];
extern const rsip_func_subset_aes_gcm_t    gp_func_aes_gcm_enc[RSIP_PRV_KEY_SUBTYPE_AES_NUM];
extern const rsip_func_subset_aes_gcm_t    gp_func_aes_gcm_dec[RSIP_PRV_KEY_SUBTYPE_AES_NUM];
extern const rsip_func_subset_aes_ccm_t    gp_func_aes_ccm_enc[RSIP_PRV_KEY_SUBTYPE_AES_NUM];
extern const rsip_func_subset_aes_ccm_t    gp_func_aes_ccm_dec[RSIP_PRV_KEY_SUBTYPE_AES_NUM];
extern const rsip_func_subset_aes_cmac_t   gp_func_aes_cmac[RSIP_PRV_KEY_SUBTYPE_AES_NUM];

extern const rsip_func_subset_chacha20_t          gp_func_chacha20[RSIP_PRV_KEY_SUBTYPE_CHACHA_NUM];
extern const rsip_func_subset_chacha20_poly1305_t gp_func_chacha20_poly1305[RSIP_PRV_KEY_SUBTYPE_CHACHA_NUM];

extern const rsip_func_ecdsa_sign_t   gp_func_ecdsa_sign[RSIP_PRV_KEY_SUBTYPE_ECC_NUM];
extern const rsip_func_ecdsa_verify_t gp_func_ecdsa_verify[RSIP_PRV_KEY_SUBTYPE_ECC_NUM];

extern const rsip_func_eddsa_sign_t   gp_func_eddsa_sign[RSIP_PRV_KEY_SUBTYPE_ECC_NUM];
extern const rsip_func_eddsa_verify_t gp_func_eddsa_verify[RSIP_PRV_KEY_SUBTYPE_ECC_NUM];

extern const rsip_func_ecdh_t gp_func_ecdh_wrapped[RSIP_PRV_KEY_SUBTYPE_ECC_NUM];
extern const rsip_func_ecdh_t gp_func_ecdh_plain[RSIP_PRV_KEY_SUBTYPE_ECC_NUM];

extern const rsip_func_rsa_t gp_func_rsa_public[RSIP_PRV_KEY_SUBTYPE_RSA_NUM];
extern const rsip_func_rsa_t gp_func_rsa_private[RSIP_PRV_KEY_SUBTYPE_RSA_NUM];

extern const rsip_func_subset_sha_t      gp_func_sha1sha2;
extern const rsip_func_subset_sha_t      gp_func_sha3;
extern const rsip_func_subset_hmac_t     gp_func_hmac_sha1sha2;
extern const rsip_func_subset_hmac_t     gp_func_hmac_sha3;
extern const rsip_func_subset_kdf_sha_t  gp_func_kdf_sha1sha2;
extern const rsip_func_subset_kdf_hmac_t gp_func_kdf_hmac_sha1sha2;

extern const rsip_func_subset_pki_ecdsa_verify_t gp_func_pki_ecdsa_verify[RSIP_PRV_KEY_SUBTYPE_ECC_NUM];
extern const rsip_func_subset_pki_rsa_verify_t   gp_func_pki_rsa_verify[RSIP_PRV_KEY_SUBTYPE_RSA_NUM];
extern const rsip_func_pki_cert_key_import_t     gp_func_pki_cert_key_import_ecc[RSIP_PRV_KEY_SUBTYPE_ECC_NUM];
extern const rsip_func_pki_cert_key_import_t     gp_func_pki_cert_key_import_rsa[RSIP_PRV_KEY_SUBTYPE_RSA_NUM];

extern const rsip_func_rng_t   gp_func_rng;
extern const rsip_func_ghash_t gp_func_ghash_compute;

extern const rsip_func_kdf_ecdh_secret_msg_wrap_t gp_func_kdf_sha_ecdh_secret_msg_wrap[RSIP_PRV_DKM_SUBTYPE_SHA_NUM];

extern const rsip_func_kdf_derived_key_import_t gp_func_kdf_sha_derived_key_import_aes
[RSIP_PRV_DKM_SUBTYPE_SHA_NUM][RSIP_PRV_KEY_SUBTYPE_AES_NUM];
extern const rsip_func_kdf_derived_iv_wrap_t gp_func_kdf_sha_derived_iv_wrap[RSIP_PRV_DKM_SUBTYPE_SHA_NUM][2];

extern const rsip_func_kdf_ecdh_secret_key_import_t gp_func_kdf_hmac_ecdh_secret_key_import[
    RSIP_PRV_KEY_SUBTYPE_HMAC_NUM
];
extern const rsip_func_kdf_ecdh_secret_msg_wrap_t gp_func_kdf_hmac_ecdh_secret_msg_wrap[RSIP_PRV_KEY_SUBTYPE_HMAC_NUM];
extern const rsip_func_kdf_dkm_key_import_t       gp_func_kdf_hmac_dkm_key_import[RSIP_PRV_KEY_SUBTYPE_HMAC_NUM];

extern const rsip_func_kdf_derived_key_import_t gp_func_kdf_hmac_derived_key_import_aes
[RSIP_PRV_DKM_SUBTYPE_HMAC_NUM][RSIP_PRV_KEY_SUBTYPE_AES_NUM];
extern const rsip_func_kdf_derived_key_import_t gp_func_kdf_hmac_derived_key_import_hmac
[RSIP_PRV_DKM_SUBTYPE_HMAC_NUM][RSIP_PRV_KEY_SUBTYPE_HMAC_NUM];
extern const rsip_func_kdf_derived_iv_wrap_t gp_func_kdf_hmac_derived_iv_wrap[RSIP_PRV_DKM_SUBTYPE_HMAC_NUM
][3];

extern const rsip_func_otf_t gp_func_otf[RSIP_OTF_CHANNEL_NUM][RSIP_PRV_KEY_SUBTYPE_AES_NUM];

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the RSIP engine.
 *
 * @return The return value of the internally called primitive functions.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_open(void);

/*******************************************************************************************************************//**
 * Finalizes the RSIP engine.
 *
 * @return The return value of the internally called primitive functions.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_close(void);

/*******************************************************************************************************************//**
 * Sets Key Update Key (KUK).
 *
 * @param[in] p_key_update_key KUK.
 **********************************************************************************************************************/
void r_rsip_kuk_set(const void * p_key_update_key);

/*******************************************************************************************************************//**
 * Gets parameters for RFC3394 AES Key Wrap from target key type.
 *
 * @param[in]  key_type         Key type of target key.
 * @param[out] wrapped_key_type Key type number used for primitives.
 *
 * @retval FSP_SUCCESS              Normal termination.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid key type.
 **********************************************************************************************************************/
fsp_err_t r_rsip_get_rfc3394_key_wrap_param(rsip_key_type_t key_type, uint32_t * wrapped_key_type);

/*******************************************************************************************************************//**
 * 1. Initialize hash operation.
 * 2. Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha_hash_init_update(rsip_sha_handle_t * p_handle, const uint8_t * p_message,
                                       uint64_t message_length);

/*******************************************************************************************************************//**
 * 1. Resume hash operation.
 * 2. Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha_hash_resume_update(rsip_sha_handle_t * p_handle,
                                         const uint8_t     * p_message,
                                         uint64_t            message_length);

/*******************************************************************************************************************//**
 * Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha_hash_update(rsip_sha_handle_t * p_handle, const uint8_t * p_message, uint64_t message_length);

/*******************************************************************************************************************//**
 * Suspend hash operation.
 *
 * @param[in,out] p_handle       Pointer to handle.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha_hash_suspend(rsip_sha_handle_t * p_handle);

/*******************************************************************************************************************//**
 * 1. Initialize hash operation.
 * 2. Input the remaining message and finalize hash operation.
 *
 * @note This function allows empty message.
 *
 * @param[in]     hash_type      Generating hash type.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 * @param[out]    p_digest       Pointer to destination of message digest. The length depends on hash type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha_hash_init_final(rsip_hash_type_t hash_type,
                                      const uint8_t  * p_message,
                                      uint64_t         message_length,
                                      uint8_t        * p_digest);

/*******************************************************************************************************************//**
 * 1. Resume hash operation.
 * 2. Input the remaining message and finalize hash operation.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[out]    p_digest       Pointer to destination of message digest. The length depends on hash type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha_hash_resume_final(rsip_sha_handle_t * p_handle, uint8_t * p_digest);

/*******************************************************************************************************************//**
 * Input the remaining message and finalize hash operation.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[out]    p_digest       Pointer to destination of message digest. The length depends on hash type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha_hash_final(rsip_sha_handle_t * p_handle, uint8_t * p_digest);

/*******************************************************************************************************************//**
 * 1. Initialize HMAC operation.
 * 2. Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_init_update(rsip_hmac_handle_t * p_handle, const uint8_t * p_message, uint64_t message_length);

/*******************************************************************************************************************//**
 * 1. Resume HMAC operation.
 * 2. Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_resume_update(rsip_hmac_handle_t * p_handle, const uint8_t * p_message, uint64_t message_length);

/*******************************************************************************************************************//**
 * Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_update(rsip_hmac_handle_t * p_handle, const uint8_t * p_message, uint64_t message_length);

/*******************************************************************************************************************//**
 * Suspend HMAC operation.
 *
 * @param[in,out] p_handle Pointer to handle.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_suspend(rsip_hmac_handle_t * p_handle);

/*******************************************************************************************************************//**
 * 1. Initialize HMAC operation.
 * 2. Input the remaining message and finalize HMAC operation.
 * 3. Output MAC.
 *
 * @note This function allows empty message.
 *
 * @param[in]     p_wrapped_key  Pointer to wrapped key of HMAC key.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 * @param[out]    p_mac          Pointer to destination of message digest. The length depends on MAC type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_init_final(const rsip_wrapped_key_t * p_wrapped_key,
                                  const uint8_t            * p_message,
                                  uint64_t                   message_length,
                                  uint8_t                  * p_mac);

/*******************************************************************************************************************//**
 * 1. Resume HMAC operation.
 * 2. Input the remaining message and finalize HMAC operation.
 * 3. Output MAC.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[out]    p_mac          Pointer to destination of message digest. The length depends on MAC type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_resume_final(rsip_hmac_handle_t * p_handle, uint8_t * p_mac);

/*******************************************************************************************************************//**
 * 1. Input the remaining message and finalize HMAC operation.
 * 2. Output MAC.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[out]    p_mac          Pointer to destination of message digest. The length depends on MAC type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_final(rsip_hmac_handle_t * p_handle, uint8_t * p_mac);

/*******************************************************************************************************************//**
 * 1. Initialize HMAC operation.
 * 2. Input the remaining message and finalize HMAC operation.
 * 3. Verify MAC.
 *
 * @note This function allows empty message.
 *
 * @param[in]     p_wrapped_key  Pointer to wrapped key of HMAC key.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 * @param[in]     p_mac          Pointer to MAC. The length depends on mac_length.
 * @param[in]     mac_length     Byte length of MAC.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_init_verify(const rsip_wrapped_key_t * p_wrapped_key,
                                   const uint8_t            * p_message,
                                   uint64_t                   message_length,
                                   const uint8_t            * p_mac,
                                   uint32_t                   mac_length);

/*******************************************************************************************************************//**
 * 1. Resume HMAC operation.
 * 2. Input the remaining message and finalize HMAC operation.
 * 3. Verify MAC.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[in]     p_mac          Pointer to MAC. The length depends on mac_length.
 * @param[in]     mac_length     Byte length of MAC.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_resume_verify(rsip_hmac_handle_t * p_handle, const uint8_t * p_mac, uint32_t mac_length);

/*******************************************************************************************************************//**
 * 1. Input the remaining message and finalize HMAC operation.
 * 2. Verify MAC.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[in]     p_mac          Pointer to MAC. The length depends on mac_length.
 * @param[in]     mac_length     Byte length of MAC.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_verify(rsip_hmac_handle_t * p_handle, const uint8_t * p_mac, uint32_t mac_length);

/*******************************************************************************************************************//**
 * 1. Initialize hash operation.
 * 2. Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_kdf_sha_init_update(rsip_kdf_sha_handle_t * p_handle,
                                      const uint8_t         * p_message,
                                      uint64_t                message_length);

/*******************************************************************************************************************//**
 * 1. Resume hash operation.
 * 2. Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_kdf_sha_resume_update(rsip_kdf_sha_handle_t * p_handle,
                                        const uint8_t         * p_message,
                                        uint64_t                message_length);

/*******************************************************************************************************************//**
 * Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_kdf_sha_update(rsip_kdf_sha_handle_t * p_handle, const uint8_t * p_message, uint64_t message_length);

/*******************************************************************************************************************//**
 * Suspend hash operation.
 *
 * @param[in,out] p_handle       Pointer to handle.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_kdf_sha_suspend(rsip_kdf_sha_handle_t * p_handle);

/*******************************************************************************************************************//**
 * 1. Initialize hash operation.
 * 2. Input the remaining message and finalize hash operation.
 *
 * @note This function allows empty message.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[out]    p_digest       Pointer to destination of message digest. The length depends on hash type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_kdf_sha_init_final(rsip_kdf_sha_handle_t * p_handle, uint8_t * p_digest);

/*******************************************************************************************************************//**
 * 1. Resume hash operation.
 * 2. Input the remaining message and finalize hash operation.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[out]    p_digest       Pointer to destination of message digest. The length depends on hash type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_kdf_sha_resume_final(rsip_kdf_sha_handle_t * p_handle, uint8_t * p_digest);

/*******************************************************************************************************************//**
 * Input the remaining message and finalize hash operation.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[out]    p_digest       Pointer to destination of message digest. The length depends on hash type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_kdf_sha_final(rsip_kdf_sha_handle_t * p_handle, uint8_t * p_digest);

/*******************************************************************************************************************//**
 * 1. Initialize HMAC operation.
 * 2. Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_kdf_hmac_init_update(rsip_kdf_hmac_handle_t * p_handle,
                                       const uint8_t          * p_message,
                                       uint64_t                 message_length);

/*******************************************************************************************************************//**
 * 1. Resume HMAC operation.
 * 2. Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_kdf_hmac_resume_update(rsip_kdf_hmac_handle_t * p_handle,
                                         const uint8_t          * p_message,
                                         uint64_t                 message_length);

/*******************************************************************************************************************//**
 * Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_kdf_hmac_update(rsip_kdf_hmac_handle_t * p_handle, const uint8_t * p_message,
                                  uint64_t message_length);

/*******************************************************************************************************************//**
 * Suspend HMAC operation.
 *
 * @param[in,out] p_handle       Pointer to handle.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_kdf_hmac_suspend(rsip_kdf_hmac_handle_t * p_handle);

/*******************************************************************************************************************//**
 * 1. Initialize HMAC operation.
 * 2. Input the remaining message and finalize HMAC operation.
 * 3. Output MAC.
 *
 * @note This function allows empty message.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[out]    p_mac          Pointer to destination of message digest. The length depends on MAC type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_kdf_hmac_init_final(rsip_kdf_hmac_handle_t * p_handle, uint8_t * p_mac);

/*******************************************************************************************************************//**
 * 1. Resume HMAC operation.
 * 2. Input the remaining message and finalize HMAC operation.
 * 3. Output MAC.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[out]    p_mac          Pointer to destination of message digest. The length depends on MAC type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_kdf_hmac_resume_final(rsip_kdf_hmac_handle_t * p_handle, uint8_t * p_mac);

/*******************************************************************************************************************//**
 * 1. Input the remaining message and finalize HMAC operation.
 * 2. Output MAC.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in,out] p_handle       Pointer to handle.
 * @param[out]    p_mac          Pointer to destination of message digest. The length depends on MAC type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_kdf_hmac_final(rsip_kdf_hmac_handle_t * p_handle, uint8_t * p_mac);

/*******************************************************************************************************************//**
 * Parses key type.
 *
 * @param[in] key_type Key type.
 *
 * @return Parsed key type.
 ***********************************************************************************************************************/
RSIP_PRV_STATIC_INLINE rsip_key_type_extend_t r_rsip_key_type_parse (rsip_key_type_t key_type)
{
    rsip_key_type_extend_t ret =
    {
        .alg = RSIP_PRV_KEY_TYPE_VAL_ALG(key_type), .subtype = RSIP_PRV_KEY_TYPE_VAL_SUBTYPE(key_type)
    };

    return ret;
}

#endif                                 /* R_RSIP_PRIVATE_H */
