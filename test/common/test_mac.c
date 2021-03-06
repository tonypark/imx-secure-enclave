/*
 * Copyright 2022 NXP
 *
 * NXP Confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#include <stdio.h>

#include "hsm_api.h"

#define MAC_KEY_GROUP	1001

static uint8_t  test_msg[300] = {
	/* Note that the first 32 Bytes are the "Z" value
	 * that can be retrieved.
	 */
	0xB2, 0xE1, 0x4C, 0x5C, 0x79, 0xC6, 0xDF, 0x5B, 0x85, 0xF4, 0xFE, 0x7E,
	0xD8, 0xDB, 0x7A, 0x26,	0x2B, 0x9D, 0xA7, 0xE0, 0x7C, 0xCB, 0x0E, 0xA9,
	0xF4, 0x74, 0x7B, 0x8C, 0xCD, 0xA8, 0xA4, 0xF3, 0x6D, 0x65, 0x73, 0x73,
	0x61, 0x67, 0x65, 0x20, 0xB2, 0xE1, 0x4C, 0x5C, 0x79, 0xC6, 0xDF, 0x5B,
	0x85, 0xF4, 0xFE, 0x7E, 0xD8, 0xDB, 0x7A, 0x26, 0x2B, 0x9D, 0xA7, 0xE0,
	0x7C, 0xCB, 0x0E, 0xA9,	0xF4, 0x74, 0x7B, 0x8C, 0xCD, 0xA8, 0xA4, 0xF3,
	0x6D, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x20,	0xB2, 0xE1, 0x4C, 0x5C,
	0x79, 0xC6, 0xDF, 0x5B, 0x85, 0xF4, 0xFE, 0x7E, 0xD8, 0xDB, 0x7A, 0x26,
	0x2B, 0x9D, 0xA7, 0xE0, 0x7C, 0xCB, 0x0E, 0xA9, 0xF4, 0x74, 0x7B, 0x8C,
	0xCD, 0xA8, 0xA4, 0xF3,	0x6D, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x20,
	0xB2, 0xE1, 0x4C, 0x5C, 0x79, 0xC6, 0xDF, 0x5B, 0x85, 0xF4, 0xFE, 0x7E,
	0xD8, 0xDB, 0x7A, 0x26, 0x2B, 0x9D, 0xA7, 0xE0, 0x7C, 0xCB, 0x0E, 0xA9,
	0xF4, 0x74, 0x7B, 0x8C, 0xCD, 0xA8, 0xA4, 0xF3, 0x6D, 0x65, 0x73, 0x73,
	0x61, 0x67, 0x65, 0x20,	0xB2, 0xE1, 0x4C, 0x5C, 0x79, 0xC6, 0xDF, 0x5B,
	0x85, 0xF4, 0xFE, 0x7E, 0xD8, 0xDB, 0x7A, 0x26,	0x2B, 0x9D, 0xA7, 0xE0,
	0x7C, 0xCB, 0x0E, 0xA9, 0xF4, 0x74, 0x7B, 0x8C, 0xCD, 0xA8, 0xA4, 0xF3,
	0x6D, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x20, 0xB2, 0xE1, 0x4C, 0x5C,
	0x79, 0xC6, 0xDF, 0x5B,	0x85, 0xF4, 0xFE, 0x7E, 0xD8, 0xDB, 0x7A, 0x26,
	0x2B, 0x9D, 0xA7, 0xE0, 0x7C, 0xCB, 0x0E, 0xA9,	0xF4, 0x74, 0x7B, 0x8C,
	0xCD, 0xA8, 0xA4, 0xF3, 0x6D, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x20,
	0xB2, 0xE1, 0x4C, 0x5C, 0x79, 0xC6, 0xDF, 0x5B, 0x85, 0xF4, 0xFE, 0x7E,
	0xD8, 0xDB, 0x7A, 0x26,	0x2B, 0x9D, 0xA7, 0xE0, 0x7C, 0xCB, 0x0E, 0xA9,
	0xF4, 0x74, 0x7B, 0x8C, 0xCD, 0xA8, 0xA4, 0xF3,	0x6D, 0x65, 0x73, 0x73,
	0x61, 0x67, 0x65, 0x20, 0xB2, 0xE1, 0x4C, 0x5C, 0x79, 0xC6, 0xDF, 0x5B,
	0x85, 0xF4, 0xFE, 0x7E, 0xD8, 0xDB, 0x7A, 0x26, 0x2B, 0x9D, 0xA7, 0xE0,
};

static hsm_err_t generate_key(hsm_hdl_t key_mgmt_hdl,
			      hsm_key_info_t key_info,
			      hsm_key_type_t key_type,
			      uint32_t *key_identifier)
{
	op_generate_key_args_t key_gen_args = {0};

	key_gen_args.key_identifier = key_identifier;
	key_gen_args.out_size = 0;
	key_gen_args.flags = HSM_OP_KEY_GENERATION_FLAGS_CREATE;
	key_gen_args.key_group = MAC_KEY_GROUP;
	key_gen_args.key_info = key_info;
	key_gen_args.key_type = key_type;
	key_gen_args.out_key = NULL;

	return hsm_generate_key(key_mgmt_hdl, &key_gen_args);
}

hsm_err_t mac_one_go_test(uint32_t key_identifier, hsm_hdl_t sg0_mac_hdl,
			  hsm_op_mac_one_go_algo_t algo,
			  uint16_t payload_size, uint16_t mac_size,
			  uint16_t verify_mac_size)
{
	op_mac_one_go_args_t mac_one_go;
	hsm_mac_verification_status_t mac_status;
	hsm_err_t err;
	uint8_t work_area[128] = {0};

	mac_one_go.key_identifier = key_identifier;
	mac_one_go.algorithm = algo;
	mac_one_go.flags = HSM_OP_MAC_ONE_GO_FLAGS_MAC_GENERATION;
	mac_one_go.payload = test_msg;
	mac_one_go.mac = work_area;
	mac_one_go.payload_size = payload_size;
	mac_one_go.mac_size = mac_size;
	err = hsm_mac_one_go(sg0_mac_hdl, &mac_one_go, &mac_status);
	if (err)
		printf("\n\terr: 0x%x hsm_mac_one_go GEN hdl: 0x%08x\n",
				err, sg0_mac_hdl);

	mac_one_go.key_identifier = key_identifier;
	mac_one_go.algorithm = algo;
	mac_one_go.flags = HSM_OP_MAC_ONE_GO_FLAGS_MAC_VERIFICATION;
	mac_one_go.payload = test_msg;
	mac_one_go.mac = work_area;
	mac_one_go.payload_size = payload_size;
	mac_one_go.mac_size = verify_mac_size;
	err = hsm_mac_one_go(sg0_mac_hdl, &mac_one_go, &mac_status);
	if (err)
		printf("\n\terr: 0x%x hsm_mac_one_go GEN hdl: 0x%08x\n",
				err, sg0_mac_hdl);

	if (mac_status == HSM_MAC_VERIFICATION_STATUS_SUCCESS) {
		printf(" --> SUCCESS\n");
	} else {
		printf("\t --> FAILURE\n");
	}
}

hsm_err_t do_mac_test(hsm_hdl_t key_store_hdl, hsm_hdl_t key_mgmt_hdl)
{
	hsm_err_t err;
	open_svc_mac_args_t mac_srv_args;
	hsm_hdl_t sg0_mac_hdl;
	uint32_t sym_key_id;

	if (!key_store_hdl)
		return -1;

	// mac test
	printf("\n---------------------------------------------------\n");
	printf("MAC ONE GO Test:\n");
	printf("---------------------------------------------------\n");
	mac_srv_args.flags = 0u;
	err = hsm_open_mac_service(key_store_hdl, &mac_srv_args, &sg0_mac_hdl);
	if (err)
		printf("err: 0x%x hsm_open_mac_service err: hdl: 0x%08x\n",
				err, sg0_mac_hdl);

	printf("HSM_KEY_TYPE_AES_256 & HSM_OP_MAC_ONE_GO_ALGO_AES_CMAC:");
	generate_key(key_mgmt_hdl, HSM_KEY_INFO_TRANSIENT,
			HSM_KEY_TYPE_AES_256, &sym_key_id);
	mac_one_go_test(sym_key_id, sg0_mac_hdl,
			HSM_OP_MAC_ONE_GO_ALGO_AES_CMAC, 32, 16, 8);

	printf("HSM_KEY_TYPE_AES_128 & HSM_OP_MAC_ONE_GO_ALGO_AES_CMAC:");
	generate_key(key_mgmt_hdl, HSM_KEY_INFO_TRANSIENT,
			HSM_KEY_TYPE_AES_128, &sym_key_id);
	mac_one_go_test(sym_key_id, sg0_mac_hdl,
			HSM_OP_MAC_ONE_GO_ALGO_AES_CMAC, 16, 16, 8);

#if PLAT_ELE_FEAT_NOT_SUPPORTED
	printf("HSM_KEY_TYPE_HMAC_224 & HSM_OP_MAC_ONE_GO_ALGO_HMAC_SHA_224:");
	generate_key(key_mgmt_hdl, HSM_KEY_INFO_TRANSIENT,
			HSM_KEY_TYPE_HMAC_224, &sym_key_id);
	mac_one_go_test(sym_key_id, sg0_mac_hdl,
			HSM_OP_MAC_ONE_GO_ALGO_HMAC_SHA_224, 28, 28, 28);

	printf("HSM_KEY_TYPE_HMAC_256 & HSM_OP_MAC_ONE_GO_ALGO_HMAC_SHA_256:");
	generate_key(key_mgmt_hdl, HSM_KEY_INFO_TRANSIENT,
			HSM_KEY_TYPE_HMAC_256, &sym_key_id);
	mac_one_go_test(sym_key_id, sg0_mac_hdl,
			HSM_OP_MAC_ONE_GO_ALGO_HMAC_SHA_256, 32, 32, 32);

	printf("HSM_KEY_TYPE_HMAC_384 & HSM_OP_MAC_ONE_GO_ALGO_HMAC_SHA_384:");
	generate_key(key_mgmt_hdl, HSM_KEY_INFO_TRANSIENT,
			HSM_KEY_TYPE_HMAC_384, &sym_key_id);
	mac_one_go_test(sym_key_id, sg0_mac_hdl,
			HSM_OP_MAC_ONE_GO_ALGO_HMAC_SHA_384, 32, 16, 8);

	printf("HSM_KEY_TYPE_HMAC_512 & HSM_OP_MAC_ONE_GO_ALGO_HMAC_SHA_512:");
	generate_key(key_mgmt_hdl, HSM_KEY_INFO_TRANSIENT,
			HSM_KEY_TYPE_HMAC_512, &sym_key_id);
	mac_one_go_test(sym_key_id, sg0_mac_hdl,
			HSM_OP_MAC_ONE_GO_ALGO_HMAC_SHA_512, 32, 16, 8);
#endif

	err = hsm_close_mac_service(sg0_mac_hdl);
	printf("0x%x hsm_close_mac_service hdl: 0x%x\n", err, sg0_mac_hdl);
	printf("---------------------------------------------------\n\n");

	return err;

}
