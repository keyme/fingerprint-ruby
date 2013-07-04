/**
\file dpfj.h

\copyright (c) 2011 DigitalPersona, Inc

\brief U.are.U SDK FingerJet Engine API

Data types and functions for feature extraction, matching and conversion.

\version 2.0.0
*/

#ifndef __DPFJ_H__
#define __DPFJ_H__


/** \cond NEVER */
#ifndef NULL
#	define NULL 0
#endif

#ifndef DPERROR
#	define _DP_FACILITY  0x05BA
#	define DPERROR(err)  ((int)err | (_DP_FACILITY << 16))
#endif /* DPERROR */

#define DPFJ_API_VERSION_MAJOR 1
#define DPFJ_API_VERSION_MINOR 0
/** \endcond */


/****************************************************************************************************
 Error codes
****************************************************************************************************/

/**
\brief API call succeeded.
*/
#define DPFJ_SUCCESS             0

/**
\brief API call is not implemented.
*/
#define DPFJ_E_NOT_IMPLEMENTED   DPERROR(10)

/**
\brief Unspecified failure.

"Catch-all" generic failure code. Can be returned by all API calls in case of failure, when the reason for the failure is unknown or cannot be specified.
 */
#define DPFJ_E_FAILURE           DPERROR(11)

/**
\brief No data is available.
*/
#define DPFJ_E_NO_DATA           DPERROR(12)

/**
\brief Memory allocated by application is not enough to contain data which is expected.
*/
#define DPFJ_E_MORE_DATA         DPERROR(13)

/**
\brief One or more parameters passed to the API call are invalid.
*/
#define DPFJ_E_INVALID_PARAMETER DPERROR(20)

/**
\brief FID is invalid.
*/
#define DPFJ_E_INVALID_FID     DPERROR(101)

/**
\brief Image is too small.
*/
#define DPFJ_E_TOO_SMALL_AREA    DPERROR(102)

/**
\brief FMD is invalid.
*/
#define DPFJ_E_INVALID_FMD       DPERROR(201)

/**
\brief Enrollment operation is in progress.
*/
#define DPFJ_E_ENROLLMENT_IN_PROGRESS  DPERROR(301)

/**
\brief Enrollment operation has not begun.
*/
#define DPFJ_E_ENROLLMENT_NOT_STARTED  DPERROR(302)

/**
\brief Not enough in the pool of FMDs to create enrollment FMD.
*/
#define DPFJ_E_ENROLLMENT_NOT_READY  DPERROR(303)

/****************************************************************************************************
 Data types and definitions
****************************************************************************************************/

/**
\brief Normalized value when probability = 1.
*/
#define DPFJ_PROBABILITY_ONE  0x7fffffff

/** 
\brief Fingerprint Image Data (FID) Format.
*/
typedef int DPFJ_FID_FORMAT;

#define	DPFJ_FID_ANSI_381_2004     0x001B0401 /**< ANSI INSITS 381-2004 format */
#define DPFJ_FID_ISO_19794_4_2005  0x01010007 /**< ISO IEC 19794-4-2005 format */

/**
\brief Fingerptint Minutiae Data (FMD) Format.
*/
typedef int DPFJ_FMD_FORMAT;

#define DPFJ_FMD_ANSI_378_2004       0x001B0001 /**< ANSI INSITS 378-2004 Fingerprint Minutiae Data format */
#define DPFJ_FMD_ISO_19794_2_2005    0x01010001 /**< ISO IEC 19794-2-2005 Fingerprint Minutiae Data format */
#define DPFJ_FMD_DP_PRE_REG_FEATURES 0          /**< deprecated DigitalPersona pre-registration feature set format */
#define DPFJ_FMD_DP_REG_FEATURES     1          /**< deprecated DigitalPersona registration template format */
#define DPFJ_FMD_DP_VER_FEATURES     2          /**< deprecated DigitalPersona verification feature set format */

/** \brief Defines finger position.
	
Finger position according to ANSI 378-2004 and ISO 19794-2-2005 standards.
*/
typedef int DPFJ_FINGER_POSITION;

#define DPFJ_POSITION_UNKNOWN  0  /**< position unknown */
#define DPFJ_POSITION_RTHUMB   1  /**< right thumb */
#define DPFJ_POSITION_RINDEX   2  /**< right index finger */
#define DPFJ_POSITION_RMIDDLE  3  /**< right middle finger */
#define DPFJ_POSITION_RRING    4  /**< right ring finger */
#define DPFJ_POSITION_RLITTLE  5  /**< right little finger */
#define DPFJ_POSITION_LTHUMB   6  /**< left thumb */
#define DPFJ_POSITION_LINDEX   7  /**< left index finger */
#define DPFJ_POSITION_LMIDDLE  8  /**< left middle finger */
#define DPFJ_POSITION_LRING    9  /**< left ring finger */
#define DPFJ_POSITION_LLITTLE  10 /**< left little finger */

/** 
\brief Defines impression type.

Impression type according to ANSI 378-2004 and ISO 19794-2-2005 standards
*/
typedef int DPFJ_SCAN_TYPE;
	
#define DPFJ_SCAN_LIVE_PLAIN     0 
#define DPFJ_SCAN_LIVE_ROLLED    1
#define DPFJ_SCAN_NONLIVE_PLAIN  2
#define DPFJ_SCAN_NONLIVE_ROLLED 3
#define DPFJ_SCAN_SWIPE          8  


/** \cond NEVER */
#define DPFJ_FID_ANSI_381_2004_RECORD_HEADER_LENGTH    36
#define DPFJ_FID_ISO_19794_4_2005_RECORD_HEADER_LENGTH 32
#define DPFJ_FID_ANSI_ISO_VIEW_HEADER_LENGTH           14

#define DPFJ_FMD_ANSI_378_2004_RECORD_HEADER_LENGTH    26
#define DPFJ_FMD_ISO_19794_2_2005_RECORD_HEADER_LENGTH 24
#define DPFJ_FMD_ANSI_ISO_VIEW_HEADER_LENGTH           4
#define DPFJ_FMD_ANSI_ISO_MINITIA_LENGTH               6
/** \endcond */

/**
\brief Maximum size of a single-view FMD with no extended data block.
*/
#define MAX_FMD_SIZE (DPFJ_FMD_ANSI_378_2004_RECORD_HEADER_LENGTH + DPFJ_FMD_ANSI_ISO_VIEW_HEADER_LENGTH + 255 * DPFJ_FMD_ANSI_ISO_MINITIA_LENGTH + 2)

/**
\brief API Version information. 
*/
typedef struct dpfj_ver_info {
	int major;       /**< major version number */
	int minor;       /**< minor version number */
	int maintanance; /**< maintanance or revision number */
} DPFJ_VER_INFO;

/**
\brief Complete information about library/SDK.
*/
typedef struct dpfj_version {
	unsigned int    size;  /**< Size of the structure, in bytes */	
	DPFJ_VER_INFO lib_ver; /**< file version of the library/SDK */
	DPFJ_VER_INFO api_ver; /**< version of the API */
} DPFJ_VERSION;

/**
\brief Candidate, result of identification.
*/
typedef struct dpfj_candidate{
 	unsigned int size;     /**< size of the structure, in bytes */
	unsigned int fmd_idx;  /**< index of the FMD in the input array */
	unsigned int view_idx; /**< index of the view in the FMD */
} DPFJ_CANDIDATE;


/****************************************************************************************************
 API calls
****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	/**
	\brief Query the library and API version information. 
	
	\param ver  		[in] Pointer to the empty structure (per DPFJ_VERSION); [out] Pointer to structure containing version information
	\return DPFJ_SUCCESS:   Version information was acquired;
	\return DPFJ_E_FAILURE: Failed to acquire version information.
	*/
	int dpfj_version( 
		DPFJ_VERSION* ver
	);


	/**
	\brief Extracts features and creates an FMD from a raw image. 

	When you do a fingerprint capture, you can receive a raw image or a FID. If you specify a raw image, you can then extract features into an FMD using this function.
	The raw image is just a buffer of pixels. This function works with raw images that have
	 - 8 bits per pixel
	 - no padding
	 - square pixels (dpi is the same for horizontal and vertical)

	The size of the resulting FMD will vary depending on the minutiae in a specific fingerprint.  The maximum possible size of a single-view FMD is MAX_FMD_SIZE. 
	If the value pointed to by fmd_size is zero, the function will return with the error code DPFJ_E_MORE_DATA and the required size will be stored in the 
	value pointed to by fmd_size. In order to determine the size, this function processes the image, extracts features and discards the FMD, so it takes significant
	processing time.  However if memory shortages are a key issue, this allows you to allocate memory more efficiently at the expense of processing time.
	If memory is available, you will get the best performance if you always allocate MAX_FMD_SIZE for the FMD.
	The value pointed to by fmd_size will always be returned as the actual size of the FMD that was extracted.	

	\param image_data    pointer to the image data
	\param image_size    size of the image data
	\param image_width   width of the image
	\param image_height  height of the image
	\param image_dpi     resolution of the image
	\param finger_pos    position of the finger
	\param cbeff_id      CBEFF product ID, from IBIA registry
	\param fmd_type      type of the FMD
	\param fmd           pointer to recieve FMD
	\param fmd_size      pointer to allocated size for the FMD, pointer to receive the actual size of the FMD
	\return DPFJ_SUCCESS:             FMD was created;
	\return DPFJ_E_MORE_DATA:         Features extracted, but allocated memory is not sufficient for FMD. The required memory size is in the fmd_size.
	\return DPFJ_E_INVALID_PARAMETER: One or more parameters passed are invalid.
	\return DPFJ_E_FAILURE:           Failed to create FMD.
	*/
	int dpfj_create_fmd_from_raw (
 		const unsigned char* image_data,
		unsigned int         image_size,
 		unsigned int         image_width,
 		unsigned int         image_height,
		unsigned int         image_dpi,
		DPFJ_FINGER_POSITION finger_pos,
		unsigned int         cbeff_id,
 		DPFJ_FMD_FORMAT      fmd_type,
 		unsigned char*       fmd,
 		unsigned int*        fmd_size 
	);

	/**
	\brief Extracts features and creates an FMD from an ANSI or ISO image. 
	
	This function works with FIDs that have
	 - 8 bits per pixel
	 - no padding
	 - square pixels (dpi is the same for horizontal and vertical)
	The size of the resulting FMD will vary depending on the minutiae in a specific fingerprint.  The maximum possible size of a single-view FMD is MAX_FMD_SIZE. 
	If the value pointed to by fmd_size is zero, the function will return with the error code DPFJ_E_MORE_DATA and the required size will be stored in the value 
	pointed to by fmd_size. In order to determine the size, this function processes the image, extracts the FMD and discards the FMD, so it takes significant processing time.  
	However if memory shortages are a key issue, this allows you to allocate memory more efficiently at the expense of processing time.
	If memory is available, you will get the best performance if you always allocate MAX_FMD_SIZE for the FMD.
	The value pointed to by fmd_size will always be returned as the actual size of the FMD that was extracted.

	\param fid_type  type of the FID
	\param fid       pointer to the FID data
	\param fid_size  size of the FID data
	\param fmd_type  type of the FMD
	\param fmd       pointer to recieve FMD data
	\param fmd_size  pointer to allocated size for the FMD, pointer to receive the actual size of the FMD
	\return DPFJ_SUCCESS:             FMD was created;
	\return DPFJ_E_MORE_DATA:         Features extracted, but allocated memory is not sufficient for FMD. The required memory size is in the fmd_size.
	\return DPFJ_E_INVALID_PARAMETER: One or more parameters passed are invalid.
	\return DPFJ_E_FAILURE:           Failed to create FMD.
	*/
	int dpfj_create_fmd_from_fid (
		DPFJ_FID_FORMAT      fid_type,
 		const unsigned char* fid,
		unsigned int         fid_size,
 		DPFJ_FMD_FORMAT      fmd_type,
 		unsigned char*       fmd,
 		unsigned int*        fmd_size 
	);

	/**
	\brief Compares two fingerprints. 

	Given two single views from two FMDs, this function returns a <b>dissimilarity score</b> indicating the quality of the match.  
	The dissimilarity scores returned values are between:
		0=match
		maxint=no match
	Values close to 0 indicate very close matches, values closer to maxint indicate very poor matches.
	For a discussion of  how to evaluate dissimilarity scores, as well as the statistical validity of the dissimilarity score and error rates, consult the Developer Guide. 
	The dpfj_compare function returns DPFJ_SUCCESS if it is able to compare the fingerprints successfully (i.e., the FMDs are valid and correctly formed). 
	However that does not mean that the fingerprints matched. To check whether they matched, you must look at the dissimilarity score.

	\param fmd1_type        type of the first FMD
	\param fmd1             pointer to the first FMD
	\param fmd1_size        size of the first FMD
	\param fmd1_view_idx    index of the view
	\param fmd2_type        type of the second FMD
	\param fmd2             pointer to the second FMD
	\param fmd2_size size   of the second FMD
	\param fmd2_view_idx    index of the view
	\param score            pointer to receive dissimilarity score
	\return DPFJ_SUCCESS:   Comparison finished;
	\return DPFJ_E_FAILURE: Unknown error.
	*/
	int dpfj_compare(
		DPFJ_FMD_FORMAT  fmd1_type, 
		unsigned char*   fmd1, 
		unsigned int     fmd1_size, 
		unsigned int     fmd1_view_idx,
		DPFJ_FMD_FORMAT  fmd2_type, 
		unsigned char*   fmd2, 
		unsigned int     fmd2_size, 
		unsigned int     fmd2_view_idx, 
		unsigned int*    score
	);

	/**
	\brief Compares a single fingerprint to an array of fingerprints.
	  
	This function takes as inputs:
		- a single view in an FMD
		- an array of FMDs (each FMD can contain up to 16 views) to compare
		- the desired number of candidates to return 
		- the threshold for False Positive Identification Rate that is permitted
	This function compares a single view against an array of FMDs.  Each time view has a score lower than the threshold, that view is marked as a possible candidate. 
	Then when all possible candidates are identified (i.e., they meet the threshold), they are ranked by their score.  Finally, the function returns as many 
	candidates as requested, based on the candidates with the lowest dissimilarity score.  
	For a discussion of setting the threshold as well as the statistical validity of the dissimilarity score and error rates, consult the Developer Guide.    
	
	\param fmd1_type         type of the FMDs
	\param fmd1              pointer to the first FMD data
	\param fmd1_size         size of the first FMD data
	\param fmd1_view_idx     index of the view
	\param fmds_type         type of the FMDs in the fmds array
	\param fmds_cnt          number of FMDs in the fmds array
	\param fmds              array of FMDs
	\param fmds_size         array of sizes of the FMDs data
	\param threshold_score   target threshold on degree of dissimilarity 
	\param candidate_cnt     [in] number of allocated entries in the candidates array; [out] receives the actual number of candidates filled in the array as a result of identification
	\param candidates        array of candidates
	\return DPFJ_SUCESS:    Identification finished;
	\return DPFJ_E_FAILURE: Unknown error.
	*/
	int dpfj_identify(
 		DPFJ_FMD_FORMAT  fmd1_type,
		unsigned char*   fmd1,
		unsigned int     fmd1_size,
 		unsigned int     fmd1_view_idx,
		DPFJ_FMD_FORMAT  fmds_type,
 		unsigned int     fmds_cnt,
		unsigned char**  fmds,
		unsigned int*    fmds_size,
		unsigned int     threshold_score,
 		unsigned int*    candidate_cnt,
 		DPFJ_CANDIDATE*  candidates
	);

	/**
	\brief Starts enrollment operation.

	\param fmd_type type of FMD to produce as a result of enrollment operation
	\return DPFJ_SUCCESS:                  Enrollment started.
	\return DPFJ_E_INVALID_PARAMETER:      Requested FMD type is invalid.
	\return DPFJ_E_ENROLLMENT_IN_PROGRESS: Another enrollment operation is in prgress.
	\return DPFJ_E_FAILURE:                Unknown error.
	*/
	int dpfj_start_enrollment(
		DPFJ_FMD_FORMAT fmd_type
	);

	/**
	\brief Adds FMD to enrollment operation.

	Add an FMD to the pool of FMDs for enrollment and return a flag indicating when the enrollment is ready.
	This function must be called before dpfj_create_enrollment_fmd.

	\param fmd_type       type of the FMD.
	\param fmd            pointer to the FMD data.
	\param fmd_size       size of the FMD data.
	\param fmd_view_idx   index of the view
	\return DPFJ_SUCCESS:                  FMD added, enrollment is ready.
	\return DPFJ_E_MORE_DATA:              FMD added, more FMDs for enrollment required.
	\return DPFJ_E_INVALID_PARAMETER:      One or more parameters passed are invalid.
	\return DPFJ_E_ENROLLMENT_NOT_STARTED: Enrollment is not started.
	\return DPFJ_E_FAILURE:                Unknown error.
	*/
	int dpfj_add_to_enrollment(
		DPFJ_FMD_FORMAT  fmd_type,
		unsigned char*   fmd,
		unsigned int     fmd_size,
		unsigned int     fmd_view_idx
	);

	/**
	\brief Creates and returns enrollment FMD.

	Create an FMD for an enrolled finger. The output FMD is suitable for storing in a database of enrolled users.  
	Some applications like voting, banking and law enforcement require that you check for duplicate fingerprints before storing a new fingerprint in the database.
	For ANSI/ISO formats, the enrollment FMD is a standard FMD (the same as an FMD generated by the extraction function). For the DigitalPersona data format, 
	the enrollment FMD uses the "fingerprint template" format as used by legacy DigitalPersona applications.
	This function must be called after dpfj_add_to_enrollment.
	The size of the resulting FMD will vary depending on the minutiae in the fingerprint(s) that were enrolled.  The maximum possible size of an FMD is MAX_FMD_SIZE. 
	If the value pointed to by fmd_size is zero, the function will return with the error code DPFJ_E_MORE_DATA and the required size will be stored in the value pointed to by fmd_size. 
	In order to determine the size, this function processes the image, extracts features and discards the FMD, so it takes significant processing time.  
	However if memory shortages are a key issue, this allows you to allocate memory more efficiently at the expense of processing time.
	If memory is available, you will get the best performance if you always allocate MAX_FMD_SIZE for the FMD.
	The value pointed to by fmd_size will always be returned as the actual size of the FMD that was extracted.

	\param fmd            pointer to recieve FMD data
	\param fmd_size       pointer to allocated size for the FMD data, pointer to receive the actual size of the FMD data
	\return DPFJ_SUCCESS:                  FMD created.
	\return DPFJ_E_MORE_DATA:              FMD created, but allocated memory is not sufficient. The required memory size is in the fmd_size.
	\return DPFJ_E_INVALID_PARAMETER:      One or more parameters passed are invalid.
	\return DPFJ_E_ENROLLMENT_NOT_STARTED: Enrollment is not started.
	\return DPFJ_E_FAILURE:                Unknown error.
	*/
	int dpfj_create_enrollment_fmd(
		unsigned char*  fmd,
		unsigned int*   fmd_size
	);

	/**
	\brief Ends enrollment operation, releases memory.

	This function releases resources used during the enrollment process.  Call after enrollment is complete.
	\return DPFJ_SUCCESS:   Enrollment ended.
	\return DPFJ_E_FAILURE: Unknown error.
	*/
	int dpfj_finish_enrollment();

	/**
	\brief Converts an FMD from any supported format to any other supported format.
	
	\param fmd1_type  type of the input FMD
	\param fmd1       pointer to the input FMD data
	\param fmd1_size  size of the input FMD data
	\param fmd2_type  type of the target FMD
	\param fmd2       pointer to receive target FMD data
	\param fmd2_size  pointer to allocated size for the FMD data, pointer to receive the actual size of the FMD data
	\return DPFJ_SUCCESS:             FMD was converted;
	\return DPFJ_E_INVALID_PARAMETER: One or more parameters passed are invalid.
	\return DPFJ_E_FAILURE:           Failed to convert FMD.
	*/
	int dpfj_fmd_convert(
		DPFJ_FMD_FORMAT  fmd1_type,
		unsigned char*   fmd1,
		unsigned int     fmd1_size,
		DPFJ_FMD_FORMAT  fmd2_type,
		unsigned char*   fmd2,
		unsigned int*    fmd2_size
	);

	/****************************************************************************************************
	 legacy DigitalPersona image format conversion
	****************************************************************************************************/

	/**
	\brief Converts legacy DigitalPersona image to the image in ANSI or ISO format. 
	
	\param dp_image         pointer to the DP image data
	\param dp_image_size    size of the DP image data
	\param fid_type         type of the FID
	\param fid_dpi          resolution of the FID, valid values are 500 and 1000
	\param rotate180        flag: rotate image, 0 - do not rotate, 1 - rotate
	\param fid              pointer to receive FID data
	\param fid_size         pointer to receive the size of the FID
	\return DPFJ_SUCCESS:   FID was created
	\return DPFJ_E_FAILURE: Failed to create FID
	*/
	int dpfj_dp_fid_convert(
		unsigned char*  dp_image,
		unsigned int    dp_image_size,
		DPFJ_FID_FORMAT fid_type,
		unsigned int    fid_dpi,
		unsigned int    rotate180,
		unsigned char*  fid,
		unsigned int*   fid_size
	);

	/****************************************************************************************************
	 FID and FMD manipulation: types and definitions
	****************************************************************************************************/

#ifndef DPFJ_NO_IM_MANIPULATION

	/** 
	\brief Define image properties.
	
	Structure defines image properties for FIDs in ANSI 381-2004 
	and ISO 19794-4-2005 formats.
	*/
	typedef struct dpfj_fid_record_params{
		unsigned int record_length;        /**< total length of the image, including headers and all views */
		unsigned int cbeff_id;             /**< CBEFF product identifier */
		unsigned int capture_device_id;    /**< vendor specified */
		unsigned int acquisition_level;    /**< from Table 1 in "ANSI INSITS 381-2004" */
		unsigned int finger_cnt;           /**< total number of fingerprints in the record, must be greater or equal to 1 */
		unsigned int scale_units;          /**< pixels/cm (2) or pixels/inch (1) */
		unsigned int scan_res;             /**< scan resolution */
		unsigned int image_res;            /**< image resolution */
		unsigned int bpp;                  /**< pixel depth, 1 - 16 bits */
		unsigned int compression;          /**< from Table 3 in "ANSI INSITS 381-2004" */
	} DPFJ_FID_RECORD_PARAMS;

	/**
	\brief Define fingerprint image view (FIV) properties.
	
	Structure defines image view properties for FIVs in ANSI 381-2004 
	and ISO 19794-4-2005 formats.
	*/
	typedef struct dpfj_fid_view_params{
		unsigned int         data_length;     /**< total length of the finger data including headers and all views */
		DPFJ_FINGER_POSITION finger_position; /**< finger position  */
		unsigned int         view_cnt;        /**< number of views associated with this finger, must be greater or equal to 1 */
		unsigned int         view_number;     /**< 1 - 256 */
		unsigned int         quality;         /**< 1 - 100 for ISO; 1 - 100, 254 for ANSI */
		DPFJ_SCAN_TYPE       impression_type; /**< impression type */
		unsigned int         width;           /**< width of the fingerprint view, in pixels */
		unsigned int         height;          /**< height of the fingerprint view, in pixels */
		unsigned char*       view_data;       /**< pointer to the view data */
	} DPFJ_FID_VIEW_PARAMS;

	/**
	\brief Define FMD properties.
	
	Structure defines minutiae data properties for FMDs in ANSI 378-2004 
	and ISO 19794-2-2005 formats.
	*/
	typedef struct dpfj_fmd_record_params{
		unsigned int record_length;           /**< total length of the image, including headers and all views */
		unsigned int cbeff_id;                /**< CBEFF product identifier */
		unsigned int capture_equipment_comp;  /**< 4 bits: compliance;  */
		unsigned int capture_equipment_id;    /**< 12 bits: capture device id, vendor specified */
		unsigned int width;                   /**< width of the fingerprint image, in pixels */
		unsigned int height;                  /**< height of the fingerprint image, in pixels */
		unsigned int resolution;              /**< resolution of the fingerprint image */
		unsigned int view_cnt;                /**< number of views */
	} DPFJ_FMD_RECORD_PARAMS;

	/**
	\brief Define fingerprint minutiae view (FMV) properties.
	
	Structure defines minutiae view properties for FMVs in ANSI 378-2004 
	and ISO 19794-2-2005 formats.
	*/
	typedef struct dpfj_fmd_view_params{
		DPFJ_FINGER_POSITION finger_position;  /**< 0 - 10, from Table 5 in "ANSI INSITS 381-2004" */
		unsigned int         view_number;      /**< 0 - 15 */
		DPFJ_SCAN_TYPE       impression_type;  /**< Table 2 in "ANSI INSITS 378-2004" */
		unsigned int         quality;          /**< 1 - 100  */
		unsigned int         minutia_cnt;      /**< number of minutiae */
		unsigned int         ext_block_length; /**< length of the extended data block, in bytes */
		unsigned char*       ext_block;        /**< pointer to the extended data block */
	} DPFJ_FMD_VIEW_PARAMS;

	/****************************************************************************************************
	 FID manipulation
	****************************************************************************************************/

	/**
	\brief Read image properties from FID.
	
	\param image_type  type of the FID (per DPFJ_FID_FORMAT)
	\param image       pointer to the FID
	\param params      pointer to the structure to receive image properties
	\return void
	*/
	static inline void dpfj_get_fid_record_params(
		DPFJ_FID_FORMAT         image_type,
		const unsigned char*    image,
		DPFJ_FID_RECORD_PARAMS* params
	);

	/** 
	\brief Writes image properties to FID.
	
	\param params      pointer to the structure containing image properties
	\param image_type  format of the FID (per DPFJ_FID_FORMAT)
	\param image       pointer to the FID
	\return void
	*/
	static inline void dpfj_set_fid_record_params(
		const DPFJ_FID_RECORD_PARAMS* params,
		DPFJ_FID_FORMAT               image_type,
		unsigned char*                image
	);

	/**
	\brief Returns pointer to the specified view from FID.
	
	\param image_type  type of the FID (per DPFJ_FID_FORMAT)
	\param image       pointer to the FID
	\param view_idx    view index
	\return offset to the specified view
	*/
	static inline unsigned int dpfj_get_fid_view_offset(
		DPFJ_FID_FORMAT      image_type,
		const unsigned char* image,
		const unsigned int   view_idx
	);

	/**
	\brief Read image view properties from FID.
	
	\param view    pointer to the view from the FID
	\param params  pointer to the structure to receive view properties
	\return void
	*/
	static inline void dpfj_get_fid_view_params(
		const unsigned char*  view,
		DPFJ_FID_VIEW_PARAMS* params
	);

	/**
	\brief Write image view properties to FID.
	
	\param params  pointer to the structure containing view properties
	\param view    pointer to the view from the FID
	\return void
	*/
	static inline void dpfj_set_fid_view_params(
		const DPFJ_FID_VIEW_PARAMS* params,
		unsigned char*              view
	);

	/****************************************************************************************************
	 FMD manipulation
	****************************************************************************************************/

	/**
	\brief Read minutiae record properties from FMD.
	
	\param fmd_type   format of the FMD (per DPFJ_FMD_FORMAT)
	\param fmd        pointer to the FMD
	\param params     pointer to the structure to receive FMD properties
	\return void
	*/
	static inline void dpfj_get_fmd_record_params(
		DPFJ_FMD_FORMAT          fmd_type,
		const unsigned char*     fmd,
		DPFJ_FMD_RECORD_PARAMS*  params
	);

	/** \brief Write minutiae record properties to FMD.
	
	\param params     pointer to the structure containing FMD properties
	\param fmd_type   format of the FMD (per DPFJ_FMD_FORMAT)
	\param fmd        pointer to the FMD 
	\return void
	*/
	static inline void dpfj_set_fmd_record_params(
		const DPFJ_FMD_RECORD_PARAMS*  params,
		DPFJ_FMD_FORMAT                fmd_type,
		unsigned char*                fmd
	);

	/**
	\brief Return pointer to the specified view from FMD.
	
	\param fmd_type   format of the FMD (per DPFJ_FMD_FORMAT)
	\param fmd        pointer to the FMD
	\param view_idx   view index
	\return offset to the specified view
	*/
	static inline unsigned int dpfj_get_fmd_view_offset(
		DPFJ_FMD_FORMAT      fmd_type,
		const unsigned char* fmd,
		const unsigned int   view_idx
	);

	/**
	\brief Read view properties from FMD.
	
	\param view    pointer to the view from the FMD
	\param params  pointer to the structure to receive view properties
	\return void
	*/
	static inline void dpfj_get_fmd_view_params(
		const unsigned char*   view,
		DPFJ_FMD_VIEW_PARAMS*  params
	);

	/**
	\brief Write view properties to FMD.
	
	\param params  pointer to the structure containing view properties
	\param view    pointer to the view from the FMD
	\return void
	*/
	static inline void dpfj_set_fmd_view_params(
		const DPFJ_FMD_VIEW_PARAMS* params,
		unsigned char*              view
	);


	/****************************************************************************************************
	 FID and FMD manipulation: implementation
	****************************************************************************************************/

	/** \cond NEVER */

	static inline unsigned int read_be16(const unsigned char* addr) { 
		unsigned int var = *addr; 
		var <<= 8; 
		var |= *(addr + 1); 
		return var;
	};

	static inline void write_be16(unsigned int var, unsigned char* addr) { 
		*(addr) = (unsigned char)(var >> 8); 
		*(addr + 1) = (unsigned char)var; 
	};

	static inline unsigned int read_be32(const unsigned char* addr) { 
		unsigned int var = *(addr); 
		var <<= 8; 
		var |= *(addr + 1); 
		var <<= 8; 
		var |= *(addr + 2); 
		var <<= 8; 
		var |= *(addr + 3); 
		return var;
	};

	static inline void write_be32(unsigned int var, unsigned char* addr) { 
		*(addr) = (unsigned char)(var >> 24); 
		*(addr + 1) = (unsigned char)(var >> 16);
		*(addr + 2) = (unsigned char)(var >> 8); 
		*(addr + 3) = (unsigned char)var; 
	};

	/****************************************************************************************************/
	/* FID functions */

	static inline void dpfj_get_fid_record_params(DPFJ_FID_FORMAT image_type, const unsigned char* image, DPFJ_FID_RECORD_PARAMS* params){
		if(NULL == image) return;

		params->record_length     = read_be32(image + 10);
		int off = (DPFJ_FID_ANSI_381_2004 == image_type) ? DPFJ_FID_ANSI_381_2004_RECORD_HEADER_LENGTH - DPFJ_FID_ISO_19794_4_2005_RECORD_HEADER_LENGTH : 0;
		params->cbeff_id          = (DPFJ_FID_ANSI_381_2004 == image_type) ? read_be32(image + 14) : 0;
		params->capture_device_id = read_be16(image + 14 + off);
		params->acquisition_level = read_be16(image + 16 + off);
		params->finger_cnt        = *(image + 18 + off);
		params->scale_units       = *(image + 19 + off);
		params->scan_res          = read_be16(image + 20 + off);
		params->image_res         = read_be16(image + 24 + off);
		params->bpp               = *(image + 28 + off);
		params->compression       = *(image + 29 + off);
	}

	static inline void dpfj_set_fid_record_params(const DPFJ_FID_RECORD_PARAMS* params, DPFJ_FID_FORMAT image_type, unsigned char* image){
		if(NULL == image) return;

		image[0] = 'F'; image[1] = 'I'; image[2] = 'R'; image[3] = 0;
		image[4] = '0'; image[5] = '1'; image[6] = '0'; image[7] = 0;
		write_be16(0, image + 8);
		write_be32(params->record_length, image + 10);
		int off = (DPFJ_FID_ANSI_381_2004 == image_type) ? 4 : 0;
		if(DPFJ_FID_ANSI_381_2004 == image_type) write_be32(params->cbeff_id, image + 14);
		write_be16(params->capture_device_id, image + 14 + off);
		write_be16(params->acquisition_level, image + 16 + off);
		*(image + 18 + off) = (unsigned char)params->finger_cnt;
		*(image + 19 + off) = (unsigned char)params->scale_units;
		write_be16(params->scan_res, image + 20 + off);
		write_be16(params->scan_res, image + 22 + off);
		write_be16(params->image_res, image + 24 + off);
		write_be16(params->image_res, image + 26 + off);
		*(image + 28 + off) = (unsigned char)params->bpp;
		*(image + 29 + off) = (unsigned char)params->compression;
		write_be16(0, image + 30 + off);
	}

	static inline unsigned int dpfj_get_fid_view_offset(DPFJ_FID_FORMAT image_type, const unsigned char* image, unsigned int view_idx){
		if(NULL == image) return 0;

		unsigned int record_length = read_be32(image + 10);
		unsigned int pos = (DPFJ_FID_ANSI_381_2004 == image_type) ? DPFJ_FID_ANSI_381_2004_RECORD_HEADER_LENGTH : DPFJ_FID_ISO_19794_4_2005_RECORD_HEADER_LENGTH;
		unsigned int i = 0;
		for(i = 0; i < view_idx && pos < record_length; i++){
			//go to next
			pos += read_be32(image + pos);
		}

		//check if offset is valid
		if(pos >= record_length) return 0;
		return pos;
	}

	static inline void dpfj_get_fid_view_params(const unsigned char* view, DPFJ_FID_VIEW_PARAMS* params){
		if(NULL == view) return;

		params->data_length     = read_be32(view);
		params->finger_position = (DPFJ_FINGER_POSITION)*(view + 4);
		params->view_cnt        = (unsigned int)*(view + 5);
		params->view_number     = (unsigned int)*(view + 6);
		params->quality         = (unsigned int)*(view + 7);
		params->impression_type = (DPFJ_SCAN_TYPE)*(view + 8);
		params->width           = read_be16(view + 9);
		params->height          = read_be16(view + 11);
		params->view_data       = (unsigned char*)(view + DPFJ_FID_ANSI_ISO_VIEW_HEADER_LENGTH);
	}

	static inline void dpfj_set_fid_view_params(const DPFJ_FID_VIEW_PARAMS* params, unsigned char* view){
		if(NULL == view) return;

		unsigned int view_size = params->width * params->height + DPFJ_FID_ANSI_ISO_VIEW_HEADER_LENGTH;
		write_be32(view_size, view);
		*(view + 4) = (unsigned char)params->finger_position;
		*(view + 5) = (unsigned char)params->view_cnt;
		*(view + 6) = (unsigned char)params->view_number;
		*(view + 7) = (unsigned char)params->quality;
		*(view + 8) = (unsigned char)params->impression_type;
		write_be16(params->width, view + 9);
		write_be16(params->height, view + 11);
		*(view + 13) = 0;
	}

	/****************************************************************************************************/
	/* FMD functions */

	static inline void dpfj_get_fmd_record_params(DPFJ_FMD_FORMAT fmd_type, const unsigned char* fmd, DPFJ_FMD_RECORD_PARAMS* params){
		if(NULL == fmd) return;

		int off = 0;
		if(DPFJ_FMD_ANSI_378_2004 == fmd_type){
			params->record_length = read_be16(fmd + 8);
			params->cbeff_id = read_be32(fmd + 10);
			off = 2;
			if(0 == params->record_length){
				params->record_length = read_be32(fmd + 10);
				params->cbeff_id = read_be32(fmd + 14);
				off = 6;
			}
		}
		else if(DPFJ_FMD_ISO_19794_2_2005 == fmd_type){
			params->record_length = read_be32(fmd + 8);
			params->cbeff_id = 0;
		}
		else return;

		params->capture_equipment_comp = *(fmd + 12 + off) & 0xf0;
		params->capture_equipment_id = read_be16(fmd + 12 + off) & 0x0fff;
		params->width = read_be16(fmd + 14 + off);
		params->height = read_be16(fmd + 16 + off);
		params->resolution = read_be16(fmd + 18 + off);
		params->view_cnt = *(fmd + 22 + off);
	}

	static inline void dpfj_set_fmd_record_params(const DPFJ_FMD_RECORD_PARAMS* params, DPFJ_FMD_FORMAT fmd_type, unsigned char* fmd){
		if(NULL == fmd) return;

		fmd[0] = 'F'; fmd[1] = 'M'; fmd[2] = 'R'; fmd[3] = 0;
		fmd[4] = ' '; fmd[5] = '2'; fmd[6] = '0'; fmd[7] = 0;

		int off = 0;
		if(DPFJ_FMD_ANSI_378_2004 == fmd_type){
			if(0xffff < params->record_length){
				off = 6;
				write_be32(params->record_length, fmd + 10);
				write_be32(params->cbeff_id, fmd + 14);
			}
			else{
				off = 2;
				write_be16(params->record_length, fmd + 8);
				write_be32(params->cbeff_id, fmd + 10);
			}
		}
		else if(DPFJ_FMD_ISO_19794_2_2005 == fmd_type){
			write_be32(params->record_length, fmd + 8);
		}
		else return;

		*(fmd + 12 + off) = (unsigned char)(((params->capture_equipment_comp & 0x0f) << 4) || ((params->capture_equipment_id >> 16) & 0x0f));
		*(fmd + 13 + off) = (unsigned char)(params->capture_equipment_id & 0xff);
		write_be16(params->width, fmd + 14 + off);
		write_be16(params->height, fmd + 16 + off);
		write_be16(params->resolution, fmd + 18 + off);
		write_be16(params->resolution, fmd + 20 + off);
		*(fmd + 22 + off) = (unsigned char)params->view_cnt;
		*(fmd + 23 + off) = 0;
	}

	static inline unsigned int dpfj_get_fmd_view_offset(DPFJ_FMD_FORMAT fmd_type, const unsigned char* fmd, unsigned int view_idx){
		if(NULL == fmd) return 0;

		DPFJ_FMD_RECORD_PARAMS rp = {0};
		dpfj_get_fmd_record_params(fmd_type, fmd, &rp);

		//check index
		if(view_idx >= rp.view_cnt) return 0; //invalid view index

		unsigned int pos = DPFJ_FMD_ISO_19794_2_2005_RECORD_HEADER_LENGTH;
		if(DPFJ_FMD_ANSI_378_2004 == fmd_type){
			pos = DPFJ_FMD_ANSI_378_2004_RECORD_HEADER_LENGTH;
			if(0xffff < rp.record_length) pos += 4;
		}
		unsigned int i = 0;
		for(i = 0; i < view_idx && pos < rp.record_length; i++){
			pos += (unsigned int)*(fmd + pos + 3) * DPFJ_FMD_ANSI_ISO_MINITIA_LENGTH + DPFJ_FMD_ANSI_ISO_VIEW_HEADER_LENGTH;
			pos += read_be16(fmd + pos) + 2;
		}

		//check if offset is valid
		if(pos >= rp.record_length) return 0;
		return pos;
	}

	static inline void dpfj_get_fmd_view_params(const unsigned char* view, DPFJ_FMD_VIEW_PARAMS* params){
		if(NULL == view) return;

		params->finger_position  = (DPFJ_FINGER_POSITION)*view;
		params->view_number      = (unsigned int)(*(view + 1) >> 4) & 0x0f;
		params->impression_type  = (DPFJ_SCAN_TYPE)(*(view + 1) & 0x0f);
		params->quality          = (unsigned int)*(view + 2);
		params->minutia_cnt      = (unsigned int)*(view + 3);
		params->ext_block_length = read_be16(view + 4 + params->minutia_cnt * DPFJ_FMD_ANSI_ISO_MINITIA_LENGTH);
		params->ext_block        = (unsigned char*)(view + 4 + params->minutia_cnt * DPFJ_FMD_ANSI_ISO_MINITIA_LENGTH + 2);
	}

	static inline void dpfj_set_fmd_view_params(const DPFJ_FMD_VIEW_PARAMS* params, unsigned char* view){
		if(NULL == view) return;

		*view       = (unsigned char)params->finger_position;
		*(view + 1) = (unsigned char)((params->view_number << 4) | (params->impression_type & 0x0f));
		*(view + 2) = (unsigned char)params->quality;
		*(view + 3) = (unsigned char)params->minutia_cnt;
		unsigned char* ext_block = view + 4 + params->minutia_cnt * DPFJ_FMD_ANSI_ISO_MINITIA_LENGTH;
		write_be16(params->ext_block_length, ext_block);
		ext_block += 2;
		if(ext_block != params->ext_block){
			unsigned int i = 0;
			for(i = 0; i < params->ext_block_length; i++) ext_block[i] = params->ext_block[i];
		}
	}

	/** \endcond */

#endif /* DPFJ_NO_IM_MANIPULATION */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DPFJ_H__ */
