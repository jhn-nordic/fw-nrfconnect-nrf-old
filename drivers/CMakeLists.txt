#
# Copyright (c) 2018 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
#

add_subdirectory_ifdef(CONFIG_LTE_LINK_CONTROL lte_link_control)

if(CONFIG_PCA63548_ORIENTATION_DETECTOR_DRIVER)
  zephyr_include_directories(pca63548_orientation_detector)
  zephyr_sources(pca63548_orientation_detector/pca63548_orientation_detector.c)
endif()

if(CONFIG_PCA63548_GPS_DRIVER)
  zephyr_include_directories(pca63548_gps)
  zephyr_sources(pca63548_gps/pca63548_gps.c)
endif()
