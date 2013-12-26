#include "rxtx.h"
#include "type.h"
#include "common.h"
#include "hostcmd.h"
#include "dev.h"
#include "mac80211.h"
#include "mdef.h"
#include "types.h"
#include "marvel_main.h"
#include "marvell_ops.h"

#pragma pack(1)
struct ethhdr {
	unsigned char	h_dest[ETH_ALEN];	/* destination eth addr	*/
	unsigned char	h_source[ETH_ALEN];	/* source ether addr	*/
	__be16		h_proto;		/* packet type ID field	*/
} __attribute__((packed));

struct eth803hdr {
	u8 dest_addr[6];
	u8 src_addr[6];
	u16 h803_len;
} __attribute__((packed));

struct rfc1042hdr {
	u8 llc_dsap;
	u8 llc_ssap;
	u8 llc_ctrl;
	u8 snap_oui[3];
	u16 snap_type;
} __attribute__((packed));

struct rxpackethdr {
	struct eth803hdr eth803_hdr;
	struct rfc1042hdr rfc1042_hdr;
} __attribute__((packed));

struct rx80211packethdr {
	struct rxpd rx_pd;
	void *eth80211_hdr;
} __attribute__((packed));

#pragma pack()

/**
 *  @brief This function processes received packet and forwards it
 *  to kernel/upper layer
 *
 *  @param priv    A pointer to struct lbs_private
 *  @param skb     A pointer to skb which includes the received packet
 *  @return 	   0 or -1
 */
int lbs_process_rxed_packet(struct lbs_private *priv, char *buffer,u16 size)
{
	int ret = 0;
	struct rxpackethdr *p_rx_pkt;
	struct rxpd *p_rx_pd;
	int hdrchop;
	struct ethhdr *p_ethhdr;
	const u8 rfc1042_eth_hdr[] = { 0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00 };
	struct eth_packet *rx_ethpkt=&priv->rx_pkt;//����Ҫ����̫�����ݱ�
	lbs_deb_enter(LBS_DEB_RX);
	p_rx_pd = (struct rxpd *)buffer;//����״̬��Ϣ
	p_rx_pkt = (struct rxpackethdr *) ((u8 *)p_rx_pd +
		le32_to_cpu(p_rx_pd->pkt_ptr));//�õ����802.3��ͷ��Ϣ�ĵ�ַ
		
//	lbs_deb_hex(LBS_DEB_RX, "RX Data: Before chop rxpd", buffer,
	//	 min(size, 100));

	if (size < (ETH_HLEN + 8 + sizeof(struct rxpd))) {
		lbs_deb_rx("rx err: frame received with bad length\n");
		ret = 0;
		goto done;
	}
#ifdef MASK_DEBUG
	lbs_deb_rx("rx data: skb->len - pkt_ptr = %d-%zd = %zd\n",
		size, (size_t)le32_to_cpu(p_rx_pd->pkt_ptr),
		size - (size_t)le32_to_cpu(p_rx_pd->pkt_ptr));

	lbs_deb_hex(LBS_DEB_RX, "RX Data: Dest", p_rx_pkt->eth803_hdr.dest_addr,
		sizeof(p_rx_pkt->eth803_hdr.dest_addr));
	lbs_deb_hex(LBS_DEB_RX, "RX Data: Src", p_rx_pkt->eth803_hdr.src_addr,
		sizeof(p_rx_pkt->eth803_hdr.src_addr));
#endif
	if (memcmp(&p_rx_pkt->rfc1042_hdr,
		   rfc1042_eth_hdr, sizeof(rfc1042_eth_hdr)) == 0) {//����RFC1042�ж����SNAPͷ��Ϣ���Ƚ��Ƿ���rfc1042��װ��mac֡
		/*
		 *  Replace the 803 header and rfc1042 header (llc/snap) with an
		 *    EthernetII header, keep the src/dst and snap_type (ethertype)
		 *
		 *  The firmware only passes up SNAP frames converting
		 *    all RX Data from 802.11 to 802.2/LLC/SNAP frames.
		 *
		 *  To create the Ethernet II, just move the src, dst address right
		 *    before the snap_type.
		 */
		 //marvelоƬ����������Ϊ802.11LLC������ݰ���ʽ����snapͷ�����ڽ������Ϊ802.3��
		 //���ݱ���ʽ��ֻҪ��802.11macͷ��Ϣ�е�Դ��ַ��Ŀ�ĵ�ַ���Ƶ�snap���ұ߼��ɣ������ʽ��ο���ر�׼��
		 //mac֡��ʽ
		p_ethhdr = (struct ethhdr *)
		    ((u8 *) & p_rx_pkt->eth803_hdr
		     + sizeof(p_rx_pkt->eth803_hdr) + sizeof(p_rx_pkt->rfc1042_hdr)
		     - sizeof(p_rx_pkt->eth803_hdr.dest_addr)
		     - sizeof(p_rx_pkt->eth803_hdr.src_addr)
		     - sizeof(p_rx_pkt->rfc1042_hdr.snap_type));//�ҳ����802.3 MAC����ʼλ��

		memcpy(p_ethhdr->h_source, p_rx_pkt->eth803_hdr.src_addr,//ֱ�Ӹ���,�Ӻ���ǰ����
		       sizeof(p_ethhdr->h_source));
		memcpy(p_ethhdr->h_dest, p_rx_pkt->eth803_hdr.dest_addr,
		       sizeof(p_ethhdr->h_dest));

		/* Chop off the rxpd + the excess memory from the 802.2/llc/snap header
		 *   that was removed
		 */
		hdrchop = (u8 *)p_ethhdr - (u8 *)p_rx_pd;//�������¸���skb->data�ĵ�ַ������ʹ�õ���skb_pull
	} else {
		lbs_deb_hex(LBS_DEB_RX, "RX Data: LLC/SNAP",
			(u8 *) & p_rx_pkt->rfc1042_hdr,
			sizeof(p_rx_pkt->rfc1042_hdr));

		/* Chop off the rxpd */
		hdrchop = (u8 *)&p_rx_pkt->eth803_hdr - (u8 *)p_rx_pd;
	}

	/* Chop off the leading header bytes so the skb points to the start of
	 *   either the reconstructed EthII frame or the 802.2/llc/snap frame
	 */
	//skb_pull(skb, hdrchop);//ȥ��ǰ���rxtp�Լ�802.11mac

	rx_ethpkt->len=size-hdrchop;
	rx_ethpkt->data=(char *)((char *)buffer+hdrchop);//������������ݵ�������ŵ�ַ
	//dbg_netdata("rx network data",rx_ethpkt->data,rx_ethpkt->len);
	/* Take the data rate from the rxpd structure
	 * only if the rate is auto
	 */
#if 0
	if (priv->enablehwauto)
		priv->cur_rate = lbs_fw_index_to_data_rate(p_rx_pd->rx_rate);//��¼�µ�ǰ���ݴ��������

	lbs_compute_rssi(priv, p_rx_pd);//����Ʒ������RSSI�ź�ǿ��
#endif
	ret = 0;
done:
	lbs_deb_leave_args(LBS_DEB_RX, ret);
	return ret;
}


int  wait_for_data_end(void)
{	
	struct lbs_private *priv=pgmarvel_priv;
	struct if_sdio_card *card=priv->card;
	u8 cause;
	int ret;
	while(1){
		cause = sdio_readb(card->func, IF_SDIO_H_INT_STATUS, &ret);
		//��ȡ�ж�״̬������������ڲ����ж�״̬�Ĵ���,��sdio���������ж�״̬�Ĵ���û�й�ϵ
		if (ret){
			printk("marvel interrupt error!\n");
			return ret;
		}
		if (cause & IF_SDIO_H_INT_DNLD){//����Ӧ����������жϣ��������������յ�����
			sdio_writeb(card->func, ~IF_SDIO_H_INT_DNLD,IF_SDIO_H_INT_STATUS, &ret);//���жϹ����־λ
			if (ret)
				return ret;
			break;
		}
	}
        return 0;
}






