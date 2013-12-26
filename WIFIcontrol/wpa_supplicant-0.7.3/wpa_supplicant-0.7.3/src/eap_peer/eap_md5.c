/*
 * EAP peer method: EAP-MD5 (RFC 3748 and RFC 1994)
 * Copyright (c) 2004-2006, Jouni Malinen <j@w1.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 */

#include "includes.h"

#include "wpa_common.h"
#include "eap_i.h"
#include "eap_common/chap.h"


static void * eap_md5_init(struct eap_sm *sm)
{
	/* No need for private data. However, must return non-NULL to indicate
	 * success. */
	return (void *) 1;
}


static void eap_md5_deinit(struct eap_sm *sm, void *priv)
{
}


static struct wpabuf * eap_md5_process(struct eap_sm *sm, void *priv,
				       struct eap_method_ret *ret,
				       const struct wpabuf *reqData)
{
	struct wpabuf *resp;
	const u8 *pos, *challenge, *password;
	u8 *rpos, id;
	size_t len, challenge_len, password_len;


	/*
	 * CHAP Response:
	 * Value-Size (1 octet) | Value(Response) | Name(optional)
	 */
	wpabuf_put_u8(resp, CHAP_MD5_LEN);

	id = eap_get_id(resp);
	rpos = wpabuf_put(resp, CHAP_MD5_LEN);
	chap_md5(id, password, password_len, challenge, challenge_len, rpos);
	wpa_hexdump(MSG_MSGDUMP, "EAP-MD5: Response", rpos, CHAP_MD5_LEN);

	return resp;
}


int eap_peer_md5_register(void)
{
	struct eap_method *eap;
	int ret;

	return ret;
}
