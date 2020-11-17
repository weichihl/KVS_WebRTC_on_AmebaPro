/**************************************************************************//**
 * @file     rtl8195bhp_crypto_ctrl.h
 * @brief    This file defines adapter,rom stubs structure and other related common MACRO_VARs for CRYPTO.
 * @version  v1.00
 * @date     2017/12/11
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

/**
 * @addtogroup hs_hal_crypto CRYPTO
 * @ingroup 8195bh_hal
 * @{
 */

#ifndef RTL8195BHP_CRYPTO_CTRL_H
#define RTL8195BHP_CRYPTO_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

#define SOMEONE_INIT_DEINIT_REG_FAIL       (-30)

/* Macros for hp crypto module general configuration */
#define CRYPTO_MAX_DIGEST_LENGTH	32  // SHA256 Digest length : 32
#define CRYPTO_MAX_KEY_LENGTH		32  // MAX  is  AES-256 : 32 byte,  3DES : 24 byte
#define CRYPTO_AUTH_PADDING         64  // HMAC key maximum size is 64 bytes
#define CRYPTO_PADSIZE 				64

// Mode Select
#define CRYPTO_MS_TYPE_CIPHER	    (0)
#define CRYPTO_MS_TYPE_AUTH         (1)
#define CRYPTO_MS_TYPE_MIX  	    (2)

//HASH Type
/* Macros for hp crypto module hash type configuration */

// HASH General
/* Macros for hp crypto module hash type general configuration */
#define AUTH_TYPE_NO_AUTH 		    ((u32)-1)

#define AUTH_TYPE_MASK_FUNC		    0x3	// bit 0, bit 1
#define AUTH_TYPE_MD5			    0x2
#define AUTH_TYPE_SHA1			    0x0
#define AUTH_TYPE_SHA2			    0x1

#define AUTH_TYPE_MASK_HMAC 	    0x4	// bit 2
#define AUTH_TYPE_HMAC_MD5 		    (AUTH_TYPE_MD5 | AUTH_TYPE_MASK_HMAC)
#define AUTH_TYPE_HMAC_SHA1 	    (AUTH_TYPE_SHA1 | AUTH_TYPE_MASK_HMAC)
#define AUTH_TYPE_HMAC_SHA2 	    (AUTH_TYPE_SHA2 | AUTH_TYPE_MASK_HMAC)

#define AUTH_TYPE_MASK_FUNC_ALL		(AUTH_TYPE_MASK_FUNC| AUTH_TYPE_MASK_HMAC)

#define CRYPTO_MD5_DIGEST_LENGTH 	16
#define CRYPTO_SHA1_DIGEST_LENGTH 	20
#define CRYPTO_SHA2_DIGEST_LENGTH 	32

// SHA2
/* Macros for hp crypto module general hash type sha2 configuration */
#define AUTH_TYPE_MASK_SHA2 	    0x30 // bit 3,4
#define AUTH_TYPE_SHA2_224	        0x10
#define AUTH_TYPE_SHA2_256  	    0x20

#define AUTH_TYPE_SHA2_224_ALL      (AUTH_TYPE_SHA2_224|AUTH_TYPE_SHA2)
#define AUTH_TYPE_SHA2_256_ALL      (AUTH_TYPE_SHA2_256|AUTH_TYPE_SHA2)
#define AUTH_TYPE_HMAC_SHA2_224_ALL (AUTH_TYPE_SHA2_224|AUTH_TYPE_HMAC_SHA2)
#define AUTH_TYPE_HMAC_SHA2_256_ALL (AUTH_TYPE_SHA2_256|AUTH_TYPE_HMAC_SHA2)

#define SHA2_NONE	                0
#define SHA2_224	                (224/8)
#define SHA2_256	                (256/8)
#define SHA2_384	                (384/8)
#define SHA2_512	                (512/8)

// Cipher Type
/* Macros for hp crypto module cipher type configuration */
#define CIPHER_TYPE_NO_CIPHER 		((u32)-1)

#define CIPHER_TYPE_MODE_ENCRYPT 	0x80

#define CIPHER_TYPE_MASK_ALL 		0x3F
#define CIPHER_TYPE_MASK_FUNC 		0x30 	// 0x00 : DES, 0x10: 3DES, 0x20: AES
#define CIPHER_TYPE_FUNC_DES		0x00
#define CIPHER_TYPE_FUNC_3DES 		0x10
#define CIPHER_TYPE_FUNC_AES 		0x20
#define CIPHER_TYPE_FUNC_CHACHA 	0x30    //Including(chaha_poly1305,chacha20,poly1305)

#define CIPHER_TYPE_FUNC_CHACHA_POLY1305	0x30
#define CIPHER_TYPE_FUNC_CHACHA20	        0x31

#define CIPHER_TYPE_MASK_BLOCK 		0xF   // 0x0:ECB, 0x1:CBC, 0x2:CFB , 0x3:OFB , 0x4:CTR, 0x5:GCTR, 0x6:GMAC, 0x7:GHASH, 0x8:GCM
#define CIPHER_TYPE_BLOCK_ECB 		0x0
#define CIPHER_TYPE_BLOCK_CBC 		0x1
#define CIPHER_TYPE_BLOCK_CFB 		0x2
#define CIPHER_TYPE_BLOCK_OFB 		0x3
#define CIPHER_TYPE_BLOCK_CTR 		0x4
#define CIPHER_TYPE_BLOCK_GCTR 		0x5
#define CIPHER_TYPE_BLOCK_GMAC 		0x6
#define CIPHER_TYPE_BLOCK_GHASH 	0x7
#define CIPHER_TYPE_BLOCK_GCM 		0x8

#define CIPHER_TYPE_BLOCK_CHACHA 	0x1
#define CIPHER_TYPE_BLOCK_CHACHA_POLY1305 	0x0

/* Data Struct for hp crypto adapter */
/**
 *  \brief Define data struct for hp crypto adapter.
 */
typedef struct hal_crypto_adapter_s {

    uint8_t     isInit;         //!< Crypto engine init state: 1=Init, 0=Not init
    uint8_t     isIntMode;      //!< Crypto engine interrupt mode state: 1=Active, 0=Inactive
    uint8_t     isMemDump;      //!< Crypto memory dump control state: 1=Enable, 0=Disable. related \ref __dbg_mem_dump

    //uint8_t dma_burst_num; // 0 ~ 32
    //uint8_t desc_num;  // total number of source/destination description
    //uint8_t mode_select;
    uint8_t     initmap;
    uint8_t     reserved1[1];   //!<  Reserve

    uint32_t    cipher_type;    //!<  Cipher_type ID
	uint8_t     des;            //!<  DES state: 1=Active, 0=Inactive
	uint8_t     trides;         //!<  3DES state: 1=Active, 0=Inactive
	uint8_t     aes;            //!<  AES state: 1=Active, 0=Inactive
	uint8_t     chacha;         //!<  Chacha(including poly1305) state: 1=Active, 0=Inactive
	uint8_t     isDecrypt;      //!<  Decryption state: 1=Enable, 0=Disable
    uint8_t     reserved2[3];   //!<  Reserve

    uint32_t    auth_type;      //!<  Hash_type ID
    uint8_t     isHMAC;         //!<  HMAC state: 1=Active, 0=Inactive
    uint8_t     isMD5;          //!<  MD5 state: 1=Active, 0=Inactive
	uint8_t     isSHA1;         //!<  SHA1 state: 1=Active, 0=Inactive
	uint8_t     isSHA2;         //!<  SHA2 state: 1=Active, 0=Inactive

    /**
     * Sha2_type ID: 0=None of this mode of sha2, 28=sha2_224 mode(output size is 28bytes),
     * 32=sha2_256 mode(output size is 32bytes)
     */
	uint8_t     sha2type;       //!< Sha2_type ID
    uint8_t     reserved3[3];   //!<  Reserve

	// hash
	uint32_t    enc_last_data_size;     //!<  Encrypted message of last data size
	uint32_t    aad_last_data_size;     //!<  Additional authenticated data of last data size

    uint32_t    lenAuthKey;     //!<  Key length of authenticated hash
    const uint8_t *pAuthKey;   //!<  Pointer to variable that points the key address of authenticated hash
	uint32_t    digestlen;      //!<  Digest length of hash

	// sequential hash
	uint8_t     hmac_seq_hash_first;    //!<  Sequential hash first one state:  1=Active, 0=Inactive
	uint8_t     hmac_seq_hash_last;     //!<  Sequential hash last one state: 1=Active, 0=Inactive
    uint8_t     hmac_seq_is_recorded;   //!<  Recording a sequential hash: 1=Active, 0=Inactive
    uint8_t     hmac_seq_buf_is_used_bytes;     //!<  Recorded data size in sequential hash buffer
	uint32_t    hmac_seq_hash_total_len;        //!<  Total data length of sequential hash
    uint32_t    hmac_seq_last_msglen;   //!<  Last message length of sequential hash
    uint8_t     *hmac_seq_last_message; //!<  Pointer to variable that points the last message address of sequential hash

    uint32_t 	        lenCipherKey;   //!<  Key length of Cipher
    const uint8_t *pCipherKey;     //!<  Pointer to variable that points the key address of cipher

	uint32_t    a2eo;           //!<  Additional authenticated data length
    uint32_t    apl_aad;        //!<  Padding length of additional authenticated data
    uint32_t    enl;            //!<  Crypto message length
    uint32_t    apl;            //!<  Padding length of crypto message

    uint8_t     *ipad;          //!<  Pointer to variable that points the inner padding data address of HMAC
    uint8_t     *opad;          //!<  Pointer to variable that points the outer padding data address of HMAC
    // crc
    int32_t     crc_order;      //!<  Cyclic redundancy check order

    //read_crc_setting used
    uint32_t    crc_sel;        //!<  Register value of cyclic redundancy check order
    uint32_t    crc_oswap;      //!<  Register value of cyclic redundancy check refout
    uint32_t    crc_iswap;      //!<  Register value of cyclic redundancy check refin
    uint32_t    crc_oxor;       //!<  Register value of cyclic redundancy check xor
    uint32_t    crc_init;       //!<  Register value of cyclic redundancy check init
    uint32_t    crc_poly;       //!<  Register value of cyclic redundancy check polynomial

    // cache
    uint8_t     is_dst_first_cache_used;    //!<  Destination descriptor that used first cache line: 1=Active, 0=Inactive
    uint8_t     is_dst_last_cache_used;     //!<  Destination descriptor that used last cache line: 1=Active, 0=Inactive
    uint8_t     reserved4[2];   //!<  Reserve

    /**
     * 32 bytes aligned buffer that store inner and outer padding data
     */
    volatile uint8_t g_IOPAD[CRYPTO_PADSIZE*2+32] __attribute__((aligned(32)));

    /**
     * 32 bytes aligned buffer that store initial vector for AES_GCM/Chacha20/Chacha_poly1305
     */
    volatile uint8_t  gcm_iv[32] __attribute__((aligned(32)));

    /**
     * 32 bytes aligned buffer that store command register data of source descriptor
     */
    volatile uint8_t  cl_buffer[32] __attribute__((aligned(32)));
    //volatile uint8_t  digest_data[32] __attribute__((aligned(32)));
    /**
     * 32 bytes aligned buffer that store digest result of Hash
     */
    volatile uint8_t  digest_result[32] __attribute__((aligned(32)));

    /**
     * 32 bytes aligned buffer that store tag result of HMAC
     */
    volatile uint8_t  tag_result[32] __attribute__((aligned(32)));

    /**
     * 32 bytes aligned buffer that store first cache line of source descriptor
     */
    volatile uint8_t  src_first_cache_line[32] __attribute__((aligned(32)));

    /**
     * 32 bytes aligned buffer that store last cache line of source descriptor
     */
    volatile uint8_t  src_last_cache_line[32] __attribute__((aligned(32)));

    /**
     * 32 bytes aligned buffer that store first cache line of destination descriptor
     */
    volatile uint8_t  dst_first_cache_line[32] __attribute__((aligned(32)));

    /**
     * 32 bytes aligned buffer that store last cache line of destination descriptor
     */
    volatile uint8_t  dst_last_cache_line[32] __attribute__((aligned(32)));

    /**
     * 32 bytes aligned buffer that store 64 bytes sequential buffer data of Hash
     */
    volatile uint8_t  hmac_seq_buf[64] __attribute__((aligned(32)));

    /**
     * 32 bytes aligned buffer that store first cache line of crc_dma modeh
     */
    volatile uint8_t  crc_first_cache_line[32] __attribute__((aligned(32)));

    /**
     * Callback function pointer : Clean D-cache.
     */
    void (*arch_clean_dcache_by_size)(uint32_t start_address, int32_t size);

    /**
     * Callback function pointer : Invalidate D-cache.
     */
    void (*arch_invalidate_dcache_by_size)(uint32_t start_address, int32_t size);

    /**
     * Callback function pointer : Wait available fifo nodes of source descriptor.
     */
    int (*fifo_wait_func)(void *pIE1);

    /**
     * Callback function pointer to \ref g_crypto_pre_exec : Initialize the notified mechanism.
     */
    int (*pre_exec_func)(void *pIE1);

    /**
     * Callback function pointer to \ref g_crypto_wait_done : Wait to be notified after
     * interrupt service routine processed over.
     */
    int (*wait_done_func)(void *pIE1);

    /**
     * 64 bytes aligned buffer that store padding value
     */
    volatile uint8_t  padding[64] __attribute__((aligned(64)));

} hal_crypto_adapter_t, *phal_crypto_adapter_t ;

//
// stub
//

/**
 *   \brief  The data structure of the stubs functions of the Crypto HAL functions in ROM
 *
 */
typedef struct {
    void (*rtl_cryptoEngine_platform_en_ctrl) (int);
    uint32_t reserved[10];  // reserved space for next ROM code version function table extending.
    
} hal_crypto_func_ext_stubs_t;

typedef struct {
    //void *gadapter;
    int (*rtl_cryptoEngine_init) (void *);
    int (*rtl_cryptoEngine_deinit) (void *);

// MD5
    int (*rtl_crypto_md5)(
		IN const u8 *message, IN const u32 msglen,
		OUT u8 *pDigest);
    int (*rtl_crypto_md5_init) (void);
    int (*rtl_crypto_md5_process) (
        IN const u8 *message, IN const u32 msglen,
        OUT u8 *pDigest);
    int (*rtl_crypto_md5_update) (
        IN const u8 *message, IN const u32 msglen);
    int (*rtl_crypto_md5_final) (OUT u8 *pDigest);

// SHA1
    int (*rtl_crypto_sha1)(
		IN const u8 *message, IN const u32 msglen,
		OUT u8 *pDigest);
    int (*rtl_crypto_sha1_init) (void);
    int (*rtl_crypto_sha1_process) (
        IN const u8 *message, IN const u32 msglen,
        OUT u8 *pDigest);
    int (*rtl_crypto_sha1_update) (
        IN const u8 *message, IN const u32 msglen);
    int (*rtl_crypto_sha1_final) (OUT u8 *pDigest);

// SHA2
    // 224
    int (*rtl_crypto_sha2_224)(
		IN const u8 *message, IN const u32 msglen,
		OUT u8 *pDigest);
    int (*rtl_crypto_sha2_224_init) (void);
    int (*rtl_crypto_sha2_224_process) (
        IN const u8 *message, IN const u32 msglen,
        OUT u8 *pDigest);
    int (*rtl_crypto_sha2_224_update) (
        IN const u8 *message, IN const u32 msglen);
    int (*rtl_crypto_sha2_224_final) (OUT u8 *pDigest);

    // 256
    int (*rtl_crypto_sha2_256)(
		IN const u8 *message, IN const u32 msglen,
		OUT u8 *pDigest);
    int (*rtl_crypto_sha2_256_init) (void);
    int (*rtl_crypto_sha2_256_process) (
        IN const u8 *message, IN const u32 msglen,
        OUT u8 *pDigest);
    int (*rtl_crypto_sha2_256_update) (
        IN const u8 *message, IN const u32 msglen);
    int (*rtl_crypto_sha2_256_final) (OUT u8 *pDigest);

// HMAC-MD5
    int (*rtl_crypto_hmac_md5)(
		IN const u8 *message, IN const u32 msglen,
        IN const u8 *key, IN const u32 keylen,
		OUT u8 *pDigest);
    int (*rtl_crypto_hmac_md5_init) (IN const u8 *key, IN const u32 keylen);
    int (*rtl_crypto_hmac_md5_process) (
        IN const u8 *message, IN const u32 msglen,
        OUT u8 *pDigest);
    int (*rtl_crypto_hmac_md5_update) (
        IN const u8 *message, IN const u32 msglen);
    int (*rtl_crypto_hmac_md5_final) (OUT u8 *pDigest);

// HMAC-SHA1
    int (*rtl_crypto_hmac_sha1)(
		IN const u8 *message, IN const u32 msglen,
        IN const u8 *key, IN const u32 keylen,
		OUT u8 *pDigest);

    int (*rtl_crypto_hmac_sha1_init) (IN const u8 *key, IN const u32 keylen);

    int (*rtl_crypto_hmac_sha1_process) (
        IN const u8 *message, IN const u32 msglen,
        OUT u8 *pDigest);

	int (*rtl_crypto_hmac_sha1_update) (
        IN const u8 *message, IN const u32 msglen);

	int (*rtl_crypto_hmac_sha1_final) (OUT u8 *pDigest);

// HMAC-SHA2
//   -- 224
    int (*rtl_crypto_hmac_sha2_224)(
		IN const u8 *message, IN const u32 msglen,
        IN const u8 *key, IN const u32 keylen,
		OUT u8 *pDigest);

    int (*rtl_crypto_hmac_sha2_224_init) (IN const u8 *key, IN const u32 keylen);

    int (*rtl_crypto_hmac_sha2_224_process) (

        IN const u8 *message, IN const u32 msglen,
        OUT u8 *pDigest);

    int (*rtl_crypto_hmac_sha2_224_update) (
        IN const u8 *message, IN const u32 msglen);

    int (*rtl_crypto_hmac_sha2_224_final) (OUT u8 *pDigest);
//   -- 256
    int (*rtl_crypto_hmac_sha2_256)(
		IN const u8 *message, IN const u32 msglen,
        IN const u8 *key, IN const u32 keylen,
		OUT u8 *pDigest);

    int (*rtl_crypto_hmac_sha2_256_init) (IN const u8 *key, IN const u32 keylen);

    int (*rtl_crypto_hmac_sha2_256_process) (
        IN const u8 *message, IN const u32 msglen,
        OUT u8 *pDigest);

    int (*rtl_crypto_hmac_sha2_256_update) (
        IN const u8 *message, IN const u32 msglen);

    int (*rtl_crypto_hmac_sha2_256_final) (OUT u8 *pDigest);

// DES-CBC

    int (*rtl_crypto_des_cbc_init) (
	IN const u8 *key, IN const u32 keylen);

    int (*rtl_crypto_des_cbc_encrypt) (
		IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);

    int (*rtl_crypto_des_cbc_decrypt) (
		IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);

// DES-ECB

    int (*rtl_crypto_des_ecb_init) (
		IN const u8 *key, IN const u32 keylen);

    int (*rtl_crypto_des_ecb_encrypt) (
	IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);

    int (*rtl_crypto_des_ecb_decrypt) (
	IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);

// 3DES-CBC

    int (*rtl_crypto_3des_cbc_init) (
		IN const u8 *key, IN const u32 keylen);

    int (*rtl_crypto_3des_cbc_encrypt) (
	IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);

    int (*rtl_crypto_3des_cbc_decrypt) (
	IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);

// 3DES-ECB

    int (*rtl_crypto_3des_ecb_init) (
		IN const u8 *key, IN const u32 keylen);

    int (*rtl_crypto_3des_ecb_encrypt) (
	IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);

    int (*rtl_crypto_3des_ecb_decrypt) (
	IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);

// AES-CBC

    int (*rtl_crypto_aes_cbc_init) (
		IN const u8 *key, IN const u32 keylen);

    int (*rtl_crypto_aes_cbc_encrypt) (
	IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);

    int (*rtl_crypto_aes_cbc_decrypt) (
	IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);

// AES-ECB

    int (*rtl_crypto_aes_ecb_init) (
		IN const u8 *key, IN const u32 keylen);

    int (*rtl_crypto_aes_ecb_encrypt) (
	IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);

    int (*rtl_crypto_aes_ecb_decrypt) (
	IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);


// AES-CTR

    int (*rtl_crypto_aes_ctr_init) (
		IN const u8 *key, IN const u32 keylen);

    int (*rtl_crypto_aes_ctr_encrypt) (
		IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);

    int (*rtl_crypto_aes_ctr_decrypt) (
	IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);


// AES-CFB

    int (*rtl_crypto_aes_cfb_init) (
		IN const u8 *key, IN const u32 keylen);

    int (*rtl_crypto_aes_cfb_encrypt) (
		IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);

    int (*rtl_crypto_aes_cfb_decrypt) (
		IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);


// AES-OFB

    int (*rtl_crypto_aes_ofb_init) (
		IN const u8 *key, IN const u32 keylen);

    int (*rtl_crypto_aes_ofb_encrypt) (
		IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);

    int (*rtl_crypto_aes_ofb_decrypt) (
		IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv, IN const u32 ivlen,
        OUT u8 *pResult);


// AES-GCM

    int (*rtl_crypto_aes_gcm_init) (
		IN const u8 *key, IN const u32 keylen);

    int (*rtl_crypto_aes_gcm_encrypt) (
		IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv,
        IN const u8 *aad, IN const u32 aadlen,
        OUT u8 *pResult, OUT u8 *pTag);

    int (*rtl_crypto_aes_gcm_decrypt) (
		IN const u8 *message, IN const u32 msglen,
        IN const u8 *iv,
        IN const u8 *aad, IN const u32 aadlen,
        OUT u8 *pResult, OUT u8 *pTag);

	// CHACHA
    int (*rtl_crypto_chacha_init) (
		IN const u8 *key);

    int (*rtl_crypto_chacha_encrypt)(
		IN const u8 *message, IN const u32 msglen,
		IN const u8 *iv, IN const u32 count,
		OUT u8 *pResult);

    int (*rtl_crypto_chacha_decrypt)(
		IN const u8 *message, IN const u32 msglen,
		IN const u8 *iv, IN const u32 count,
		OUT u8 *pResult);

	// POLY1305
    int (*rtl_crypto_poly1305) (
		IN const u8 *message, IN const u32 msglen,
		IN const u8 *key,
		OUT u8 *pDigest);

    int (*rtl_crypto_poly1305_init) (
		IN const u8 *key);

    int (*rtl_crypto_poly1305_process) (
		IN const u8 *message, IN const u32 msglen,
		OUT u8 *pDigest);

// CHACHA+POLY1305

    int (*rtl_crypto_chacha_poly1305_init) (
	IN const u8 *key);

    int (*rtl_crypto_chacha_poly1305_encrypt)(
	IN const u8 *message, IN const u32 msglen,
	IN const u8 *nonce,
	IN const u8 *aad, IN const u32 aadlen,
	OUT u8 *pResult, OUT u8 *pTag);

    int (*rtl_crypto_chacha_poly1305_decrypt)(
	IN const u8 *message, IN const u32 msglen,
	IN const u8 *iv,
	IN const u8 *aad, IN const u32 aadlen,
	OUT u8 *pResult, OUT u8 *pTag);

// CRC
	int (*rtl_crypto_crc_setting)(
	    IN int order, IN uint32_t polynom,
	    IN uint32_t crcinit, IN uint32_t crcxor, IN uint32_t refin, IN uint32_t refout);

    int (*rtl_crypto_crc_cmd)(
    	IN const u8 *message,	IN const uint32_t msglen);

    int (*rtl_crypto_crc_dma)(
    	IN const u8 *message,	IN const uint32_t msglen);

	uint32_t  (*rtl_crypto_crc_get_result)(void);

    int (*rtl_crypto_crc32_cmd)(
            IN const u8 *message,   IN const uint32_t msglen);

    int (*rtl_crypto_crc32_dma)(
            IN const u8 *message,   IN const uint32_t msglen);

} hal_crypto_func_stubs_t;


#ifdef __cplusplus
}
#endif

#endif /* RTL8195BHP_CRYPTO_CTRL_H */

/** @} */ /* End of group hs_hal_crypto */

