#include "system.h"
#include "lwip.h"
#include "lwip/ip_addr.h"
#include "marvell_ops.h"
#include "parmcfg.h"
#include "netapp.h"
#include "yeelink.h"

#if 1

static void dns_found_callbackx(const char *name, struct ip_addr *ipaddr, void *callback_arg){
}

void recv_mac_event(int event)
{
    //���յ������쳣����״̬��Ϊ����
    if (event == 3 || event == 8 || event == 9 || event == 14 || event == 13 )
    {
        pgmarvel_priv->connect_status = LBS_DISCONNECTED;
    }
}

static int dns_test_test()
{
    struct ip_addr addr;
    err_t err;
    char hostname[]="www.yeelink.net";

    if (err = dns_gethostbyname((char*)(hostname), &(addr),dns_found_callbackx,NULL) == ERR_OK) {
    } else {
    }
}
#endif

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int  main (void)
{
    /*������ʼ��*/
    extern struct netif netif;
    extern int app_time;
    extern int app_time2;
    extern int newpower_time_out_current_state;
    extern int g_random;

    struct lbs_private *priv;
    char dhcp_ok=0;				//using by dhcp
    long *cfg_ip;
	static u8 state_in[8] = {0};
    extern char * psk_out;
    newpower_time_out_current_state = 0;

    /*оƬ������ʼ��*/
    RCC_Configuration();
    NVIC_Configuration();
    GPIO_Configuration();
    /*�û�������ʼ��*/
    MAR_POW(1);                         //�ر�wifiģ��

    USART_Configuration(CONSOLE_UART);  //���ô���1������̨
    printf("\n\r ############ www.csgsm.com ############ ("__DATE__ " - " __TIME__ ")\n\r\n\r");

    mem_init();         //�����Ȱ��ڴ��ʼ��Ū����
    //load_netcfg();//�����������ò���,�����Ҫ��������������Ϣ��FLASH������ش򿪴�ѡ������ڲ�flash���ܲ���Ч����ͻ����������һ���֡�

    priv=init_marvell_driver();         //��ʼ��marvellģ������,����SDIO�豸ö�٣������豸�̼��Ȳ���*/
    lbs_scan_worker(priv);              //ɨ��wifi������������priv->network�������У�ʹ��bss_descriptor�ṹ������*/
    printf("################scanning finish####################### \r\n");

    psk_out = mem_malloc(32);
    marvel_assoc_network(priv,marvel_ssid,marvel_key,marvel_mode);  //��������  ·���������ƣ�·���������룬ģʽ0·����|1adhocģʽ
    mem_free(psk_out);

    Init_lwIP();                        //��ʼ��Э��ջ
    printf("################lwIP stack  finish####################### \r\n");
    watch_dog_config();                 //���Ź�����

    cfg_ip=(long *)wireless_ip;
    if(*cfg_ip!=0)
    {
        //static ip,web config
        dhcp_ok=1;
#if LWIP_DHCP_SERVER
        if(marvel_mode=='1')        //adhoc mode start dhcp server
            dhcpsrv_start(&netif);  //dhcp server start
#endif
        httpd_init();               //������ҳ������
        printf("Http init [OK]\r\n");
        //TCP_Client_Init();          //����TCP�ͻ������ӵ�PC
        //printf("TCP Client init [OK]\r\n");
        tcp_server_init();          //����TCP������
        printf("TCP Server init [OK]\r\n");
        //netbios_init();
        printf("################all stack finish####################### \r\n");
    }


/***********************DHCP Assign IP**********************************************/
#if 0
    while(0)
    {
        // �����ǹر�DHCP �ͻ���
        unsigned char *pchr;
        if((priv->connect_status==LBS_DISCONNECTED)&&
           marvel_mode=='0')//AP����,��������,Ad-hoc������
        {
            printf("LBS_DISCONNECTED!!!\r\n");
            //NVIC_GenerateSystemReset();
            config_delay();
            config_delay();
            config_delay();
            lbs_scan_worker(priv);//ɨ��wifi������������priv->network�������У�ʹ��bss_descriptor�ṹ������*/
            printf("####################################### re scanning finish !\r\n");
            psk_out = mem_malloc(32);
            marvel_assoc_network(priv,marvel_ssid,marvel_key,marvel_mode);//��������
            mem_free(psk_out);
        }
        IWDG_ReloadCounter();
        ethernetif_input(&netif);
        IWDG_ReloadCounter();

        if((!dhcp_ok)&&(netif.dhcp!=NULL &&
                        netif.dhcp->offered_ip_addr.addr!=0 &&
                        netif.dhcp->offered_sn_mask.addr!=0 &&
                        netif.dhcp->offered_gw_addr.addr!=0)){
            dhcp_ok=1;
            pchr=(unsigned char *)&netif.dhcp->offered_ip_addr.addr;
            printf("dhcp ip=%d:%d:%d:%d\n",pchr[0],pchr[1],pchr[2],pchr[3]);
            pchr=(unsigned char *)&netif.dhcp->offered_gw_addr.addr;
            printf("dhcp gw=%d:%d:%d:%d\n",pchr[0],pchr[1],pchr[2],pchr[3]);
            netif_set_addr(&netif, &(netif.dhcp->offered_ip_addr),
                           &(netif.dhcp->offered_sn_mask),&(netif.dhcp->offered_gw_addr));
            printf("dhcp ok!\n");
            netif_set_default(&netif);    //reassign ip address
            netif_set_up(&netif);
            ip_init();
            dhcp_stop(&netif);
            httpd_init();
            TCP_Client_Init();
            tcp_server_init();
            netbios_init();
        }
        else if(dhcp_ok)//assign ip address ok
            break;
    }
#endif

/************************** network testing**************************************************************/
    while(1)
    {	
    	if(INPUT_0_PIN != state_in[0]){
			printf("INPUT_0_PIN:%d,state_in[0]:%d\r\n",INPUT_0_PIN,state_in[0]);
			state_in[0] = INPUT_0_PIN;
		}else if(INPUT_1_PIN != state_in[1]){
			printf("INPUT_1_PIN:%d,state_in[1]:%d\r\n",INPUT_1_PIN,state_in[1]);
			state_in[1] = INPUT_1_PIN;
		}else if(INPUT_2_PIN != state_in[2]){
			printf("INPUT_2_PIN:%d,state_in[2]:%d\r\n",INPUT_2_PIN,state_in[2]);
			state_in[2] = INPUT_2_PIN;
		}else if(INPUT_3_PIN != state_in[3]){
			printf("INPUT_3_PIN:%d,state_in[3]:%d\r\n",INPUT_3_PIN,state_in[3]);
			state_in[3] = INPUT_3_PIN;
		}else if(INPUT_4_PIN != state_in[4]){
			printf("INPUT_4_PIN:%d,state_in[4]:%d\r\n",INPUT_4_PIN,state_in[4]);
			state_in[4] = INPUT_4_PIN;
		}else if(INPUT_5_PIN != state_in[5]){
			printf("INPUT_5_PIN:%d,state_in[5]:%d\r\n",INPUT_5_PIN,state_in[5]);
			state_in[5] = INPUT_5_PIN;
		}else if(INPUT_6_PIN != state_in[6]){
			printf("INPUT_6_PIN:%d,state_in[6]:%d\r\n",INPUT_6_PIN,state_in[6]);
			state_in[6] = INPUT_6_PIN;
		}else if(INPUT_7_PIN != state_in[7]){
			printf("INPUT_7_PIN:%d,state_in[7]:%d\r\n",INPUT_7_PIN,state_in[7]);
			state_in[7] = INPUT_7_PIN;
		} 		
        if((priv->connect_status==LBS_DISCONNECTED)&&marvel_mode=='0')      //AP����,��������,Ad-hoc������
        {
            printf("LBS_DISCONNECTED!!!\r\n");
#if (AUTO_CONN == 1)
            //����Ͽ����ӽ�����������
            config_delay();
            config_delay();
            config_delay();
            lbs_scan_worker(priv);//ɨ��wifi������������priv->network�������У�ʹ��bss_descriptor�ṹ������*/
            printf("####################################### re scanning finish !\r\n");
            psk_out = mem_malloc(32);
            marvel_assoc_network(priv,marvel_ssid,marvel_key,marvel_mode);//��������
            mem_free(psk_out);
#elif (AUTO_CONN == 2)
            NVIC_GenerateSystemReset(); // reset system
#endif
        }

        IWDG_ReloadCounter();
        ethernetif_input(&netif);
        IWDG_ReloadCounter();
        timer_thread();
        IWDG_ReloadCounter();

        if(app_time>10)
        { // sleep 18 tick
            if (newpower_time_out_current_state != 8){
                continue;
            }
            app_time=0;
        }

        if (app_time2 > 50)
        {
            app_time2 = 0;
        }
    }
}
