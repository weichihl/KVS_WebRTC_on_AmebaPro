/**************************************************************************//**
 * @file     crypto_api.c
 * @brief    This file implements the CRYPTO Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2017-12-11
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/
#include "hal_crypto.h"
#include "platform_conf.h"

#if CONFIG_CRYPTO_EN

#ifdef  __cplusplus
extern "C" {
#endif

int crypto_init(void)
{
    int ret;

    ret = rtl_cryptoEngine_init();
    return ret;
}

int crypto_deinit(void)
{
    int ret;

    ret = rtl_cryptoEngine_deinit();
    return ret;
}


//Auth md5
int crypto_md5(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_md5(message, msglen, pDigest);
    return ret;
}

int crypto_md5_init(void)
{
    int ret;

    ret = rtl_crypto_md5_init();
    return ret;
}

int crypto_md5_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_md5_process(message, msglen, pDigest);
    return ret;
}

int crypto_md5_update(const uint8_t *message, const uint32_t msglen)
{
    int ret;

    ret = rtl_crypto_md5_update(message, msglen);
    return ret;
}

int crypto_md5_final(uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_md5_final(pDigest);
    return ret;
}

//Auth SHA1
int crypto_sha1(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_sha1(message, msglen, pDigest);
    return ret;
}

int crypto_sha1_init(void)
{
    int ret;

    ret = rtl_crypto_sha1_init();
    return ret;
}

int crypto_sha1_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_sha1_process(message, msglen, pDigest);
    return ret;
}

int crypto_sha1_update(const uint8_t *message, const uint32_t msglen)
{
    int ret;

    ret = rtl_crypto_sha1_update(message, msglen);
    return ret;
}

int crypto_sha1_final(uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_sha1_final(pDigest);
    return ret;
}

//Auth SHA2_224
int crypto_sha2_224(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_sha2_224(message, msglen, pDigest);
    return ret;
}

int crypto_sha2_224_init(void)
{
    int ret;

    ret = rtl_crypto_sha2_224_init();
    return ret;
}

int crypto_sha2_224_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_sha2_224_process(message, msglen, pDigest);
    return ret;
}

int crypto_sha2_224_update(const uint8_t *message, const uint32_t msglen)
{
    int ret;

    ret = rtl_crypto_sha2_224_update(message, msglen);
    return ret;
}

int crypto_sha2_224_final(uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_sha2_224_final(pDigest);
    return ret;
}

//Auth SHA2_256
int crypto_sha2_256(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_sha2_256(message, msglen, pDigest);
    return ret;
}

int crypto_sha2_256_init(void)
{
    int ret;

    ret = rtl_crypto_sha2_256_init();
    return ret;
}

int crypto_sha2_256_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_sha2_256_process(message, msglen, pDigest);
    return ret;
}

int crypto_sha2_256_update(const uint8_t *message, const uint32_t msglen)
{
    int ret;

    ret = rtl_crypto_sha2_256_update(message, msglen);
    return ret;
}

int crypto_sha2_256_final(uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_sha2_256_final(pDigest);
    return ret;
}

//Auth HMAC_MD5
int crypto_hmac_md5(const uint8_t *message, const uint32_t msglen,
                    const uint8_t *key, const uint32_t keylen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_hmac_md5(message, msglen, key, keylen, pDigest);
    return ret;
}

int crypto_hmac_md5_init(const uint8_t *key, const uint32_t keylen)
{
    int ret;

    ret = rtl_crypto_hmac_md5_init(key, keylen);
    return ret;
}

int crypto_hmac_md5_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_hmac_md5_process(message, msglen, pDigest);
    return ret;
}

int crypto_hmac_md5_update(const uint8_t *message, const uint32_t msglen)
{
    int ret;

    ret = rtl_crypto_hmac_md5_update(message, msglen);
    return ret;
}

int crypto_hmac_md5_final(uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_hmac_md5_final(pDigest);
    return ret;
}

//Auth HMAC_SHA1
int crypto_hmac_sha1(const uint8_t *message, const uint32_t msglen,
                     const uint8_t *key, const uint32_t keylen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_hmac_sha1(message, msglen, key, keylen, pDigest);
    return ret;
}

int crypto_hmac_sha1_init(const uint8_t *key, const uint32_t keylen)
{
    int ret;

    ret = rtl_crypto_hmac_sha1_init(key, keylen);
    return ret;
}

int crypto_hmac_sha1_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_hmac_sha1_process(message, msglen, pDigest);
    return ret;
}

int crypto_hmac_sha1_update(const uint8_t *message, const uint32_t msglen)
{
    int ret;

    ret = rtl_crypto_hmac_sha1_update(message, msglen);
    return ret;
}

int crypto_hmac_sha1_final(uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_hmac_sha1_final(pDigest);
    return ret;
}

//Auth HMAC_SHA2_224
int crypto_hmac_sha2_224(const uint8_t *message, const uint32_t msglen,
                         const uint8_t *key, const uint32_t keylen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_hmac_sha2_224(message, msglen, key, keylen, pDigest);
    return ret;
}

int crypto_hmac_sha2_224_init(const uint8_t *key, const uint32_t keylen)
{
    int ret;

    ret = rtl_crypto_hmac_sha2_224_init(key, keylen);
    return ret;
}

int crypto_hmac_sha2_224_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_hmac_sha2_224_process(message, msglen, pDigest);
    return ret;
}

int crypto_hmac_sha2_224_update(const uint8_t *message, const uint32_t msglen)
{
    int ret;

    ret = rtl_crypto_hmac_sha2_224_update(message, msglen);
    return ret;
}

int crypto_hmac_sha2_224_final(uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_hmac_sha2_224_final(pDigest);
    return ret;
}

//Auth HMAC_SHA2_256
int crypto_hmac_sha2_256(const uint8_t *message, const uint32_t msglen,
                         const uint8_t *key, const uint32_t keylen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_hmac_sha2_256(message, msglen, key, keylen, pDigest);
    return ret;
}

int crypto_hmac_sha2_256_init(const uint8_t *key, const uint32_t keylen)
{
    int ret;

    ret = rtl_crypto_hmac_sha2_256_init(key, keylen);
    return ret;
}

int crypto_hmac_sha2_256_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_hmac_sha2_256_process(message, msglen, pDigest);
    return ret;
}

int crypto_hmac_sha2_256_update(const uint8_t *message, const uint32_t msglen)
{
    int ret;

    ret = rtl_crypto_hmac_sha2_256_update(message, msglen);
    return ret;
}

int crypto_hmac_sha2_256_final(uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_hmac_sha2_256_final(pDigest);
    return ret;
}

// DES-ECB
int crypto_des_ecb_init (const uint8_t *key, const uint32_t keylen){
    int ret;

    ret = rtl_crypto_des_ecb_init(key, keylen);
    return ret;
}

int crypto_des_ecb_encrypt (const uint8_t *message, const uint32_t msglen,
                            const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_des_ecb_encrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

int crypto_des_ecb_decrypt (const uint8_t *message, const uint32_t msglen,
                            const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_des_ecb_decrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

// DES-CBC
int crypto_des_cbc_init (const uint8_t *key, const uint32_t keylen){
    int ret;

    ret = rtl_crypto_des_cbc_init(key, keylen);
    return ret;
}

int crypto_des_cbc_encrypt (const uint8_t *message, const uint32_t msglen,
                            const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_des_cbc_encrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

int crypto_des_cbc_decrypt (const uint8_t *message, const uint32_t msglen,
                            const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_des_cbc_decrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

// 3DES-ECB
int crypto_3des_ecb_init (const uint8_t *key, const uint32_t keylen){
    int ret;

    ret = rtl_crypto_3des_ecb_init(key, keylen);
    return ret;
}

int crypto_3des_ecb_encrypt (const uint8_t *message, const uint32_t msglen,
                             const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_3des_ecb_encrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

int crypto_3des_ecb_decrypt (const uint8_t *message, const uint32_t msglen,
                             const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_3des_ecb_decrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

// 3DES-CBC
int crypto_3des_cbc_init (const uint8_t *key, const uint32_t keylen){
    int ret;

    ret = rtl_crypto_3des_cbc_init(key, keylen);
    return ret;
}

int crypto_3des_cbc_encrypt (const uint8_t *message, const uint32_t msglen,
                             const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_3des_cbc_encrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

int crypto_3des_cbc_decrypt (const uint8_t *message, const uint32_t msglen,
                             const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_3des_cbc_decrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

// AES-ECB
int crypto_aes_ecb_init (const uint8_t *key, const uint32_t keylen){
    int ret;

    ret = rtl_crypto_aes_ecb_init(key, keylen);
    return ret;
}

int crypto_aes_ecb_encrypt (const uint8_t *message, const uint32_t msglen,
                            const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_aes_ecb_encrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

int crypto_aes_ecb_decrypt (const uint8_t *message, const uint32_t msglen,
                            const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_aes_ecb_decrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

// AES-CBC
int crypto_aes_cbc_init (const uint8_t *key, const uint32_t keylen){
    int ret;

    ret = rtl_crypto_aes_cbc_init(key, keylen);
    return ret;
}

int crypto_aes_cbc_encrypt (const uint8_t *message, const uint32_t msglen,
                            const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_aes_cbc_encrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

int crypto_aes_cbc_decrypt (const uint8_t *message, const uint32_t msglen,
                            const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_aes_cbc_decrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

// AES-CTR
int crypto_aes_ctr_init (const uint8_t *key, const uint32_t keylen){
    int ret;

    ret = rtl_crypto_aes_ctr_init(key, keylen);
    return ret;
}

int crypto_aes_ctr_encrypt (const uint8_t *message, const uint32_t msglen,
                            const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_aes_ctr_encrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

int crypto_aes_ctr_decrypt (const uint8_t *message, const uint32_t msglen,
                            const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_aes_ctr_decrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

// AES-CFB
int crypto_aes_cfb_init (const uint8_t *key, const uint32_t keylen){
    int ret;

    ret = rtl_crypto_aes_cfb_init(key, keylen);
    return ret;
}

int crypto_aes_cfb_encrypt (const uint8_t *message, const uint32_t msglen,
                            const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_aes_cfb_encrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

int crypto_aes_cfb_decrypt (const uint8_t *message, const uint32_t msglen,
                            const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_aes_cfb_decrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

// AES-OFB
int crypto_aes_ofb_init (const uint8_t *key, const uint32_t keylen){
    int ret;

    ret = rtl_crypto_aes_ofb_init(key, keylen);
    return ret;
}

int crypto_aes_ofb_encrypt (const uint8_t *message, const uint32_t msglen,
                            const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_aes_ofb_encrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

int crypto_aes_ofb_decrypt (const uint8_t *message, const uint32_t msglen,
                            const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_aes_ofb_decrypt(message, msglen, iv, ivlen, pResult);
    return ret;
}

// AES-GCM
int crypto_aes_gcm_init (const uint8_t *key, const uint32_t keylen){
    int ret;

    ret = rtl_crypto_aes_gcm_init(key, keylen);
    return ret;
}

int crypto_aes_gcm_encrypt (const uint8_t *message, const uint32_t msglen, const uint8_t *iv,
                            const uint8_t *aad, const uint32_t aadlen, uint8_t *pResult, uint8_t *pTag)
{
    int ret;

    ret = rtl_crypto_aes_gcm_encrypt(message, msglen, iv, aad, aadlen, pResult, pTag);
    return ret;
}

int crypto_aes_gcm_decrypt (const uint8_t *message, const uint32_t msglen, const uint8_t *iv,
                            const uint8_t *aad, const uint32_t aadlen, uint8_t *pResult, uint8_t *pTag)
{
    int ret;

    ret = rtl_crypto_aes_gcm_decrypt(message, msglen, iv, aad, aadlen, pResult, pTag);
    return ret;
}

// CHACHA20
int crypto_chacha_init (const uint8_t *key){
    int ret;

    ret = rtl_crypto_chacha_init(key);
    return ret;
}

int crypto_chacha_encrypt (const uint8_t *message, const uint32_t msglen,
                           const uint8_t *iv, const uint32_t count, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_chacha_encrypt(message, msglen, iv, count, pResult);
    return ret;
}

int crypto_chacha_decrypt (const uint8_t *message, const uint32_t msglen,
                           const uint8_t *iv, const uint32_t count, uint8_t *pResult)
{
    int ret;

    ret = rtl_crypto_chacha_decrypt(message, msglen, iv, count, pResult);
    return ret;
}

// POLY1305
int crypto_poly1305(const uint8_t *message, const uint32_t msglen, const uint8_t *key, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_poly1305(message, msglen, key, pDigest);
    return ret;
}

int crypto_poly1305_init(const uint8_t *key)
{
    int ret;

    ret = rtl_crypto_poly1305_init(key);
    return ret;
}

int crypto_poly1305_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
    int ret;

    ret = rtl_crypto_poly1305_process(message, msglen, pDigest);
    return ret;
}

// CHACHA+POLY1305
int crypto_chacha_poly1305_init (const uint8_t *key){
    int ret;

    ret = rtl_crypto_chacha_poly1305_init(key);
    return ret;
}

int crypto_chacha_poly1305_encrypt (const uint8_t *message, const uint32_t msglen, const uint8_t *nonce,
                                    const uint8_t *aad, const uint32_t aadlen, uint8_t *pResult, uint8_t *pTag)
{
    int ret;

    ret = rtl_crypto_chacha_poly1305_encrypt(message, msglen, nonce, aad, aadlen, pResult, pTag);
    return ret;
}

int crypto_chacha_poly1305_decrypt (const uint8_t *message, const uint32_t msglen, const uint8_t *nonce,
                                    const uint8_t *aad, const uint32_t aadlen, uint8_t *pResult, uint8_t *pTag)
{
    int ret;

    ret = rtl_crypto_chacha_poly1305_decrypt(message, msglen, nonce, aad, aadlen, pResult, pTag);
    return ret;
}

// crc
int crypto_crc32_cmd(const uint8_t *message, const uint32_t msglen, uint32_t *pCrc)
{
    int ret;

    ret = rtl_crypto_crc32_cmd(message, msglen, pCrc);
    return ret;
}

int crypto_crc32_dma(const uint8_t *message, const uint32_t msglen, uint32_t *pCrc)
{
    int ret;

    ret = rtl_crypto_crc32_dma(message, msglen, pCrc);
    return ret;
}

int crypto_crc_setting(int order, unsigned long polynom, unsigned long crcinit,
                       unsigned long crcxor, int refin, int refout)
{
    int ret;

    ret = rtl_crypto_crc_setting(order, polynom, crcinit, crcxor, refin, refout);
    return ret;
}

int crypto_crc_cmd(const uint8_t *message, const uint32_t msglen, uint32_t *pCrc)
{
    int ret;

    ret = rtl_crypto_crc_cmd( message, msglen, pCrc);
    return ret;
}

int crypto_crc_dma(const uint8_t *message, const uint32_t msglen, uint32_t *pCrc)
{
    int ret;

    ret = rtl_crypto_crc_dma( message, msglen, pCrc);
    return ret;
}



#ifdef  __cplusplus
}
#endif

#endif
