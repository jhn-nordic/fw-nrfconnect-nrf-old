/*$$$LICENCE_NORDIC_STANDARD<2017>$$$*/
#include <string.h>
#include <errno.h>
#include <zephyr.h>
#include <misc/printk.h>
#include <device.h>
#include <spi.h>
#include <gpio.h>
#include <pca63548_gps.h>
#include <string.h>

#define NMEA_SENTENCE           "$GPGGA" //NMEA sentence that is searched for
#define SPI_MAX_SIZE_DMA_BUFFER 250
#define GPS_RX_BUFFER_SIZE      80

static uint8_t              m_nmea_buffer[1024];
static struct device *my_spi_dev;

#define NRF_SUCCESS 0
#define NRF_ERROR_NOT_FOUND 5
#define NRF_ERROR_INVALID_LENGTH   9 


#define GPS_POWER_CONTROL      25 //ARDUINO_A0_PIN
#define GPS_ON            24 //ARDUINO_A5_PIN
#define GPS_WAKEUP        6 //ARDUINO_6_PIN
#define GPS_RESET         8 //ARDUINO_8_PIN
#define GPS_TRANSFER_DONE 0xAA

static struct device *gpiob;
static const struct spi_config *my_spi;

static int NMEA_search(const char * p_buffer, const char * p_NMEA_token,
                              char ** p_NMEA_sentence, uint16_t * p_length)
{
    *p_NMEA_sentence = (char *)strstr(p_buffer, p_NMEA_token);

    if (*p_NMEA_sentence != NULL)
    {
        char * p_ret = strchr(*p_NMEA_sentence, '\n');
        if (p_ret)
        {
            *p_length = p_ret - (*p_NMEA_sentence) + 1;
        }
        else
        {
            return NRF_ERROR_NOT_FOUND;
        }
    }
    else
    {
        return NRF_ERROR_NOT_FOUND;
    }

    return NRF_SUCCESS;
}


static int read_data(const struct spi_config *config, char * p_data)
{
    uint16_t   length;
    char *     p_nmea_string     = NULL;
    uint8_t    gps_transfer_done = 0;
    int err_code          = NRF_SUCCESS;

    while (gps_transfer_done < 4)
    {
        const struct spi_buf tx_bufs[] = {
          {
              .buf = NULL,
              .len = 0,
            },
        };
        const struct spi_buf rx_bufs[] = {
          {
            .buf =  &m_nmea_buffer[gps_transfer_done * SPI_MAX_SIZE_DMA_BUFFER],
            .len = SPI_MAX_SIZE_DMA_BUFFER,
          },
        };
        const struct spi_buf_set tx = {
          .buffers = tx_bufs,
          .count = ARRAY_SIZE(tx_bufs)
        };
        const struct spi_buf_set rx = {
          .buffers = rx_bufs,
          .count = ARRAY_SIZE(rx_bufs)
        };
        err_code = spi_transceive(my_spi_dev, config, &tx, &rx);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        gps_transfer_done++;

        if ((m_nmea_buffer[(gps_transfer_done * SPI_MAX_SIZE_DMA_BUFFER)-1] == 0xB4)
            || (m_nmea_buffer[(gps_transfer_done * SPI_MAX_SIZE_DMA_BUFFER) - 1] == 0xA7))
        {
            m_nmea_buffer[gps_transfer_done * SPI_MAX_SIZE_DMA_BUFFER] = 0;

            if (NMEA_search((char *)m_nmea_buffer, NMEA_SENTENCE, &p_nmea_string, &length) == NRF_SUCCESS)
            {
                memcpy((void *)p_data, (void *)p_nmea_string, length);
                p_data[length] = 0;
                return NRF_SUCCESS;
            }
        }
    }

    return NRF_ERROR_NOT_FOUND;
}


int pca63548_gps_init(struct device * spi_dev, const struct spi_config *config, struct device *gpio_device)
{

  gpiob = gpio_device;
  my_spi = config;
  my_spi_dev=spi_dev;
  gpio_pin_configure(gpiob, 23, GPIO_DIR_OUT); //OD CS
	gpio_pin_write(gpiob, 23, 1); //OD CS
	gpio_pin_configure(gpiob, GPS_POWER_CONTROL, GPIO_DIR_OUT); //GPS_POWER_CONTROL
	gpio_pin_write(gpiob,GPS_POWER_CONTROL, 0); //GPS_POWER_CONTROL
	gpio_pin_configure(gpiob, GPS_ON, GPIO_DIR_OUT); //GPS_ON
	gpio_pin_write(gpiob,GPS_ON, 1);


    return NRF_SUCCESS;
}


int pca63548_gps_start(void)
{ 
    gpio_pin_write(gpiob,GPS_POWER_CONTROL, 1); //GPS_POWER_CONTROL

    return NRF_SUCCESS;
}


int pca63548_gps_poll(char * p_buffer, uint32_t buffer_len)
{
    if (buffer_len < GPS_RX_BUFFER_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    return read_data(my_spi, p_buffer); 
}
