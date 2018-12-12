/*$$$LICENCE_NORDIC_STANDARD<2017>$$$*/
/**@file
 *
 * @defgroup drv_acc Accel driver
 * @{
 * @ingroup ext_drivers
 * @brief   Orientation module.
 *
 * Module that use accelerometer data to detect its orientation
 */

#ifndef PCA63548_ORIENTATION_DETECTOR_H__
#define PCA63548_ORIENTATION_DETECTOR_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Orientation states. */
typedef enum
{
    ORIENTATION_NOT_KNOWN,      /**< Initial staste. Orientation not known. */
    ORIENTATION_NORMAL,         /**< Has normal orientation. */
    ORIENTATION_UPSIDE_DOWN,    /**< System is upside down. */
    ORIENTATION_ON_SIDE         /**< System is placed on its side. */
} pca63548_orientation_state_t;


/**@brief Struct containing current orientation and 3 axis acceleration data. */
typedef struct
{
    int8_t              x;              /** X-axis acceleration normalized to +- 2G. */
    int8_t              y;              /** y-axis acceleration normalized to +- 2G. */
    int8_t              z;              /** z-axis acceleration normalized to +- 2G. */
    pca63548_orientation_state_t orientation;    /** Current orientation. */
} pca63548_orientation_detector_sensor_data_t;


/**@brief Function for configuring and setting up the orientation detector.
*
* @retval NRF_SUCCESS                  If the operation is successful.
*/
int pca63548_orientation_detector_init(struct device * spi_dev, const struct spi_config *config);


/**@brief Function to poll the orientation detector.
 *
 * @param[in] p_sensor_data        Pointer to a orientation_detector_sensor_data_t struct where the orientation data will be stored.
 *
 * @retval NRF_SUCCESS             If the operation is successful.
 * @retval NRF_ERROR_NOT_FOUND     If there is no new data present since last poll.
 */
int pca63548_orientation_detector_poll(pca63548_orientation_detector_sensor_data_t * p_sensor_data);

#ifdef __cplusplus
}
#endif

#endif //  PCA63548_ORIENTATION_DETECTOR_H__

/** @} */
