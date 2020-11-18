/**
 * \file bignum.h
 *
 * \brief Multi-precision integer library
 */
/*
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */
#ifndef MBEDTLS_BIGNUM_ROM_H
#define MBEDTLS_BIGNUM_ROM_H

#include "mbedtls/bignum.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief           Initialize an MPI context.
 *
 *                  This makes the MPI ready to be set or freed,
 *                  but does not define a value for the MPI.
 *
 * \param X         The MPI context to initialize. This must not be \c NULL.
 */
void _mbedtls_mpi_init( mbedtls_mpi *X );

/**
 * \brief          This function frees the components of an MPI context.
 *
 * \param X        The MPI context to be cleared. This may be \c NULL,
 *                 in which case this function is a no-op. If it is
 *                 not \c NULL, it must point to an initialized MPI.
 */
void _mbedtls_mpi_free( mbedtls_mpi *X );

/**
 * \brief          Enlarge an MPI to the specified number of limbs.
 *
 * \note           This function does nothing if the MPI is
 *                 already large enough.
 *
 * \param X        The MPI to grow. It must be initialized.
 * \param nblimbs  The target number of limbs.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if memory allocation failed.
 * \return         Another negative error code on other kinds of failure.
 */
int _mbedtls_mpi_grow( mbedtls_mpi *X, size_t nblimbs );

/**
 * \brief          This function resizes an MPI downwards, keeping at least the
 *                 specified number of limbs.
 *
 *                 If \c X is smaller than \c nblimbs, it is resized up
 *                 instead.
 *
 * \param X        The MPI to shrink. This must point to an initialized MPI.
 * \param nblimbs  The minimum number of limbs to keep.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if memory allocation failed
 *                 (this can only happen when resizing up).
 * \return         Another negative error code on other kinds of failure.
 */
int _mbedtls_mpi_shrink( mbedtls_mpi *X, size_t nblimbs );

/**
 * \brief          Make a copy of an MPI.
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param Y        The source MPI. This must point to an initialized MPI.
 *
 * \note           The limb-buffer in the destination MPI is enlarged
 *                 if necessary to hold the value in the source MPI.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if memory allocation failed.
 * \return         Another negative error code on other kinds of failure.
 */
int _mbedtls_mpi_copy( mbedtls_mpi *X, const mbedtls_mpi *Y );

/**
 * \brief          Swap the contents of two MPIs.
 *
 * \param X        The first MPI. It must be initialized.
 * \param Y        The second MPI. It must be initialized.
 */
void _mbedtls_mpi_swap( mbedtls_mpi *X, mbedtls_mpi *Y );

/**
 * \brief          Perform a safe conditional copy of MPI which doesn't
 *                 reveal whether the condition was true or not.
 *
 * \param X        The MPI to conditionally assign to. This must point
 *                 to an initialized MPI.
 * \param Y        The MPI to be assigned from. This must point to an
 *                 initialized MPI.
 * \param assign   The condition deciding whether to perform the
 *                 assignment or not. Possible values:
 *                 * \c 1: Perform the assignment `X = Y`.
 *                 * \c 0: Keep the original value of \p X.
 *
 * \note           This function is equivalent to
 *                      `if( assign ) mbedtls_mpi_copy( X, Y );`
 *                 except that it avoids leaking any information about whether
 *                 the assignment was done or not (the above code may leak
 *                 information through branch prediction and/or memory access
 *                 patterns analysis).
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if memory allocation failed.
 * \return         Another negative error code on other kinds of failure.
 */
int _mbedtls_mpi_safe_cond_assign( mbedtls_mpi *X, const mbedtls_mpi *Y, unsigned char assign );

/**
 * \brief          Perform a safe conditional swap which doesn't
 *                 reveal whether the condition was true or not.
 *
 * \param X        The first MPI. This must be initialized.
 * \param Y        The second MPI. This must be initialized.
 * \param assign   The condition deciding whether to perform
 *                 the swap or not. Possible values:
 *                 * \c 1: Swap the values of \p X and \p Y.
 *                 * \c 0: Keep the original values of \p X and \p Y.
 *
 * \note           This function is equivalent to
 *                      if( assign ) mbedtls_mpi_swap( X, Y );
 *                 except that it avoids leaking any information about whether
 *                 the assignment was done or not (the above code may leak
 *                 information through branch prediction and/or memory access
 *                 patterns analysis).
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if memory allocation failed.
 * \return         Another negative error code on other kinds of failure.
 *
 */
int _mbedtls_mpi_safe_cond_swap( mbedtls_mpi *X, mbedtls_mpi *Y, unsigned char assign );

/**
 * \brief          Store integer value in MPI.
 *
 * \param X        The MPI to set. This must be initialized.
 * \param z        The value to use.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if memory allocation failed.
 * \return         Another negative error code on other kinds of failure.
 */
int _mbedtls_mpi_lset( mbedtls_mpi *X, mbedtls_mpi_sint z );

/**
 * \brief          Get a specific bit from an MPI.
 *
 * \param X        The MPI to query. This must be initialized.
 * \param pos      Zero-based index of the bit to query.
 *
 * \return         \c 0 or \c 1 on success, depending on whether bit \c pos
 *                 of \c X is unset or set.
 * \return         A negative error code on failure.
 */
int _mbedtls_mpi_get_bit( const mbedtls_mpi *X, size_t pos );

/**
 * \brief          Modify a specific bit in an MPI.
 *
 * \note           This function will grow the target MPI if necessary to set a
 *                 bit to \c 1 in a not yet existing limb. It will not grow if
 *                 the bit should be set to \c 0.
 *
 * \param X        The MPI to modify. This must be initialized.
 * \param pos      Zero-based index of the bit to modify.
 * \param val      The desired value of bit \c pos: \c 0 or \c 1.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if memory allocation failed.
 * \return         Another negative error code on other kinds of failure.
 */
int _mbedtls_mpi_set_bit( mbedtls_mpi *X, size_t pos, unsigned char val );

/**
 * \brief          Return the number of bits of value \c 0 before the
 *                 least significant bit of value \c 1.
 *
 * \note           This is the same as the zero-based index of
 *                 the least significant bit of value \c 1.
 *
 * \param X        The MPI to query.
 *
 * \return         The number of bits of value \c 0 before the least significant
 *                 bit of value \c 1 in \p X.
 */
size_t _mbedtls_mpi_lsb( const mbedtls_mpi *X );

/**
 * \brief          Return the number of bits up to and including the most
 *                 significant bit of value \c 1.
 *
 * * \note         This is same as the one-based index of the most
 *                 significant bit of value \c 1.
 *
 * \param X        The MPI to query. This must point to an initialized MPI.
 *
 * \return         The number of bits up to and including the most
 *                 significant bit of value \c 1.
 */
size_t _mbedtls_mpi_bitlen( const mbedtls_mpi *X );

/**
 * \brief          Return the total size of an MPI value in bytes.
 *
 * \param X        The MPI to use. This must point to an initialized MPI.
 *
 * \note           The value returned by this function may be less than
 *                 the number of bytes used to store \p X internally.
 *                 This happens if and only if there are trailing bytes
 *                 of value zero.
 *
 * \return         The least number of bytes capable of storing
 *                 the absolute value of \p X.
 */
size_t _mbedtls_mpi_size( const mbedtls_mpi *X );

/**
 * \brief          Import an MPI from an ASCII string.
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param radix    The numeric base of the input string.
 * \param s        Null-terminated string buffer.
 *
 * \return         \c 0 if successful.
 * \return         A negative error code on failure.
 */
int _mbedtls_mpi_read_string( mbedtls_mpi *X, int radix, const char *s );

/**
 * \brief          Export an MPI to an ASCII string.
 *
 * \param X        The source MPI. This must point to an initialized MPI.
 * \param radix    The numeric base of the output string.
 * \param buf      The buffer to write the string to. This must be writable
 *                 buffer of length \p buflen Bytes.
 * \param buflen   The available size in Bytes of \p buf.
 * \param olen     The address at which to store the length of the string
 *                 written, including the  final \c NULL byte. This must
 *                 not be \c NULL.
 *
 * \note           You can call this function with `buflen == 0` to obtain the
 *                 minimum required buffer size in `*olen`.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL if the target buffer \p buf
 *                 is too small to hold the value of \p X in the desired base.
 *                 In this case, `*olen` is nonetheless updated to contain the
 *                 size of \p buf required for a successful call.
 * \return         Another negative error code on different kinds of failure.
 */
int _mbedtls_mpi_write_string( const mbedtls_mpi *X, int radix,
                              char *buf, size_t buflen, size_t *olen );

#if defined(MBEDTLS_FS_IO)
/**
 * \brief          Read an MPI from a line in an opened file.
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param radix    The numeric base of the string representation used
 *                 in the source line.
 * \param fin      The input file handle to use. This must not be \c NULL.
 *
 * \note           On success, this function advances the file stream
 *                 to the end of the current line or to EOF.
 *
 *                 The function returns \c 0 on an empty line.
 *
 *                 Leading whitespaces are ignored, as is a
 *                 '0x' prefix for radix \c 16.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL if the file read buffer
 *                 is too small.
 * \return         Another negative error code on failure.
 */
int _mbedtls_mpi_read_file( mbedtls_mpi *X, int radix, FILE *fin );

/**
 * \brief          Export an MPI into an opened file.
 *
 * \param p        A string prefix to emit prior to the MPI data.
 *                 For example, this might be a label, or "0x" when
 *                 printing in base \c 16. This may be \c NULL if no prefix
 *                 is needed.
 * \param X        The source MPI. This must point to an initialized MPI.
 * \param radix    The numeric base to be used in the emitted string.
 * \param fout     The output file handle. This may be \c NULL, in which case
 *                 the output is written to \c stdout.
 *
 * \return         \c 0 if successful.
 * \return         A negative error code on failure.
 */
int _mbedtls_mpi_write_file( const char *p, const mbedtls_mpi *X,
                            int radix, FILE *fout );
#endif /* MBEDTLS_FS_IO */

/**
 * \brief          Import an MPI from unsigned big endian binary data.
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param buf      The input buffer. This must be a readable buffer of length
 *                 \p buflen Bytes.
 * \param buflen   The length of the input buffer \p p in Bytes.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if memory allocation failed.
 * \return         Another negative error code on different kinds of failure.
 */
int _mbedtls_mpi_read_binary( mbedtls_mpi *X, const unsigned char *buf,
                             size_t buflen );

/**
 * \brief          Export an MPI into unsigned big endian binary data
 *                 of fixed size.
 *
 * \param X        The source MPI. This must point to an initialized MPI.
 * \param buf      The output buffer. This must be a writable buffer of length
 *                 \p buflen Bytes.
 * \param buflen   The size of the output buffer \p buf in Bytes.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL if \p buf isn't
 *                 large enough to hold the value of \p X.
 * \return         Another negative error code on different kinds of failure.
 */
int _mbedtls_mpi_write_binary( const mbedtls_mpi *X, unsigned char *buf,
                              size_t buflen );

/**
 * \brief          Perform a left-shift on an MPI: X <<= count
 *
 * \param X        The MPI to shift. This must point to an initialized MPI.
 * \param count    The number of bits to shift by.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         Another negative error code on different kinds of failure.
 */
int _mbedtls_mpi_shift_l( mbedtls_mpi *X, size_t count );

/**
 * \brief          Perform a right-shift on an MPI: X >>= count
 *
 * \param X        The MPI to shift. This must point to an initialized MPI.
 * \param count    The number of bits to shift by.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         Another negative error code on different kinds of failure.
 */
int _mbedtls_mpi_shift_r( mbedtls_mpi *X, size_t count );

/**
 * \brief          Compare the absolute values of two MPIs.
 *
 * \param X        The left-hand MPI. This must point to an initialized MPI.
 * \param Y        The right-hand MPI. This must point to an initialized MPI.
 *
 * \return         \c 1 if `|X|` is greater than `|Y|`.
 * \return         \c -1 if `|X|` is lesser than `|Y|`.
 * \return         \c 0 if `|X|` is equal to `|Y|`.
 */
int _mbedtls_mpi_cmp_abs( const mbedtls_mpi *X, const mbedtls_mpi *Y );

/**
 * \brief          Compare two MPIs.
 *
 * \param X        The left-hand MPI. This must point to an initialized MPI.
 * \param Y        The right-hand MPI. This must point to an initialized MPI.
 *
 * \return         \c 1 if \p X is greater than \p Y.
 * \return         \c -1 if \p X is lesser than \p Y.
 * \return         \c 0 if \p X is equal to \p Y.
 */
int _mbedtls_mpi_cmp_mpi( const mbedtls_mpi *X, const mbedtls_mpi *Y );

/**
 * \brief          Check if an MPI is less than the other in constant time.
 *
 * \param X        The left-hand MPI. This must point to an initialized MPI
 *                 with the same allocated length as Y.
 * \param Y        The right-hand MPI. This must point to an initialized MPI
 *                 with the same allocated length as X.
 * \param ret      The result of the comparison:
 *                 \c 1 if \p X is less than \p Y.
 *                 \c 0 if \p X is greater than or equal to \p Y.
 *
 * \return         0 on success.
 * \return         MBEDTLS_ERR_MPI_BAD_INPUT_DATA if the allocated length of
 *                 the two input MPIs is not the same.
 */
int _mbedtls_mpi_lt_mpi_ct( const mbedtls_mpi *X, const mbedtls_mpi *Y,
        unsigned *ret );

/**
 * \brief          Compare an MPI with an integer.
 *
 * \param X        The left-hand MPI. This must point to an initialized MPI.
 * \param z        The integer value to compare \p X to.
 *
 * \return         \c 1 if \p X is greater than \p z.
 * \return         \c -1 if \p X is lesser than \p z.
 * \return         \c 0 if \p X is equal to \p z.
 */
int _mbedtls_mpi_cmp_int( const mbedtls_mpi *X, mbedtls_mpi_sint z );

/**
 * \brief          Perform an unsigned addition of MPIs: X = |A| + |B|
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param A        The first summand. This must point to an initialized MPI.
 * \param B        The second summand. This must point to an initialized MPI.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         Another negative error code on different kinds of failure.
 */
int _mbedtls_mpi_add_abs( mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *B );

/**
 * \brief          Perform an unsigned subtraction of MPIs: X = |A| - |B|
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param A        The minuend. This must point to an initialized MPI.
 * \param B        The subtrahend. This must point to an initialized MPI.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_NEGATIVE_VALUE if \p B is greater than \p A.
 * \return         Another negative error code on different kinds of failure.
 *
 */
int _mbedtls_mpi_sub_abs( mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *B );

/**
 * \brief          Perform a signed addition of MPIs: X = A + B
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param A        The first summand. This must point to an initialized MPI.
 * \param B        The second summand. This must point to an initialized MPI.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         Another negative error code on different kinds of failure.
 */
int _mbedtls_mpi_add_mpi( mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *B );

/**
 * \brief          Perform a signed subtraction of MPIs: X = A - B
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param A        The minuend. This must point to an initialized MPI.
 * \param B        The subtrahend. This must point to an initialized MPI.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         Another negative error code on different kinds of failure.
 */
int _mbedtls_mpi_sub_mpi( mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *B );

/**
 * \brief          Perform a signed addition of an MPI and an integer: X = A + b
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param A        The first summand. This must point to an initialized MPI.
 * \param b        The second summand.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         Another negative error code on different kinds of failure.
 */
int _mbedtls_mpi_add_int( mbedtls_mpi *X, const mbedtls_mpi *A,
                         mbedtls_mpi_sint b );

/**
 * \brief          Perform a signed subtraction of an MPI and an integer:
 *                 X = A - b
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param A        The minuend. This must point to an initialized MPI.
 * \param b        The subtrahend.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         Another negative error code on different kinds of failure.
 */
int _mbedtls_mpi_sub_int( mbedtls_mpi *X, const mbedtls_mpi *A,
                         mbedtls_mpi_sint b );

/**
 * \brief          Perform a multiplication of two MPIs: X = A * B
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param A        The first factor. This must point to an initialized MPI.
 * \param B        The second factor. This must point to an initialized MPI.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         Another negative error code on different kinds of failure.
 *
 */
int _mbedtls_mpi_mul_mpi( mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *B );

/**
 * \brief          Perform a multiplication of an MPI with an unsigned integer:
 *                 X = A * b
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param A        The first factor. This must point to an initialized MPI.
 * \param b        The second factor.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         Another negative error code on different kinds of failure.
 *
 */
int _mbedtls_mpi_mul_int( mbedtls_mpi *X, const mbedtls_mpi *A,
                         mbedtls_mpi_uint b );

/**
 * \brief          Perform a division with remainder of two MPIs:
 *                 A = Q * B + R
 *
 * \param Q        The destination MPI for the quotient.
 *                 This may be \c NULL if the value of the
 *                 quotient is not needed.
 * \param R        The destination MPI for the remainder value.
 *                 This may be \c NULL if the value of the
 *                 remainder is not needed.
 * \param A        The dividend. This must point to an initialized MPi.
 * \param B        The divisor. This must point to an initialized MPI.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if memory allocation failed.
 * \return         #MBEDTLS_ERR_MPI_DIVISION_BY_ZERO if \p B equals zero.
 * \return         Another negative error code on different kinds of failure.
 */
int _mbedtls_mpi_div_mpi( mbedtls_mpi *Q, mbedtls_mpi *R, const mbedtls_mpi *A,
                         const mbedtls_mpi *B );

/**
 * \brief          Perform a division with remainder of an MPI by an integer:
 *                 A = Q * b + R
 *
 * \param Q        The destination MPI for the quotient.
 *                 This may be \c NULL if the value of the
 *                 quotient is not needed.
 * \param R        The destination MPI for the remainder value.
 *                 This may be \c NULL if the value of the
 *                 remainder is not needed.
 * \param A        The dividend. This must point to an initialized MPi.
 * \param b        The divisor.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if memory allocation failed.
 * \return         #MBEDTLS_ERR_MPI_DIVISION_BY_ZERO if \p b equals zero.
 * \return         Another negative error code on different kinds of failure.
 */
int _mbedtls_mpi_div_int( mbedtls_mpi *Q, mbedtls_mpi *R, const mbedtls_mpi *A,
                         mbedtls_mpi_sint b );

/**
 * \brief          Perform a modular reduction. R = A mod B
 *
 * \param R        The destination MPI for the residue value.
 *                 This must point to an initialized MPI.
 * \param A        The MPI to compute the residue of.
 *                 This must point to an initialized MPI.
 * \param B        The base of the modular reduction.
 *                 This must point to an initialized MPI.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         #MBEDTLS_ERR_MPI_DIVISION_BY_ZERO if \p B equals zero.
 * \return         #MBEDTLS_ERR_MPI_NEGATIVE_VALUE if \p B is negative.
 * \return         Another negative error code on different kinds of failure.
 *
 */
int _mbedtls_mpi_mod_mpi( mbedtls_mpi *R, const mbedtls_mpi *A,
                         const mbedtls_mpi *B );

/**
 * \brief          Perform a modular reduction with respect to an integer.
 *                 r = A mod b
 *
 * \param r        The address at which to store the residue.
 *                 This must not be \c NULL.
 * \param A        The MPI to compute the residue of.
 *                 This must point to an initialized MPi.
 * \param b        The integer base of the modular reduction.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         #MBEDTLS_ERR_MPI_DIVISION_BY_ZERO if \p b equals zero.
 * \return         #MBEDTLS_ERR_MPI_NEGATIVE_VALUE if \p b is negative.
 * \return         Another negative error code on different kinds of failure.
 */
int _mbedtls_mpi_mod_int( mbedtls_mpi_uint *r, const mbedtls_mpi *A,
                         mbedtls_mpi_sint b );

/**
 * \brief          Perform a sliding-window exponentiation: X = A^E mod N
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param A        The base of the exponentiation.
 *                 This must point to an initialized MPI.
 * \param E        The exponent MPI. This must point to an initialized MPI.
 * \param N        The base for the modular reduction. This must point to an
 *                 initialized MPI.
 * \param _RR      A helper MPI depending solely on \p N which can be used to
 *                 speed-up multiple modular exponentiations for the same value
 *                 of \p N. This may be \c NULL. If it is not \c NULL, it must
 *                 point to an initialized MPI. If it hasn't been used after
 *                 the call to mbedtls_mpi_init(), this function will compute
 *                 the helper value and store it in \p _RR for reuse on
 *                 subsequent calls to this function. Otherwise, the function
 *                 will assume that \p _RR holds the helper value set by a
 *                 previous call to mbedtls_mpi_exp_mod(), and reuse it.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         #MBEDTLS_ERR_MPI_BAD_INPUT_DATA if \c N is negative or
 *                 even, or if \c E is negative.
 * \return         Another negative error code on different kinds of failures.
 *
 */
int _mbedtls_mpi_exp_mod( mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *E, const mbedtls_mpi *N,
                         mbedtls_mpi *_RR );

/**
 * \brief          Fill an MPI with a number of random bytes.
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param size     The number of random bytes to generate.
 * \param f_rng    The RNG function to use. This must not be \c NULL.
 * \param p_rng    The RNG parameter to be passed to \p f_rng. This may be
 *                 \c NULL if \p f_rng doesn't need a context argument.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         Another negative error code on failure.
 *
 * \note           The bytes obtained from the RNG are interpreted
 *                 as a big-endian representation of an MPI; this can
 *                 be relevant in applications like deterministic ECDSA.
 */
int _mbedtls_mpi_fill_random( mbedtls_mpi *X, size_t size,
                     int (*f_rng)(void *, unsigned char *, size_t),
                     void *p_rng );

/**
 * \brief          Compute the greatest common divisor: G = gcd(A, B)
 *
 * \param G        The destination MPI. This must point to an initialized MPI.
 * \param A        The first operand. This must point to an initialized MPI.
 * \param B        The second operand. This must point to an initialized MPI.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         Another negative error code on different kinds of failure.
 */
int _mbedtls_mpi_gcd( mbedtls_mpi *G, const mbedtls_mpi *A,
                     const mbedtls_mpi *B );

/**
 * \brief          Compute the modular inverse: X = A^-1 mod N
 *
 * \param X        The destination MPI. This must point to an initialized MPI.
 * \param A        The MPI to calculate the modular inverse of. This must point
 *                 to an initialized MPI.
 * \param N        The base of the modular inversion. This must point to an
 *                 initialized MPI.
 *
 * \return         \c 0 if successful.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         #MBEDTLS_ERR_MPI_BAD_INPUT_DATA if \p N is less than
 *                 or equal to one.
 * \return         #MBEDTLS_ERR_MPI_NOT_ACCEPTABLE if \p has no modular inverse
 *                 with respect to \p N.
 */
int _mbedtls_mpi_inv_mod( mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *N );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief          Perform a Miller-Rabin primality test with error
 *                 probability of 2<sup>-80</sup>.
 *
 * \deprecated     Superseded by mbedtls_mpi_is_prime_ext() which allows
 *                 specifying the number of Miller-Rabin rounds.
 *
 * \param X        The MPI to check for primality.
 *                 This must point to an initialized MPI.
 * \param f_rng    The RNG function to use. This must not be \c NULL.
 * \param p_rng    The RNG parameter to be passed to \p f_rng.
 *                 This may be \c NULL if \p f_rng doesn't use a
 *                 context parameter.
 *
 * \return         \c 0 if successful, i.e. \p X is probably prime.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         #MBEDTLS_ERR_MPI_NOT_ACCEPTABLE if \p X is not prime.
 * \return         Another negative error code on other kinds of failure.
 */
MBEDTLS_DEPRECATED int _mbedtls_mpi_is_prime( const mbedtls_mpi *X,
                          int (*f_rng)(void *, unsigned char *, size_t),
                          void *p_rng );
#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

/**
 * \brief          Miller-Rabin primality test.
 *
 * \warning        If \p X is potentially generated by an adversary, for example
 *                 when validating cryptographic parameters that you didn't
 *                 generate yourself and that are supposed to be prime, then
 *                 \p rounds should be at least the half of the security
 *                 strength of the cryptographic algorithm. On the other hand,
 *                 if \p X is chosen uniformly or non-adversially (as is the
 *                 case when mbedtls_mpi_gen_prime calls this function), then
 *                 \p rounds can be much lower.
 *
 * \param X        The MPI to check for primality.
 *                 This must point to an initialized MPI.
 * \param rounds   The number of bases to perform the Miller-Rabin primality
 *                 test for. The probability of returning 0 on a composite is
 *                 at most 2<sup>-2*\p rounds</sup>.
 * \param f_rng    The RNG function to use. This must not be \c NULL.
 * \param p_rng    The RNG parameter to be passed to \p f_rng.
 *                 This may be \c NULL if \p f_rng doesn't use
 *                 a context parameter.
 *
 * \return         \c 0 if successful, i.e. \p X is probably prime.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         #MBEDTLS_ERR_MPI_NOT_ACCEPTABLE if \p X is not prime.
 * \return         Another negative error code on other kinds of failure.
 */
int mbedtls_mpi_is_prime_ext( const mbedtls_mpi *X, int rounds,
                              int (*f_rng)(void *, unsigned char *, size_t),
                              void *p_rng );

/**
 * \brief          Generate a prime number.
 *
 * \param X        The destination MPI to store the generated prime in.
 *                 This must point to an initialized MPi.
 * \param nbits    The required size of the destination MPI in bits.
 *                 This must be between \c 3 and #MBEDTLS_MPI_MAX_BITS.
 * \param flags    A mask of flags of type #mbedtls_mpi_gen_prime_flag_t.
 * \param f_rng    The RNG function to use. This must not be \c NULL.
 * \param p_rng    The RNG parameter to be passed to \p f_rng.
 *                 This may be \c NULL if \p f_rng doesn't use
 *                 a context parameter.
 *
 * \return         \c 0 if successful, in which case \p X holds a
 *                 probably prime number.
 * \return         #MBEDTLS_ERR_MPI_ALLOC_FAILED if a memory allocation failed.
 * \return         #MBEDTLS_ERR_MPI_BAD_INPUT_DATA if `nbits` is not between
 *                 \c 3 and #MBEDTLS_MPI_MAX_BITS.
 */
int _mbedtls_mpi_gen_prime( mbedtls_mpi *X, size_t nbits, int flags,
                   int (*f_rng)(void *, unsigned char *, size_t),
                   void *p_rng );

#ifdef __cplusplus
}
#endif

#endif /* bignum_rom.h */
