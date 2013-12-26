#include "netapp.h"
#include "common.h"

extern const unsigned char html[];
enum{JDQ_1 = 1<<0,JDQ_2 = 1<<1,JDQ_3 = 1<<2,JDQ_4 = 1<<3,JDQ_5 = 1<<4,JDQ_6 = 1<<5};
void send_char(char ch);
struct TcpClientCon{
    struct tcp_pcb *pcb;
    struct ip_addr ipaddr;//server ip
    long port;
    char connected;
};

static struct TcpClientCon TcpClient;

static void app_delay()
{
    int i;
    for(i=0;i<1000;i++);
}
void jdq_pro(u8 nData)
{
	if(nData & JDQ_1){
		JDQ1(0);
	}else{
		JDQ1(1);
	}
	if(nData & JDQ_2){
		JDQ2(0);
	}else{
		JDQ2(1);
	}
	if(nData & JDQ_3){
		JDQ3(0);
	}else{
		JDQ3(1);
	}
	if(nData & JDQ_4){
		JDQ4(0);
	}else{
		JDQ4(1);
	}
	if(nData & JDQ_5){
		JDQ5(0);
	}else{
		JDQ5(1);
	}
	if(nData & JDQ_6){
		JDQ6(0);
	}else{
		JDQ6(1);
	}
}

void state_pro(U8 * p)
{
	*(p+6) = 0x00;
	*(p+9) = (GPIOA->ODR & 1<<4)?(*(p+9) & (~(1<<0))):(*(p+9) | 1<<0);
	*(p+9) = (GPIOA->ODR & 1<<5)?(*(p+9) & (~(1<<1))):(*(p+9) | 1<<1);
	*(p+9) = (GPIOB->ODR & 1<<1)?(*(p+9) & (~(1<<2))):(*(p+9) | 1<<2);
	*(p+9) = (GPIOA->ODR & 1<<2)?(*(p+9) & (~(1<<3))):(*(p+9) | 1<<3);
	*(p+9) = (GPIOA->ODR & 1<<1)?(*(p+9) & (~(1<<4))):(*(p+9) | 1<<4);
	*(p+9) = (GPIOA->ODR & 1<<0)?(*(p+9) & (~(1<<5))):(*(p+9) | 1<<5);

	*(p+10) = INPUT_0_PIN ? (*(p+10) | 1<<0) : (*(p+10) & (~(1<<0)));
	*(p+10) = INPUT_1_PIN ? (*(p+10) | 1<<1) : (*(p+10) & (~(1<<1)));
	*(p+10) = INPUT_2_PIN ? (*(p+10) | 1<<2) : (*(p+10) & (~(1<<2)));
	*(p+10) = INPUT_3_PIN ? (*(p+10) | 1<<3) : (*(p+10) & (~(1<<3)));
	*(p+10) = INPUT_4_PIN ? (*(p+10) | 1<<4) : (*(p+10) & (~(1<<4)));
	*(p+10) = INPUT_5_PIN ? (*(p+10) | 1<<5) : (*(p+10) & (~(1<<5)));
	*(p+10) = INPUT_6_PIN ? (*(p+10) | 1<<6) : (*(p+10) & (~(1<<6)));
	*(p+10) = INPUT_7_PIN ? (*(p+10) | 1<<7) : (*(p+10) & (~(1<<7)));
}

void UDP_Receive(void *arg, struct udp_pcb *upcb, struct pbuf *p,struct ip_addr *addr, u16_t port) 
{ 
    struct ip_addr ipaddr=*addr;
    char *pt=NULL;
    if(p != NULL)
    {
	app_delay();
        udp_sendto(upcb,p,&ipaddr,port);  /* 将收到的数据再发送出去                   */
        pt=p->payload;
        pbuf_free(p);                                           /*  释放缓冲区数据                      */
    } 
} 

/* UDP 客户端建立，IP_ADDR_ANY为本机IP，UDP_Receiv为客户端接收到数据 */
const static char UDPData[]={"LwIP UDP客户端测试\r\n"}; 
void UDP_Test(void) 
{ 
    struct udp_pcb *UdpPcb; 
    struct ip_addr ipaddr;
    struct pbuf *p;
    p = pbuf_alloc(PBUF_RAW,sizeof(UDPData),PBUF_RAM);
    if(p==NULL)
        return;
    p->payload=(void *)UDPData;
    UdpPcb=udp_new();                                       /*  建立UDP 通信的控制块(pcb)             */
    udp_bind(UdpPcb,IP_ADDR_ANY,8080);                      /*  绑定本地IP 地址                      */
    IP4_ADDR(&ipaddr,192, 168, 10, 100);
    udp_sendto(UdpPcb,p,&ipaddr,8080);                      /* 将收到的数据再发送出去                   */ 
    udp_recv(UdpPcb,UDP_Receive,NULL);                      /* 设置数据接收时的回调函数                   */

    LED1(1);
    LED2(1);
    LED3(1);
}


const static char TCP_TestData[]="This is LwIP TCP Client  在Luminary Cortex-M3 上的测试！\r\n"; 

/*******  这是一个回调函数，当TCP 客户端请求的连接建立时被调用********/ 
extern const char demo[];
err_t tcp_sended(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
    //printf("send len=%d\n",len);
    //tcp_write(tpcb,html,1200,0);
    return 0;
}


/* TCP 客户端接收到PC发送过来的数据，tcp_client_recv为数据处理*/
static err_t   tcp_client_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
	u8 temp[17];
    printf("TCP client receive 0: %s\n",p->payload);
    if(err == ERR_OK && p != NULL) {
        /* Inform TCP that we have taken the data. */
        tcp_recved(pcb, p->tot_len);
		tcp_write(pcb,p->payload,p->tot_len,0);   
        printf("TCP client receive : %s\n",p->payload);
		MEMCPY(temp,p->payload,14);
		printf("TCP client receive : %d\n",temp[9]);
    }
    else if(err == ERR_OK && p == NULL) {
        tcp_close(pcb);
	TcpClient.connected=0;
    }
    pbuf_free(p);
    return ERR_OK;
}


/* TCP 客户端接收到PC发送过来的数据，tcp_client_recv为数据处理*/
err_t TcpCli_Connected(void *arg,struct tcp_pcb *pcb,err_t err) 
{ 
    //printf("tcp connect %s",err ?"error":"ok");
    // tcp_write(pcb,html,1200,0);
    // tcp_sent(pcb, tcp_sended);
    tcp_arg(pcb,(void *)TCP_TestData);
    tcp_recv(pcb,tcp_client_recv);
    TcpClient.connected=1;
    return ERR_OK;

} 

void TCP_Client_Init(void);

/* TCP 客户端连接到服务器反馈*/
static void ClientConError(void *arg, err_t err)
{
    TcpClient.connected=0;
    printf("TCP connect to server %d \r\n",err);
}

/* TCP 客户端初始化 ，TcpClient.ipaddr连接到远程的服务器 ，*/
void TCP_Client_Init(void) 
{ 
    TcpClient.connected=1;
    IP4_ADDR(&TcpClient.ipaddr,192,168,1,3);
    TcpClient.port=8080;
    TcpClient.pcb=tcp_new();                  /*  建立通信的TCP 控制块(Clipcb)                */
    tcp_bind(TcpClient.pcb,IP_ADDR_ANY,0);    /*  绑定本地IP 地址和端口号*/
    tcp_err(TcpClient.pcb, ClientConError);
    tcp_connect(TcpClient.pcb,&TcpClient.ipaddr,
                TcpClient.port,TcpCli_Connected);
} 


void ReConTcpServer(void)
{
    if(!TcpClient.connected){
        TCP_Client_Init();
    }
}

/* TCP 服务器接收数据 server_recv 处理*/
static err_t   server_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
	u8 len = 15;
	u8 i;
    printf("TCP server receive:");
	for(i = 0;i< len;i++){
		printf("%x_",*((u8*)p->payload + i));
	}
	printf("\n");
    if(err == ERR_OK && p != NULL)
    {
        /* Inform TCP that we have taken the data. */
        tcp_recved(pcb, p->tot_len);

		if((*((u8*)p->payload) == 0xAA) && (*((u8*)p->payload+1) == 0x55) &&
			(*((u8*)p->payload+13) == 0xcc) && (*((u8*)p->payload+14) == 0xdd)){
			if(*((u8*)p->payload+6) == 0x01){
				state_pro((u8*)p->payload);
				tcp_write(pcb,p->payload,p->tot_len,0);
			}else if(*((u8*)p->payload+6) == 0x00){
				jdq_pro(*((u8*)p->payload+9));
				state_pro((u8*)p->payload);
				tcp_write(pcb,p->payload,p->tot_len,0);
			}
		}
		pbuf_free(p);
    }

    if(err == ERR_OK && p == NULL) {
		tcp_abort(pcb);
        tcp_close(pcb);
    }
    return ERR_OK;
}


/* TCP 服务器接收数据server_accept*/
static err_t server_accept(void *arg, struct tcp_pcb *pcb, err_t err)
{
    /* Tell TCP that this is the structure we wish to be passed for our callbacks. */
    tcp_arg(pcb, NULL);
    /* Tell TCP that we wish to be informed of incoming data by a call to the http_recv() function. */
    tcp_recv(pcb, server_recv);
    return ERR_OK;
}

/* TCP 服务器初始化，本地IP IP_ADDR_ANY，接收数据server_accept*/
void tcp_server_init(void)
{
    struct tcp_pcb *pcb;
    pcb = tcp_new();
    tcp_bind(pcb, IP_ADDR_ANY,8080);
    pcb = tcp_listen(pcb);
    //pcb = tcp_listen_with_backlog(pcb,1);
    tcp_accept(pcb, server_accept);
}













