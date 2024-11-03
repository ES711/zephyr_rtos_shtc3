#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

int main(void){
    const struct device *const dev = DEVICE_DT_GET_ANY(sensirion_shtc3);
    int rc;

	if (!device_is_ready(dev)) {
		printf("Device %s is not ready\n", dev->name);
		return 0;
	}

     while (true)
     {
        struct sensor_value temp, hum;
        rc = sensor_sample_fetch(dev);
        
        /*get temp & hum*/
        if(rc == 0){
            rc = sensor_channel_get(
                dev, 
                SENSOR_CHAN_AMBIENT_TEMP,
                &temp);
        }
        if (rc == 0)
        {
            rc = sensor_channel_get(
                dev, 
                SENSOR_CHAN_HUMIDITY,
                &hum);
        }
        /*get temp & hum*/

        /*error handle*/
        if (rc!= 0)
        {
            printf("shtc3 error, code: %d", rc);
            break;
        }
        
        printf("Temperature: %.2f °C\n", sensor_value_to_double(&temp));
        printf("Humidity: %.2f %%\n", sensor_value_to_double(&hum));

        k_sleep(K_SECONDS(2));
     }
     
}