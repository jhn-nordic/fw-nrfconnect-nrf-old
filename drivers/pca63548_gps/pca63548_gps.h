/*$$$LICENCE_NORDIC_STANDARD<2017>$$$*/
/**@file
 *
 * @defgroup drv_gps GPS driver
 * @{
 * @ingroup ext_drivers
 *
 * @brief Global Positioning System (GPS) driver.
 *
 * @details Simple driver to poll a NMEA string from a GPS module.
 *
 */

#ifndef GPS_H__
#define GPS_H__

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Function for configuring and setting up the GPS.
*
* @retval NRF_SUCCESS                  If the operation is successful.
*/
int pca63548_gps_init(struct device * spi_dev, const struct spi_config *config, struct device *gpio_device);


/**@brief Function for enabling the power to the GPS module.
*
* @retval NRF_SUCCESS                  If the operation is successful.
*/
int pca63548_gps_start(void);


/**@brief Function to poll gps module.
 *
 * @param[in] p_buffer                Pointer to a buffer that can store the NMEA string.
 * @param[in] buffer_len              Lenght of the buffer.
 *
 * @retval NRF_SUCCESS                If the operation is successful.
 * @retval NRF_ERROR_INVALID_LENGTH   If the provided buffer is too short.
 */
int pca63548_gps_poll(char * p_buffer, uint32_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif // GPS_H__

/** @} */
