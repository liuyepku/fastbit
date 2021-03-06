/* File: $Id$
   Author: John Wu <John.Wu at acm.org>
      Lawrence Berkeley National Laboratory
   Copyright 20014-2014 the Regents of the University of California
*/
#ifndef IBIS_IAPI_H
#define IBIS_IAPI_H
/**
@file This header file defines an in-memory C API for accessing the
querying functionality of FastBit IBIS implementation.  It is primarily for
in memory data.

@note Following the convension established in capi.h, all functions are in
lower case letters mixed with underscores, and all custom data types are in
camel cases with the first letter capitalized.

@note For functions that return integer error code, 0 always indicate
success, a negative number indicate error, a positive number may also be
returned to carry results, such as in fastbit_get_result_size.

@note For functions that returns pointers, a nil pointer is returned in
case of error.

@note About the name: IAPI was original intended to be "In memory API", but
the word iapi appears to be a Dekota word for "word" or "language".
 */
#include "const.h"	// common definitions and declarations
#include "capi.h"	// reuse the definitions from capi.h

/** An enum type for data types supported by this interface.

    @note Would have preferred to reuse the enum type ibis::TYPE_T,
    however, there isn't a good way known to the author.
*/
typedef enum FastBitDataType {
    FastBitDataTypeUnknown=0,
    FastBitDataTypeByte=2,
    FastBitDataTypeUByte=3,
    FastBitDataTypeShort=4,
    FastBitDataTypeUShort=5,
    FastBitDataTypeInt=6,
    FastBitDataTypeUInt=7,
    FastBitDataTypeLong=8,
    FastBitDataTypeULong=9,
    FastBitDataTypeFloat=10,
    FastBitDataTypeDouble=11
} FastBitDataType;

/** An enum type for comparison operators supported.
 */
typedef enum FastBitCompareType {
    FastBitCompareLess,
    FastBitCompareLessEqual,
    FastBitCompareGreater,
    FastBitCompareGreaterEqual,
    FastBitCompareEqual,
    FastBitCompareNotEqual,
} FastBitCompareType;

/** An enum type for specifying how selection conditions are to be
    combined.
 */
typedef enum FastBitCombineType {
    FastBitCombineAnd,
    FastBitCombineOr,
    FastBitCombineXor,
    FastBitCombineNand,
    FastBitCombineNor,
} FastBitCombineType;

/** An opaque pointer to the selection object. */
#ifdef __cplusplus
typedef ibis::qExpr* FastBitSelectionHandle;
#else
typedef void* FastBitSelectionHandle;
#endif

/**
@defgroup FastBitIAPI FastBit In-memory API.
@{
*/
#ifdef __cplusplus
extern "C" {
#endif

    /** Create a simple one-sided range condition. */
    FastBitSelectionHandle fastbit_create_selection
    (FastBitDataType, void*, uint64_t, FastBitCompareType, void*);

    /** Create a simple one-sided range condition on a n-dimensional array. */
    FastBitSelectionHandle fastbit_create_selection_nd
    (FastBitDataType, void*, uint64_t*, uint64_t, FastBitCompareType, void*);

    /** Free the selection object. */
    void fastbit_free_selection(FastBitSelectionHandle);

    /** Free all cached object for IAPI. */
    void fastbit_free_all_iapi_objects();

    /** Combining two selection conditions into one. */
    FastBitSelectionHandle fastbit_combine_selections
    (FastBitSelectionHandle, FastBitCombineType, FastBitSelectionHandle);

    /** Provide an upper bound on the number of hits. */
    int64_t fastbit_estimate_num_hits(FastBitSelectionHandle);

    /** Compute the number of hits. */
    int64_t fastbit_get_num_hits(FastBitSelectionHandle);

    /** Extract the coordinates of the elements of arrays satisfying the
        selection. */
    int64_t fastbit_get_coordinates
    (FastBitSelectionHandle, uint64_t*, uint64_t, uint64_t);

    /** Read the elements of the array satisfying the selection conditions */
    int64_t fastbit_read_selection
    (FastBitDataType, const void*, uint64_t, FastBitSelectionHandle,
     void*, uint64_t, uint64_t);
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif






