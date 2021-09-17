
/*************************************************************************
   LAB 1                                                                

    Edit this file ONLY!

*************************************************************************/



#include "dns.h"
#include "Treap.h"
#include "stdio.h"

typedef struct {
    DNSHandle Handle;
    struct Node* Hosts;
}DNSserver;

DNSserver servers[5];

DNSHandle InitDNS( )
{
    for(int i = 1; i < 6; i++)
        if (servers[i-1].Handle == 0)
        {
            servers[i-1].Handle = i;
            servers[i-1].Hosts = InitTreap(malloc(0), 0);
            return (DNSHandle)i;
        }
    return (DNSHandle)0;
}

void LoadHostsFile( DNSHandle hDNS, const char* hostsFilePath )
{
    
    if (servers[(int)hDNS - 1].Handle != 0)
    {
        FILE* HostsFile = fopen(hostsFilePath, "r");

        if (HostsFile == NULL)
        {
            perror("Error occured while opening hostsFile");
            exit(0);
        }


        while (feof(HostsFile) == 0)
        {
            char* Domen = malloc(70*sizeof(char));
            unsigned int ip1 = 0, ip2 = 0, ip3 = 0, ip4 = 0;
            fscanf(HostsFile, "%d.%d.%d.%d %s", &ip1, &ip2, &ip3, &ip4, Domen);
            unsigned int IP = (ip1 & 0xFF) << 24 |
                (ip2 & 0xFF) << 16 |
                (ip3 & 0xFF) << 8 |
                (ip4 & 0xFF);
            Insert(&servers[hDNS - 1].Hosts, Domen, IP);
        }
        fclose(HostsFile);
    }
}

IPADDRESS DnsLookUp( DNSHandle hDNS, const char* hostName )
{
    if (servers[(int)hDNS - 1].Handle != 0)
    {
       return Find(servers[(int)hDNS - 1].Hosts, hostName);
    }

    return INVALID_IP_ADDRESS;
}

void ShutdownDNS( DNSHandle hDNS )
{
    if (servers[(int)hDNS - 1].Handle != 0)
    {
        servers[(int)hDNS - 1].Handle = 0;
        Erase(servers[(int)hDNS - 1].Hosts);
    }
}

