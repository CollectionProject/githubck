#ifndef wpa_supp_linux_plat__
#define wpa_supp_linux_plat__


#define ETH_ALEN	6		/* Octets in one ethernet addr	 */
#define ETH_HLEN	14		/* Total octets in header.	 */
#define ETH_ZLEN	60		/* Min. octets in frame sans FCS */
#define ETH_DATA_LEN	1500		/* Max. octets in payload	 */
#define ETH_FRAME_LEN	1514		/* Max. octets in frame sans FCS */
#define ETH_FCS_LEN	4		/* Octets in the FCS		 */




#define abort(...)
#define exit(...)
#define alarm(...)

struct sockaddr 
{
	unsigned short sa_family; /* address family */
	char sa_data[14]; /* up to 14 bytes of direct address */
}; 




#endif