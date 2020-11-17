#include <autoconf.h>
#include <lwip_intf.h>
#include <lwip/netif.h>
#if !defined(CONFIG_MBED_ENABLED)
#include <lwip_netconf.h>
#include <ethernetif.h>
#endif
#include <osdep_service.h>
#include <wifi/wifi_util.h>
#include <string.h>
#include "sockets.h"
//----- ------------------------------------------------------------------
// External Reference
//----- ------------------------------------------------------------------
#if (CONFIG_LWIP_LAYER == 1)
extern struct netif xnetif[];			//LWIP netif
#endif

/*
 * Get all the data requested by SIOCGIFCONF for a particular interface.
 *
 * When ifc->ifc_ifreq == NULL, this function is being called for getting
 * the needed buffer length and not the actual data.
 */
int
SocketGetInterfaceConfig (void* ptr)
{
  struct ifconf* ifc = (struct ifconf*)ptr;
  struct netif *netif;
  struct ifreq *ifr;
  struct sockaddr_in *saddr;
  int i = 0;
  int n = ifc->ifc_len / sizeof (struct ifreq);

  for(i = 0; i<NET_IF_NUM; i++)
  {
    if(i<n)
    {  
        ifr = &ifc->ifc_req[i];
        saddr = (struct sockaddr_in *) &ifr->ifr_addr;
        netif = &xnetif[i];     
        memset (ifr, 0, sizeof (struct ifreq));
        strncpy (ifr->ifr_name, netif->name,2);
        saddr->sin_len = sizeof (struct sockaddr_in);
        saddr->sin_family = AF_INET;
        saddr->sin_addr.s_addr = netif_ip4_addr (netif)->addr;
    }
  }

  ifc->ifc_len = i*sizeof (struct ifreq);
}

static struct netif *
get_if (char *name,short *idx)
{
  char ifname[IFNAMSIZ];
  struct netif *netif;
  short i = 0;

  memcpy (ifname, name, IFNAMSIZ - 1);
  ifname[IFNAMSIZ - 1] = 0;

  for(i = 0; i<NET_IF_NUM; i++)
  {
    netif = &xnetif[i];
    if (strcmp (netif->name, ifname) == 0)
    {  
      *idx = i;
      break;
    }
  }

  return netif;
}

int
SocketGetInterfaceFlags (void* ptr)
{
  int err = 0;
  struct ifreq* ifr = (struct ifreq*)ptr;
  struct netif *netif;
  short idx = 0;
  netif = get_if (ifr->ifr_name,&idx);
  if (!netif)
    err = ENODEV;
  else
    {
      ifr->ifr_ifru.ifru_flags[0] = netif->flags;
    }

  return err;
  
}

int SocketGetInterfaceAddress(void* ptr)
{
  int err = 0;
  struct ifreq* ifr = (struct ifreq*)ptr;
  struct netif *netif;
  short idx = 0;
  netif = get_if (ifr->ifr_name,&idx);
  if (!netif)
    err = ENODEV;
  else
    {
      struct sockaddr_in* addr = (struct sockaddr_in*) &ifr->ifr_ifru.ifru_addr;
      addr->sin_len = sizeof(struct sockaddr_in);
      addr->sin_family = AF_INET;
      addr->sin_addr.s_addr = netif_ip4_addr(netif)->addr;
      return 0;
    }

  return err;
}

int SocketGetInterfaceNetmask(void* ptr)
{
  int err = 0;
  struct ifreq* ifr = (struct ifreq*)ptr;
  struct netif *netif;
  short idx = 0;
  netif = get_if (ifr->ifr_name,&idx);
  if (!netif)
    err = ENODEV;
  else
    {
      struct sockaddr_in* addr = (struct sockaddr_in*) &ifr->ifr_ifru.ifru_addr;
      addr->sin_len = sizeof(struct sockaddr_in);
      addr->sin_family = AF_INET;
      addr->sin_addr.s_addr = netif_ip4_netmask(netif)->addr;
      return 0;
    }

  return err;  
}

int SocketGetInterfaceHardwareAddress(void* ptr)
{
  int err = 0;
  struct ifreq* ifr = (struct ifreq*)ptr;
  struct netif *netif;
  short idx = 0;
  netif = get_if (ifr->ifr_name,&idx);
  if (!netif)
    err = ENODEV;
  else
    {
      struct sockaddr * addr = (struct sockaddr*) &ifr->ifr_ifru.ifru_hwaddr;
      memcpy (addr->sa_data, netif->hwaddr, netif->hwaddr_len);
      addr->sa_family = AF_INET;
      return 0;
    }

  return err; 
       
}

int SocketGetInterfaceidx(void* ptr)
{
  int err = 0;
  struct ifreq* ifr = (struct ifreq*)ptr;
  struct netif *netif;
  short idx = 0;
  netif = get_if (ifr->ifr_name,&idx);
  if (!netif)
    err = ENODEV;
  else
    {
      ifr->ifr_ifru.ifru_index = idx;
      return 0;
    }

  return err; 
       
}
