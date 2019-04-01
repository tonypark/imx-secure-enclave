/*
 * Copyright 2019 NXP
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

#ifndef SECO_MU_IOCTL_H
#define SECO_MU_IOCTL_H

/* IOCTL definitions. */
struct seco_mu_ioctl_setup_iobuf {
	uint8_t *user_buf;
	uint32_t length;
	uint32_t flags;
	uint64_t seco_addr;
};
struct seco_mu_ioctl_shared_mem_cfg {
	uint32_t base_offset;
	uint32_t size;
};

#define SECO_MU_IO_FLAGS_IS_INTPUT	0x01
#define SECO_MU_IO_FLAGS_USE_SEC_MEM	0x02
#define SECO_MU_IO_FLAGS_USE_SHORT_ADDR	0x04

#define SECO_MU_IOCTL			0x0A /* like MISC_MAJOR. */
#define SECO_MU_IOCTL_ENABLE_CMD_RCV	_IO(SECO_MU_IOCTL, 0x01u)
#define SECO_MU_IOCTL_SHARED_BUF_CFG	_IOW(SECO_MU_IOCTL, 0x02u, struct seco_mu_ioctl_shared_mem_cfg)
#define SECO_MU_IOCTL_SETUP_IOBUF	_IOWR(SECO_MU_IOCTL, 0x03u, struct seco_mu_ioctl_setup_iobuf)

#endif
