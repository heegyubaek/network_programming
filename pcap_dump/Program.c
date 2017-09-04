#include "ehpacket.h"
#include <stdio.h>
#include <arpa/inet.h>

#define MAX_PACKET  10
pcap_header headers[MAX_PACKET];
int pcnt;
int Parsing(FILE *fp);
int main()
{
    char fname[256];
    FILE *fp = 0;
    printf("���� ��:");
    scanf("%s",fname);
    fp = fopen(fname, "rb");//��޹��� ������ �б�/���̳ʸ����� ����

    printf("pcap_file_header[%d], timeval[%d], pcap_header[%d]\n", sizeof(pcap_file_header), sizeof(timeval), sizeof(pcap_header));

    Parsing(fp);//�м��ϱ�
    fclose(fp);//���� �ݱ�
    return 0;
}

void ParsingEthernet(FILE *fp);
int Parsing(FILE *fp)
{
    pcap_file_header pfh;
    fread(&pfh, sizeof(pfh), 1, fp);//pcap ���� ��� �б�    
    if (pfh.magic != MAGIC) //������ �ٸ���
    {
        printf("this file format is not correct \n");
        return -1;
    }
    printf("version:%d.%d\n", pfh.version_major, pfh.version_minor);//pcap ��� ���� ���
    
    switch (pfh.linktype)//��ũ Ÿ�Կ� ���
    {
    case 1:ParsingEthernet(fp); break; //Ethernet ������� �м�
    case 6:printf("Not support Token Ring\n");break;
    case 10:printf("Not support FDDI\n"); break;
    case 0:printf("Not support Loopback\n"); break;
    default:printf("Unknown\n"); break;
    }
    return 0;
}

void ViewPacketHeader(pcap_header *ph);
void ViewEthernet(char *buf);
void ParsingEthernet(FILE *fp)
{
    char buf[65536];
    pcap_header *ph = headers;//ph�� ��Ŷ ����� ���� ��ġ�� �ʱ�ȭ
    int i = 0;
    while (feof(fp) == 0) //������ ���� �ƴϸ� �ݺ�
    {
        if (fread(ph, sizeof(pcap_header), 1, fp) != 1)//��Ŷ ��� �б⸦ �����ϸ�
        {
            break;//���� Ż��
        }
        if (pcnt == MAX_PACKET) //����ź���� �м��� �� �ְ� ������ ��Ŷ ���� ����
        {
            break;//���� Ż��
        }
        ViewPacketHeader(ph); //��Ŷ ��� ���� ���
        fread(buf, 1, ph->caplen, fp); //��Ŷ �б�
        ViewEthernet(buf); //�̴��� ���� ���
        ph++;//ph�� ���� ��ġ�� �̵�
    }
}


void ViewPacketHeader(pcap_header *ph)
{
    pcnt++;//��Ŷ ������ 1 ����
    printf("\nNo:%dtime:%08d:%06d caplen:%u length:%u \n",
        pcnt, ph->ts.tv_sec, ph->ts.tv_usec, ph->caplen, ph->len);
}

void ViewMac(unsigned char *mac);
void ViewIP(char *buf);
void ViewARP(char *buf);
void ViewEthernet(char *buf)
{
    ethernet *ph = (ethernet *)buf; //��Ŷ ���۸� ethernet ����ü �����ͷ� �� ��ȯ
    printf("===========ETHERNET Header==============\n");
    printf("dest mac:0x");
    ViewMac(ph->dest_mac);//MAC �ּ� ���
    printf("  src mac:0x");
    ViewMac(ph->src_mac);//MAC �ּ� ���
    printf("  type:%#x\n", ntohs(ph->type));    
    //Link Ÿ���� ���(2����Ʈ �̻����ʹ� network byte order -> host byte order �� ��ȯ�ؾ� ��
    
    switch (ntohs(ph->type))
	{
    case 0x800:ViewIP(buf + sizeof(ethernet)); /*IP ���� ��� */ break;
    case 0x806:ViewARP(buf + sizeof(ethernet)); /*ARP ���� ���*/ break;
    default:printf("Not support Protocol [0x%x]\n", ntohs(ph->type)); break;
    }
}

void ViewMac(unsigned char *mac)
{
    int i;
    for (i = 0;i < MAC_ADDR_LEN; ++i)
    {
        printf("%02x ", mac[i]);
    }
}

ushort ip_checksum(ushort *base, int len);
void ViewIP(char *buf)
{
    struct sockaddr_in addr;
    iphdr *ip = (iphdr *)buf; //��Ŷ ���۸� ethernet ����ü �����ͷ� ��ȯ
    printf("\n=========== IPv4 Header ==============\n");

    bzero(&addr, sizeof(addr));
    addr.sin_addr.s_addr = htonl(ip->src_address);
    
    printf("src:%s, ", inet_ntoa(addr.sin_addr));

    addr.sin_addr.s_addr = htonl(ip->dst_address);
    printf("dst:%s\n", inet_ntoa(addr.sin_addr));

    printf("header length:%d bytes, ", ip->hlen * 4);
    printf("version:%d, ", ip->version);
    printf("total length:%d bytes\n", ntohs(ip->tlen));
    printf("id:%d, ", ntohs(ip->id));
    if (DONT_FRAG(ip->frag))
    {
        printf("Don't Fragment\n");
    }
    else
    {
        if (MORE_FRAG(ip->frag) == 0)
        {
            printf("last fragment, ");
        }
        printf("offset:%d ", FRAG_OFFSET(ip->frag));
    }
    if (ip_checksum((ushort *)buf, sizeof(iphdr)) == 0)
    {
        printf("checksum is correct, ");
    }
    else
    {
        printf("checksum is not correct, ");
    }
    printf("TTL:%d\n", ip->ttl);
    switch (ip->protocol)
    {
    case 1: printf("ICMP\n"); break;
    case 2: printf("IGMP\n"); break;
    case 6: printf("TCP\n"); break;
    case 17: printf("UDP\n"); break;
    case 89: printf("OSPF\n"); break;
    default: printf("Not support\n"); break;
    }
}
void ViewARP(char *buf)
{
    arphdr *arphd = (arphdr *)buf;
    printf("\n===========  ARP Header ==============\n");
    printf("h/w type: %u", ntohs(arphd->hwtype));
    if (ntohs(arphd->hwtype) == 1)
    {
        printf("  Ethernet");
    }
    printf("\nprotocol type:%#x", ntohs(arphd->prototype));
    if (ntohs(arphd->prototype) == 0x800)
    {
//        IN_ADDR addr;
        struct sockaddr_in addr;
        printf("  IP\n");
        printf("\n opcode: %d ", ntohs(arphd->opcode));
        
        printf("sender mac:0x");
        ViewMac(arphd->sender_mac);

        bzero(&addr, sizeof(addr));
        addr.sin_addr.s_addr = htonl(arphd->sender_address);

        printf("\nsender ip: %s\n", inet_ntoa(addr.sin_addr));
        
        printf("target mac:0x");
        ViewMac(arphd->target_mac);
        addr.sin_addr.s_addr = htonl(arphd->target_address);

        printf("\ntarget ip: %s\n", inet_ntoa(addr.sin_addr));
    }
}

ushort ip_checksum(ushort *base, int len)
{
    int nleft = len;
    int sum = 0;
    ushort *w = base;
    ushort answer = 0;
    while (nleft>1)
    {
        sum += *w;
        w++;
        nleft -= 2;
    }

    if (nleft == 1)
    {
        *(ushort *)(&answer) = *(uchar *)w;
        sum += answer;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    answer = ~sum;
    return (answer);
}
