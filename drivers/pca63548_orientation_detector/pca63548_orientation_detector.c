/*$$$LICENCE_NORDIC_STANDARD<2017>$$$*/
#include <string.h>
#include <errno.h>
#include <zephyr.h>
#include <misc/printk.h>
#include <device.h>
#include <spi.h>
#include <gpio.h>
#include <pca63548_orientation_detector.h>
#include <lis2dh12_types.h>

static pca63548_orientation_state_t m_current_orientation;

static const struct spi_config *my_spi;
static struct device *my_spi_dev;

#define NRF_SUCCESS 0
#define NRF_ERROR_NOT_FOUND 5
/*
static nrf_drv_spi_t const m_master = NRF_DRV_SPI_INSTANCE(1);  // SPIM1

static nrf_drv_spi_config_t m_master_config =
{
    .sck_pin      = ARDUINO_13_PIN,
    .mosi_pin     = ARDUINO_11_PIN,
    .miso_pin     = ARDUINO_12_PIN,
    .ss_pin       = ARDUINO_10_PIN,
    .irq_priority = APP_IRQ_PRIORITY_HIGH,
    .orc          = 0x00,
    .frequency    = NRF_DRV_SPI_FREQ_1M,
    .mode         = NRF_DRV_SPI_MODE_0,
    .bit_order    = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST,
};
*/

static int lis2dh12_read_data(const struct spi_config *config, u8_t reg, u8_t * p_content, u8_t num_regs)
{
	u8_t tx_buf[1];
    const struct spi_buf tx_bufs[] = {
		{
			.buf = tx_buf,
			.len = 1,
		},
	};
	const struct spi_buf rx_bufs[] = {
		{
			.buf = p_content,
			.len = num_regs+1,
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

    tx_buf[0] = reg | LIS2DH12_REG_READ;
    if (num_regs > 1)
    {
        tx_buf[0] |= LIS2DH12_REG_AUTO_INCREMENT;
    }
    if(spi_transceive(my_spi_dev, config, &tx, &rx))
	{
		printk("read data failed");
	}


    return 0;
}


static int lis2dh12_write_data(const struct spi_config *config ,u8_t reg, u8_t content)
{
    u8_t tx_buf[2];
    u8_t rx_buf[1];

	  const struct spi_buf tx_bufs[] = {
		{
			.buf = tx_buf,
			.len = 2,
		},
	};
	const struct spi_buf rx_bufs[] = {
		{
			.buf = rx_buf,
			.len = 0,
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

    tx_buf[0] = reg;
    tx_buf[1] = content;

    if(spi_transceive(my_spi_dev, config, &tx, &rx))
		{
		printk("write data failed");
	}
	

    return 0;
}

static int lis2dh12_setup_10Hz_8_bit_low_power(const struct spi_config *config )
{
    int err_code;
    u8_t setup_data = (LIS2DH12_ODR_10Hz << 4) | LIS2DH12_CTRL_REG1_LPEN |
                         LIS2DH12_CTRL_REG1_ZEN | LIS2DH12_CTRL_REG1_YEN | LIS2DH12_CTRL_REG1_XEN;

    err_code = lis2dh12_write_data(config, LIS2DH12_CTRL_REG1, setup_data);

    return err_code;
}

// static int lis2dh12_setup_1Hz_8_bit_low_power(const struct spi_config *config )
// {
//     int err_code;
//     u8_t setup_data = (LIS2DH12_ODR_1Hz << 4) | LIS2DH12_CTRL_REG1_LPEN |
//                          LIS2DH12_CTRL_REG1_ZEN | LIS2DH12_CTRL_REG1_YEN | LIS2DH12_CTRL_REG1_XEN;

//     err_code = lis2dh12_write_data(config, LIS2DH12_CTRL_REG1, setup_data);

//     return err_code;
// }

static int lis2dh12_get_acceleration_data(const struct spi_config *config , s8_t * p_acceleration_data)
{
    int err_code;
    u8_t    sensordata[7];
    s8_t    rx_buf[2];



    err_code = lis2dh12_read_data(config, LIS2DH12_STATUS_REG, rx_buf, 1);

	if(!err_code)
	{
		if (rx_buf[1] & LIS2DH12_ZYXDA)
		{
			err_code = lis2dh12_read_data(config,LIS2DH12_OUT_X_L, sensordata, 6);
			p_acceleration_data[0] = sensordata[2];
			p_acceleration_data[1] = sensordata[4];
			p_acceleration_data[2] = sensordata[6];
		}
		else
		{
			err_code = -1;
		}

	}
    return err_code;
}


int lisdh12_init(const struct spi_config *config)
{
    uint8_t rx_buf[2];
    int err_code;


    err_code = lis2dh12_write_data(config, LIS2DH12_CTRL_REG5, LIS2DH12_CTRL_REG5_BOOT);
    if(err_code)
      return -1;

    //k_sleep(LIS2DH12_BOOT_DELAY_MS);

    err_code = lis2dh12_read_data(config, LIS2DH12_WHO_AM_I, rx_buf, 1);
    if(err_code)
      return -1;

    if (rx_buf[1] != LIS2DH12_I_AM_LIS2DH12)
    {
        err_code = NRF_ERROR_NOT_FOUND;
    }
    else
    {
        err_code = lis2dh12_setup_10Hz_8_bit_low_power(config);
    }

    return err_code;
}

int pca63548_orientation_detector_poll(pca63548_orientation_detector_sensor_data_t * p_sensor_data)
{
    int err_code;

    err_code = lis2dh12_get_acceleration_data(my_spi, (int8_t *)p_sensor_data);

    if (err_code == NRF_SUCCESS)
    {
        switch (m_current_orientation)
        {
            case ORIENTATION_NORMAL:
                if (p_sensor_data->z < -40)
                {
                    m_current_orientation = ORIENTATION_UPSIDE_DOWN;
                }
                else if (p_sensor_data->z < 40)
                {
                    m_current_orientation = ORIENTATION_ON_SIDE;
                }
                break;

            case ORIENTATION_ON_SIDE:
                if (p_sensor_data->z < -50)
                {
                    m_current_orientation = ORIENTATION_UPSIDE_DOWN;
                }
                else if (p_sensor_data->z > 50)
                {
                    m_current_orientation = ORIENTATION_NORMAL;
                }
                break;

            case ORIENTATION_UPSIDE_DOWN:
                if (p_sensor_data->z > 40)
                {
                    m_current_orientation = ORIENTATION_NORMAL;
                }
                else if (p_sensor_data->z > -50)
                {
                    m_current_orientation = ORIENTATION_ON_SIDE;
                }
                break;

            default:
                break;
        }
    }
    p_sensor_data->orientation = m_current_orientation;

    return err_code;
}


int pca63548_orientation_detector_init(struct device *spi_dev, const struct spi_config *config)
{
    my_spi_dev=spi_dev;
    my_spi=config;
    m_current_orientation = ORIENTATION_NORMAL;
    return lisdh12_init(my_spi);
}
