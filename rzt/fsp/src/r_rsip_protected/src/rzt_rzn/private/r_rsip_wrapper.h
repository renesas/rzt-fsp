/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RSIP_WRAPPER_H
#define R_RSIP_WARPPER_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Primitive function names */
#define RSIP_PRV_FUNC_NAME_RANDOM_NUMBER_GENERATE                       r_rsip_p20

#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_AES_128                         r_rsip_p07
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_AES_128                         r_rsip_p19
#define RSIP_PRV_FUNC_NAME_RFC3394_AES_128_KEY_WRAP                     r_rsip_wrapper_p8f_aes128
#define RSIP_PRV_FUNC_NAME_RFC3394_AES_128_KEY_UNWRAP                   r_rsip_wrapper_p90_aes128

#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_ENC_128                  r_rsip_wrapper_p48i_ecb_enc
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_DEC_128                  r_rsip_wrapper_p48i_ecb_dec
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_128                  r_rsip_wrapper_p48i_cbc_enc
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_128                  r_rsip_wrapper_p48i_cbc_dec
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_128_WRAPPED_IV       r_rsip_wrapper_p48i_cbc_enc_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_128_WRAPPED_IV       r_rsip_wrapper_p48i_cbc_dec_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CTR_128                      r_rsip_wrapper_p48i_ctr
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_UPDATE_128                        r_rsip_p48u
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_FINAL_128                         r_rsip_p48f

#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_128                         r_rsip_wrapper_p29i_plain_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_128_WRAPPED_IV              r_rsip_wrapper_p29i_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_AAD_128                   r_rsip_p29a
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_TRANSITION_128            r_rsip_p29t
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_128                       r_rsip_p29u
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_FINAL_128                        r_rsip_p29f
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_128                         r_rsip_wrapper_p32i_plain_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_128_WRAPPED_IV              r_rsip_wrapper_p32i_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_AAD_128                   r_rsip_p32a
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_TRANSITION_128            r_rsip_p32t
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_128                       r_rsip_p32u
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_FINAL_128                        r_rsip_p32f

#define RSIP_PRV_FUNC_NAME_AES_CMAC_INIT_128                            r_rsip_p41i
#define RSIP_PRV_FUNC_NAME_AES_CMAC_UPDATE_128                          r_rsip_p41u
#define RSIP_PRV_FUNC_NAME_AES_CMAC_GENERATE_FINAL_128                  r_rsip_wrapper_p41f_gen
#define RSIP_PRV_FUNC_NAME_AES_CMAC_VERIFY_FINAL_128                    r_rsip_wrapper_p41f_veri

#define RSIP_PRV_FUNC_NAME_OTF_CHANNEL_0_AES_128                        r_rsip_wrapper_pba_ch0
#define RSIP_PRV_FUNC_NAME_OTF_CHANNEL_1_AES_128                        r_rsip_wrapper_pba_ch1

#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_AES_256                         r_rsip_p08
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_AES_256                         r_rsip_p1c
#define RSIP_PRV_FUNC_NAME_RFC3394_AES_256_KEY_WRAP                     r_rsip_wrapper_p8f_aes256
#define RSIP_PRV_FUNC_NAME_RFC3394_AES_256_KEY_UNWRAP                   r_rsip_wrapper_p90_aes256

#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_ENC_256                  r_rsip_wrapper_p50i_ecb_enc
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_DEC_256                  r_rsip_wrapper_p50i_ecb_dec
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_256                  r_rsip_wrapper_p50i_cbc_enc
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_256                  r_rsip_wrapper_p50i_cbc_dec
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_256_WRAPPED_IV       r_rsip_wrapper_p50i_cbc_enc_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_256_WRAPPED_IV       r_rsip_wrapper_p50i_cbc_dec_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CTR_256                      r_rsip_wrapper_p50i_ctr
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_UPDATE_256                        r_rsip_p50u
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_FINAL_256                         r_rsip_p50f

#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_256                         r_rsip_wrapper_p34i_plain_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_256_WRAPPED_IV              r_rsip_wrapper_p34i_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_AAD_256                   r_rsip_p34a
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_TRANSITION_256            r_rsip_p34t
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_256                       r_rsip_p34u
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_FINAL_256                        r_rsip_p34f
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_256                         r_rsip_wrapper_p36i_plain_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_256_WRAPPED_IV              r_rsip_wrapper_p36i_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_AAD_256                   r_rsip_p36a
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_TRANSITION_256            r_rsip_p36t
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_256                       r_rsip_p36u
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_FINAL_256                        r_rsip_p36f

#define RSIP_PRV_FUNC_NAME_AES_CMAC_INIT_256                            r_rsip_p44i
#define RSIP_PRV_FUNC_NAME_AES_CMAC_UPDATE_256                          r_rsip_p44u
#define RSIP_PRV_FUNC_NAME_AES_CMAC_GENERATE_FINAL_256                  r_rsip_wrapper_p44f_gen
#define RSIP_PRV_FUNC_NAME_AES_CMAC_VERIFY_FINAL_256                    r_rsip_wrapper_p44f_veri

#define RSIP_PRV_FUNC_NAME_OTF_CHANNEL_0_AES_256                        r_rsip_wrapper_pbc_ch0
#define RSIP_PRV_FUNC_NAME_OTF_CHANNEL_1_AES_256                        r_rsip_wrapper_pbc_ch1

#define RSIP_PRV_FUNC_NAME_GHASH_COMPUTE                                r_rsip_p21

#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_XTS_AES_128                     r_rsip_p16
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_XTS_AES_128                     r_rsip_p1b

#define RSIP_PRV_FUNC_NAME_XTS_AES_ENC_INIT_128                         r_rsip_pb3i
#define RSIP_PRV_FUNC_NAME_XTS_AES_ENC_UPDATE_128                       r_rsip_pb3u
#define RSIP_PRV_FUNC_NAME_XTS_AES_ENC_FINAL_128                        r_rsip_pb3f
#define RSIP_PRV_FUNC_NAME_XTS_AES_DEC_INIT_128                         r_rsip_pb6i
#define RSIP_PRV_FUNC_NAME_XTS_AES_DEC_UPDATE_128                       r_rsip_pb6u
#define RSIP_PRV_FUNC_NAME_XTS_AES_DEC_FINAL_128                        r_rsip_pb6f

#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_XTS_AES_256                     r_rsip_p17
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_XTS_AES_256                     r_rsip_p1d

#define RSIP_PRV_FUNC_NAME_XTS_AES_ENC_INIT_256                         r_rsip_pb9i
#define RSIP_PRV_FUNC_NAME_XTS_AES_ENC_UPDATE_256                       r_rsip_pb9u
#define RSIP_PRV_FUNC_NAME_XTS_AES_ENC_FINAL_256                        r_rsip_pb9f
#define RSIP_PRV_FUNC_NAME_XTS_AES_DEC_INIT_256                         r_rsip_pc2i
#define RSIP_PRV_FUNC_NAME_XTS_AES_DEC_UPDATE_256                       r_rsip_pc2u
#define RSIP_PRV_FUNC_NAME_XTS_AES_DEC_FINAL_256                        r_rsip_pc2f

#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_SECP256R1              r_rsip_wrapper_pf4_secp256r1
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP256R1_PUBLIC            r_rsip_wrapper_p2c_secp256r1
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP256R1_PRIVATE           r_rsip_wrapper_p1e_secp256r1

#define RSIP_PRV_FUNC_NAME_ECDSA_SIGN_SECP256R1                         r_rsip_wrapper_pf0_secp256r1
#define RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_SECP256R1                       r_rsip_wrapper_pf1_secp256r1

#define RSIP_PRV_FUNC_NAME_ECDH_WRAPPED_SECP256R1                       r_rsip_wrapper_pe2_wrapped
#define RSIP_PRV_FUNC_NAME_ECDH_PLAIN_SECP256R1                         r_rsip_wrapper_pe2_plain

#define RSIP_PRV_FUNC_NAME_PKI_ECDSA_VERIFY_INIT_SECP256R1              r_rsip_peei
#define RSIP_PRV_FUNC_NAME_PKI_ECDSA_VERIFY_FINAL_SECP256R1             r_rsip_peef
#define RSIP_PRV_FUNC_NAME_PKI_CERT_KEY_IMPORT_ECC_SECP256R1            r_rsip_wrapper_pe1_secp256r1

#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_BRAINPOOLP256R1        r_rsip_wrapper_pf4_brainpoolp256r1
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_BRAINPOOLP256R1_PUBLIC      r_rsip_wrapper_p2c_brainpoolp256r1
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_BRAINPOOLP256R1_PRIVATE     r_rsip_wrapper_p1e_brainpoolp256r1

#define RSIP_PRV_FUNC_NAME_ECDSA_SIGN_BRAINPOOLP256R1                   r_rsip_wrapper_pf0_brainpoolp256r1
#define RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_BRAINPOOLP256R1                 r_rsip_wrapper_pf1_brainpoolp256r1

#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_RSA_1024                   r_rsip_wrapper_p2a
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_1024_PUBLIC                 r_rsip_p0b
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_1024_PRIVATE                r_rsip_p0c

#define RSIP_PRV_FUNC_NAME_RSA_ENCRYPT_1024                             r_rsip_p53
#define RSIP_PRV_FUNC_NAME_RSA_DECRYPT_1024                             r_rsip_p54

#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_RSA_2048                   r_rsip_wrapper_p2b
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_2048_PUBLIC                 r_rsip_p0d
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_2048_PRIVATE                r_rsip_p0e

#define RSIP_PRV_FUNC_NAME_RSA_ENCRYPT_2048                             r_rsip_p56
#define RSIP_PRV_FUNC_NAME_RSA_DECRYPT_2048                             r_rsip_p57

#define RSIP_PRV_FUNC_NAME_PKI_RSA_VERIFY_INIT_2048                     r_rsip_pedi
#define RSIP_PRV_FUNC_NAME_PKI_RSA_VERIFY_FINAL_2048                    r_rsip_pedf
#define RSIP_PRV_FUNC_NAME_PKI_CERT_KEY_IMPORT_RSA_2048                 r_rsip_wrapper_pe1_rsa2048

#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_RSA_3072                   r_rsip_wrapper_p3a
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_3072_PUBLIC                 r_rsip_p38
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_3072_PRIVATE                r_rsip_p9d

#define RSIP_PRV_FUNC_NAME_RSA_ENCRYPT_3072                             r_rsip_p79
#define RSIP_PRV_FUNC_NAME_RSA_DECRYPT_3072                             r_rsip_p7a

#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_RSA_4096                   r_rsip_wrapper_p3b
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_4096_PUBLIC                 r_rsip_p9e
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_4096_PRIVATE                r_rsip_p9f

#define RSIP_PRV_FUNC_NAME_RSA_ENCRYPT_4096                             r_rsip_p7b
#define RSIP_PRV_FUNC_NAME_RSA_DECRYPT_4096                             r_rsip_p7c

#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_HMAC_SHA1                       r_rsip_p6d
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_HMAC_SHA1                       r_rsip_wrapper_p0f_hmac_sha1

#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_HMAC_SHA224                     r_rsip_p6e
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_HMAC_SHA224                     r_rsip_wrapper_p0f_hmac_sha224

#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_HMAC_SHA256                     r_rsip_p6f
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_HMAC_SHA256                     r_rsip_wrapper_p0f_hmac_sha256

#define RSIP_PRV_FUNC_NAME_KDF_ECDH_SECRET_KEY_IMPORT_SHA256            r_rsip_wrapper_pe4_sha256
#define RSIP_PRV_FUNC_NAME_KDF_ECDH_SECRET_MSG_WRAP_SHA256              r_rsip_wrapper_pe3_sha256
#define RSIP_PRV_FUNC_NAME_KDF_MAC_KEY_IMPORT_SHA256                    r_rsip_wrapper_pe6_sha256
#define RSIP_PRV_FUNC_NAME_KDF_DERIVED_KEY_IMPORT_SHA256_AES_128        r_rsip_wrapper_pe7_sha256_aes128
#define RSIP_PRV_FUNC_NAME_KDF_DERIVED_KEY_IMPORT_SHA256_AES_256        r_rsip_wrapper_pe7_sha256_aes256
#define RSIP_PRV_FUNC_NAME_KDF_DERIVED_KEY_IMPORT_SHA256_HMAC_SHA1      r_rsip_wrapper_pe7_sha256_hmac_sha1
#define RSIP_PRV_FUNC_NAME_KDF_DERIVED_KEY_IMPORT_SHA256_HMAC_SHA256    r_rsip_wrapper_pe7_sha256_hmac_sha256
#define RSIP_PRV_FUNC_NAME_KDF_DERIVED_IV_WRAP_SHA256_AES               r_rsip_wrapper_pe7_sha256_iv_aes
#define RSIP_PRV_FUNC_NAME_KDF_DERIVED_IV_WRAP_SHA256_TLS12             r_rsip_wrapper_pe7_sha256_iv_tls12
#define RSIP_PRV_FUNC_NAME_KDF_DERIVED_IV_WRAP_SHA256_TLS13             r_rsip_wrapper_pe7_sha256_iv_tls13
#define RSIP_PRV_FUNC_NAME_KDF_TLS12_PRF_VERIFY_DATA_CLIENT_SHA256      r_rsip_wrapper_pe9_sha256_client
#define RSIP_PRV_FUNC_NAME_KDF_TLS12_PRF_VERIFY_DATA_SERVER_SHA256      r_rsip_wrapper_pe9_sha256_server

#define RSIP_PRV_PKI_HASH_TYPE_SHA1                                     (0U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA224                                   (0U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA256                                   (1U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA384                                   (4U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA512                                   (5U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA512_224                               (2U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA512_256                               (3U)

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

/* Key pair generation */
rsip_ret_t r_rsip_wrapper_pf4_secp256r1(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_pf4_brainpoolp256r1(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_p2a(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_p2b(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_p3a(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_p3b(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);

/* Key import with KUK */
rsip_ret_t r_rsip_wrapper_p2c_secp256r1(uint32_t const InData_IV[],
                                        uint32_t const InData_InstData[],
                                        uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p1e_secp256r1(uint32_t const InData_IV[],
                                        uint32_t const InData_InstData[],
                                        uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p2c_brainpoolp256r1(uint32_t const InData_IV[],
                                              uint32_t const InData_InstData[],
                                              uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p1e_brainpoolp256r1(uint32_t const InData_IV[],
                                              uint32_t const InData_InstData[],
                                              uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p0f_hmac_sha1(const uint32_t InData_IV[],
                                        const uint32_t InData_InstData[],
                                        uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p0f_hmac_sha224(const uint32_t InData_IV[],
                                          const uint32_t InData_InstData[],
                                          uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p0f_hmac_sha256(const uint32_t InData_IV[],
                                          const uint32_t InData_InstData[],
                                          uint32_t       OutData_KeyIndex[]);

/* RFC3394 AES key wrap */
rsip_ret_t r_rsip_wrapper_p8f_aes128(const uint32_t InData_KeyIndex[],
                                     const uint32_t InData_WrappedKeyType[],
                                     const uint32_t InData_WrappedKeyIndex[],
                                     uint32_t       OutData_Text[],
                                     uint32_t       KEY_INDEX_SIZE,
                                     uint32_t       WRAPPED_KEY_SIZE);

rsip_ret_t r_rsip_wrapper_p8f_aes256(const uint32_t InData_KeyIndex[],
                                     const uint32_t InData_WrappedKeyType[],
                                     const uint32_t InData_WrappedKeyIndex[],
                                     uint32_t       OutData_Text[],
                                     uint32_t       KEY_INDEX_SIZE,
                                     uint32_t       WRAPPED_KEY_SIZE);

rsip_ret_t r_rsip_wrapper_p90_aes128(const uint32_t InData_KeyIndex[],
                                     const uint32_t InData_WrappedKeyType[],
                                     const uint32_t InData_Text[],
                                     uint32_t       OutData_KeyIndex[],
                                     uint32_t       WRAPPED_KEY_SIZE,
                                     uint32_t       KEY_INDEX_SIZE);

rsip_ret_t r_rsip_wrapper_p90_aes256(const uint32_t InData_KeyIndex[],
                                     const uint32_t InData_WrappedKeyType[],
                                     const uint32_t InData_Text[],
                                     uint32_t       OutData_KeyIndex[],
                                     uint32_t       WRAPPED_KEY_SIZE,
                                     uint32_t       KEY_INDEX_SIZE);

/* AES-ECB/CBC/CTR */
rsip_ret_t r_rsip_wrapper_p48i_ecb_enc(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p48i_ecb_dec(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p48i_cbc_enc(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p48i_cbc_dec(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p48i_cbc_enc_wrapped_iv(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p48i_cbc_dec_wrapped_iv(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p48i_ctr(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_ecb_enc(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_ecb_dec(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_cbc_enc(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_cbc_dec(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_cbc_enc_wrapped_iv(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_cbc_dec_wrapped_iv(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_ctr(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);

/* AES-GCM */
rsip_ret_t r_rsip_wrapper_p29i_plain_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p29i_wrapped_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p32i_plain_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p32i_wrapped_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p34i_plain_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p34i_wrapped_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p36i_plain_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p36i_wrapped_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);

/* AES-CMAC */
rsip_ret_t r_rsip_wrapper_p41f_gen(const uint32_t InData_Text[], uint32_t OutData_DataT[], const uint32_t all_msg_len);
rsip_ret_t r_rsip_wrapper_p44f_gen(const uint32_t InData_Text[], uint32_t OutData_DataT[], const uint32_t all_msg_len);
rsip_ret_t r_rsip_wrapper_p41f_veri(const uint32_t InData_Text[],
                                    const uint32_t InData_DataT[],
                                    const uint32_t InData_DataTLen[],
                                    const uint32_t all_msg_len);
rsip_ret_t r_rsip_wrapper_p44f_veri(const uint32_t InData_Text[],
                                    const uint32_t InData_DataT[],
                                    const uint32_t InData_DataTLen[],
                                    const uint32_t all_msg_len);

/* ECDSA */
rsip_ret_t r_rsip_wrapper_pf0_secp256r1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf1_secp256r1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        const uint32_t InData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf0_brainpoolp256r1(const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_MsgDgst[],
                                              uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf1_brainpoolp256r1(const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_MsgDgst[],
                                              const uint32_t InData_Signature[]);

/* ECDH */
rsip_ret_t r_rsip_wrapper_pe2_wrapped(const uint32_t InData_PubKey[],
                                      const uint32_t InData_KeyIndex[],
                                      uint32_t       OutData_EncSecret[]);

rsip_ret_t r_rsip_wrapper_pe2_plain(const uint32_t InData_PubKey[],
                                    const uint32_t InData_KeyIndex[],
                                    uint32_t       OutData_EncSecret[]);

/* Key import with UFPK */
rsip_ret_t r_rsip_wrapper_pfa_secp256r1(const uint32_t InData_SharedKeyNum[],
                                        const uint32_t InData_SharedKeyIndex[],
                                        const uint32_t InData_SessionKey[],
                                        const uint32_t InData_IV[],
                                        const uint32_t InData_InstData[],
                                        uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pf3_secp256r1(const uint32_t InData_SharedKeyNum[],
                                        const uint32_t InData_SharedKeyIndex[],
                                        const uint32_t InData_SessionKey[],
                                        const uint32_t InData_IV[],
                                        const uint32_t InData_InstData[],
                                        uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pf3_brainpoolp256r1(const uint32_t InData_SharedKeyNum[],
                                              const uint32_t InData_SharedKeyIndex[],
                                              const uint32_t InData_SessionKey[],
                                              const uint32_t InData_IV[],
                                              const uint32_t InData_InstData[],
                                              uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pfa_brainpoolp256r1(const uint32_t InData_SharedKeyNum[],
                                              const uint32_t InData_SharedKeyIndex[],
                                              const uint32_t InData_SessionKey[],
                                              const uint32_t InData_IV[],
                                              const uint32_t InData_InstData[],
                                              uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p80_hmac_sha1(const uint32_t InData_SharedKeyNum[],
                                        const uint32_t InData_SharedKeyIndex[],
                                        const uint32_t InData_SessionKey[],
                                        const uint32_t InData_IV[],
                                        const uint32_t InData_InstData[],
                                        uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p80_hmac_sha224(const uint32_t InData_SharedKeyNum[],
                                          const uint32_t InData_SharedKeyIndex[],
                                          const uint32_t InData_SessionKey[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_InstData[],
                                          uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p80_hmac_sha256(const uint32_t InData_SharedKeyNum[],
                                          const uint32_t InData_SharedKeyIndex[],
                                          const uint32_t InData_SessionKey[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_InstData[],
                                          uint32_t       OutData_KeyIndex[]);

/* Root certificate key import */
rsip_ret_t r_rsip_wrapper_pe0_secp256r1(const uint32_t InData_RootCertificate[],
                                        const uint32_t InData_RootCertificateInfo[],
                                        const uint32_t InData_RootCertificatePubKey[],
                                        uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe0_rsa2048(const uint32_t InData_RootCertificate[],
                                      const uint32_t InData_RootCertificateInfo[],
                                      const uint32_t InData_RootCertificatePubKey[],
                                      uint32_t       OutData_KeyIndex[]);

/* PKI */
rsip_ret_t r_rsip_wrapper_pe1_secp256r1(const uint32_t InData_HashType[],
                                        const uint32_t InData_Certificate[],
                                        const uint32_t InData_CertificateLength[],
                                        const uint32_t InData_CertificatePubKey[],
                                        const uint32_t InData_EncCertificateInfo[],
                                        uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe1_rsa2048(const uint32_t InData_HashType[],
                                      const uint32_t InData_Certificate[],
                                      const uint32_t InData_CertificateLength[],
                                      const uint32_t InData_CertificatePubKey[],
                                      const uint32_t InData_EncCertificateInfo[],
                                      uint32_t       OutData_KeyIndex[]);

/* KDF */
rsip_ret_t r_rsip_wrapper_pe3_sha256(const uint32_t InData_EncSecret[], uint32_t OutData_EncMsg[]);
rsip_ret_t r_rsip_wrapper_pe4_sha256(const uint32_t InData_EncSecret[], uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe6_sha256(const uint32_t InData_KDFInfo[],
                                     const uint32_t InData_KDFInfo_Count[],
                                     const uint32_t InData_OutDataLength[],
                                     uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe7_sha256_aes128(const uint32_t InData_KDFInfo[],
                                            const uint32_t InData_KDFInfo_Count[],
                                            const uint32_t InData_OutDataLocation[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe7_sha256_aes256(const uint32_t InData_KDFInfo[],
                                            const uint32_t InData_KDFInfo_Count[],
                                            const uint32_t InData_OutDataLocation[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe7_sha256_hmac_sha1(const uint32_t InData_KDFInfo[],
                                               const uint32_t InData_KDFInfo_Count[],
                                               const uint32_t InData_OutDataLocation[],
                                               uint32_t       OutData_HMACKeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe7_sha256_hmac_sha256(const uint32_t InData_KDFInfo[],
                                                 const uint32_t InData_KDFInfo_Count[],
                                                 const uint32_t InData_OutDataLocation[],
                                                 uint32_t       OutData_HMACKeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe7_sha256_iv_aes(const uint32_t InData_KDFInfo[],
                                            const uint32_t InData_KDFInfo_Count[],
                                            const uint32_t InData_OutDataLocation[],
                                            const uint32_t InData_SeqNum[],
                                            uint32_t       OutData_EncIV[]);
rsip_ret_t r_rsip_wrapper_pe7_sha256_iv_tls12(const uint32_t InData_KDFInfo[],
                                              const uint32_t InData_KDFInfo_Count[],
                                              const uint32_t InData_OutDataLocation[],
                                              const uint32_t InData_SeqNum[],
                                              uint32_t       OutData_EncIV[]);
rsip_ret_t r_rsip_wrapper_pe7_sha256_iv_tls13(const uint32_t InData_KDFInfo[],
                                              const uint32_t InData_KDFInfo_Count[],
                                              const uint32_t InData_OutDataLocation[],
                                              const uint32_t InData_SeqNum[],
                                              uint32_t       OutData_EncIV[]);
rsip_ret_t r_rsip_wrapper_pe9_sha256_client(const uint32_t InData_Hash[],
                                            const uint32_t InData_KeyIndex[],
                                            uint32_t       OutData_Verify_data[]);
rsip_ret_t r_rsip_wrapper_pe9_sha256_server(const uint32_t InData_Hash[],
                                            const uint32_t InData_KeyIndex[],
                                            uint32_t       OutData_Verify_data[]);

/* Password hash generation */
rsip_ret_t r_rsip_wrapper_p15_jtag_level1(const uint32_t InData_SharedKeyNum[],
                                          const uint32_t InData_SharedKeyIndex[],
                                          const uint32_t InData_SessionKey[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_EncAuthData[],
                                          uint32_t       OutData_Hash[]);
rsip_ret_t r_rsip_wrapper_p15_jtag_level2(const uint32_t InData_SharedKeyNum[],
                                          const uint32_t InData_SharedKeyIndex[],
                                          const uint32_t InData_SessionKey[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_EncAuthData[],
                                          uint32_t       OutData_Hash[]);
rsip_ret_t r_rsip_wrapper_p15_sci_usb(const uint32_t InData_SharedKeyNum[],
                                      const uint32_t InData_SharedKeyIndex[],
                                      const uint32_t InData_SessionKey[],
                                      const uint32_t InData_IV[],
                                      const uint32_t InData_EncAuthData[],
                                      uint32_t       OutData_Hash[]);

/* OTF */
rsip_ret_t r_rsip_wrapper_pba_ch0(const uint32_t InData_KeyIndex[], const uint32_t InData_DOTFSEED[]);
rsip_ret_t r_rsip_wrapper_pba_ch1(const uint32_t InData_KeyIndex[], const uint32_t InData_DOTFSEED[]);
rsip_ret_t r_rsip_wrapper_pbc_ch0(const uint32_t InData_KeyIndex[], const uint32_t InData_DOTFSEED[]);
rsip_ret_t r_rsip_wrapper_pbc_ch1(const uint32_t InData_KeyIndex[], const uint32_t InData_DOTFSEED[]);

#endif                                 /* R_RSIP_WRAPPER_H */
